void api19() {
     mqw1 = server.arg("on_off").toInt();//on 1/ off 0
     mqw2 = server.arg("server_mqtt");//Cервер MQTT server_mqtt
     mqw3 = server.arg("port").toInt();//Порт port    
     mqw4 = server.arg("username_mqtt");//Логин MQTT username_mqtt
     mqw5 = server.arg("password_mqtt");//Пароль MQTT password_mqtt
     mqw6 = server.arg("name");//Имя  name
     mqw7 = server.arg("group");//Группа group
     save19();//запись в память модуля
     server.send(200, "text/json", "{\"status\":\"1\"}");  
     
}
void openfilehtm19() {
     File configFile = SPIFFS.open("/htm19.json", "r");
     size_t size = configFile.size();
     std::unique_ptr<char[]> buf(new char[size]);
     configFile.readBytes(buf.get(), size);

     DynamicJsonDocument json(2048);
     DeserializationError error = deserializeJson(json, buf.get());
  
             mqw1 = json["d1"];// 
     String mqw2_ = json["d2"];//    
             mqw3 = json["d3"];//  
     String mqw4_ = json["d4"];// 
     String mqw5_ = json["d5"];// 
     String mqw6_ = json["d6"];// 
     String mqw7_ = json["d7"];//
     mqw2=mqw2_;
     mqw4=mqw4_;
     mqw5=mqw5_;
     mqw6=mqw6_;
     mqw7=mqw7_;
} 

bool save19() {
     String output;
     DynamicJsonDocument  json(2048);
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
     serializeJson(json, configFile);
     return true;
}       

void htm19json(){
     String output;
     DynamicJsonDocument  json(2048);
     json["on_off"] = mqw1;//on 1/ off 0
     json["server_mqtt"] = mqw2;//Cервер MQTT 
     json["port"] = mqw3;// 
     json["username_mqtt"] = mqw4;// 
     json["password_mqtt"] = mqw5;// 
     json["name"] = mqw6;// 
     json["group"] = mqw7;// 
     json["device_level"] = top3;//уровень устройства 
     json["room_level"] = top2;//уровень комнаты  
     json["house_level"] = top1;//уровень дома 
     serializeJson(json, output);
     server.send(200, "text/json",output); 
     Serial.println(output);
} 
