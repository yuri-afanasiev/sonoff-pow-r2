# Прошивка для Sonoff Pow R2 v0.1
### Не поддерживает обновление до AFYU 2.0

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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

 
После загрузки создастся точка доступа ESP8266 пароль 12345678 
На вкладке Настройки WIFI прописуем параметры доступа к wifi сети.Сохраняем и перезагружаем.

Доступ к web интерфейсу 
Username admin 
Password admin

В коде используется библиотека для  считывания данных CSE7766  [ingeniuske/CSE7766 Copyright (C) 2016-2018 by Xose Pérez Copyright (C) 2018 by Ingeniuske ](https://github.com/ingeniuske/CSE7766) 
