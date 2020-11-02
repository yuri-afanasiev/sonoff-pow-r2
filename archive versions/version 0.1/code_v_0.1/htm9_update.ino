void htm9xml(){
 String  url1="<?xml version='1.0'?>";
         url1+="<Donnees>"; 
         url1+="<q1>";
         url1+=rev_code;//rev кода
         url1+="</q1>";
         url1+="</Donnees>"; 
 server.send(200,"text/xml",url1);
} 

void esp_update(String fs_bin,String code_bin) {
     server.send(200, "text/json", "{\"status\":\"1\"}");  
     //Serial.println("Update SPIFFS...");
     ESPhttpUpdate.rebootOnUpdate(false); 
     t_httpUpdate_return ret = ESPhttpUpdate.updateSpiffs(fs_bin);
     save(); 
     save19();
     save20();
     save27();
     save28();
      
     ESPhttpUpdate.rebootOnUpdate(true); 
     if(ret == HTTP_UPDATE_OK) {
        //Serial.println("Update code...");
        ret = ESPhttpUpdate.update(code_bin);
       }
} 
 
 
