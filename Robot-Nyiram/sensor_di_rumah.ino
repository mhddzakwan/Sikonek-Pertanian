// Library WiFi ESP32
#include <WiFi.h>
// Library HTTPClient untuk HTTP request
#include <HTTPClient.h>
#include "DHT.h"
#define DHTPIN 5    

// WiFi SSID dan Password
#define WIFI_SSID "KelilingDunia1"
#define WIFI_PASSWORD "12julham12"

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
const int ledPin = 2;

void setup() {
  Serial.begin(9600);
  //Koneksikan ssid dan password
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  // Loading Menunggu wifi terkoneksi
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  dht.begin();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.println("Humidity: " + String(h) + "%");
  Serial.println("Temperature: " + String(t) + "°C ");

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

}