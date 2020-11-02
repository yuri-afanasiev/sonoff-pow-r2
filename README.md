# Прошивка для Sonoff Pow R2
# AFYU 2.0

## [Документация](https://github.com/yuri-afanasiev/sonoff-pow-r2/wiki)
![15](https://raw.githubusercontent.com/yuri-afanasiev/sonoff-pow-r2/master/doc/15.jpeg)

## Поддерживаемые сервисы: 
- Narodmon 
- Thingspeak 
- Отправка данных на свой сервер 

## Установка
!!! Логическое заземление устройства подключено к нейтральной линии сети 220V !!!
- Нужно отключить устройство от сети 220v
- Загружать прошивку только от внешнего питания в 3.3v !!!
 
Загрузка прошивки с помощью NodeMCU Flasher  https://github.com/nodemcu/nodemcu-flasher
Скачать можно [тут](https://github.com/nodemcu/nodemcu-flasher/blob/master/Win32/Release/ESP8266Flasher.exe)
Последнюю версию прошивки можно скачать из папки [build](https://github.com/yuri-afanasiev/sonoff-pow-r2/tree/master/build)
Как загрузить прошивку рассказано в виде [тут](https://youtu.be/BzPQeN5GVMM)
 ![12](https://raw.githubusercontent.com/yuri-afanasiev/sonoff-pow-r2/master/doc/12.png)
 ![2.0_2](https://github.com/yuri-afanasiev/sonoff-pow-r2/raw/master/doc/2.0_2.jpg)
  
 
 
После загрузки создастся точка доступа AFYU_Setting пароль 12345678 
На вкладке Настройки WIFI прописуем параметры доступа к wifi сети.Сохраняем и перезагружаем.

Доступ к web интерфейсу 
Username admin 
Password admin
 ![2.0_1](https://github.com/yuri-afanasiev/sonoff-pow-r2/raw/master/doc/2.0_1.jpg)

В коде используется библиотека для  считывания данных CSE7766  [ingeniuske/CSE7766 Copyright (C) 2016-2018 by Xose Pérez Copyright (C) 2018 by Ingeniuske ](https://github.com/ingeniuske/CSE7766) 


## Прошивки для других устройств:
- [Sonoff BN-SZ01](https://github.com/yuri-afanasiev/esp8285-BN-SZ01)
- [Sonoff Touch](https://github.com/yuri-afanasiev/sonoff-touch)
- [Sonoff S20](https://github.com/yuri-afanasiev/sonoff-s20)

## Thingspeak 
 ![14](https://raw.githubusercontent.com/yuri-afanasiev/sonoff-pow-r2/master/doc/14.png)
