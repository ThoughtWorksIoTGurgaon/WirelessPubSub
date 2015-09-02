/*
 MQTT subscriber example

  - connects to an MQTT server
  - subscribes to the topic "inTopic"
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid =  "XT1033";   // cannot be longer than 32 characters!
const char *pass =  "12345678";   //

// Update these with values suitable for your network.
IPAddress server(192, 168, 43, 11);

#define BUFFER_SIZE 100

const int LED = BUILTIN_LED;
const bool ON = 0;
const bool OFF = 1;

void callback(const MQTT::Publish& pub) {
//  Serial.print(pub.topic());
//  Serial.print(" => ");
//  if (pub.has_stream()) {
//    Serial.println("a stream");
//    uint8_t buf[BUFFER_SIZE];
//    int read;
//    while (read = pub.payload_stream()->read(buf, BUFFER_SIZE)) {
//      Serial.write(buf, read);
//    }
//    pub.payload_stream()->stop();
//    Serial.println("");
//  } else
    if (pub.payload_string() == "ON"){
      digitalWrite(LED, ON);
    } else {
      digitalWrite(LED, OFF);
    }
//    Serial.println(pub.payload_string());
}

WiFiClient wclient;
PubSubClient client(wclient, server);

void setup() {
  // Setup console
//  Serial.begin(115200);
  delay(10);
//  Serial.println();
//  Serial.println();

// prepare LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, ON);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
//    Serial.print("Connecting to ");
//    Serial.print(ssid);
//    Serial.println("...");
    WiFi.begin(ssid, pass);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
//    Serial.println("WiFi connected");
  }

  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      if (client.connect("arduinoClient")) {
	      client.set_callback(callback);
	      client.subscribe("inTopic");
      }
    }

    if (client.connected())
      client.loop();
  }
}
