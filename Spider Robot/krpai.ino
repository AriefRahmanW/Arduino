#include <Servo.h>

Servo satu_k;
Servo satu_l;
Servo dua_k;
Servo dua_l;
Servo tiga_k;
Servo tiga_l;
Servo empat_k;
Servo empat_l;

byte mula_k = 0;
byte mula_l = 30;

byte beda_k = 180;
byte beda_l = 90;


void setup() {
  satu_k.attach(2);
  satu_l.attach(3);
  dua_k.attach(4);
  dua_l.attach(5);
  tiga_k.attach(6);
  tiga_l.attach(7);
  empat_k.attach(8);
  empat_l.attach(9);
  

  satu_k.write(90);
  satu_l.write(90);
  
  dua_k.write(90);
  dua_l.write(90);
  
  tiga_k.write(90);
  tiga_l.write(90);
  
  empat_k.write(90);
  empat_l.write(90);
  delay(2000);
  // 
  satu_k.write(mula_k);
  satu_l.write(mula_l);
  
  dua_k.write(mula_k + beda_k);
  dua_l.write(mula_l + beda_l);
  
  tiga_k.write(mula_k);
  tiga_l.write(mula_l);
  
  empat_k.write(mula_k + beda_k);
  empat_l.write(mula_l + beda_l);
  delay(2000);

}

void loop() {
  maju(50, 20, 10);
  
}

// kec = kecepatan
// l = cakupan lengan
// a = sudut angkat kaki
void maju(int kec, byte l, byte a){

  //hormat
  satu_k.write(mula_k + 40);
  tiga_k.write(mula_k + 40);
  delay(kec);
  satu_l.write(mula_l);
  tiga_l.write(mula_l + 30 + 10);
  delay(kec);
  dua_k.write(140 + a);
  empat_k.write(140 + a);
  satu_k.write(mula_k);
  tiga_k.write(mula_k);
  delay(kec);
  satu_l.write(mula_l + l);
  tiga_l.write(mula_l + l);
  delay(kec);

  // hormat kebalik
  dua_k.write(140);
  empat_k.write(140);
  delay(kec);
  dua_l.write(mula_k + beda_l);
  empat_l.write(mula_k + beda_l + 30 + 10);
  delay(kec);
  satu_k.write(mula_k + a);
  tiga_k.write(mula_k + a);
  dua_k.write(mula_k + beda_k);
  empat_k.write(mula_k + beda_k);
  delay(kec);
  dua_l.write(mula_k + beda_l + l);
  empat_l.write(mula_k + beda_l + l);
  delay(kec);
  
}

void geserKiri(int kec, byte l, byte a){
  satu_k.write(mula_k + 40);
  tiga_k.write(mula_k + 40);
  delay(kec);
  satu_l.write(mula_l);
  tiga_l.write(mula_l);
}
