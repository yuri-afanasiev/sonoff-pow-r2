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
}

