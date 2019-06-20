#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

String  httpurl;
HTTPClient http;

int c = 0;
int b = 0;
int d = 0;
int v1 = 0;
int v2 = 0;

void setup()
{
  Serial.begin(9600);
  WiFi.disconnect();
   WiFi.begin("tripura","tripura53");
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.println(".");

  }
  Serial.println("Connected");

  pinMode(D5,INPUT);
  pinMode(D4,INPUT);
  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
  Serial.begin(9600);

}


void send_data(String data)
{

    httpurl = "http://";
    httpurl+="192.168.43.202";
    httpurl+="/";
    httpurl+=data;
    http.begin(httpurl);
    http.GET();
    http.end();

}


void loop()

{
  // put your main code here, to run repeatedly:
  int a = digitalRead(D5);
  int b = digitalRead(D4);
  int v1 = digitalRead(D1);
  int v2 = digitalRead(D0);
  if(a==1)
  {
    d=1;
    Serial.println("density is low");
  }
  else if(a==0 && c==0 && d==1 )
  {
    c=1;
  Serial.println("density reached 50%");
  }
  else if(a==0 && b == 0 && c==1 && d==1 )
  {
    c=0;
    d=0;
   Serial.println("density reached 100%");
  }
  if(v1==0)
  {
    if(a==0 && b==0)
    {
      Serial.println("speed 60KMPH");
    send_data(String ("Max Speed  60kmph"));
    }
    else if(a==0)
    {
      Serial.println("speed 75KMPH");
      send_data(String ("Max Speed  75kmph"));
    }
    else
    {
      Serial.println("speed 90KMPH");
      send_data(String ("Max Speed  90kmph"));
    }
  }
  if(v2==0)
  {
    if(a==0 && b==0)
    {
      Serial.println("max Speed 40kmph");
      send_data(String ("Max Speed  40kmph"));
    }
    else if(a==0)
    {
      Serial.println("speed 55KMPH");
      send_data(String ("Max Speed  55kmph"));
    }
    else
    {
      Serial.println("speed 70KMPH");
      send_data(String ("Max Speed  70kmph"));
    }
  }
  delay(1000);
}
