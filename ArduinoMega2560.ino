//--------------------------------------------------------------------|
//       PROGRAM ALAT SKRIPSI - SEMESTER 7 ( TAHUN 2021-2022)         |
//--------------------------------------------------------------------|
//NAMA    : WAHYU UMMY PUTRA                                          |
//NOBP    : 18101152620073                                            |
//JURUSAN : SISTEM KOMPUTER                                           |
//JUDUL   : "PERANCANGAN SISTEM PEMANTAUAN DAN PENGENDALIAN           |
//           PEMBIBITAN IKAN NILA MENGGUNAKAN APLIKASI TELEGRAM       |
//           BERBASIS INTERNET OF THINGS (IOT) DAN ARDUINO MEGA 2560" |
//DOSEN PEMBIMBING : 1. OKTA ANDRICA PUTRA, S.Kom, M.Kom              |
//                   2. HALIFIA HENDRI, S.Pd, M.Kom                   |
//--------------------------------------------------------------------|
//Sensor RTC
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;
//Sensor Salinitas
#define analogInPin  A2  // Analog input pin 2
//Sensor PH
#define SensorPinpH A1         // the pH meter Analog output is connected with the Arduino’s Analog
//Sensor Suhu DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2  // sensor diletakkan di pin 2
OneWire oneWire(ONE_WIRE_BUS); // setup sensor DS18B20
DallasTemperature sensor(&oneWire); // berikan nama variabel,masukkan ke pustaka Dallas
//LCD 20X4
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCD.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//Motor Servo
#include <Servo.h>
Servo MainServo;
//Pin Sensor Ultrasonic
int trig = 10;           // membuat varibel trig yang di set ke-pin 10
int echo = 9;           // membuat variabel echo yang di set ke-pin 9
long durasi, jarak;     // membuat variabel durasi dan jarak
//Pin LED (Merah,Hijau)
const int ledPinMerah = 13; // pH Air Tidak Sesuai pH Ikan Nila
const int ledPinHijau = 12; // pH Air Sesuai pH Ikan Nila
//Pin Buzzer
const int buzzer = 11;
//Variabel Sensor Suhu DS18B20
int suhuAir;
//variable Salinitas
int sensorValue; //adc value
float outputValueConductivity; //conductivity value
float outputValueTDS; //TDS value
//Pin Sensor Turbidity
int sensorPin = A0;
//Variabel Sensor pH
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10], temp;
//Serial Komunikasi Arduino to NodeMCU
String data = "";
char c;

