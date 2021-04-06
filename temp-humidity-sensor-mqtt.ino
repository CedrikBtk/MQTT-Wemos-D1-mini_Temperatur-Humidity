#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MQTT_MAX_PACKET_SIZE 512
#include <OneWire.h>
#include <DallasTemperature.h>

//ONE WIRE PINS definieren
#define ONE_WIRE_BUS_1 4
//#define ONE_WIRE_BUS_2 5

OneWire oneWire_out(ONE_WIRE_BUS_1);
//OneWire oneWire_in(ONE_WIRE_BUS_2);
DallasTemperature sensor_outhouse(&oneWire_out);
//DallasTemperature sensor_inhouse(&oneWire_in);


const char* SSID = "<NETZWERK NAME>";
const char* PSK = "<WLAN PASSWORT>";
const char* MQTT_BROKER = "<MQTT_BROKER IP>";

//Variablen definieren
String temp_out_str;
//String temp_in_str;
String hum_one_str;
char temp_out[50];
//char temp_in[50];
char hum_one[50];
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(MQTT_BROKER, 1883);
    sensor_outhouse.begin();
    //sensor_inhouse.begin();
}
 
void setup_wifi() {
    WiFi.begin(SSID, PSK);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }
    
    Serial.println(WiFi.localIP());
}
void loop() {
    if (!client.connected()) {
        while (!client.connected()) {
            client.connect("ESP8266Client");
            delay(100);
        }
    }
    client.loop();

    sensor_outhouse.requestTemperatures();
    //sensor_inhouse.requestTemperatures();
    
    float humidity_one = analogRead(A0);
    float ftemp_out = sensor_outhouse.getTempCByIndex(0);
    //float ftemp_in = sensor_inhouse.getTempCByIndex(0);

    temp_out_str = String(ftemp_out);
    temp_out_str.toCharArray(temp_out, temp_out_str.length() + 1);
    //temp_in_str = String(ftemp_in);
    //temp_in_str.toCharArray(temp_in, temp_in_str.length() + 1);

    hum_one_str = String(humidity_one);
    hum_one_str.toCharArray(hum_one, hum_one_str.length() + 1);

    Serial.println(temp_out);
    Serial.println(temp_in);

    //Upload zum MQTT-Server
    client.publish("/home/cedrik-draussen/temp", temp_out);
    //client.publish("/home/cedrik-drinnen/temp", temp_in);
    client.publish("/home/cedrik-draussen/humidity_one", hum_one);
    delay(5000);

    //DeepSleep Zeit definieren (aktuell 300 Sekunden)
    ESP.deepSleep(300e6);
}
