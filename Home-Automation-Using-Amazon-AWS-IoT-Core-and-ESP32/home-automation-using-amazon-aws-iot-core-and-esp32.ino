#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
 
#define AWS_IOT_SUBSCRIBE_TOPIC1 "esp32/light1" 
 
#define light1 19 
 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
 
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
/*##################### Light 1 #####################*/
  if ( strstr(topic, "esp32/light1") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay1 = doc["status"];
    int r1 = Relay1.toInt();
    if(r1==1)
    {
      digitalWrite(light1, HIGH);
      Serial.print("Light 1 is ON");
    }
    else if(r1==0)
    {
      digitalWrite(light1, LOW);
      Serial.print("Light 1 is OFF");
    }
  }
  
  Serial.println();
}
 
 
void setup()
{
  Serial.begin(115200);
  
  pinMode (light1, OUTPUT); 
 
  digitalWrite(light1, HIGH); 
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC1); 
 
  Serial.println("AWS IoT Connected!");
}
 
 
void loop()
{
  client.loop();
  delay(1000);
}
