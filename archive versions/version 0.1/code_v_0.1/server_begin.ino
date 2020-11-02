void serveron() {
  server.on("/esp_update", []() { //Обнавление
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    String fs_bin_test = server.arg("fs_bin");//fs
    String code_bin_test = server.arg("code_bin");//code
    esp_update(fs_bin_test, code_bin_test);
  });

  server.on("/config", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    testjson();
  });
  
  server.on("/xml9", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    htm9xml();
  });

  server.on("/json19", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    htm19json();
  });

  server.on("/json20", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    htm20json();
  });


  server.on("/api", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    api();
  });

  server.on("/api20", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    api20();
  });
  
  server.on("/sending_data", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    api28();
  });

  server.on("/sending_data_json", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    htm28json();
  });  

  server.on("/reset", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    server.send(200, "text/json", "{\"status\":\"1\"}");
    ESP.restart();
  });

  server.on("/relay/on", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    if (re1 == 1) {
      relay_status = 1;
      save27();
    }
    digitalWrite(pin_relay, HIGH);
    if (mqw1 == 1) {
      mqttclient.publish(top3 + "sonoff-pow2/status", "{\"status\":\"1\",\"activated\":\"1\"}"); //status 1-on activated 1-web
    }
    server.send(200, "text/json", "{\"status\":\"1\",\"activated\":\"1\"}"); //status 1-on activated 1-web
  });

  server.on("/relay/off", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    if (re1 == 1) {
      relay_status = 0;
      save27();
    }
    digitalWrite(pin_relay, LOW);
    if (mqw1 == 1) {
      mqttclient.publish(top3 + "sonoff-pow2/status", "{\"status\":\"0\",\"activated\":\"1\"}"); //status 0-off activated 1-web
    }
    server.send(200, "text/json", "{\"status\":\"0\",\"activated\":\"1\"}"); //status 0-off activated 1-web
  });

  server.on("/api19", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    api19();
  });

  server.on("/led/off", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    digitalWrite(pin_green_led, HIGH);
    led_status = 0;
    if (mqw1 == 1) {
      mqttclient.publish(top3 + "sonoff-pow2/led/status", "{\"status\":\"0\",\"activated\":\"1\"}"); //status 0-off activated 1-web
    }
    server.send(200, "text/json", "{\"status\":\"0\",\"activated\":\"1\"}"); //status 0-off activated 1-web
  });


  server.on("/led/on", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    digitalWrite(pin_green_led, LOW);
    led_status = 1;
    if (mqw1 == 1) {
      mqttclient.publish(top3 + "sonoff-pow2/led/status", "{\"status\":\"1\",\"activated\":\"1\"}"); //status 1-on activated 1-web
    }
    server.send(200, "text/json", "{\"status\":\"1\",\"activated\":\"1\"}");//status 1-on activated 1-web
  });

  server.on("/energy", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    
    String url;
    url += "{\"voltage\":\"";
    url += sensor_CSE7766.getVoltage();
    url += "\",\"current\":\"";
    url += sensor_CSE7766.getCurrent();
    url += "\",\"active_power\":\"";
    url += sensor_CSE7766.getActivePower();
    url += "\",\"apparent_power\":\"";
    url += sensor_CSE7766.getApparentPower();
    url += "\",\"reactive_power\":\"";
    url += sensor_CSE7766.getReactivePower();
    url += "\",\"power_factor\":\"";
    url += sensor_CSE7766.getPowerFactor();
    url += "\",\"energy\":\"";
    url += sensor_CSE7766.getEnergy();
    url +=  "\"}";
    server.send(200, "text/json", url);
  });
  server.on("/status", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    String url;
    url += "{\"relay\":\"";
    url += relay_status;
    url += "\",\"led\":\"";
    url += led_status;
    url += "\",\"button\":\"";
    url += button_status;
    url += "\",\"version\":\"";
    url += rev_code;
    url +=  "\"}";
    server.send(200, "text/json", url);
  });

  server.on("/button/off", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    button_off = 1;
    button_status = 0;
    if (mqw1 == 1) {
      mqttclient.publish(top3 + "sonoff-pow2/button/status", "{\"status\":\"0\",\"activated\":\"1\"}"); //status 0-off activated 1-web
    }
    server.send(200, "text/json", "{\"status\":\"0\",\"activated\":\"1\"}"); //status 0-off activated 1-web
  });

  server.on("/button/on", []() {
    if (!server.authenticate(w5.c_str(), w6.c_str()))
      return server.requestAuthentication();
    button_off = 0;
    button_status = 1;
    if (mqw1 == 1) {
      mqttclient.publish(top3 + "sonoff-pow2/button/status", "{\"status\":\"1\",\"activated\":\"1\"}"); //status 1-on activated 1-web
    }
    server.send(200, "text/json", "{\"status\":\"1\",\"activated\":\"1\"}"); //status 1-on activated 1-web
  });

  server.on("/config.json", []() {
    server.send(403, "text/plain", "Forbidden");
  });

  server.on("/htm19.json", []() {
    server.send(403, "text/plain", "Forbidden");
  });


  server.onNotFound([]() {
    if (!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });
  server.on("/list", HTTP_GET, handleFileList);
  server.on("/edit", HTTP_GET, []() {
    if (!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
  });
  server.on("/edit", HTTP_PUT, handleFileCreate);
  server.on("/edit", HTTP_DELETE, handleFileDelete);
  server.on("/edit", HTTP_POST, []() {
    server.send(200, "text/plain", "");
  }, handleFileUpload);
  server.begin();

}
