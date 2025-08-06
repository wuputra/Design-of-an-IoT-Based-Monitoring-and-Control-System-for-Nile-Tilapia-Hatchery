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
#include "CTBot.h"
CTBot myBot;
String ssid = "Redmi Note 8";     //ID HOSTPOT HANDPHONE
String pass = "XCH456RA"; //PASSWORD HOSTPOT HANDPHONE
String token = "5208157224:AAGYgOWxfUkriS9WS49S8GopFbqR8zF9RIU";   // TOKEN BOT TELEGRAM
const int id = 1111830152;
String data = "";
String arrayData[6];
char c;
void setup() {
  // initialize the Serial
  Serial.begin(115200);

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("Koneksi Berhasil");
  else
    Serial.println("Koneksi Gagal");

}

void loop() {
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("/CekKetinggianAir")) {
      Serial.print("/CekKetinggianAir");
    }
    else if (msg.text.equalsIgnoreCase("/CekSuhuAir")) {
      Serial.print("/CekSuhuAir");
    }
    else if (msg.text.equalsIgnoreCase("/CekpHAir")) {
      Serial.print("/CekpHAir");
    }
    else if (msg.text.equalsIgnoreCase("/CekKualitasAir")) {
      Serial.print("/CekKualitasAir");
    }
    else if (msg.text.equalsIgnoreCase("/CekKadarGaramAir")) {
      Serial.print("/CekKadarGaramAir");
    }
    else if (msg.text.equalsIgnoreCase("/KontrolPakanIkan")) {
      Serial.print("/KontrolPakanIkan");
    }
    else if (msg.text.equalsIgnoreCase("/start")) {
      String mulai;
      mulai = (String)"Assalamu'alaikum Wr.Wb \n" +
              (String)"Selamat Datang " + msg.sender.username + (String)" di Pemantauan dan Pengendalian Pembibitan Ikan Nila Berbasis IoT. Silahkan klik /disini untuk melihat dan melakukan perintah yang diinginkan.";
      myBot.sendMessage(msg.sender.id, mulai); // Notifikasi Start Telegram
    }
    else if (msg.text.equalsIgnoreCase("/disini")) {
      String cekperintah;
      cekperintah = (String)"Dibawah ini merupakan data-data perintah yang akan digunakan untuk pemantauan dan pengendalian pembibitan ikan nila menggunakan aplikasi telegram: \n" +
                    (String)"/CekKetinggianAir : Melakukan pemantauan kondisi dari ketinggian air di kolam ternak ikan nila. \n" +
                    (String)"/CekSuhuAir : Untuk memantau kondisi dari temperatur air di kolam ternak ikan nila. \n" +
                    (String)"/CekpHAir : Untuk melakukan pemantauan kondisi keasaman air berdasarkan tingkat pH air di kolam ternak ikan nila. \n" +
                    (String)"/CekKualitasAir : Untuk memantau kondisi kejernihan/kekeruhan air di kolam ternak ikan nila. \n" +
                    (String)"/CekKadarGaramAir : Untuk melakukan pemantauan kondisi kadar garam air di kolam ternak ikan nila. \n" +
                    (String)"/KontrolPakanIkan : Untuk melakukan pengendalian pemberian pakan ikan di kolam ternak ikan nila.";
      myBot.sendMessage(msg.sender.id, cekperintah);
    }
    else {
      //JIKA PERINTAH SALAH
      String salahperintah;
      salahperintah = (String)"Perintah yang diinputkan tidak benar. Silahkan klik /disini untuk melihat perintahnya kembali.";
      myBot.sendMessage(msg.sender.id, salahperintah);
    }
  }
  //DATA PARSING
  while (Serial.available() > 0) {
    delay(10);
    c = Serial.read();
    data +=  c;
  }
  data.trim();
  //if (data.length() > 0) {
  if (data != "") {
    int index = 0;
    for (int i = 0; i < data.length(); i++) {
      char delimiter = '.';
      if (data[i] != delimiter)
        arrayData[index] += data[i];
      else
        index++;
    }
    if (index == 5) {
      myBot.sendMessage(msg.sender.id, arrayData[0] + "\n" + arrayData[1] +  "\n" + arrayData[2] +  "\n" + arrayData[3] + "\n" + arrayData[4] +  "\n" + arrayData[5]);
      arrayData[0] = "";
      arrayData[1] = "";
      arrayData[2] = "";
      arrayData[3] = "";
      arrayData[4] = "";
      arrayData[5] = "";
      data = "";
    }
    else {
      myBot.sendMessage(msg.sender.id, data);
      data = "";
    }
  }
}
