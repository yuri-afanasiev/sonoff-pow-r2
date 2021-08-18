void serveron() {
     server.on("/esp_update", [](){//Обнавление   
     if(!server.authenticate(w5.c_str(),w6.c_str()))
        return server.requestAuthentication();  
        String fs_bin_test = server.arg("fs_bin");//fs 
        String code_bin_test = server.arg("code_bin");//code
        esp_update(fs_bin_test,code_bin_test);
     }); 
     
     server.on("/config", [](){    
     if(!server.authenticate(w5.c_str(),w6.c_str()))
     return server.requestAuthentication();  
     testjson();
     }); 

    server.on("/sending_data", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
    return server.requestAuthentication();
    api28();
    });


    server.on("/relay/timer", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
    return server.requestAuthentication();
    relay_timer(server.arg("time").toInt());//Интервал 
    server.send(200, "text/json", "{\"status\":\"1\"}"); 
    });
    
    server.on("/relay/timer/off", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
    return server.requestAuthentication();
    interval_time_common_triggering();
    server.send(200, "text/json", "{\"status\":\"1\"}"); 
    });
    
    server.on("/sending_data_json", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
    return server.requestAuthentication();
    htm28json();
    });  
    
    server.on("/xml9", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    htm9xml();
    });   
   
    server.on("/json19", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    htm19json();
    }); 
    
    server.on("/json_20", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    htm20_json();
    });     
     
    server.on("/readtest", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
    return server.requestAuthentication();
    String url;   
             url += "{\"ChipId\":\""; 
             url+= ESP.getChipId();
             url += "\",\"CoreVersion\":\"";
             url+=ESP.getCoreVersion();
             url += "\",\"FlashChipId\":\"";
             url+=ESP.getFlashChipId();
             url += "\",\"SdkVersion\":\"";
             url+=ESP.getSdkVersion();
             url += "\",\"SketchMD5\":\"";
             url+=ESP.getSketchMD5();
             url += "\"}"; 
      server.send(200, "text/json",url);
    });

    
    server.on("/system", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
    return server.requestAuthentication();
    String url;   
             url += "{\"ChipId\":\""; 
             url+= ESP.getChipId();
             url += "\",\"FlashChipId\":\"";
             url+=ESP.getFlashChipId();
             url += "\",\"SdkVersion\":\"";
             url+=ESP.getSdkVersion();
             url += "\",\"MD5\":\"";
             url+=ESP.getSketchMD5();
             url += "\"}"; 
      server.send(200, "text/json",url);
    });


    
    server.on("/status", []() {
           if (!server.authenticate(w5.c_str(), w6.c_str()))
                return server.requestAuthentication();
           String output;
           DynamicJsonDocument  json(512);
           json["relay"] = relay_status;
           json["timer"] = common_ticker_status;
           json["led"] = led_status;
           json["button"] = button_status;
           json["mqtt"] = mqw1;
           json["rssi"] = WiFi.RSSI();
           serializeJson(json, output);
           server.send(200, "text/json",output);
    }); 
    server.on("/energy", []() {
           if (!server.authenticate(w5.c_str(), w6.c_str()))
                return server.requestAuthentication();
           String output;
           DynamicJsonDocument  json(512);
           json["voltage"] = sensor_CSE7766.getVoltage();
           json["current"] = sensor_CSE7766.getCurrent();
           json["active_power"] = sensor_CSE7766.getActivePower();
           json["apparent_power"] = sensor_CSE7766.getApparentPower();
           json["reactive_power"] = sensor_CSE7766.getReactivePower();
           json["power_factor"] = sensor_CSE7766.getPowerFactor();
           json["energy_kwh"] = sensor_CSE7766.getEnergy()/1000000/4;
           serializeJson(json, output);
           server.send(200, "text/json",output);
    }); 
    
    server.on("/api", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    api();
    });  

    server.on("/api20", [](){    
    if(!server.authenticate(w5.c_str(),w6.c_str()))
    return server.requestAuthentication();  
    api20();
    }); 
     
    server.on("/relay/on", [](){
              if(!server.authenticate(w5.c_str(),w6.c_str()))
                 return server.requestAuthentication();
                 relay_status=1;
                 if (save_state == 1){ 
                     save_27();
                    }
                 digitalWrite(pin_relay, HIGH);  
                 if (mqw1 == 1){
                     mqttclient.publish(top3 + "/relay/status","{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
                    }
                 server.send(200, "text/json","{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
    });
    
    server.on("/relay/off", [](){
              if(!server.authenticate(w5.c_str(),w6.c_str()))
                 return server.requestAuthentication();
                 relay_status=0;
                 if (save_state == 1){ 
                     save_27();
                    }
                 digitalWrite(pin_relay, LOW);  
                 if (mqw1 == 1){
                     mqttclient.publish(top3 + "/relay/status","{\"status\":\"0\",\"activated\":\"1\"}");//status 1-on activated 1-web
                    }
                 server.send(200, "text/json","{\"status\":\"0\",\"activated\":\"1\"}");//status 1-on activated 1-web
    });    

    server.on("/led/on", [](){
              if(!server.authenticate(w5.c_str(),w6.c_str()))
                 return server.requestAuthentication();
                 digitalWrite(pin_green_led, LOW); 
                 led_status=1;
                 if (mqw1 == 1){
                     mqttclient.publish(top3 + "/led/status","{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
                    }
                 server.send(200, "text/json", "{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
    }); 
    
    server.on("/led/off", [](){
              if(!server.authenticate(w5.c_str(),w6.c_str()))
                 return server.requestAuthentication();
                 digitalWrite(pin_green_led, HIGH); 
                 led_status=0;
                 if (mqw1 == 1){
                     mqttclient.publish(top3 + "/led/status","{\"status\":\"0\",\"activated\":\"1\"}");//status 1-on activated 1-web
                    }
                 server.send(200, "text/json", "{\"status\":\"0\",\"activated\":\"1\"}");//status 1-on activated 1-web
    });    

    server.on("/button/on", [](){
              if(!server.authenticate(w5.c_str(),w6.c_str()))
                 return server.requestAuthentication();
                 button_off=0;
                 button_status=1;
                 if (mqw1 == 1){
                     mqttclient.publish(top3 + "/button/status","{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
                    }
                 server.send(200, "text/json","{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
    }); 
    
    server.on("/button/off", [](){
              if(!server.authenticate(w5.c_str(),w6.c_str()))
                 return server.requestAuthentication();
                 button_off=1;
                 button_status=0;
                 if (mqw1 == 1){
                     mqttclient.publish(top3 + "/button/status","{\"status\":\"0\",\"activated\":\"1\"}");//status 1-on activated 1-web
                    }
                 server.send(200, "text/json","{\"status\":\"0\",\"activated\":\"1\"}");//status 1-on activated 1-web
    });     
    
    
    server.on("/reset", [](){
     if(!server.authenticate(w5.c_str(),w6.c_str()))
        return server.requestAuthentication();  
        server.send(200, "text/json", "{\"status\":\"1\"}");
        delay(200);  
        ESP.restart();    
     }); 
     
       server.on("/api19", [](){    
       if(!server.authenticate(w5.c_str(),w6.c_str()))
       return server.requestAuthentication();  
       api19();
       });   
     

      
    
    server.on("/config.json", [](){      
    server.send(403, "text/plain", "Forbidden");       
    });  
    
    server.on("/htm19.json", [](){      
    server.send(403, "text/plain", "Forbidden");       
    }); 
    
     
     server.onNotFound([](){
            if(!server.authenticate(w5.c_str(),w6.c_str()))
               return server.requestAuthentication();  
               if(!handleFileRead(server.uri()))
                  server.send(404, "text/plain", "FileNotFound");
              }); 
     server.begin();
}