void setup() {
    //PENGECEKKAN KONDISI RTC
  if (! rtc.begin()) {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
  }
  //Atur Waktu
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  //Tampilan LCD 20 X 4
  lcd.begin(20, 4);
  // JUDUL SKRIPSI
  lcd.setCursor(1, 0);
  lcd.print("PERANCANGAN SISTEM");
  lcd.setCursor(0, 1);
  lcd.print("PEMANTAUAN & KENDALI");
  lcd.setCursor(0, 2);
  lcd.print("PEMBIBITAN IKAN NILA");
  lcd.setCursor(0, 3);
  lcd.print("MENGGUNAKAN APLIKASI");
  delay(8000);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("TELEGRAM  BERBASIS");
  lcd.setCursor(1, 1);
  lcd.print("INTERNET OF THINGS");
  lcd.setCursor(2, 2);
  lcd.print("DAN ARDUINO MEGA");
  lcd.setCursor(8, 3);
  lcd.print("2560");
  delay(10000);
  lcd.clear();
  // NAMA MAHASISWA DAN NOBP
  lcd.setCursor(3, 0);
  lcd.print("NAMA MAHASISWA");
  lcd.setCursor(2, 1);
  lcd.print("WAHYU UMMY PUTRA");
  lcd.setCursor(3, 2);
  lcd.print("18101152620073");
  lcd.setCursor(2, 3);
  lcd.print("SISTEM  KOMPUTER");
  delay(8000);
  lcd.clear();
  // TAMPILAN DATA PANTAUAN ( Tinggi Air , Suhu Air , pH Air, Salinitas & Kualitas Air)
  lcd.setCursor(11, 1);
  lcd.print("Pakan:");
  lcd.setCursor(0, 2);
  lcd.print("T:");
  lcd.setCursor(4, 2);
  lcd.print("CM|");
  lcd.setCursor(7, 2);
  lcd.print("S:");
  lcd.setCursor(11, 2);
  lcd.print("C|");
  lcd.setCursor(13, 2);
  lcd.print("pH:");
  lcd.setCursor(0, 3);
  lcd.print("S:");
  lcd.setCursor(8, 3);
  lcd.print("PPM|");
  lcd.setCursor(12, 3);
  lcd.print("K:");
  
  //PIN MOTOR SERVO (8)
  MainServo.attach(8);
  //LED Merah dan Hijau
  pinMode(ledPinMerah, OUTPUT);
  pinMode(ledPinHijau, OUTPUT);
  //BUZZER
  pinMode(buzzer, OUTPUT);
  //Sensor Ultrasonic
  pinMode(trig, OUTPUT);    // set pin trig menjadi OUTPUT
  pinMode(echo, INPUT);     // set pin echo menjadi INPUT
  //Serial Begin
  Serial.begin(115200);   // digunakan untuk komunikasi Serial dengan komputer
}
void loop() {
  //RTC (HARI-WAKTU)
  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day();
  bulan   = now.month();
  tahun   = now.year();
  jam     = now.hour();
  menit   = now.minute();
  detik   = now.second();
  //TAMPILAN WAKTU DAN TANGGAL/HARI
  lcd.setCursor(2, 0);
  lcd.print(String() + hari + "," + tanggal + "-" + bulan + "-" + tahun);
  lcd.setCursor(0, 1);
  lcd.print(String() + jam + ":" + menit + ":" + detik + " |");
  //Kondisi Pemberian Pakan Ikan Nila
  if (jam == 8 & menit == 15 & detik ==30) {
    lcd.setCursor(17, 1);
    lcd.print("ON ");
    delay(5000);
    KasihPakanIkan(2);
    Serial.print("Pemberian pakan ikan nila telah selesai dilakukan.");
  }
  else if (jam == 15 & menit == 19 & detik == 0) {
    lcd.setCursor(17, 1);
    lcd.print("ON ");
    delay(5000);
    KasihPakanIkan(3);
    Serial.print("Pemberian pakan ikan nila telah selesai dilakukan.");
  }
  else {
    lcd.setCursor(17, 1);
    lcd.print("OFF");
  }
  
  //Sensor Salinitas
  sensorValue = analogRead(analogInPin);
  //Mathematical Conversion from ADC to conductivity (uSiemens)
  //rumus berdasarkan datasheet
  outputValueConductivity = (0.2142 * sensorValue) + 494.93;
  //Mathematical Conversion from ADC to TDS (ppm)
  //rumus berdasarkan datasheet
  outputValueTDS = (0.3417 * sensorValue) + 281.08;
  lcd.setCursor(2, 3);
  lcd.print(String() + outputValueTDS);
  delay(1000);
  
  //Sensor Turbidity
  int sensorValue = analogRead(sensorPin);
  int turbidity = map(sensorValue, 0, 615, 100, 0);
  delay(100);
  if (turbidity < 20) {
    lcd.setCursor(14, 3);
    lcd.print("BERSIH");
  }
  else if ((turbidity > 20 && turbidity < 50)) {
    lcd.setCursor(14, 3);
    lcd.print("KERUH ");
    
  }
  //Sensor pH
  for (int i = 0; i < 10; i++)  //Get 10 sample value from the sensor for smooth the value
  {
    buf[i] = analogRead(SensorPinpH);
    delay(10);
  }
  for (int i = 0; i < 9; i++)  //sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)               //take the average value of 6 center sample
    avgValue += buf[i];
  float phValue = (float)avgValue * 5.0 / 1024 / 6; //convert the analog into millivolt
  phValue = 3.5 * phValue; 
  lcd.setCursor(16, 2);
  lcd.print(phValue, 2);
  
  //Sensor Ds18b20
  sensor.setResolution(9);
  sensor.requestTemperatures();
  suhuAir = sensor.getTempCByIndex(0);
  lcd.setCursor(9, 2);
  lcd.print(suhuAir, 1);
  delay(1000);
  
  //Sensor Ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  digitalWrite(trig, HIGH);
  delayMicroseconds(8);
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  durasi = pulseIn(echo, HIGH); // menerima suara ultrasonic
  jarak = (durasi / 2) / 29.1;  // mengubah durasi menjadi jarak (cm)
  lcd.setCursor(2, 2);
  lcd.print(jarak);
  delay (1000);
  //Pembacaan data yang masuk dari NodeMCU
  while (Serial.available() > 0) {
    delay(10);
    c = Serial.read();
    data += c;
  }
  if (data.length() > 0) {
    Serial.println("Perintah Masuk : " + data );
    if ( data == "/CekKetinggianAir" ) {
      ultrasonic(); //Baca Data Sensor Ultrasonic
    }
    else if (data == "/CekSuhuAir") {
      suhuds18b20(); //Baca Data Sensor Suhu
    }
    else if (data == "/CekpHAir") {
     // phAir(); //Baca Data Sensor pH
      if (phValue >= 6.5 && phValue <= 8.5){
        digitalWrite(ledPinHijau, HIGH);
        digitalWrite(ledPinMerah, LOW);
        Serial.print("Data pemantauan keasaman air kolam ternak ikan nila sesuai dengan tingkat keasaman pada habitat ikan nila.");
      }
      else {
        digitalWrite(ledPinMerah, HIGH);
        digitalWrite(ledPinHijau, LOW);
        Serial.print("Data pemantauan keasaman air kolam ternak ikan nila tidak sesuai dengan tingkat keasaman pada habitat ikan nila.");
      }
    }
    else if (data == "/KontrolPakanIkan") {
      KasihPakanIkan(1); //Baca Data Motor Servo dan RTC
    }
    else if (data == "/CekKadarGaramAir") {
      Salinitas(); //Baca Data Sensor Salinitas
    }
    else if (data == "/CekKualitasAir") {
      //turbidity(); //Baca Data Sensor Turbidity
       if (turbidity < 20) {
        lcd.setCursor(14, 3);
        lcd.print("BERSIH");
        Serial.print("Data pemantauan kualitas air kolam ternak ikan nila  saat ini berada dalam kondisi air bersih.");
       }
       else if (turbidity >= 20) {
        lcd.setCursor(14, 3);
        lcd.print("KERUH ");
        Serial.print("Data pemantauan kualitas air kolam ternak ikan nila  saat ini berada dalam kondisi air keruh.");
        digitalWrite(buzzer, HIGH);
        delay(8000);
        digitalWrite(buzzer, LOW);
      }
   }
   data = ""; //Kosongkan Data Setelah selesai membaca. Agar tidak SPAM
  }
}
void ultrasonic() { //Sytanx Program untuk Sensor Ultrasonic
  if (jarak >= 5 && jarak <= 13) {
    Serial.print("Data pemantauan ketinggian air kolam ternak ikan nila pada saat ini berada di ketinggian: " + String(jarak) + " CM. Yaitu, berada di ketinggian air yang stabil");
  }
  else {
    Serial.print("Data pemantauan ketinggian air kolam ternak ikan nila pada saat ini berada di ketinggian: " + String(jarak) + " CM. Yaitu, berada di ketinggian air yang sangat rendah");
  }
}
void suhuds18b20() { //Sytanx Program untuk Sensor Suhu DS18B20
   if ((suhuAir >= 25 && suhuAir <= 32)) {
    Serial.print("Data Pantauan Suhu Air pada kolam ternak ikan nila saat ini berada di temperatur: " + String(suhuAir) + " °C. Suhu ini sesuai dengan suhu yang ada pada habitat ikan nila");
  }
  else if ((suhuAir < 25 && suhuAir > 32)) {
    Serial.print("Data Pantauan Suhu Air pada kolam ternak ikan nila saat ini berada di temperatur: " + String(suhuAir) + " °C. Suhu ini tidak sesuai dengan suhu yang ada pada habitat ikan nila");
  }
}
void KasihPakanIkan(int jumlah) { //Sytanx Program Pemberian Pakan Ikan
  for (int i = 1; i <= jumlah; i++) {
    MainServo.write(25);
    delay(500);
    MainServo.write(0);
    delay(500);
    Serial.print("Pemberian pakan ikan nila telah selesai dilakukan.");
    lcd.setCursor(17, 1);
    lcd.print("ON ");
    delay(5000);
    lcd.setCursor(17, 1);
    lcd.print ("OFF");
  }
}
void Salinitas() {
 Serial.print("Data pemantauan kadar garam air kolam ternak ikan nila pada saat ini berada di " + String(outputValueTDS) + " PPM.");
}
