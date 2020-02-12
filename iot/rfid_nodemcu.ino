#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <SPI.h>
#include <MFRC522.h>
 
#define SDA D4
#define RST D3

const int buzzer = D0;
const int hijau = D1;

MFRC522 mfrc522(SDA, RST);

// Replace with your network credentials
const char* ssid     = "xxx"; // ganti dengan ssid wifi mu
const char* password = "xxx"; // ganti dengan password wifi mu

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://absen.xxx.xxx.com/xxx"; // ganti dengan url yang ingin di tuju

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "xxxx"; // ganti api sesukamu


void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  pinMode(buzzer, OUTPUT);
  pinMode(hijau, OUTPUT);
  
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }

  digitalWrite(hijau, HIGH);

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // (you can also pass in a Wire library object like &Wire2)
}

void loop() {
//  String data = "oke";
  // buka rfid
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor

  Serial.print("UID tag :");
      String data= "";
      byte letter;
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
         data.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
         data.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      data.toUpperCase();
      Serial.println(data);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);

  // tutup rfid
  
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
          
    String httpRequestData = "api_key=" + apiKeyValue + "&data=" + data + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);
    
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

    // Send HTTP POST request
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(500);
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(500);
      
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      digitalWrite(hijau, HIGH);
      delay(100);
      digitalWrite(hijau, LOW);
      delay(100);
      digitalWrite(hijau, HIGH);
      delay(100);
      digitalWrite(hijau, LOW);
      delay(100);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
    digitalWrite(hijau, LOW);
  }
  //Send an HTTP POST request every 30 seconds
}
