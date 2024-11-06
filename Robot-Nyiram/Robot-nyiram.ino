// Library WiFi ESP32
#include <WiFi.h>
// Library HTTPClient untuk HTTP request
#include <HTTPClient.h>
// Library ArduinoJson untuk parsing JSON
#include <ArduinoJson.h>

// WiFi SSID dan Password
#define WIFI_SSID "KelilingDunia1"
#define WIFI_PASSWORD "12julham12"

// URL endpoint server untuk mendapatkan data dengan id = 1
String serverURL = "http://ummuhafidzah.sch.id/kehadiran/get.php";


//PWM Pin for Controlling the speed
// int enA = 5;
// int enB = 23;
// int IN1 = 22;
// int IN2 = 21;
// int IN3 = 19;
// int IN4 = 18;
//Right motor
int enableRightMotor=23; 
int rightMotorPin1=18;
int rightMotorPin2=19;
//Left motor
int enableLeftMotor=5;
int leftMotorPin1=22;
int leftMotorPin2=21;
const int relay = 26;
String data_val = "1";
String nyala = "1";
int rightMotorSpeed=0;
int leftMotorSpeed=0;
#define MAX_MOTOR_SPEED 200

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }
  
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  
  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed));
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));  
}

void setUpPinModes()
{
  pinMode(enableRightMotor,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);
  
  pinMode(enableLeftMotor,OUTPUT);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);

  //Set up PWM for speed
  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);  
  ledcAttachPin(enableRightMotor, rightMotorPWMSpeedChannel);
  ledcAttachPin(enableLeftMotor, leftMotorPWMSpeedChannel); 

  rotateMotor(0,0); 
}

void setup()
{
  Serial.begin(9600);
  setUpPinModes();
  Serial.println("Bluetooth initialized");
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Dabble.processInput();
  // if (GamePad.isUpPressed())
  // {
  //   rightMotorSpeed = MAX_MOTOR_SPEED;
  //   leftMotorSpeed = MAX_MOTOR_SPEED;
  //   Serial.println("atas");
  // }

  // if (GamePad.isDownPressed())
  // {
  //   rightMotorSpeed = -MAX_MOTOR_SPEED;
  //   leftMotorSpeed = -MAX_MOTOR_SPEED;
  //   Serial.println("bawah");
  // }

  // if (GamePad.isLeftPressed())
  // {
  //   rightMotorSpeed = MAX_MOTOR_SPEED;
  //   leftMotorSpeed = -MAX_MOTOR_SPEED;
  //   Serial.println("kiri");
  // }

  // if (GamePad.isRightPressed())
  // {
  //   rightMotorSpeed = -MAX_MOTOR_SPEED;
  //   leftMotorSpeed = MAX_MOTOR_SPEED;
  //   Serial.println("kanan");
  // }
  getData();
  if (nyala == "1") {
    lurus();
  } else {
    stop(); // Stop both motors if nyala is 0
  }
  delay(2000);

  getData();
  if (nyala == "1") {
    kiri();
  } else {
    stop(); // Stop both motors if nyala is 0
  }
  delay(2000);
  
}

void getData(){
  do{
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      // Mulai koneksi ke URL server
      http.begin(client, serverURL);

      // Kirim permintaan GET
      int httpResponseCode = http.GET();
      
      if (httpResponseCode > 0) {
        // Jika respons berhasil, baca isi respons
        String payload = http.getString();
        Serial.println("Data received:");
        Serial.println(payload);

        // Membuat buffer untuk parsing JSON
        StaticJsonDocument<200> doc;

        // Parse JSON dari payload
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
          Serial.print("Failed to parse JSON: ");
          Serial.println(error.c_str());
          return;
        }

        // Mengakses data JSON yang diterima
        int id = doc["id"];                  // Misalnya, akses data id
        String data_val2 = doc["data_val"];    // Misalnya, akses data data_val
        String data_nyala = doc["nyala"];
        data_val = data_val2;
        nyala = data_nyala;
        
        // Tampilkan hasil parsing JSON di Serial Monitor
        Serial.print("ID: ");
        Serial.println(id);
        Serial.print("Data Value: ");
        Serial.println(data_val);
        
        // Jika data_nyala == "0", lanjutkan looping
        if(data_nyala == "0"){
          http.end(); // Tutup koneksi HTTP sebelum melanjutkan loop
          delay(1000); // Tambahkan delay agar tidak terlalu cepat mengirim permintaan GET
          continue;
        }

      } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpResponseCode);
      }

      // Tutup koneksi HTTP
      http.end();
    } else {
      Serial.println("Wi-Fi not connected!");
    }

    // Tindakan ketika data_val bukan "2"
    if(data_val != "2"){
      stop();
      digitalWrite(relay, HIGH);
      delay(1000);
    }

  } while(data_val != "2");
  digitalWrite(relay, LOW); // Jika ingin mematikan relay di akhir loop
}


void lurus(){
  rotateMotor(MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
}

void kiri(){
  rotateMotor(0, MAX_MOTOR_SPEED);
}

void stop(){
  rotateMotor(0, 0);
}