/*
  Warning: This is not for first time users. Use the IASLoader instead!

  This sketch is meant for adding large quantities of devices to an existing Devicebatch
  without having to do/repeat the initial setup.(Wifi, registration etc.)

  This sketch:
  - Erases EEPROM
  - Sets up initial hardcode WiFi connection
  - Contacts IOTAppStory.com over https
  - Registers your device with IOTAppStory.com
  - Saves the device activation code
  - Saves generated device name (eg. XXXX-22, XXXX-23 ...)
  - Saves the Fingerprint or Certificate (depends on config.h settings)
  - Saves the WiFi credentials (optional)
  - Calls home to get the latest firmware
  
  You will need:
  - IOTAppStory.com account
  - Device hash
  - Local WiFi credentials

  Copyright (c) [2021] [Onno Dirkzwager]

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#define COMPDATE __DATE__ __TIME__
#define MODEBUTTON 0                      // Button pin on the esp for selecting modes. D3 for the Wemos!


#include <IOTAppStory.h>                  // IOTAppStory.com library
IOTAppStory IAS(COMPDATE, MODEBUTTON);    // Initialize IOTAppStory



// ================================================ VARS =================================================
const char* ssid          = "***";        // Wifi SSID
const char* password      = "***";        // WiFi password
const bool  saveWifiCred  = true;         // true : Save the Wifi credentials for future use
                                          // false: only use Wifi credentials for adding this device and doing the initial update

const char* hash          = "***";
const char* host          = "iotappstory.com";
const char* url           = "/ota/addtoaccount";


#if defined  ESP8266 && HTTPS_8266_TYPE == FNGPRINT
  // Use web browser to view and copy SHA1 fingerprint of the certificate
  const char fingerprint[] PROGMEM = "2b 14 1a f1 5e 54 87 fc 0d f4 6f 0e 01 1c 0d 77 25 28 5b 9e";
#else
  // Use web browser to save a copy of the root certificate
  const char ROOT_CA[] = \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIEMjCCAxqgAwIBAgIBATANBgkqhkiG9w0BAQUFADB7MQswCQYDVQQGEwJHQjEb\n" \
    "MBkGA1UECAwSR3JlYXRlciBNYW5jaGVzdGVyMRAwDgYDVQQHDAdTYWxmb3JkMRow\n" \
    "GAYDVQQKDBFDb21vZG8gQ0EgTGltaXRlZDEhMB8GA1UEAwwYQUFBIENlcnRpZmlj\n" \
    "YXRlIFNlcnZpY2VzMB4XDTA0MDEwMTAwMDAwMFoXDTI4MTIzMTIzNTk1OVowezEL\n" \
    "MAkGA1UEBhMCR0IxGzAZBgNVBAgMEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UE\n" \
    "BwwHU2FsZm9yZDEaMBgGA1UECgwRQ29tb2RvIENBIExpbWl0ZWQxITAfBgNVBAMM\n" \
    "GEFBQSBDZXJ0aWZpY2F0ZSBTZXJ2aWNlczCCASIwDQYJKoZIhvcNAQEBBQADggEP\n" \
    "ADCCAQoCggEBAL5AnfRu4ep2hxxNRUSOvkbIgwadwSr+GB+O5AL686tdUIoWMQua\n" \
    "BtDFcCLNSS1UY8y2bmhGC1Pqy0wkwLxyTurxFa70VJoSCsN6sjNg4tqJVfMiWPPe\n" \
    "3M/vg4aijJRPn2jymJBGhCfHdr/jzDUsi14HZGWCwEiwqJH5YZ92IFCokcdmtet4\n" \
    "YgNW8IoaE+oxox6gmf049vYnMlhvB/VruPsUK6+3qszWY19zjNoFmag4qMsXeDZR\n" \
    "rOme9Hg6jc8P2ULimAyrL58OAd7vn5lJ8S3frHRNG5i1R8XlKdH5kBjHYpy+g8cm\n" \
    "ez6KJcfA3Z3mNWgQIJ2P2N7Sw4ScDV7oL8kCAwEAAaOBwDCBvTAdBgNVHQ4EFgQU\n" \
    "oBEKIz6W8Qfs4q8p74Klf9AwpLQwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQF\n" \
    "MAMBAf8wewYDVR0fBHQwcjA4oDagNIYyaHR0cDovL2NybC5jb21vZG9jYS5jb20v\n" \
    "QUFBQ2VydGlmaWNhdGVTZXJ2aWNlcy5jcmwwNqA0oDKGMGh0dHA6Ly9jcmwuY29t\n" \
    "b2RvLm5ldC9BQUFDZXJ0aWZpY2F0ZVNlcnZpY2VzLmNybDANBgkqhkiG9w0BAQUF\n" \
    "AAOCAQEACFb8AvCb6P+k+tZ7xkSAzk/ExfYAWMymtrwUSWgEdujm7l3sAg9g1o1Q\n" \
    "GE8mTgHj5rCl7r+8dFRBv/38ErjHT1r0iWAFf2C3BUrz9vHCv8S5dIa2LX1rzNLz\n" \
    "Rt0vxuBqw8M0Ayx9lt1awg6nCpnBBYurDC/zXDrPbDdVCYfeU0BsWO/8tqtlbgT2\n" \
    "G9w84FoVxp7Z8VlIMCFlA2zs6SFz7JsDoeA3raAVGI/6ugLOpyypEBMs1OUIJqsi\n" \
    "l2D4kF501KKaU73yqWjgom7C12yxow+ev+to51byrvLjKzg6CYG1a4XXvi3tPxq3\n" \
    "smPi9WIsgtRqAEFQ8TmDn5XpNpaYbg==\n" \
    "-----END CERTIFICATE-----\n";
#endif



// ================================================ SETUP ================================================
void setup() {
  Serial.println(FPSTR(SER_DEV));       // print divider
  IAS.eraseEEPROM('F');                 // Optional! What to do with EEPROM on First boot of the app? 'F' Fully erase | 'P' Partial erase
                                        // This should not be necessary on new devices, but may be for existing (test) devices that have used EEPROM
  
  // setup Wifi connection
  Serial.printf("\n Connecting to %s\n ", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  IAS.WiFiConnected = true;
  Serial.print(F("\n WiFi connected\n IP address: "));
  Serial.println(WiFi.localIP());
  
  {
    // Synchronize the internal clock useing SNTP | used for verifying certificates on the ESP8266
    #if defined  ESP8266 && HTTPS_8266_TYPE == CERTIFICATE
      IAS.setClock();
      IAS.ntpWaitForSync();
    #endif
    
    // Use WiFiClientSecure class to create TLS connection
    WiFiClientSecure client;
    Serial.printf("\n Connecting to %s\n", host);
  
    #if defined  ESP8266
      #if HTTPS_8266_TYPE == FNGPRINT
        Serial.printf(" Using fingerprint '%s'\n", fingerprint);
        client.setFingerprint(fingerprint);
      #else
        client.setCACert((uint8_t*)ROOT_CA, strlen(ROOT_CA));
      #endif
    #elif defined ESP32
      client.setCACert(ROOT_CA);
    #endif

    Serial.print(" ");
    while (!client.connect(host, 443)) {
      delay(500);
      Serial.print(".");
    }
  
    // request url from host
    Serial.printf("\n Requesting URL: %s%s\n", host, url);
    client.print(String("GET ") + url + "?hash=" + hash + F(" HTTP/1.1") +
                 F("\r\nHost: ") + host + 
                 F("\r\nUser-Agent: ESP-http-Update") +
                 F("\r\nx-ESP-STA-MAC: ") + WiFi.macAddress() +
                 F("\r\nx-ESP-LOCIP: ") + WiFi.localIP().toString() +
                 F("\r\nx-ESP-SKETCH-MD5: ") + ESP.getSketchMD5() +
                 F("\r\nx-ESP-FLASHCHIP-ID: ") + ESP_GETFLASHCHIPID +
                 F("\r\nx-ESP-CHIP-ID: ") + ESP_GETCHIPID +
                 F("\r\nx-ESP-FLASHCHIP-SIZE: ") + ESP.getFlashChipSize() +
                 F("\r\nConnection: close\r\n\r\n"));
  
    // process server respons header & return error if not 200 - OK
    int code;
    String actcode, deviceName;
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      
      if(line.startsWith(F("HTTP/1.1 "))) {
          line.remove(0, 9);
          code = line.substring(0, 3).toInt();
  
          if(code != 200){
            line.remove(0, 4);
            Serial.print(F(" Request error!\n Code\t\t: "));
            Serial.print(code);
            Serial.print(F("\n Message\t: "));
            Serial.println(line);
            break;
          }
      }else if(line.startsWith(F("actcode: "))) {
          line.remove(0, 9);
          actcode = line;
      }else if(line.startsWith(F("devname: "))) {
          line.remove(0, 9);
          deviceName = line;
      }else if (line == "\r") {
          Serial.println(F("\n Headers received"));
          break;
      }
    }
  
    // Close connection
    client.stop();
    Serial.println(F(" Closing connection"));
  
  
    // If server respons code is OK and we received the activation code
    if(code == 200 && actcode != ""){
      Serial.println(F("\n Success! Added device to IAS.\n Updating device..."));
  
      // create new config struc
      ConfigStruct newConfig;

      // read config | this gets the default settings
      IAS.readConfig(newConfig);
      {
        // copy activation code to newConfig struct
        actcode.toCharArray(newConfig.actCode, 7);
        Serial.println(F(" - Added activation code."));
        
        // copy deviceName to newConfig struct
        deviceName.toCharArray(newConfig.deviceName, STRUCT_BNAME_SIZE);
        Serial.print(" - Added device name: ");
        Serial.println(deviceName);

        // copy fingerprint to newConfig struct OR certificate to file system
        #if defined  ESP8266 && HTTPS_8266_TYPE == FNGPRINT
          strcpy(newConfig.sha1, fingerprint);
          Serial.println(F(" - Added fingerprint"));
        #endif
        
        // write config to EEPROM
        IAS.writeConfig(newConfig);
        delay(100);

        // if set write certificate to file system for future use
        #if defined  ESP32 || HTTPS_8266_TYPE == CERTIFICATE
          
          // Mount file system
          if(!ESP_FSBEGIN){
            Serial.println(F("- Failed to mount file system"));
          }

          // open new file for writing data
          File fsUploadFile;
          fsUploadFile = FILESYSTEM.open("/cert/iasRootCa.cer", "w"); /// close file

          // write certificate(hardcoded char array) to file
          if(fsUploadFile.write((uint8_t *)ROOT_CA, strlen(ROOT_CA)) != strlen(ROOT_CA)){
            Serial.println(F(" - Failed to write certificate to file system"));
          }
    
          // close file
          fsUploadFile.close();
    
          Serial.println(F(" - Added Certificate to file system"));
        #endif
      }
      
      // write WiFi credentials to EEPROM
      if(saveWifiCred){
        WiFiConnector WiFiConn;
        WiFiConn.addAPtoEEPROM(ssid, password, 1);
        Serial.println(F(" - Added WiFi credentials"));
      }
  
      // print divider
      Serial.println(FPSTR(SER_DEV));
    }else{
      return;
    }
  }
  
  // callback for showing update progress
  IAS.onFirmwareUpdateProgress([](int written, int total){
      Serial.print(".");
  });

  // callhome and get the latest firmware
  IAS.callHome();

  // if callhome failed retry every 60 sec
  IAS.setCallHomeInterval(60);
}



// ================================================ LOOP =================================================
void loop() {
  IAS.loop();   // this routine handles the calling home functionality,
                // reaction of the MODEBUTTON pin. If short press (<4 sec): update of sketch, long press (>7 sec): Configuration
                // reconnecting WiFi when the connection is lost,
                // and setting the internal clock (ESP8266 for BearSSL)
}
