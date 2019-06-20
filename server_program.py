#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

WiFiServer server(80);
WiFiClient client;

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET    -1

String read_data;
String req_data;
String prsnt_data = "";
int l;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 


void setup()
{
  Serial.begin(9600);
  WiFi.disconnect();
   WiFi.begin("tripura","tripura53");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.println(".");
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  display.setTextSize(2);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,0);               
  display.print("Safe");
  display.setCursor(20,16);               
  display.print("Journey");
  display.display();
  delay(5000);
  Serial.println("Connected");
  Serial.println((WiFi.localIP().toString()));
  server.begin();
}


void loop()
{

    WiFiClient client = server.available();
    if (!client) 
    { 
      return; 
    }
    /*while(!client.available())
    {  
      delay(1); 
    }*/
    read_data = client.readStringUntil('\r');
    l = read_data.length();
    req_data = read_data.substring(5,l-9);
    if (prsnt_data != req_data)
    {
      prsnt_data = req_data;
      Serial.println(req_data);
      display.clearDisplay();
      display.setTextSize(2);                    
      display.setTextColor(WHITE);             
      display.setCursor(0,0);               
      display.print(req_data);
      display.display();
    }

}
