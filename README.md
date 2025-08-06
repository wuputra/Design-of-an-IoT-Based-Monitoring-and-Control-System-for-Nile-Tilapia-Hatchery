
# Sistem Pemantauan dan Pengendalian Pembibitan Ikan Nila Berbasis IoT dan Arduino Mega 2560

Proyek ini merupakan **perancangan dan pembangunan sistem Internet of Things (IoT)** untuk **memantau dan mengendalikan proses pembibitan ikan nila (Oreochromis niloticus)**. Sistem ini mengintegrasikan berbagai sensor dan aktuator untuk otomatisasi pengendalian lingkungan serta memberikan pembaruan data secara **real-time** melalui integrasi **BOT Telegram**.

## 🔧 Komponen Perangkat Keras

- **Arduino Mega 2560** – Mikrokontroler utama  
- **ESP8266** – Modul Wi-Fi untuk konektivitas internet  
- **Sensor pH** – Mengukur tingkat keasaman air  
- **Sensor Kekeruhan (Turbidity)** – Mendeteksi kejernihan air  
- **Sensor Ultrasonik** – Mengukur ketinggian permukaan air  
- **Sensor DS18B20** – Mengukur suhu air  
- **Sensor Salinitas** – Mengukur kadar garam pada air  
- **Buzzer** – Alarm jika terjadi kondisi abnormal  
- **LED** – Indikator status sistem  
- **Motor Servo** – Menggerakkan mekanisme (misalnya katup atau alat pemberi pakan)  
- **LCD 20x4** – Menampilkan data lokal di tempat  

## 🌐 Fitur Sistem

- Pemantauan parameter air secara **real-time**  
- Pengendalian perangkat (servo, buzzer, LED) secara otomatis  
- **Notifikasi otomatis** melalui **BOT Telegram**  
- Tampilan data langsung di LCD  
- Akses jarak jauh melalui jaringan internet (ESP8266)  
- Membantu otomatisasi dalam proses pembibitan ikan nila  

## 📲 Integrasi BOT Telegram

Sistem ini terhubung dengan **BOT Telegram** untuk mengirimkan informasi ketika:  

- Parameter air (pH, suhu, kekeruhan, dll.) berada di luar batas aman  
- Perangkat pengendali diaktifkan (alarm, servo, dll.)  
- Pengguna meminta data status terbaru  

## 🔌 Arsitektur Jaringan

Sistem terhubung ke internet melalui **ESP8266** dan mengirim data ke API BOT Telegram. Semua pembacaan sensor dilakukan oleh **Arduino Mega 2560**, kemudian data dikirimkan ke Telegram melalui permintaan HTTP.

```
[Sensor] → Arduino Mega 2560 → ESP8266 → BOT Telegram → Pengguna
```

## 📊 Contoh Data (LCD & Telegram)

- Suhu Air: 28.5°C  
- pH: 6.9  
- Kekeruhan: 80 NTU  
- Ketinggian Air: 13 cm  
- Salinitas: 0.4 ppt  
- Status: ✅ Normal  

## 🚀 Pengembangan Selanjutnya (Opsional)

- Penyimpanan data di cloud untuk analisis jangka panjang  
- Dashboard berbasis web atau mobile  
- Kontrol penuh melalui perintah di BOT Telegram  
- Prediksi otomatis menggunakan machine learning
  
## 🎥 Referensi & Dokumentasi Video

 **Demo Alat**: [Klik di sini untuk menonton](https://drive.google.com/file/d/1BWs9cAS0MUr0V3pRrCKHXJSMx9GZajtf/view?usp=sharing)  

## 🛠️ Instalasi & Konfigurasi

> Panduan wiring, kode, dan cara konfigurasi dapat dilihat di folder `/docs` atau `/src` (akan ditambahkan kemudian).  
