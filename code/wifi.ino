void wifi() {
     WiFi.disconnect();
     WiFi.hostname (device_name);
     if (mesh_on_off == 1){
         WiFi.mode(WIFI_AP_STA);//AP(точка доступа) + STA(клиент) 
        } else {
          WiFi.mode(WIFI_STA);//WIFI_STA(клиент)
        }
     WiFi.begin(w1.c_str(), w2.c_str()); 
     int i = 0;
     while (WiFi.status() != WL_CONNECTED && i < w7) {//w7 Время подключение    
            delay(1000);
            i++;
           }
     if (mesh_on_off == 0){      
         if (WiFi.status() != WL_CONNECTED)  {     
             wifi_ap();    
            }
        } else {
          mesh();
        }
}
void wifi_ap() { 
     WiFi.disconnect();
     WiFi.mode(WIFI_AP);//AP(точка доступа)  
     WiFi.softAP("AFYU_Setting",w4.c_str());
     digitalWrite(13, HIGH);
     wifi_ap_r=1; //wifire=1;
     ap_ticker.attach(600,ap_ticker_triggering);      
      
}
void wifi_connect_test() {
     int iw = 0;  
     if (wifi_ap_r == 0){
         if (WiFi.status() != WL_CONNECTED)  { 
             while (WiFi.status() != WL_CONNECTED && iw< w8) {//w8 Время при reconnect 
                    digitalWrite(13, HIGH); 
                    delay(1000); 
                    digitalWrite(13, LOW);
                    //Serial.print("reconnect ");
                    iw++;
                   }
             wifi_reconnect++;//Количество попыток переподключиться
            }
         if (iw == w8){
             if (mesh_on_off == 1){
                 mesh_sta_connect();
                 mesh();
                } 
            }
       }
} 
void  ap_ticker_triggering(){
      ESP.restart();  
}  
