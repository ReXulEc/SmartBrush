/*
  Mert Doğu | ReXulEc
  github.com/rexulec
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

//Wifi Settings
const char* ssid = "SUPERONLINE_Wi-Fi_8476";
const char* password = "S6RFKCKes7Cu";

#define botToken "1579138550:AAGnj5PIFMVOKFHHzdnM2KJX2jPnh-NvIzQ"  //Bot-Token from Botfather)
#define userID "1002010782"

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

int buzzerpin = 15;
int switchState = 0;

void setup() {
  Serial.begin(115200);
  client.setInsecure();

  // Verwendete Pins
  pinMode(buzzerpin, OUTPUT);
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
    tone(buzzerpin, 1000, 250);
    delay(250);
    tone(buzzerpin, 600, 250);
  }
}
