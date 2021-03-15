#include "ESP8266WiFi.h"


char receivedChar;
char WifiSelect ;
char password[]="1004soclab1004";

int status = WL_IDLE_STATUS;

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
  }
}


void printMacAddress() {
     // the MAC address of your Wifi shield
  byte mac[6];
  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX); 
}

char SSID_Name_Menu[20][33]={};
String SSID_Name ="";
int RSSIval =0;

void setup(){
    Serial.begin(115200);
        
      // Set WiFi to station mode and 
      //disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);

    //disconnect wifi(i.e,initial state)
    WiFi.disconnect();
    delay(100);
    Serial.println("***SYSTEM START***");   
    
     Serial.println("***Scan Start***");                                               
         
               // n =  # of wifi
          int n = WiFi.scanNetworks();
           
          Serial.println("Scan Finish");
          if (n ==0)Serial.println("no networks found");
          else{
               Serial.print(n); 
               Serial.println(" networks had found.");
      
          for(int i = 0;i<n;++i){  
           //SSID_Name_Menu[i] = WiFi.SSID(i);
               SSID_Name = WiFi.SSID(i);
               RSSIval= WiFi.RSSI(i);
              
               //Serial.println(SSID_Name.length());
              //Serial.println(SSID_Name[0]);
              for(int j =0; j<SSID_Name.length();j++){
                SSID_Name_Menu[i][j] = SSID_Name[j];
              }
              Serial.print(i);
              Serial.print(".");
              Serial.print(SSID_Name_Menu[i]);
              Serial.print("\t     Signal: ");
              Serial.print(RSSIval);
              Serial.print(" dBm");
              Serial.print("\tEncryption: ");
              printEncryptionType(WiFi.encryptionType(i));
              
              
        }
        
              // Print WiFi MAC address:
              Serial.print("Your WIFI MAC ");
              printMacAddress();
              Serial.println("Which one do you want to select?"); 
          }                  
}





void loop(){
 
   while(Serial.available()>0){
           ///select wifi 
            //會自己跑兩遍??
            WifiSelect = Serial.read();
                   
            int selectnumber=(int)WifiSelect-48;
            
                 Serial.print("Attempting to connect to SSID: ");
              Serial.println(SSID_Name_Menu[selectnumber]);
          
             status = WiFi.begin(SSID_Name_Menu[selectnumber], password);
            
              Serial.println("You're connected to the network");
              
            
               
    }  
       
                                      
}                 
              
            



