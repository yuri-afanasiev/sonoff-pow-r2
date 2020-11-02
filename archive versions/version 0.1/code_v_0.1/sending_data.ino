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
             url+= sensor_CSE7766.getEnergy();  
             url+= "&field8=";//GPIO12 status   
             if (relay_status == 1){ 
                 url+= "0";    
                 } else {
                 url+= "1";  
                 }
            
     WiFiClient client_thingspeak;
     if (client_thingspeak.connect("api.thingspeak.com",80)) {
         client_thingspeak.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + "api.thingspeak.com" + "\r\n" + 
          "Connection: close\r\n\r\n");  
        }   
     client_thingspeak.stop();
}



void narodmon() {
     String  url="#" + WiFi.macAddress() + " \r\n";
             url+= "#RSSI#";  
             url+=  WiFi.RSSI();    
             url+= "#RSSI\r\n"; 
             url+= "#U1#";  
             url+=  sensor_CSE7766.getVoltage();//Напряжение    
             url+= "#voltage\r\n"; 
             url+= "#I1#";  
             url+=  sensor_CSE7766.getCurrent();//Ток   
             url+= "#current\r\n"; 
             url+= "#W1#";  
             url+=  sensor_CSE7766.getActivePower();//Активная мощность 
             url+= "#active_power\r\n";
             url+= "#W2#";  
             url+=  sensor_CSE7766.getApparentPower();//Полная мощность
             url+= "#apparent_power\r\n";
             url+= "#W3#";  
             url+=  sensor_CSE7766.getReactivePower();//Реактивная мощность
             url+= "#reactive_power\r\n"; 
             url+= "#power_factor#";  
             url+=  sensor_CSE7766.getPowerFactor();//Коэффициент мощности
             url+= "#power_factor\r\n"; 
             url+= "#energy#";  
             url+=  sensor_CSE7766.getEnergy();//Энергия
             url+= "#energy\r\n";
             url+= "#GPIO12#";  
             if (relay_status == 1){ 
                 url+= "0";    
                 } else {
                 url+= "1";  
                 }
             url+= "#relay_status\r\n"; 
             url+= "##";          
     WiFiClient narodmon_client; 
     if (narodmon_client.connect("narodmon.ru",8283)) {
         narodmon_client.print(url);
        } 
     narodmon_client.stop();   
}

void your_server() {
        String   url=url_your_server;
                 url += "?id=";
                 url+=ESP.getChipId();
                 url+= "&voltage=";  
                 url+= sensor_CSE7766.getVoltage();;   
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
                 url+= sensor_CSE7766.getEnergy();  
                 url+="&relay_status=";
                 if (relay_status == 1){ 
                 url+= "0";    
                 } else {
                 url+= "1";  
                 }
                 url+="&led_status=";
                 url+= led_status; 
                 url+="&button_status=";
                 url+= button_status;  
                 url+= "&vcc="; 
                 float vcc1 = ESP.getVcc();
                 String vcc ;  
                 vcc += vcc1/1000,2;  
                 url+= vcc;
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


