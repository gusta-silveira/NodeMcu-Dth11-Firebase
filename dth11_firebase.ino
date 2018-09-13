
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DHT.h"

//FIREBASE
#define FIREBASE_HOST "watcherbytrillage.firebaseio.com"
#define FIREBASE_AUTH "dzo5Wp9zYOOHpnGWkfztEtZJ7ItPOhcqmiqRXpu8"
//Wifi
#define WIFI_SSID "Honor 8"
#define WIFI_PASSWORD "92350092"

DHT dht;

void setup()
{
  Serial.begin(9600);
  delay(2000);
  //WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
   while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500); 
   }
   Serial.println();
   Serial.print("connected: ");
   Serial.println(WiFi.localIP());
   
  //FIREBASE  
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  //DHT11
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.setup(D1);   /* D1 is used for data communication */
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());/* Delay of amount equal to sampling period */
  float humidity = dht.getHumidity();/* Get humidity value */
  float temperature = dht.getTemperature();/* Get temperature value */
  Serial.print(dht.getStatusString());/* Print status of communication */
  Serial.print("\t Humidade: ");
  Serial.print(humidity, 1);
  Firebase.setFloat("watchers/-LKRFEqYp05ir7IH6vHD/umi",humidity);
  Serial.print("\t\tTemperatura: ");
  Serial.print(temperature, 1);
  Firebase.setInt("watchers/-LKRFEqYp05ir7IH6vHD/temp",temperature);
  Serial.print("\n");
}
