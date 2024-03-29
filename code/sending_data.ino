 void thingspeak() { 
      String  url="/update?api_key=";
             url+=api_key_thingspeak; 
             url+= "&field1=";//voltage 
             url+= sensor_CSE7766.getVoltage(); 
             url+= "&field2=";//current
             url+= sensor_CSE7766.getCurrent();  
             url+= "&field3=";//active_power   
             url+= sensor_CSE7766.getActivePower();  
             url+= "&field4=";//apparent_power  
             url+= sensor_CSE7766.getApparentPower();  
             url+= "&field5=";//reactive_power   
             url+= sensor_CSE7766.getReactivePower(); 
             url+= "&field6=";//power_factor   
             url+= sensor_CSE7766.getPowerFactor(); 
             url+= "&field7=";//energy   
             url+= sensor_CSE7766.getEnergy()/1000000/4; 
             url+= "&field8=";
             url+= relay_status;//relay status 
 
            
            
      WiFiClient client_thingspeak;
      if (client_thingspeak.connect("api.thingspeak.com",80)) {
          client_thingspeak.print(String("GET ") + url + " HTTP/1.1\r\n" +
                                  "Host: " + "api.thingspeak.com" + "\r\n" + 
                                  "Connection: close\r\n\r\n");  
                                 }   
         client_thingspeak.stop();
}
void narodmon() {
     String output;
     DynamicJsonDocument  json(2048);
     json["devices"][0]["mac"] = WiFi.macAddress();
     json["devices"][0]["sensors"][0]["id"] = "RSSI";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][0]["name"] = "RSSI";//название датчика
     json["devices"][0]["sensors"][0]["value"] = WiFi.RSSI();//показание датчика
           
     json["devices"][0]["sensors"][1]["id"] = "U1";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][1]["name"] = "voltage";//название датчика
     json["devices"][0]["sensors"][1]["value"] = sensor_CSE7766.getVoltage();//Напряжение

     json["devices"][0]["sensors"][2]["id"] = "I1";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][2]["name"] = "current";//название датчика
     json["devices"][0]["sensors"][2]["value"] = sensor_CSE7766.getCurrent();//Ток  

     json["devices"][0]["sensors"][3]["id"] = "W1";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][3]["name"] = "active_power";//название датчика
     json["devices"][0]["sensors"][3]["value"] = sensor_CSE7766.getActivePower();//Активная мощность 

     json["devices"][0]["sensors"][4]["id"] = "W2";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][4]["name"] = "apparent_power";//название датчика
     json["devices"][0]["sensors"][4]["value"] = sensor_CSE7766.getApparentPower();//Полная мощность

     json["devices"][0]["sensors"][5]["id"] = "W3";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][5]["name"] = "reactive_power";//название датчика
     json["devices"][0]["sensors"][5]["value"] = sensor_CSE7766.getReactivePower();//Реактивная мощность

     json["devices"][0]["sensors"][6]["id"] = "power_factor";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][6]["name"] = "power_factor";//название датчика
     json["devices"][0]["sensors"][6]["value"] = sensor_CSE7766.getPowerFactor();//Коэффициент мощности

     json["devices"][0]["sensors"][7]["id"] = "energy";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][7]["name"] = "energy";//название датчика
     json["devices"][0]["sensors"][7]["value"] = sensor_CSE7766.getEnergy()/1000000/4;//Энергия
                                                                              
     json["devices"][0]["sensors"][8]["id"] = "relay";// метрика датчика, уникальная для прибора;
     json["devices"][0]["sensors"][8]["name"] = "relay_status";//название датчика
     json["devices"][0]["sensors"][8]["value"] = relay_status;
     serializeJson(json, output);
      
     WiFiClient narodmon_client;
     if (narodmon_client.connect("narodmon.ru",80)) {
         narodmon_client.print(String("POST ") + "http://narodmon.ru/post" + " HTTP/1.1\r\n" +
                               "Host: " + "narodmon.ru" + "\r\n" + 
                               "Content-Type: application/x-www-form-urlencoded\r\n"+
                               "Content-Length:"+output.length()+"\r\n\r\n"+output); 
        }   
     narodmon_client.stop();
}
void emoncms() {
     String output;
     DynamicJsonDocument  json(512);
     json["voltage"] = sensor_CSE7766.getVoltage();
     json["current"] = sensor_CSE7766.getCurrent();
     json["active_power"] = sensor_CSE7766.getActivePower();
     json["apparent_power"] = sensor_CSE7766.getApparentPower();
     json["reactive_power"] = sensor_CSE7766.getReactivePower();
     json["power_factor"] = sensor_CSE7766.getPowerFactor();
     json["energy"] = sensor_CSE7766.getEnergy()/1000000/4;
     serializeJson(json, output);
     String   url=url_emoncms_server;
              url += "?fulljson=";
              url+=output;
              url+="&apikey=";  
              url+= api_key_emoncms;  
              url+="&node=";  
              url+= node_emoncms_server;
     WiFiClient emoncms_server_client;
     char **pointer, *stringVar;
     unsigned long emoncms_server_http_port;
     emoncms_server_http_port = strtoul(port_emoncms_server.c_str(),pointer,10);    
     if (emoncms_server_client.connect(host_emoncms_server.c_str(),emoncms_server_http_port)) {
         emoncms_server_client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                                  "Host: " + host_emoncms_server + "\r\n" + 
                                  "Connection: close\r\n\r\n"); 
         } 
     emoncms_server_client.stop(); 
}
void your_server() {
     String   url=url_your_server;
                 url += "?id=";
                 url+=ESP.getChipId();
                 url+= "&voltage=";  
                 url+= sensor_CSE7766.getVoltage();   
                 url+="&current=";
                 url+= sensor_CSE7766.getCurrent();  
                 url+="&=active_power"; 
                 url+= sensor_CSE7766.getActivePower();       
                 url+="&apparent_power=";
                 url+= sensor_CSE7766.getApparentPower(); 
                 url+="&reactive_power=";
                 url+= sensor_CSE7766.getReactivePower(); 
                 url+="&power_factor=";
                 url+= sensor_CSE7766.getPowerFactor();
                 url+="&energy=";
                 url+= sensor_CSE7766.getEnergy()/1000000/4;  
                 url+="&relay_status=";
                 url+= relay_status;  
                 url+="&led_status=";
                 url+= led_status; 
                 url+="&button_status=";
                 url+= button_status;
                 url+="&rssi="; 
                 url+= WiFi.RSSI();
                 
     WiFiClient your_server_client;
     char **pointer, *stringVar;
     unsigned long your_server_http_port;
     your_server_http_port = strtoul(port_your_server.c_str(),pointer,10);    
     if (your_server_client.connect(host_your_server.c_str(),your_server_http_port)) {
         your_server_client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                                  "Host: " + host_your_server + "\r\n" + 
                                  "Connection: close\r\n\r\n"); 
         } 
     your_server_client.stop(); 
}
