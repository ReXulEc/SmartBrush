/*
   Dash Button with Telegram and an ESP8266 - polluxlabs.net
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

//Wifi Ayarları Yapıyoruz
const char* ssid = "CHARLESHAANEL";
const char* password = "evcfe7597!";

//Telegram Bot Tokeniizi Giriyoruz
#define botToken "1579138550:AAGnj5PIFMVOKFHHzdnM2KJX2jPnh-NvIzQ"  //Bot-Token from Botfather)

//User ID'mizi giriyoruz
#define userID "1002010782"

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

//Butonun durumunu ayarlıyoruz
int switchState = 0;

void setup() {
  Serial.begin(115200);
  client.setInsecure();

  // Verwendete Pins
  pinMode(13, INPUT); //Buttonun Pinini Ayarlıyoruz

  //Connect to WiFi
  Serial.print("Bağlanılan ağ: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Bot İnternete Bağlandı!");

  bot.sendMessage(userID, "Bot Servere Bağlandı.", "");
}

void loop() {

  switchState = digitalRead(13);
  Serial.println(switchState);
  if (switchState) {
    bot.sendMessage(userID, "Test123", "");

  }
}
