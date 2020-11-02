/*  
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/ 

#include <ESP8266WiFi.h>            //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
#include <WiFiClient.h>
#include <ESP8266WebServer.h>       //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <ESP8266mDNS.h>            //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS
#include <FS.h>                     //http://esp8266.github.io/Arduino/versions/2.1.0/doc/filesystem.html  
#include <ArduinoJson.h>            //https://bblanchon.github.io/ArduinoJson/
#include <PubSubClient.h>           //https://github.com/Imroy/pubsubclient
#include <ESP8266httpUpdate.h>      //https://github.com/Links2004/Arduino/tree/esp8266/hardware/esp8266com/esp8266/libraries/ESP8266httpUpdate        
#include <ESP8266HTTPClient.h>      //https://github.com/Links2004/Arduino/tree/libraries/ESP8266HTTPClient 
#include <ESP8266HTTPUpdateServer.h>//https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPUpdateServer 
#include <Wire.h>                   //https://github.com/esp8266/Arduino/tree/master/libraries/Wire 
#include <Ticker.h>                 //https://github.com/esp8266/Arduino/tree/master/libraries/Ticker 
#include <SPI.h>                    //http://www.arduino.cc/en/Reference/SPI
#include <SoftwareSerial.h>
#include "CSE7766.h"                //github.com/ingeniuske/CSE7766  Copyright (C) 2016-2018 by Xose Pérez Copyright (C) 2018 by Ingeniuske 

CSE7766 sensor_CSE7766;
 
#define button 16


 

String w1,w2,w3,w4,w5,w6; //настройки wifi
int w7,w8;//настройки wifi

int var=1;//wifi 
int wifire;
int reconnect;
 
bool button_off;
bool task_mqtt_button;

#define pin_button 0  
#define pin_green_led 13      
#define pin_relay 12 

int relay_status;
bool led_status;
bool button_status=1;


volatile long lastEventTime = 0;
volatile bool lastState = HIGH;
   
volatile bool isOn = false;
volatile bool isled = false; 

int on_off_thingspeak;
String api_key_thingspeak;
int interval_time_thingspeak=15;

bool on_off_narodmon;
int interval_time_narodmon;  

bool on_off_your_server;
int interval_time_your_server;
String host_your_server,port_your_server,url_your_server;

 



int mqw1,mqw3;//htm19
String mqw2,mqw4,mqw5,mqw6,mqw7;//htm19
String top1,top2,top3,top4; //адресное пространство MQTT 
int mqtt_data_status;
String mqtt_code_bin,mqtt_fs_bin;

float rev_code=0.01;//текущая версия кода
WiFiClient mqtttestclient; 
PubSubClient mqttclient(mqtttestclient);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80); 
WiFiClient client;
File fsUploadFile;
Ticker thingspeak_ticker;
int thingspeak_ticker_test;
Ticker narodmon_ticker;
int narodmon_ticker_test;
Ticker your_server_ticker;
int your_server_test;
 

int re1;
  
void callback(const MQTT::Publish& pub){
     String payload = pub.payload_string();
//relay     
     if(String(pub.topic()) == top3 + "sonoff-pow2/relay"){ //уровень устройства
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     if (re1 == 1){ 
                        relay_status=1;
                        save27();
                        }
                     digitalWrite(pin_relay, HIGH);  
                     mqttclient.publish(top3 + "sonoff-pow2/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       mqttclient.publish(top3 + "sonoff-pow2/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt);
                       digitalWrite(pin_relay, LOW);
                       if (re1 == 1){ 
                           relay_status=0;
                           save27();
                           }
                    }    
                } 
      if(String(pub.topic()) == top2 + "sonoff-pow2/relay"){ //уровень комнаты
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                    if (re1 == 1){ 
                        relay_status=1;
                        save27();
                        }
                       digitalWrite(pin_relay, HIGH);  
                       mqttclient.publish(top3 + "sonoff-pow2/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                      } else {
                        mqttclient.publish(top3 + "sonoff-pow2/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                        digitalWrite(pin_relay, LOW);
                          if (re1 == 1){ 
                             relay_status=0;
                             save27();
                            }
                      }    
                   
                }
     if(String(pub.topic()) == top1 + "sonoff-pow2/relay"){ //уровень дома
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){
                    if (re1 == 1){ 
                        relay_status=1;
                        save27();
                        } 
                       digitalWrite(pin_relay, HIGH);  
                        mqttclient.publish(top3 + "sonoff-pow2/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                      } else {
                        mqttclient.publish(top3 + "sonoff-pow2/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                        digitalWrite(pin_relay, LOW);
                          if (re1 == 1){ 
                              relay_status=0;
                              save27();
                             }
                    }    
                      
                }     
//led
              if(String(pub.topic()) == top3 + "sonoff-pow2/led"){ //уровень устройства
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_green_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "sonoff-pow2/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "sonoff-pow2/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_green_led, HIGH); 
                    }    
                }
              if(String(pub.topic()) == top2 + "sonoff-pow2/led"){ //уровень комнаты 
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_green_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "sonoff-pow2/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "sonoff-pow2/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_green_led, HIGH); 
                    }    
                }

             if(String(pub.topic()) == top1 + "sonoff-pow2/led"){ //уровень дома
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_green_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "sonoff-pow2/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "sonoff-pow2/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_green_led, HIGH); 
                    }    
                }

//button
             if(String(pub.topic()) == top3 + "sonoff-pow2/button"){ //уровень устройства
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     button_off=0; 
                     button_status=1;
                     mqttclient.publish(top3 + "sonoff-pow2/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       mqttclient.publish(top3 + "sonoff-pow2/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       button_off=1; 
                       button_status=0;
                    }    
                }

             if(String(pub.topic()) == top2 + "sonoff-pow2/button"){ //уровень комнаты 
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     button_off=0; 
                     button_status=1;
                     mqttclient.publish(top3 + "sonoff-pow2/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       mqttclient.publish(top3 + "sonoff-pow2/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       button_off=1; 
                       button_status=0;
                    }    
                }

           if(String(pub.topic()) == top1 + "sonoff-pow2/button"){ //уровень дома 
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     button_off=0; 
                     button_status=1;
                     mqttclient.publish(top3 + "sonoff-pow2/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       mqttclient.publish(top3 + "sonoff-pow2/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       button_off=1; 
                       button_status=0;
                    }    
                }
//status
                if(String(pub.topic()) == top3 + "sonoff-pow2/status"){  
                   String url;   
                          url += "{\"relay\":\""; 
                          url+=relay_status;
                          url += "\",\"led\":\"";
                          url+=led_status;
                          url += "\",\"button\":\"";
                          url+=button_status;
                          url +=  "\"}"; 
                   mqttclient.publish(top3 + "sonoff-pow2/status/status",url); 
                 }    

//reset
                  if(String(pub.topic()) == top3 + "sonoff-pow2/reset"){ // 
                     mqttclient.publish(top3 + "sonoff-pow2/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    }    
                  if(String(pub.topic()) == top2 + "sonoff-pow2/reset"){ // 
                     mqttclient.publish(top3 + "sonoff-pow2/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    } 
                  if(String(pub.topic()) == top1 + "sonoff-pow2/reset"){ // 
                     mqttclient.publish(top3 + "sonoff-pow2/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    }       

//update
                if(String(pub.topic()) == top3 + "sonoff-pow2/update"){ //уровень устройства
                   DynamicJsonBuffer  jsonBuffer;
                   JsonObject& json = jsonBuffer.parseObject(payload);
                   String code_bin = json["code"];//code
                   String fs_bin = json["fs"];// fs 
                   mqtt_code_bin = code_bin;
                   mqtt_fs_bin = fs_bin;
                   mqttclient.publish(top3 + "sonoff-pow2/update/status","{\"status\":\"1\"}"); 
                   esp_update(mqtt_fs_bin,mqtt_code_bin);
                }
//save_state
                if(String(pub.topic()) == top3 + "sonoff-pow2/save_state"){ //уровень устройства
                   DynamicJsonBuffer  jsonBuffer;
                   JsonObject& json = jsonBuffer.parseObject(payload);
                   re1 = json["save_state"];// 
                   save20();//  запись в память модуля
                   mqttclient.publish(top3 + "sonoff-pow2/save_state/status","{\"status\":\"1\"}"); 
                   
                }
//energy                      
                if(String(pub.topic()) == top3 + "sonoff-pow2/energy"){ //уровень устройства
                   String url;
                          url += "{\"voltage\":\"";
                          url += sensor_CSE7766.getVoltage();
                          url += "\",\"current\":\"";
                          url += sensor_CSE7766.getCurrent();
                          url += "\",\"active_power\":\"";
                          url += sensor_CSE7766.getActivePower();
                          url += "\",\"apparent_power\":\"";
                          url += sensor_CSE7766.getApparentPower();
                          url += "\",\"reactive_power\":\"";
                          url += sensor_CSE7766.getReactivePower();
                          url += "\",\"power_factor\":\"";
                          url += sensor_CSE7766.getPowerFactor();
                          url += "\",\"energy\":\"";
                          url += sensor_CSE7766.getEnergy();
                          url +=  "\"}"; 
                   mqttclient.publish(top3 + "sonoff-pow2/energy/status",url);
                  }               
                  
}

void setup(void){
     //Serial.begin(9600);
     SPIFFS.begin();
     pinMode(pin_button, INPUT); // 0 
     pinMode(pin_green_led, OUTPUT);
     pinMode(pin_relay, OUTPUT);
     attachInterrupt(pin_button,button_testing,CHANGE);
     sensor_CSE7766.setRX(1);
     sensor_CSE7766.begin(); 
     openfile();//файл настроек 
     openfilehtm19();// файл настроек  htm19 MQTT
     openfilehtm20();// файл настроек  htm20 файл настроек
     openfilehtm27();// relay status
     openfilehtm28();// sending_data
 
     if (on_off_thingspeak == 1){
         thingspeak_ticker.attach(interval_time_thingspeak,thingspeak_ticker_triggering);
        }
     if (on_off_narodmon == 1){
         narodmon_ticker.attach(interval_time_narodmon,narodmon_ticker_triggering);
        }
     if (on_off_your_server == 1){
         your_server_ticker.attach(interval_time_your_server,your_server_ticker_triggering);
        }  
        
      top3 += "/home/"+mqw7+ "/"+mqw6+"/";//уровень устройства
      top2 += "/home/"+mqw7+"/";//уровень комнаты     
      top1 += "/home/";//уровень дома

      condition();//Запоминать % состояние  
      //Serial.println(top3);//уровень устройства
      //Serial.println(top2);//уровень комнаты
      //Serial.println(top1);//уровень дома
     wifi();//подключение к wifi 
     //Serial.println(WiFi.localIP());
     serveron();//запуск сервера порт 80  

}
void loop(void){   
     server.handleClient(); 
     sensor_CSE7766.handle();
     wifitest(); 
     if (mqw1 == 1){//
         if (mqttclient.connected()){
             mqttclient.loop();
             }else {
              mqtt_connect();
             }
                  
           
        }

       
     task_plan();        
     if (task_mqtt_button == 1){//
         if (relay_status == HIGH){
             mqttclient.publish(top3 + "sonoff-pow2/relay/status","{\"status\":\"1\",\"activated\":\"0\"}");//status 1-on activated 0-кнопка );
             task_mqtt_button=0;
            }
         if (relay_status == LOW){
             mqttclient.publish(top3 + "sonoff-pow2/relay/status","{\"status\":\"0\",\"activated\":\"0\"}");//status 0-off activated 0-кнопка );
             task_mqtt_button=0;
            }
         }
         
}
