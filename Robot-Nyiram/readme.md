# Robot-nyiram.ino
File tersebut merupakan kode untuk menjalankan robot penyiram, silahkan otak - atik di sktip void loop():
gunakan function untuk menggerakkan roda misalnya lurus(), kiri() dll.
Pengaturan kecepatan ada di skrip ini:
```
#define MAX_MOTOR_SPEED 200

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

```

# sensor_di-rumah.ino
File ini adalah skrip untuk esp yang ada di rumah, yg terhubung dengan sensor DHT22 (di skrip masik pakai dht11), dan motor servo.
silahkan konfigurasi. untuk melakukan pengkondisian pada cek suhu dht, konfigtuasi bagian if pada variabel t nya
'''
if(t > 35.00){
    WiFiClient client;
    HTTPClient http;

    //ALamat server
    String address = "http://ummuhafidzah.sch.id/kehadiran/send.php?suhu=2"; //Alamat, tempat notif dibuat
    Serial.println("------------------KIRIM DATA------------------");
    // Mulai koneksi HTTP
    http.begin(client,address);  
    // Kirim request GET
    int httpCode = http.GET(); 
    digitalWrite(ledPin, LOW);
  }else if (t < 35.00 && t > 25.00){
    WiFiClient client;
    HTTPClient http;
    //ALamat server
    String address = "http://ummuhafidzah.sch.id/kehadiran/send.php?suhu=1"; //Alamat, tempat notif dibuat
    Serial.println("------------------KIRIM DATA------------------");
    // Mulai koneksi HTTP
    http.begin(client,address);  
    // Kirim request GET
    int httpCode = http.GET(); 
    digitalWrite(ledPin, LOW);
  }else{
    digitalWrite(ledPin, HIGH);
  }
  
'''
