/*  
                                 AFYU 2.0
                              Yuriy Afanasiev
                              
YouTube  https://youtube.com/c/YuriyAfanasiev
GitHub   https://github.com/yuri-afanasiev/
Telegram https://t.me/af_yu
VK       https://vk.com/public126750524 
  
Arduino IDE 1.8.10  https://www.arduino.cc/en/Main/Software          
Arduino core for ESP8266 Версия 2.7.4 https://github.com/esp8266/Arduino {GNU Lesser General Public License v2.1} https://github.com/esp8266/Arduino/blob/master/LICENSE
lwIP Variant v2 Higher Bandwidth
FS 160KB  OTA 422KB


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


 */
#include <ESP8266WiFi.h>                    //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi     
#include <WiFiClient.h>                     
#include <ESP8266WebServer.h>               //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <ESP8266mDNS.h>                    //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS
#include <FS.h>                             //FS 160KB  OTA 422KB http://arduino.esp8266.com/Arduino/versions/2.1.0/doc/filesystem.html
#include <ArduinoJson.h>                    //Версия 6.17.0 https://arduinojson.org  {MIT License} https://github.com/bblanchon/ArduinoJson/blob/6.x/LICENSE.md
#include <PubSubClient.h>                   //https://github.com/Imroy/pubsubclient  {MIT License} Copyright (c) 2008-2012 Nicholas O'Leary https://github.com/Imroy/pubsubclient/blob/master/LICENSE.txt
#include <ESP8266httpUpdate.h>              //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266httpUpdate
#include <ESP8266HTTPClient.h>              //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient    
#include <ESP8266HTTPUpdateServer.h>        //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPUpdateServer
#include <Wire.h>                   
#include <Ticker.h>                
#include <SPI.h>
#include <SoftwareSerial.h>
#include "CSE7766.h"                        //github.com/ingeniuske/CSE7766  Copyright (C) 2016-2018 by Xose Pérez Copyright (C) 2018 by Ingeniuske 
#include <lwip/napt.h>                      //lwIP Variant v2 Higher Bandwidth https://github.com/esp8266/Arduino/tree/master/tools/sdk/lwip2 / https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples/RangeExtender-NAPT


int mesh_on_off, mesh_hidden_ssid, mesh_max_connection; //Mesh
String mesh_name_ap_wifi , mesh_password_ap_wifi, mesh_name_sta_wifi, mesh_password_sta_wifi; //настройки mesh wifi
IPAddress subnet_ap(255, 255, 255, 0);
IPAddress ip_sta, ip_ap, ip_gateway, ip;

String w1, w2, w3, w4, w5, w6; //настройки wifi
int w7, w8; //настройки wifi

int wifi_ap_r;
int wifi_reconnect;

int mqw1, mqw3; //htm19
String mqw2, mqw4, mqw5, mqw6, mqw7; //htm19
String top1, top2, top3, top4; //адресное пространство MQTT
int mqtt_data_status;
String mqtt_code_bin, mqtt_fs_bin;

int on_off_thingspeak;
String api_key_thingspeak;
int interval_time_thingspeak = 15;

int relay_status;//Состояние relay 
int save_state;//Состояние сохранить

int on_off_narodmon;
int interval_time_narodmon;

int on_off_your_server;
int interval_time_your_server;
String host_your_server, port_your_server, url_your_server;


float rev_code = 2.2; //текущая версия кода
String device_name = "AFYU 2.0";
#define device_mqtt "sonoff-pow2"//Название устройства
#define pin_button 0  
#define pin_green_led 13      
#define pin_relay 12 

volatile long lastEventTime = 0;
volatile bool lastState = HIGH;

volatile bool isOn = false;
volatile bool isled = false;

bool button_status=1;
bool button_off;
bool led_status;
bool task_mqtt_button;


WiFiClient mqtttestclient;
PubSubClient mqttclient(mqtttestclient);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80);
WiFiClient client;
File fsUploadFile;

CSE7766 sensor_CSE7766;

