void api20() {
     re1 = server.arg("save_state").toInt();//Запоминать % состояние 
     save20();//  запись в память модуля
     server.send(200, "text/json","{\"status\":\"1\"}");
}

void openfilehtm20() {
  File configFile = SPIFFS.open("/htm20.json", "r");
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
        re1 = json["d1"];// 
} 

bool save20() {
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["d1"] = re1;// 
  File configFile = SPIFFS.open("/htm20.json", "w");
  if (!configFile) {   
    return false;
  }
  json.printTo(configFile);
  return true;
}

void  htm20json(){
       String url;   
              url += "{\"save_state\":\""; 
              url+=re1;
              url += "\",\"relay_status\":\"";
              url+=relay_status;
              url +=  "\"}"; 
server.send(200, "text/json",url); 
}   
////////////////////////////////


void openfilehtm27() {
  File configFile = SPIFFS.open("/htm27.json", "r");
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  relay_status = json["d1"];
} 

bool save27() {
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["d1"] = relay_status;
  File configFile = SPIFFS.open("/htm27.json", "w");
  if (!configFile) {   
    return false;
  }
  json.printTo(configFile);
  return true;
}

