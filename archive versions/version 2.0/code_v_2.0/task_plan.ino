void task_plan() {
     if (thingspeak_ticker_test == 1){
         thingspeak(); 
         thingspeak_ticker_test=0;
        }
     if (narodmon_ticker_test == 1){
         narodmon();
         narodmon_ticker_test=0;
        }
     if (your_server_test == 1){
         your_server();
         your_server_test=0;
        }
     if (one_minute_test == 1){
         one_minute=0;
         one_minute_test=0;
        }

     if (mqw1 == 1) { // 
         if (task_mqtt_button == 1){//
             if (relay_status == 1){
                 mqttclient.publish(top3 + "/relay/status","{\"status\":\"1\",\"activated\":\"0\"}");//status 1-on activated 0-кнопка );
                 task_mqtt_button=0;
                 }else {
                  mqttclient.publish(top3 + "/relay/status","{\"status\":\"0\",\"activated\":\"0\"}");//status 0-off activated 0-кнопка );
                  task_mqtt_button=0;
                }
             }
/*
     if (one_minute == 4){
             isled = !isled;
             if (isled == true){
                 mqttclient.publish("", "");
                 }else {
                 mqttclient.publish("", "");
                }
             one_minute=0;
            } 
*/
         }   
}