Ticker thingspeak_ticker;
int thingspeak_ticker_test;
Ticker narodmon_ticker;
int narodmon_ticker_test;
Ticker your_server_ticker;
int your_server_test;
Ticker common_ticker;
bool common_ticker_status;
Ticker ap_ticker;

Ticker one_minute_ticker;
int one_minute_test;
volatile int one_minute;

void callback(const MQTT::Publish& pub) {
     String payload = pub.payload_string();
     //update
     if (String(pub.topic()) == top3 + "/update") { //уровень устройства
         DynamicJsonDocument json(2048);
         DeserializationError error = deserializeJson(json, payload);
         String code_bin = json["code"];//code
         String fs_bin = json["fs"];// fs
         mqtt_code_bin = code_bin;
         mqtt_fs_bin = fs_bin;
         mqttclient.publish(top3 + "/update/status", "{\"status\":\"1\"}");
         esp_update(mqtt_fs_bin, mqtt_code_bin);
        }
     //relay
     if (String(pub.topic()) == top3 + "/relay") { //уровень устройства
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];// 
         if (mqtt_data_status == 1){ 
             relay_status=1;
             if (save_state == 1){ 
                 save_27();
                 }
             digitalWrite(pin_relay, HIGH);  
             mqttclient.publish(top3 + "/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               mqttclient.publish(top3 + "/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt);
               digitalWrite(pin_relay, LOW);
               relay_status=0;
               if (save_state == 1){
                   save_27();
                   }
             }    
        } 
     if (String(pub.topic()) == top2 + "/relay") { //
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];// 
         if (mqtt_data_status == 1){ 
             relay_status=1;
             if (save_state == 1){ 
                 save_27();
                 }
             digitalWrite(pin_relay, HIGH);  
             mqttclient.publish(top3 + "/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               mqttclient.publish(top3 + "/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt);
               digitalWrite(pin_relay, LOW);
               relay_status=0;
               if (save_state == 1){ 
                   save_27();
                   }
             }    
        }
     if (String(pub.topic()) == top1 + "/relay") { //
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];// 
         if (mqtt_data_status == 1){
             relay_status=1; 
             if (save_state == 1){ 
                 save_27();
                 }
             digitalWrite(pin_relay, HIGH);  
             mqttclient.publish(top3 + "/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               mqttclient.publish(top3 + "/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt);
               digitalWrite(pin_relay, LOW);
               relay_status=0;
               if (save_state == 1){
                   save_27();
                   }
             }    
        }   
        
     //timer
     if (String(pub.topic()) == top3 + "/relay/timer") { //уровень устройства
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         int time_timer = json["time"];//Интервал  
         relay_timer(time_timer);
        }   
     if (String(pub.topic()) == top3 + "/relay/timer/off") { //уровень устройства
         interval_time_common_triggering();
        }  
        
     //led
     if (String(pub.topic()) == top3 + "/led") { //уровень устройства
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];// 
         if (mqtt_data_status == 1){ 
             digitalWrite(pin_green_led, LOW); 
             led_status=1;
             mqttclient.publish(top3 + "/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               led_status=0;
               mqttclient.publish(top3 + "/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
               digitalWrite(pin_green_led, HIGH); 
             }    
        }
     if (String(pub.topic()) == top2 + "/led") { //
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];// 
         if (mqtt_data_status == 1){ 
             digitalWrite(pin_green_led, LOW); 
             led_status=1;
             mqttclient.publish(top3 + "/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               led_status=0;
               mqttclient.publish(top3 + "/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
               digitalWrite(pin_green_led, HIGH); 
             }    
        }
     if (String(pub.topic()) == top1 + "/led") { //
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];// 
         if (mqtt_data_status == 1){ 
             digitalWrite(pin_green_led, LOW); 
             led_status=1;
             mqttclient.publish(top3 + "/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               led_status=0;
               mqttclient.publish(top3 + "/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
               digitalWrite(pin_green_led, HIGH); 
             }    
        }       




     //button
     if (String(pub.topic()) == top3 + "/button") { //уровень устройства
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];//
         if (mqtt_data_status == 1){ 
             button_off=0; 
             button_status=1;
             mqttclient.publish(top3 + "/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               mqttclient.publish(top3 + "/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
               button_off=1; 
               button_status=0;
             }    
        }
     if (String(pub.topic()) == top2 + "/button") { //
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];//
         if (mqtt_data_status == 1){ 
             button_off=0; 
             button_status=1;
             mqttclient.publish(top3 + "/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               mqttclient.publish(top3 + "/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
               button_off=1; 
               button_status=0;
             }    
        }
     if (String(pub.topic()) == top1 + "/button") { //
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         mqtt_data_status = json["status"];//
         if (mqtt_data_status == 1){ 
             button_off=0; 
             button_status=1;
             mqttclient.publish(top3 + "/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
             } else {
               mqttclient.publish(top3 + "/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
               button_off=1; 
               button_status=0;
             }    
        }        

     //save_state
     if (String(pub.topic()) == top3 + "/save_state") { //уровень устройства
         DynamicJsonDocument json(512);
         DeserializationError error = deserializeJson(json, payload);
         save_state = json["status"];// 
         save_20();//запись в память модуля
         mqttclient.publish(top3 + "/save_state/status","{\"status\":\"1\"}"); 
        }

        
     if (String(pub.topic()) == top3 + "/energy") {
         String output;
         DynamicJsonDocument  json(512);
         json["voltage"] = sensor_CSE7766.getVoltage();
         json["current"] = sensor_CSE7766.getCurrent();
         json["active_power"] = sensor_CSE7766.getActivePower();
         json["apparent_power"] = sensor_CSE7766.getApparentPower();
         json["reactive_power"] = sensor_CSE7766.getReactivePower();
         json["power_factor"] = sensor_CSE7766.getPowerFactor();
         json["energy"] = sensor_CSE7766.getEnergy()/ 1000000;
         serializeJson(json, output);
         mqttclient.publish(top3 + "/energy/status", output);
        }
         
                    
     //reset
     if (String(pub.topic()) == top3 + "/reset") { //
          mqttclient.publish(top3 + "/reset/status", "{\"status\":\"1\"}");
          ESP.restart();
        }
     if (String(pub.topic()) == top2 + "/reset") { //
         mqttclient.publish(top3 + "/reset/status", "{\"status\":\"1\"}");
         ESP.restart();
        }
     if (String(pub.topic()) == top1 + "/reset") { //
         mqttclient.publish(top3 + "/reset/status", "{\"status\":\"1\"}");
         ESP.restart();
        }
     //status
     if (String(pub.topic()) == top3 + "/status") {
         String output;
         DynamicJsonDocument  json(512);
         json["relay"] = relay_status;
         json["timer"] = common_ticker_status;
         json["led"] = led_status;
         json["button"] = button_status;
         json["rssi"] = WiFi.RSSI();
         serializeJson(json, output);
         mqttclient.publish(top3 + "/status/status", output);
        }

     //mesh
     if (String(pub.topic()) == top3 + "/mesh/set") {
         String output;
         DynamicJsonDocument  json(512);
         json["on_off"] = mesh_on_off;////Mesh on 1/ off 0
         json["apssid"] = w3;//APssid
         json["appassword"] = w4;//APpassword
         json["hidden_ssid"] = mesh_hidden_ssid;//скрывать SSID
         json["max_connection"] = mesh_max_connection;//максимально  количества одновременно подключенных станций 0-8
         save();//запись в память модуля
         mqttclient.publish(top3 + "/mesh/set/status", "{\"status\":\"1\"}");
        }
     if (String(pub.topic()) == top3 + "/mesh/get") { //
         String output;
         DynamicJsonDocument  json_web(2048);
         json_web["ssid"] = w1;//ssid
         json_web["password"] = w2;//password
         json_web["apssid"] = w3;//APssid
         json_web["appassword"] = w4;//APpassword
         json_web["www_username"] = w5;//www_username
         json_web["www_password"] = w6;//www_password
         json_web["connection_time"] = w7;//Время подключение
         json_web["time_reconnect"] = w8;//Время при reconnect
         json_web["on_off"] = mesh_on_off;//Mesh on 1/ off 0
         json_web["hidden_ssid"] = mesh_hidden_ssid;//скрывать SSID
         json_web["max_connection"] = mesh_max_connection;//максимально  количества одновременно подключенных станций 0-8
         json_web["localIP"] = toString (WiFi.localIP());
         json_web["subnetMask"] = toString (WiFi.subnetMask());
         json_web["gatewayIP"] = toString (WiFi.gatewayIP());
         json_web["macAddress"] = WiFi.macAddress();
         json_web["dnsIP"] = toString (WiFi.dnsIP());
         json_web["APnum"] = WiFi.softAPgetStationNum();//количество станций, которые подключены к интерфейсу soft-AP
         json_web["rssi"] = WiFi.RSSI();
         json_web["APmac"] = WiFi.softAPmacAddress();
         json_web["APip"] = toString (WiFi.softAPIP());
         serializeJson(json_web, output);
         mqttclient.publish(top3 + "/mesh/get/status", output);
        }
}
void ICACHE_RAM_ATTR button_testing() {
     long currentTime = millis();
     bool currentState = digitalRead(pin_button);
     
     if(currentTime - lastEventTime  > 50) {
        if(currentState == LOW && lastState == HIGH) {
           one_minute++;
          }
       }
     if(button_off == 0) {   
        if(currentTime - lastEventTime) {
           if(currentState == LOW && lastState == HIGH) {
              //isOn = !isOn;
              relay_status=!relay_status;
              task_mqtt_button=1;
              digitalWrite(pin_relay, relay_status);
              if(save_state == 1) { 
                 save_27();
                }
              }
           }
        }
       lastEventTime = currentTime;
       lastState = currentState;
       
}
void ICACHE_RAM_ATTR encoderISR(){//interrupt service routines need to be in ram
      attachInterrupt(pin_button,button_testing,CHANGE);
}
void setup(void) {
     //Serial.begin(9600);
     SPIFFS.begin();
     pinMode(pin_button, INPUT); // 0 
     pinMode(pin_green_led, OUTPUT);
     pinMode(pin_relay, OUTPUT);
     digitalWrite(pin_green_led, HIGH); 
     encoderISR();
     sensor_CSE7766.setRX(1);
     sensor_CSE7766.begin();
     openfile();//файл настроек
     testjson();
     open_file_htm20();
     openfilehtm19();//файл настроек  htm19 MQTT
     open_file_htm27();
     openfilehtm28();// sending_data
     if (save_state == 1){ 
         digitalWrite(pin_relay, relay_status);  
        }
     
     
     if (on_off_thingspeak == 1) {
         thingspeak_ticker.attach(interval_time_thingspeak, thingspeak_ticker_triggering);
        }
     if (on_off_narodmon == 1) {
         narodmon_ticker.attach(interval_time_narodmon, narodmon_ticker_triggering);
        }
     if (on_off_your_server == 1) {
         your_server_ticker.attach(interval_time_your_server, your_server_ticker_triggering);
        }
     one_minute_ticker.attach(60,one_minute_ticker_triggering);
     top3 += "/home/" + mqw7 + "/" + mqw6 + "/" + device_mqtt; //уровень устройства
     top2 += "/home/" + mqw7 + "/" + device_mqtt; //уровень комнаты
     top1 += "/home/";//уровень дома
     top1 += device_mqtt;//уровень дома

     Serial.println(top3);//уровень устройства
     Serial.println(top2);//уровень комнаты
     Serial.println(top1);//уровень дома
     wifi();//подключение к wifi
     Serial.println(WiFi.localIP());
     serveron();//запуск сервера порт 80
}
void loop(void) {
     server.handleClient();
     sensor_CSE7766.handle();
     wifi_connect_test();
     task_plan();
     if (mqw1 == 1) { //
         if (mqttclient.connected()) {
             mqttclient.loop();
            } else {
              mqtt_connect(mqw2, mqw3, mqw6, mqw4, mqw5);
            }  

         }
}
