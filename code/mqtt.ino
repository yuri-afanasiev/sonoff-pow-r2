void mqtt_connect(){// подключение к MQTT серверу
     mqttclient.set_server(mqw2,mqw3);      
     if (mqttclient.connect(MQTT::Connect(mqw6).set_auth(mqw4.c_str(), mqw5.c_str()))) {
         mqttclient.set_callback(callback);
         //Serial.println("Connected to MQTT server ");
         // подписываемся под топики
         //mqttclient.subscribe("/home/#");
          mqttclient.subscribe(top3 + "sonoff-pow2/relay");
          mqttclient.subscribe(top2 + "sonoff-pow2/relay");
          mqttclient.subscribe(top1 + "sonoff-pow2/relay");

          mqttclient.subscribe(top3 + "sonoff-pow2/led");
          mqttclient.subscribe(top2 + "sonoff-pow2/led");
          mqttclient.subscribe(top1 + "sonoff-pow2/led");

          mqttclient.subscribe(top3 + "sonoff-pow2/button");
          mqttclient.subscribe(top2 + "sonoff-pow2/button");
          mqttclient.subscribe(top1 + "sonoff-pow2/button");

          mqttclient.subscribe(top3 + "sonoff-pow2/status");

          mqttclient.subscribe(top3 + "sonoff-pow2/reset");
          mqttclient.subscribe(top2 + "sonoff-pow2/reset");
          mqttclient.subscribe(top1 + "sonoff-pow2/reset");
          
          mqttclient.subscribe(top3 + "sonoff-pow2/update");
          
          mqttclient.subscribe(top3 + "sonoff-pow2/save_state");

          mqttclient.subscribe(top3 + "sonoff-pow2/energy");
          
          
        } 
}
 
