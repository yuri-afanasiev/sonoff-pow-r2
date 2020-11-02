void button_testing() {
     long currentTime = millis();
     bool currentState = digitalRead(pin_button);

  
 //relay
 if(button_off == 0) {  
     if(currentState == LOW && lastState == HIGH) {
        isOn = !isOn;
        relay_status=isOn;
        task_mqtt_button=1;
        digitalWrite(pin_relay, isOn);
        save27(); 
       }
   }
   
  lastEventTime = currentTime;
  lastState = currentState;
}

void condition() {
if (re1 == 1){ 
        digitalWrite(pin_relay, relay_status);     
         save27();
         } else {
         
        }
}


 
