void api() {
     w1 = server.arg("ssid");//ssid
     w2 = server.arg("password");//password
     w3 = server.arg("apssid");//APssid     
     w4 = server.arg("appassword");//APpassword
     w5 = server.arg("www_username");//www_username
     w6 = server.arg("www_password");//www_password        
     w7 = server.arg("connection_time").toInt();//Время подключение     
     w8 = server.arg("time_reconnect").toInt();//Время при reconnect
     
     mesh_on_off = server.arg("on_off").toInt();//Mesh on 1/ off 0 
     mesh_hidden_ssid = server.arg("hidden_ssid").toInt();//скрывать SSID
     mesh_max_connection = server.arg("max_connection").toInt();//максимально  количества одновременно подключенных станций 0-8 
     
     save();//  запись в память модуля
     server.send(200, "text/json", "{\"status\":\"1\"}");  
}
void openfile() {
     File configFile = SPIFFS.open("/config.json", "r");
     size_t size = configFile.size();
     std::unique_ptr<char[]> buf(new char[size]);
     configFile.readBytes(buf.get(), size);
     DynamicJsonDocument json(2048);
     DeserializationError error = deserializeJson(json, buf.get());
     String w1_ = json["d1"];//ssid
     String w2_ = json["d2"];//password   
     String w3_ = json["d3"];//APssid 
     String w4_ = json["d4"];//APpassword
     String w5_ = json["d5"];//www_username
     String w6_ = json["d6"];//www_password
             w7 = json["d7"];//Время подключение
             w8 = json["d8"];//Время при reconnect 
             mesh_on_off = json["d9"];//Mesh on 1/ off 0  
        mesh_hidden_ssid = json["d12"];//скрывать SSID 
     mesh_max_connection = json["d13"];//максимально  количества одновременно подключенных станций 0-8 
     w1=w1_;
     w2=w2_;
     w3=w3_;
     w4=w4_;
     w5=w5_;
     w6=w6_;
} 
bool save() {
     String output;
     DynamicJsonDocument  json(2048);
     json["d1"] = w1;//ssid
     json["d2"] = w2;//password
     json["d3"] = w3;//APssid
     json["d4"] = w4;//APpassword
     json["d5"] = w5;//www_username
     json["d6"] = w6;//www_password
     json["d7"] = w7;//Время подключение
     json["d8"] = w8;//Время при reconnect
     json["d9"] = mesh_on_off;//Mesh on 1/ off 0  
     json["d12"] = mesh_hidden_ssid;//скрывать SSID  
     json["d13"] = mesh_max_connection;//максимально  количества одновременно подключенных станций 0-8 
     File configFile = SPIFFS.open("/config.json", "w");
     if (!configFile) {   
         return false;
        }
     serializeJson(json, configFile);
     return true;
}
void testjson(){
     String output;
     DynamicJsonDocument  json_web(2048);
     json_web["ssid"] = w1;//ssid
     json_web["password"] = w2;//password
     json_web["apssid"] = w3;//APssid
     json_web["appassword"] = w4;//APpassword
     json_web["www_username"] = w5;//www_username
     json_web["www_password"] = w6;//www_password
     json_web["connection_time"] = w7;//Время подключение
     json_web["time_reconnect"] = w8;//Время при reconnect
     json_web["on_off"] = mesh_on_off;//Mesh on 1/ off 0  
     json_web["hidden_ssid"] = mesh_hidden_ssid;//скрывать SSID 
     json_web["max_connection"] = mesh_max_connection;//максимально  количества одновременно подключенных станций 0-8 
     json_web["localIP"] = toString (WiFi.localIP());
     json_web["subnetMask"] = toString (WiFi.subnetMask()); 
     json_web["gatewayIP"] = toString (WiFi.gatewayIP()); 
     json_web["macAddress"] = WiFi.macAddress();
     json_web["dnsIP"] = toString (WiFi.dnsIP());
     json_web["APnum"] = WiFi.softAPgetStationNum();//количество станций, которые подключены к интерфейсу soft-AP
     json_web["rssi"] = WiFi.RSSI();
     json_web["APmac"] = WiFi.softAPmacAddress();
     json_web["APip"] = toString (WiFi.softAPIP());
     serializeJson(json_web, output);
     server.send(200, "text/json",output); 
} 

String toString(const IPAddress& address){
       return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}
