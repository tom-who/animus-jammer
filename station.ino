#include "WiFi.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const int buttonPin = 2;
const short minPin = 3;
const short maxPin = 12;
short int buttonState = 0;
const int MODES[2] = {LOW, HIGH};

void setup() {
  for(int i = minPin; i <= maxPin; i++){
    pinMode(i, OUTPUT);
  }
  ledBar("off", 0);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);


  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  pinMode(buttonPin, INPUT);

  delay(100);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    wifiSetup();
    delay(500);
    ledBar("off", 0);
  }
  while(WiFi.status() == WL_CONNECTED){
    wifiStrength();
    buttonState = digitalRead(buttonPin);
    if(buttonState == HIGH){
      ledBar("off", 0);
      lcd.clear();
      WiFi.disconnect();
      break;
    }
  }
}

void ledBar(String type, short var) {
  if (type == "on"){
    for (int i = minPin; i <= maxPin; i++) {
      digitalWrite(i, HIGH);
      delay(500);
    }
  }
  else if(type == "off"){
    for (int i = minPin; i <= maxPin; i++) {
      digitalWrite(i, LOW);
    }
  }
  else if(type == "blink"){
    for (int i = 0; i < 4; i++) {
      for (int m = 0; m < 2; m++) {
        for (int j = minPin; j <= maxPin; j++) {
          digitalWrite(j, MODES[m]);
        }
        delay(300);
      }
    }
  }
  if(var != 0){
    var = var + 2;
    for (int i = minPin; i <= var; i++) {
      digitalWrite(i, HIGH);
    }
  }
  
}

void wifiStrength(){
  ledBar("off", 0);
  short signalStrength = WiFi.RSSI();
  if(signalStrength >= -50){
    ledBar("foo", 10);
  }
  else if(signalStrength >= -60 && signalStrength < -50){
    ledBar("foo", 8);
  }
  else if(signalStrength >= -70 && signalStrength < -60){
    ledBar("foo", 6);
  }  
  else if(signalStrength >= -80 && signalStrength < -70){
    ledBar("foo", 4);
  }
    else if(signalStrength >= -90 && signalStrength < -80){
    ledBar("foo", 2);
  }
    else if(signalStrength <= -90){
    ledBar("foo", 0);
  }
  delay(300);
}

void wifiSetup(){
  lcd.print("Scanning...");
  short n = WiFi.scanNetworks();
  delay(1700);
  lcd.clear();
  for (int i = 0; i < n; i++){
    Serial.print("[");
    Serial.print(i + 1);
    Serial.print("]" );
    Serial.println(WiFi.SSID(i));
  }

  lcd.print("Select AP");
  while (Serial.available() == 0){}
  short ssidNum = (Serial.readStringUntil('\n').toInt() - 1);
  Serial.println(ssidNum + 1);
  lcd.clear();
  lcd.print("Selected:");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.SSID(ssidNum));

  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter pass:");
  while (Serial.available() == 0){}
  String wifiPass = Serial.readStringUntil('\n');
  Serial.println(wifiPass);

  lcd.clear();
  lcd.print("Connecting...");
  WiFi.begin(WiFi.SSID(ssidNum), wifiPass);
  while(WiFi.status() != WL_CONNECTED){}

  ledBar("on", 0);
  ledBar("blink", 0);

  lcd.clear();
  lcd.print("Connected !");
  delay(1000);
  lcd.clear();
  lcd.print(WiFi.SSID(ssidNum));
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
}