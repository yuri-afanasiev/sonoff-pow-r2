void api20() {
     save_state = server.arg("save_state").toInt();//Запоминать % состояние
     save_20();//Запись в память модуля
     server.send(200, "text/json", "{\"status\":\"1\"}"); 
}
void open_file_htm20() {
     File configFile = SPIFFS.open("/htm20.json", "r");
     size_t size = configFile.size();
     std::unique_ptr<char[]> buf(new char[size]);
     configFile.readBytes(buf.get(), size);
     DynamicJsonDocument json(512);
     DeserializationError error = deserializeJson(json, buf.get());
     save_state = json["d1"];//Состояние relay 
} 
bool save_20() {
     DynamicJsonDocument  json(512);
     json["d1"] = save_state;// 
     File configFile = SPIFFS.open("/htm20.json", "w");
     if (!configFile) {   
         return false;
         }
     serializeJson(json, configFile);
     return true;
}
void  htm20_json(){
      String output;
      DynamicJsonDocument  json_web(512);
      json_web["save_state"] = save_state;
      json_web["relay_status"] = relay_status;
      
      serializeJson(json_web, output);
      server.send(200, "text/json",output); 
}   
void open_file_htm27() {
     File configFile = SPIFFS.open("/htm27.json", "r");
     size_t size = configFile.size();
     std::unique_ptr<char[]> buf(new char[size]);
     configFile.readBytes(buf.get(), size);
     DynamicJsonDocument json(512);
     DeserializationError error = deserializeJson(json, buf.get());
     relay_status = json["d1"];//Состояние relay 
} 
bool save_27() {
     DynamicJsonDocument  json(512);
     json["d1"] = relay_status;// 
     File configFile = SPIFFS.open("/htm27.json", "w");
     if (!configFile) {   
         return false;
         }
     serializeJson(json, configFile);
     return true;
}
void relay_timer(int interval_time_common){
     relay_status=1;//Статус relay
     common_ticker_status=1;
     common_ticker.attach(interval_time_common,interval_time_common_triggering);
     digitalWrite(pin_relay, HIGH); 
     if (mqw1 == 1){
         String url;   
         url += "{\"status\":\"1"; 
         url += "\",\"time\":\"";
         url += interval_time_common; 
         url += "\",\"activated\":\"3";
         url += "\"}"; 
         mqttclient.publish(top3 + "/relay/status",url);//status 1-on activated time-Интервал с. 3-timer 
        }
}  
void interval_time_common_triggering(){
     common_ticker.detach(); 
     common_ticker_status=0;
     relay_status=0;
     digitalWrite(pin_relay, LOW);
     if (mqw1 == 1){
         mqttclient.publish(top3 + "/relay/status","{\"status\":\"0\",\"activated\":\"3\"}");//status 1-on activated 3-timer
        }
}  
