/*
  This example shows how to program a Telegram Bot
  that provide the surrounding temperature to the user
  The temperature reading is obtained using DHT22. 
  
  Compatible boards:
  Arduino/Genuino mkr1000
  Arduino/Genuino Zero + WiFi shield
*/

#include <WiFi101.h>
#include <SPI.h>
#include <TelegramBot.h>
#include "DHT.h"

// Initialize sensor input pin & DHT sensor type
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

// initialize variables
float temp;
float hum;
float heat_index;

// Initialize Wifi connection to the router
char ssid[] = "****";             // your network SSID (name)
char pass[] = "****";           // your network key

// Initialize Telegram BOT

const char* BotToken = "306990732:AAH9yHYaBch0wUqPp5uJVDz2UHrZ0TaK7As";
const char* BotName = "Jad's MKR1000";     // your Bot Name 
const char* BotUsername = "Jad_MKR1000_bot"; // your Bot User Name 


WiFiSSLClient client;
TelegramBot bot (BotToken,client);

void get_reading(void);  //function to get the temperature reading


void setup() {

  Serial.begin(115200);
  while (!Serial) {}
  delay(3000);


  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");

  bot.begin();
  dht.begin();

}

void loop() {

  message m = bot.getUpdates(); // Read new messages

  if ( m.text.equals("Hi!")) {
    get_reading();
    Serial.println("message received");
    Serial.println(temp);
    if (temp<-0) {
    bot.sendMessage(m.chat_id, "The temperature is too cold. Stay indoor!");
  } else {
      bot.sendMessage(m.chat_id, "Enjoy!");
  }
}
}
void get_reading() {
// Wait a few seconds between measurements.
  delay(2000);
  
  //Read temperature
  temp = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if isnan(temp) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

}
