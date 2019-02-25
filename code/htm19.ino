void api19() {
     mqw1 = server.arg("on_off").toInt();//on 1/ off 0
     mqw2 = server.arg("server_mqtt"); //  сервер MQTT server_mqtt
     mqw3 = server.arg("port").toInt(); //    Порт port    
     mqw4 = server.arg("username_mqtt"); //   Логин MQTT username_mqtt
     mqw5 = server.arg("password_mqtt"); //  Пароль MQTT password_mqtt
     mqw6 = server.arg("name"); //имя  name
     mqw7 = server.arg("group"); //Группа group
     save19();//  запись в память модуля
     server.send(200, "text/json", "{\"status\":\"1\"}");  
     ESP.restart(); 
}
void openfilehtm19() {
  File configFile = SPIFFS.open("/htm19.json", "r");
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
        mqw1 = json["d1"];// 
  String ee2 = json["d2"];//    
        mqw3 = json["d3"];//  
  String ee4 = json["d4"];// 
  String ee5 = json["d5"];// 
  String ee6 = json["d6"];// 
  String ee7 = json["d7"];//
  mqw2=ee2;
  mqw4=ee4;
  mqw5=ee5;
  mqw6=ee6;
  mqw7=ee7;
} 

bool save19() {
  DynamicJsonBuffer  jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["d1"] = mqw1;// 
  json["d2"] = mqw2;// 
  json["d3"] = mqw3;// 
  json["d4"] = mqw4;// 
  json["d5"] = mqw5;// 
  json["d6"] = mqw6;// 
  json["d7"] = mqw7;//
  
  File configFile = SPIFFS.open("/htm19.json", "w");
  if (!configFile) {   
    return false;
  }
  json.printTo(configFile);
  return true;
}       

void htm19json(){
       String url;   
              url += "{\"on_off\":\""; 
              url+=mqw1;
              url += "\",\"server_mqtt\":\"";
              url+=mqw2;
              url += "\",\"port\":\"";
              url+=mqw3;
              url += "\",\"username_mqtt\":\"";
              url+=mqw4;
              url += "\",\"password_mqtt\":\"";
              url+=mqw5;
              url += "\",\"name\":\"";
              url+=mqw6;
              url += "\",\"group\":\"";
              url+=mqw7;
              url += "\",\"device_level\":\"";
              url+=top3 + "sonoff-pow2";// уровень устройства
              url += "\",\"room_level\":\"";
              url+=top2 + "sonoff-pow2";// уровень комнаты 
              url += "\",\"house_level\":\"";
              url+=top1 + "sonoff-pow2";// уровень дома
              url +=  "\"}"; 
server.send(200, "text/json",url); 
} 

   
