// nama file harus dengan format urut 0001.mp3, dan berada didalam direktori mp3

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(D3, D2); // RX, TX

//
void setup () {
  Serial.begin (115200);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (15);
}


//
void loop () {
//  mp3_stop ();
  mp3_play(1);       
  delay (6000);


}
