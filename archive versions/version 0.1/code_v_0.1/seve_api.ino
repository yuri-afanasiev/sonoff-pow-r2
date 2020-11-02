void api() {
     w1 = server.arg("ssid"); //ssid
     w2 = server.arg("password"); //password
     w3 = server.arg("apssid"); //APssid     
     w4 = server.arg("appassword"); //APpassword
     w5 = server.arg("www_username"); //www_username
     w6 = server.arg("www_password"); //www_password        
     w7 = server.arg("connection_time").toInt(); //Время подключение     
     w8 = server.arg("time_reconnect").toInt(); //Время при reconnect
     save();//  запись в память модуля
     server.send(200, "text/json", "{\"status\":\"1\"}");  
}
void openfile() {
  File configFile = SPIFFS.open("/config.json", "r");
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  String ee1 = json["d1"];//ssid
  String ee2 = json["d2"];//password   
  String ee3 = json["d3"];//APssid 
  String ee4 = json["d4"];//APpassword
  String ee5 = json["d5"];//www_username
  String ee6 = json["d6"];//www_password
          w7 = json["d7"];//Время подключение
          w8 = json["d8"];//Время при reconnect
  
  w1=ee1;
  w2=ee2;
  w3=ee3;
  w4=ee4;
  w5=ee5;
  w6=ee6;
} 

bool save() {
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["d1"] = w1;//ssid
  json["d2"] = w2;//password
  json["d3"] = w3;//APssid
  json["d4"] = w4;//APpassword
  json["d5"] = w5;//www_username
  json["d6"] = w6;//www_password
  json["d7"] = w7;//Время подключение
  json["d8"] = w8;//Время при reconnect
  
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {   
    return false;
  }
  json.printTo(configFile);
  return true;
}

 

void testjson(){
       String url;   
              url += "{\"ssid\":\""; 
              url+=w1;
              url += "\",\"password\":\"";
              url+=w2;
              url += "\",\"apssid\":\"";
              url+=w3;
              url += "\",\"appassword\":\"";
              url+=w4;
              url += "\",\"www_username\":\"";
              url+=w5;
              url += "\",\"www_password\":\"";
              url+=w6;
              url += "\",\"connection_time\":\"";
              url+=w7;
              url += "\",\"time_reconnect\":\"";
              url+=w8;
              url +=  "\"}"; 
server.send(200, "text/json",url); 
} 

   
