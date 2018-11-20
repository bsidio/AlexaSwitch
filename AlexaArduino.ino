#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"

// prototypes
boolean connectWifi();

//on/off callbacks 
bool mbedroomLightsOn();
bool mbedroomLightsOff();
bool bedroomLightsOn();
bool bedroomLightsOff();
bool kitchenLightsOn();
bool kitchenLightsOff();
bool bathroomLightsOn();
bool bathroomLightsOff();


// Change this before you flash
const char* ssid = "******"; //WIFI SSID
const char* password = "*****"; //WIFI PASSWORD

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

//Add Switch Names

Switch *mbedroom = NULL;
Switch *mbedroomz = NULL;
Switch *bedroom = NULL;
Switch *bathroom = NULL;
Switch *bedroomz = NULL;
Switch *passage = NULL;

//Assign PINS
const int S3 = D5; //passage
const int S2 = D6; //bedroom
const int S1 = D2; //mbed
const int S4 = D4; //bath
const int S5 = D1; //mbz
const int S6 = D2;
const int S7 = D1;
const int S8 = D7; //bz






bool ismbedroomLightsOn = false;
bool ismbedroomzLightsOn = false;
bool isbedroomLightsOn = false;
bool isbedroomzLightsOn = false;
bool isbathroomLightsOn = false;
bool ispassageLightsOn = false;


void setup()
{
  Serial.begin(9600);
   pinMode (S1, OUTPUT);
   pinMode (S2, OUTPUT);
   pinMode (S3, OUTPUT);
   pinMode (S4, OUTPUT);
   pinMode (S5, OUTPUT);
   pinMode (S6, OUTPUT);
   pinMode (S7, OUTPUT);
   pinMode (S8, OUTPUT);

   
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    upnpBroadcastResponder.beginUdpMulticast();
    
    // Define your switches here. Max 10
    // Format: Alexa invocation name, local port no, on callback, off callback
    mbedroom = new Switch("Master Bedroom lights", 80, mbedroomLightsOn, mbedroomLightsOff);
    mbedroomz = new Switch("Master Bedroom Zero lights", 85, mbedroomzLightsOn, mbedroomzLightsOff);
    bedroom = new Switch("Bedroom lights", 81, bedroomLightsOn, bedroomLightsOff);
    bedroomz = new Switch("Bedroom zero lights", 82, bedroomzLightsOn, bedroomzLightsOff);
    bathroom = new Switch("Bathroom lights", 83, bathroomLightsOn, bathroomLightsOff);
    passage = new Switch("Passage lights", 84, passageLightsOn, passageLightsOff);



    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*mbedroom);
    upnpBroadcastResponder.addDevice(*mbedroomz);
    upnpBroadcastResponder.addDevice(*bedroom);
    upnpBroadcastResponder.addDevice(*bathroom);
    upnpBroadcastResponder.addDevice(*bedroomz);
    upnpBroadcastResponder.addDevice(*passage);



  }
}
 
void loop()
{
	 if(wifiConnected){
      upnpBroadcastResponder.serverLoop();
      
      mbedroom->serverLoop();
      mbedroomz->serverLoop();
      bedroom->serverLoop();
      bathroom->serverLoop();
      bedroomz->serverLoop();
      passage->serverLoop();

	 }
}

bool  passageLightsOn() {
    Serial.println("Switch 1 turn on ...");
    digitalWrite (S3, HIGH); 
    ispassageLightsOn = true;    
    return ispassageLightsOn;
}

bool  passageLightsOff() {
    Serial.println("Switch 1 turn off ...");
     digitalWrite (S3, LOW); 
    ispassageLightsOn = false;
    return ispassageLightsOn;
}

bool  mbedroomLightsOn() {
    Serial.println("Switch 1 turn on ...");
    digitalWrite (S1, HIGH); 
    ismbedroomLightsOn = true;    
    return ismbedroomLightsOn;
}

bool  mbedroomLightsOff() {
    Serial.println("Switch 1 turn off ...");
     digitalWrite (S1, LOW); 
    ismbedroomLightsOn = false;
    return ismbedroomLightsOn;
}
bool  mbedroomzLightsOn() {
    Serial.println("Switch 1 turn on ...");
    digitalWrite (S5, HIGH); 
    ismbedroomzLightsOn = true;    
    return ismbedroomzLightsOn;
}

bool  mbedroomzLightsOff() {
    Serial.println("Switch 1 turn off ...");
     digitalWrite (S5, LOW); 
    ismbedroomzLightsOn = false;
    return ismbedroomzLightsOn;
}

bool  bedroomLightsOn() {
    Serial.println("Switch 2 turn on ...");
    digitalWrite (S2, HIGH); 
    isbedroomLightsOn = true;    
    return isbedroomLightsOn;
}

bool  bedroomLightsOff() {
    Serial.println("Switch 2 turn off ...");
     digitalWrite (S2, LOW); 
    isbedroomLightsOn = false;
    return isbedroomLightsOn;
}

bool bedroomzLightsOn() {
    Serial.println("Switch 3 turn on ...");
     digitalWrite (S8, HIGH); 

    isbedroomzLightsOn = true;
    return isbedroomzLightsOn;
}

bool bedroomzLightsOff() {
  Serial.println("Switch 3 turn off ...");
     digitalWrite (S8, LOW); 

  isbedroomzLightsOn = false;
  return isbedroomzLightsOn;
}

bool bathroomLightsOn() {
    Serial.println("Switch 4 turn on ...");
     digitalWrite (S4, HIGH); 

    isbathroomLightsOn = true;
    return isbathroomLightsOn;
}

bool bathroomLightsOff() {
  Serial.println("Switch 4 turn off ...");
     digitalWrite (S4, LOW); 

  isbathroomLightsOn = false;
  return isbathroomLightsOn;
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }
  
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}
