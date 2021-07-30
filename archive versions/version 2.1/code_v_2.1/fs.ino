String formatBytes(size_t bytes){
       if (bytes < 1024){
           return String(bytes)+"B";
          } else if(bytes < (1024 * 1024)){
                    return String(bytes/1024.0)+"KB";
                    } else if(bytes < (1024 * 1024 * 1024)){
                              return String(bytes/1024.0/1024.0)+"MB";
                              } else {
                                      return String(bytes/1024.0/1024.0/1024.0)+"GB";
                                     }
}

String getContentType(String filename){
       if(server.hasArg("download")) return "application/octet-stream";
          else if(filename.endsWith(".htm")) return "text/html";
          else if(filename.endsWith(".html")) return "text/html";
          else if(filename.endsWith(".css")) return "text/css";
          else if(filename.endsWith(".js")) return "application/javascript";
          else if(filename.endsWith(".png")) return "image/png";
          else if(filename.endsWith(".json")) return "text/json";
          else if(filename.endsWith(".gif")) return "image/gif";
          else if(filename.endsWith(".jpg")) return "image/jpeg";
          else if(filename.endsWith(".ico")) return "image/x-icon";
          else if(filename.endsWith(".xml")) return "text/xml";
          else if(filename.endsWith(".pdf")) return "application/x-pdf";
          else if(filename.endsWith(".zip")) return "application/x-zip";
          else if(filename.endsWith(".gz")) return "application/x-gzip";
          return "text/plain";
}

bool handleFileRead(String path){  
     Serial.println("handleFileRead: " + path);
     if(path.endsWith("/")) path += "index.htm";
        String contentType = getContentType(path);
        String pathWithGz = path + ".gz";
        if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
           if(SPIFFS.exists(pathWithGz))
              path += ".gz";
              File file = SPIFFS.open(path, "r");
              size_t sent = server.streamFile(file, contentType);
              file.close();
              return true;
             }
        return false;
}
