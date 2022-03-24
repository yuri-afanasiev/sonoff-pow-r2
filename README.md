# Прошивка для Sonoff Pow R2
## [Документация](https://github.com/yuri-afanasiev/sonoff-pow-r2/wiki)
- Код основан на системе [AFYU 2.0](https://github.com/yuri-afanasiev/AFYU)
- Поддерживает Mesh  
- Текущая версия 2.21

![15](https://raw.githubusercontent.com/yuri-afanasiev/sonoff-pow-r2/master/doc/15.jpeg)

## Поддерживаемые сервисы: 
- [Thingspeak](https://thingspeak.com)
- [Emoncms](https://emoncms.org/)
- [Отправка данных на свой сервер](https://github.com/yuri-afanasiev/sonoff-pow-r2/wiki/REST-API-Передача-данных#Свой-сервер) 

### Возможны неправильные данные по energy_kwh

## Установка
!!! Логическое заземление устройства подключено к нейтральной линии сети 220V !!!
- Нужно отключить устройство от сети 220v
- Загружать прошивку только от внешнего питания в 3.3v !!!
 
- ### Загрузка прошивки с помощью NodeMCU Flasher  https://github.com/nodemcu/nodemcu-flasher

- ### Скачать можно [тут](https://github.com/nodemcu/nodemcu-flasher/blob/master/Win32/Release/ESP8266Flasher.exe)

- ### Последнюю версию прошивки можно скачать из папки [build](https://github.com/yuri-afanasiev/sonoff-pow-r2/tree/master/build)

 ![12](https://raw.githubusercontent.com/yuri-afanasiev/sonoff-pow-r2/master/doc/12.png)
 ![2.0_2](https://github.com/yuri-afanasiev/sonoff-pow-r2/raw/master/doc/2.0_2.jpg)
  
 
 
- ### После загрузки создастся точка доступа AFYU_MESH Пароль 12345678 

- ### На вкладке Настройки WIFI прописуем параметры доступа к wifi сети. Сохраняем и перезагружаем.

- ### Доступ к web интерфейсу 

#### Username admin 
#### Password admin


 ![2.0_1](https://github.com/yuri-afanasiev/sonoff-pow-r2/raw/master/doc/2.0_1.jpg)
 
 ## Прошивки для других устройств:
- [Sonoff BN-SZ01](https://github.com/yuri-afanasiev/esp8285-BN-SZ01)
- [Sonoff Touch](https://github.com/yuri-afanasiev/sonoff-touch)
- [Sonoff S20](https://github.com/yuri-afanasiev/sonoff-s20)

## Thingspeak 
 ![14](https://raw.githubusercontent.com/yuri-afanasiev/sonoff-pow-r2/master/doc/14.png)
 
## Используемые библиотеки
### В коде используется библиотека для  считывания данных CSE7766  [ingeniuske/CSE7766 Copyright (C) 2016-2018 by Xose Pérez Copyright (C) 2018 by Ingeniuske ](https://github.com/ingeniuske/CSE7766) 
### [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi) 
### [ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer) 
### [ESP8266mDNS](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS) 
### [ESP8266HTTPClient](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient) 
### [ESP8266HTTPUpdateServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPUpdateServer) 
### [ArduinoJson](https://arduinojson.org) 
### [PubSubClient](https://github.com/Imroy/pubsubclient)
### [ESP8266httpUpdate](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266httpUpdate) 
### [FS](http://esp8266.github.io/Arduino/versions/2.1.0/doc/filesystem.html) 
### [esp-lwip](https://github.com/espressif/esp-lwip) 
### [RangeExtender-NAPT](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples/RangeExtender-NAPT) 
### [Ticker](https://github.com/esp8266/Arduino/tree/master/libraries/Ticker) 
### [SPI](http://www.arduino.cc/en/Reference/SPI) 


 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
