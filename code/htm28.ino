void api28() {
     on_off_thingspeak= server.arg("on_off_thingspeak").toInt();//on 1/ off 0 thingspeak
     api_key_thingspeak= server.arg("api_key_thingspeak");//API Key thingspeak
     interval_time_thingspeak= server.arg("interval_time_thingspeak").toInt();//Интервал отправки thingspeak

     on_off_narodmon= server.arg("on_off_narodmon").toInt();//on 1/ off 0 thingspeak
     interval_time_narodmon= server.arg("interval_time_narodmon").toInt();//Интервал отправки thingspeak

     on_off_your_server = server.arg("on_off_your_server").toInt();// on 1/ off 0  your server
     interval_time_your_server = server.arg("interval_time_your_server").toInt();//интервал между запросами 
     host_your_server = server.arg("host_your_server"); // host 
     port_your_server = server.arg("port_your_server");//  httpPort    
     url_your_server = server.arg("url_your_server");//   url   
      
     save28();//  запись в память модуля
     server.send(200, "text/json", "{\"status\":\"1\"}");  
       
}

void openfilehtm28() {
     File configFile = SPIFFS.open("/htm28.json", "r");
     size_t size = configFile.size();
     std::unique_ptr<char[]> buf(new char[size]);
     configFile.readBytes(buf.get(), size);
     
     DynamicJsonDocument json(2048);
     DeserializationError error = deserializeJson(json, buf.get());
     
                  on_off_thingspeak = json["d1"];// 
     String api_key_thingspeak_test = json["d2"];//
            api_key_thingspeak=api_key_thingspeak_test;
            interval_time_thingspeak= json["d3"];//
            
                     on_off_narodmon= json["d4"];//
              interval_time_narodmon= json["d5"];//
              
                  on_off_your_server= json["d6"];//
           interval_time_your_server= json["d7"];//
        String host_your_server_test= json["d8"];//
               host_your_server=host_your_server_test; 
        String port_your_server_test= json["d9"];//
               port_your_server=port_your_server_test;
        String url_your_server_test= json["d10"];//
               url_your_server=url_your_server_test;  
} 

bool save28() {
     DynamicJsonDocument  json(2048);
     json["d1"] = on_off_thingspeak;//
     json["d2"] = api_key_thingspeak;//
     json["d3"] = interval_time_thingspeak;// 
     
     json["d4"] = on_off_narodmon;// 
     json["d5"] = interval_time_narodmon;//
   
     json["d6"] = on_off_your_server;// 
     json["d7"] = interval_time_your_server;//
     json["d8"] = host_your_server;//  
     json["d9"] = port_your_server;// 
     json["d10"] = url_your_server;// 
     File configFile = SPIFFS.open("/htm28.json", "w");
     if (!configFile) {   
         return false;
         }
     serializeJson(json, configFile);
     return true;
}
void  htm28json(){
      String output;
      DynamicJsonDocument  json_web(2048);
      json_web["on_off_thingspeak"] = on_off_thingspeak;
      json_web["api_key_thingspeak"] = api_key_thingspeak;
      json_web["interval_time_thingspeak"] = interval_time_thingspeak;
      
      json_web["on_off_narodmon"] = on_off_narodmon;
      json_web["interval_time_narodmon"] = interval_time_narodmon;

      json_web["on_off_your_server"] = on_off_your_server;
      json_web["interval_time_your_server"] = interval_time_your_server;
      json_web["host_your_server"] = host_your_server;
      json_web["port_your_server"] = port_your_server;
      json_web["url_your_server"] = url_your_server;
      json_web["macAddress"] = WiFi.macAddress();
      
      serializeJson(json_web, output);
      server.send(200, "text/json",output); 
}   
void  thingspeak_ticker_triggering(){
      thingspeak_ticker_test=1;
}  
void  narodmon_ticker_triggering(){
      narodmon_ticker_test=1;
} 
void  your_server_ticker_triggering(){
      your_server_test=1;
} 
void  one_minute_ticker_triggering(){
      one_minute_test=1;
}  
