//-- Libraries Included --------------------------------------------------------------
  #include <ESP8266WiFi.h>
//------------------------------------------------------------------------------------
  // Define I/O Pins
  #define     LED1      D0          // Connectivity With Client #1
//------------------------------------------------------------------------------------
  // Authentication Variables
  char*       TKDssid;              // SERVER WIFI NAME
  char*       TKDpassword;          // SERVER PASSWORD

  IPAddress    apIP(192, 168, 10, 1);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1
//------------------------------------------------------------------------------------
  WiFiServer  TKDServer(9001);      // THE SERVER AND THE PORT NUMBER
  WiFiClient  TKDClient;     // THE SERVER CLIENTS
//====================================================================================
void setup() {
    // Setting The Serial Port
    Serial.begin(115200);           // Computer Communication
    
    // Setting The Mode Of Pins
    pinMode(LED1, OUTPUT);          // Indicator For Client #1 Connectivity

    
    // Print Message Of I/O Setting Progress
    Serial.println();
    Serial.println("I/O Pins Modes Set .... Done");

    // Setting Up A Wifi Access Point
    SetWifi("TAKEONE", "");

}

void loop() {
      IsClients();
}
//====================================================================================
  
  void SetWifi(char* Name, char* Password)
  {
    // Stop Any Previous WIFI
    WiFi.disconnect();

    // Setting The Wifi Mode
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00 
    Serial.println("WIFI Mode : AccessPoint Station");
    
    // Setting The Access Point
    TKDssid      = Name;
    TKDpassword  = Password;
    
    // Starting The Access Point
    WiFi.softAP(TKDssid, TKDpassword);
    Serial.println("WIFI < " + String(TKDssid) + " > ... Started");
    
    // Wait For Few Seconds
    delay(1000);
    
    // Getting Server IP
    IPAddress IP = WiFi.softAPIP();
    
    // Printing The Server IP Address
    Serial.print("AccessPoint IP : ");
    Serial.println(IP);

    // Starting Server
    TKDServer.begin();
    Serial.println("Server Started");
  }

//====================================================================================

  void IsClients()
  {
    if(TKDServer.hasClient())
    {
      WiFiClient TKDClient = TKDServer.available();
      
      digitalWrite(LED1, HIGH);

      while(1)
      {

        //--[ Draft ] ---------------------------------------------------

        
              
        //---------------------------------------------------------------
        // If Clients Are Connected 
        //---------------------------------------------------------------
        
        if(TKDClient.available())
        {
          // Here We Read The Message
          String Message = TKDClient.readStringUntil('\r');
          // Here We Print The Message On The Screen
          Serial.println(Message);
          // Here We Reply To The Client With A Message
          TKDClient.print("\nWe Got Your Message");
          TKDClient.flush();
        }
        
        //---------------------------------------------------------------
        // If Clients Are Disconnected
        //---------------------------------------------------------------
        
        if(!TKDClient || !TKDClient.connected())
        {
          // Here We Turn Off The LED To Indicated The Its Disconnectted
          digitalWrite(LED1, LOW);
          // Here We Jump Out Of The While Loop
          break;
        }

        //----------------------------------------------------------------
        
      }
      
    }
    else
    {
      // This LED Blinks If No Clients Where Available
      digitalWrite(LED1, HIGH);
      delay(250);
      digitalWrite(LED1, LOW);
      delay(250);
    }
  }

//====================================================================================
