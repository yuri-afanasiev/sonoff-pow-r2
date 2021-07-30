void mqtt_connect(String mqtt_server ,int mqtt_port,String mqtt_name,String mqtt_username,String mqtt_password){// подключение к MQTT серверу
     mqttclient.set_server(mqtt_server,mqtt_port);      
     if (mqttclient.connect(MQTT::Connect(mqtt_name).set_auth(mqtt_username.c_str(), mqtt_password.c_str()))) {
         mqttclient.set_callback(callback);
         Serial.println("Connected to MQTT server ");
         // подписываемся под топики
         //mqttclient.subscribe("/home/#");
       
          mqttclient.subscribe(top3 + "/relay");
          mqttclient.subscribe(top2 + "/relay");
          mqttclient.subscribe(top1 + "/relay");
          
          mqttclient.subscribe(top3 + "/relay/timer");
          mqttclient.subscribe(top3 + "/relay/timer/off");

          mqttclient.subscribe(top3 + "/led");
          mqttclient.subscribe(top2 + "/led");
          mqttclient.subscribe(top1 + "/led");

          mqttclient.subscribe(top3 + "/button");
          mqttclient.subscribe(top2 + "/button");
          mqttclient.subscribe(top1 + "/button");

          mqttclient.subscribe(top3 + "/status");

          mqttclient.subscribe(top3 + "/reset");
          mqttclient.subscribe(top2 + "/reset");
          mqttclient.subscribe(top1 + "/reset");
          
          mqttclient.subscribe(top3 + "/update");
          
          mqttclient.subscribe(top3 + "/save_state");
         
          mqttclient.subscribe(top3 + "/energy");

          mqttclient.subscribe(top3 + "/mesh/get");
          mqttclient.subscribe(top3 + "/mesh/get");
         
        } 
}
  
