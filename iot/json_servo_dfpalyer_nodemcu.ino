#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Servo.h>

#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(D3, D2); // RX, 

Servo servo;
int mulai = 10;
int akhir = 105;

const int hijau = D1;

// Replace with your network credentials
const char* ssid     = "kebaratan"; // ganti dengan ssid mu
const char* password = "Wifilemot"; // ganti dengan passwodmu

String myKey = "2";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://gaskenjogja.000webhostapp.com/xxxx"; // ganti dengan url yang mau dituju
const char* serverApi = "http://gaskenjogja.000webhostapp.com/xxxx";  // ganti dengan url yang mau dituju

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  pinMode(hijau, OUTPUT);
  servo.attach(D4);
  servo.write(mulai);
  
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  //initial json data
  digitalWrite(hijau, HIGH);
// mp3
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (15);  

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // (you can also pass in a Wire library object like &Wire2)
}

void loop() {
  
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    HTTPClient api;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    api.begin(serverApi);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/json");
    api.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP GET receive data

    int httpCode = http.GET();
    if(http.getString() != ""){ 
         
      Serial.println(http.getString());
      int apiCode = api.POST("id_wisata=" + myKey);
      if(apiCode > 0){
        DynamicJsonDocument doc(70);
        DeserializationError error = deserializeJson(doc, http.getString());
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.c_str());
          return;
        }
        String message = doc["message"];
        String key = doc["data"];
        Serial.println(message + ", " + key );
          if(key == myKey && message == "sukses"){

              for(int i = mulai; i <= akhir; i++){
                servo.write(i);
                delay(20);
              }
              mp3_play (1);
              delay(3000);
              
              for(int i = akhir; i >= mulai; i--){
                servo.write(i);
                delay(20);
              }
          }
          else{
            Serial.println("parameter salah");
          }

      }
      else{
        Serial.println("tidak");
      }
    }


    // Send HTTP POST request
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpCode>0) {
        
      }else {
        Serial.print("Error code http: ");
        Serial.println(httpCode);
        
      }
      http.end();
      api.end();
      
    }else {
      Serial.println("WiFi Disconnected");
      digitalWrite(hijau, LOW);
    }

  //Send an HTTP POST request every 30 seconds
}
