void mesh() {
     WiFi.mode(WIFI_AP_STA);
     // Инициализировать функцию NAT
       ip_napt_init(IP_NAPT_MAX, IP_PORTMAP_MAX);
     // Включить NAT на интерфейсе AP 0 = STA, 1 = AP
       ip_napt_enable_no(1, 1);

     ip[0]=192;
     ip[1]=168;
     ip[2]=1;
     ip[3]=1; 
          
     ip_ap[0]=192;//разлача wifi 
     ip_ap[1]=168;
     ip_ap[2]= WiFi.gatewayIP()[2]+1;
     ip_ap[3]=1; 
     
     WiFi.softAPConfig(ip_ap, ip_ap, subnet_ap);
     WiFi.softAP(w3.c_str(),w4.c_str(),6,mesh_hidden_ssid,mesh_max_connection);
}
void mesh_sta_connect() {
     WiFi.begin(w3.c_str(), w4.c_str()); 
     int i = 0;
     while (WiFi.status() != WL_CONNECTED && i < w7) {//w7 Время подключение    
            delay(1000);
            i++;
           }
 
}
