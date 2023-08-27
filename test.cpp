#define BLYNK_TEMPLATE_ID "TMPL3_7xXHTb5"
#define BLYNK_TEMPLATE_NAME "Aquawatch"
#define BLYNK_TEMPLATE_AUTH "WPg5Ue3V92IEaCSXMXcfTTw4f-claEpj"
#define BLYNK_PRINT Serial

// #include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// #include <BlynkSimpleEsp8266.h>
// #include<WiFi.h>

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

#define DHT11_PIN D4

char ssid[] = "Somani_5G";
char password[] ="9893255266";
char auth[] = "WPg5Ue3V92IEaCSXMXcfTTw4f-claEpj";

int LDRSensor = D7;
int LEDB = D5;
int Buzzer = D0;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

void setup() {
  // WiFi.begin(ssid,password);  
  // Blynk.begin(auth,ssid,password);

  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("  Machine   Active   ");
  display.display();

  delay(4000);

  display.clearDisplay();

  pinMode(A0,INPUT);
  pinMode(D5,OUTPUT);
  pinMode(D0,OUTPUT);
  
}

void loop() {


  int s1=analogRead(A0);
  Serial.println(s1);

  DHT.read(DHT11_PIN);
  
  int LDR_Vp=digitalRead(LDRSensor);
  Serial.println(LDR_Vp);

  if(LDR_Vp==0){
    if (DHT.temperature<=27){
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,40);
    display.println("Temperature too low,increase");
    display.display();
    delay(1000);
    digitalWrite(Buzzer,HIGH);
    digitalWrite(LEDB,HIGH);
    delay(3000);
    digitalWrite(Buzzer,LOW);
    digitalWrite(LEDB,LOW);
  }
  else if(DHT.temperature>=35){
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,40);
    display.println("Temperature too high,reduce it ");
    display.display();
    delay(1000);
    digitalWrite(Buzzer,HIGH);
    digitalWrite(LEDB,HIGH);
    delay(3000);
    digitalWrite(Buzzer,LOW);
    digitalWrite(LEDB,LOW);
  }
  if(s1<=100){  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,2);
    display.println("Water Level is critically low");
    display.setCursor(0,20);
    display.println("Add water immediately");
    display.display();

    digitalWrite(Buzzer,HIGH);
    digitalWrite(LEDB,HIGH);
    delay(3000);
    digitalWrite(Buzzer,LOW);
    digitalWrite(LEDB,LOW);
    
  }
  else if(s1>=100 and s1<=200) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,2);
    display.println("Need More Water");
    display.display();
  }
  else{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,2);
    display.println("System healthy");
    display.display();
  }
  }
  else{
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0,14);
  display.println(DHT.temperature);
  display.setTextSize(3);
  display.setCursor(40,14);
  display.println(DHT.humidity);
  display.display();
  }

  // Blynk.virtualWrite(V0,DHT.humidity);
  // Blynk.virtualWrite(V1,DHT.temperature);
  // Blynk.virtualWrite(V2,LDRSensor);
  // Blynk.virtualWrite(V3,LEDB);
  // Blynk.virtualWrite(V4,A0);
  // Blynk.virtualWrite(V5,Buzzer);
  // Blynk.run();
}
