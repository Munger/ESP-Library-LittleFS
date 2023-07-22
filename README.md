<img src="https://github.com/iotappstory/ESP-Library/blob/master/readme.jpg"/>

Wifi & OTA update manager for IOT devices (ESP8266 and ESP32). ESP8266's need at least 1MB flash. You will need a free account at IOTAppStory.com.
</br></br>
<span style="background-color: #FFFF00">
This fork provides optional support for LittleFS instead of SPIFFS.
To use LittleFS build with -DESP_USELITTLEFS=1. Please note that as LittleFS has support for real directories you will need to pass 'true' as the 'create' param when opening files if you want to create the directory hierarchy when opening a file. THe constant FS_CREATE_DIR_PATH has been defined for this purpose, e.g.
</br></br>
File fsUploadFile;</br>
fsUploadFile = FILESYSTEM.open("/cert/iasRootCa.cer", "w", FS_CREATE_DIR_PATH);
</br></br>
FS_CREATE_DIR_PATH is true when using LittleFS, otherwise false. I have not yet checked all of the example code so if you have problems opening files, this is probably why.
</span>
</br></br>

## Latest release 3.0.0-a.1
https://github.com/Munger/ESP-Library-LittleFS/releases/latest
</br></br>

## Arduino IDE [![arduino-library-badge](https://www.ardu-badge.com/badge/IOTAppStory-ESP.svg?)](https://www.ardu-badge.com/IOTAppStory-ESP)
<img src="https://github.com/iotappstory/ESP8266-Library/blob/master/arduinoIDE_lib_manager.jpg"/>
</br>

## Prerequisites
#### ESP8266 specific
- <a href="https://github.com/esp8266/Arduino" target="_blank">ESP8266</a> core for Arduino &gt;= 2.4.2
- <a href="https://github.com/me-no-dev/ESPAsyncTCP" target="_blank">Async TCP Library</a> for ESP8266

#### ESP32 specific
- <a href="https://github.com/espressif/arduino-esp32" target="_blank">Arduino core</a> for the ESP32 &gt;= 1.0.0
- <a href="https://github.com/me-no-dev/AsyncTCP" target="_blank">Async TCP</a> Library for ESP32

#### ESP8266 and ESP32
- <a href="https://www.arduino.cc/en/Main/Software" target="_blank">Arduino IDE</a> &gt;= 1.8.5
- <a href="https://github.com/me-no-dev/ESPAsyncWebServer" target="_blank">Async Web Server</a>
</br>

## IAS WIKI
https://iotappstory.com/wiki/arduino-esp</br></br>

## Contributions and thanks
Thankyou to all of you who made a [pull request](https://github.com/iotappstory/ESP-Library/graphs/contributors)</br>

## Donation
Consider supporting IOTAppStory.com by contributing to its development.</br>
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=5LQHCDGKDMW38)
