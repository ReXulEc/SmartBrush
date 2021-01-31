#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

//Wifi Settings
const char* ssid = "Wifi Name";
const char* password = "Wifi Password";

//Initialize Telegram-Bot
#define botToken "Bot_Token"  //Bot-Token from Botfather)

//Initialize User Id
#define userID "User_Id"

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

//State of Button
int switchState = 0;

void setup() {
  Serial.begin(115200);
  client.setInsecure();

  // Verwendete Pins
  pinMode(13, INPUT); //We Set The Button's Pin

  //Connect to WiFi
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Bot Connected!");

  bot.sendMessage(userID, "Bot Connected to the Server!", "");
}

void loop() {

  switchState = digitalRead(13);
  Serial.println(switchState);
  if (switchState) {
    bot.sendMessage(userID, "Button pressed.", "");

  }
}
