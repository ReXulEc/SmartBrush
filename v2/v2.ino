/*
  Mert Doğu | ReXulEc
  github.com/rexulec
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

//Wifi Settings
const char* ssid = "xxxxxxxxxxxxxxxxxxxx";
const char* password = "xxxxxxxxx";

#define botToken "xxxxxxxxxxxxxxxxxxxxxxxx"  //Bot-Token from Botfather)
#define userID "xxxxxxxxx"

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

int buzzerpin = 15;
int sendMessageState = 0;
int alarmState = 0;

// Slash commands

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

unsigned long bot_lasttime; // last time messages' scan has been done
X509List cert(TELEGRAM_CERTIFICATE_ROOT);

void handleNewMessages(int numNewMessages)
{
  
  String answer;
  for (int i = 0; i < numNewMessages; i++)
  {
    telegramMessage &msg = bot.messages[i];
    Serial.println("Received " + msg.text + " from " + msg.from_name);
    if (msg.text == "/help")
      answer = "Yardıma mı ihtiyacınız var?\nAktif olan konumlar:\n/github , /durum";
    else if (msg.text == "/start")
      answer = "Merhaba *" + msg.from_name + "*.\nEğer bir sorun var ise lütfen @rexulec adresine sorunu bildirin\n/help";
    else if (msg.text == "/durum")
      answer = "💻: ✅\n📶: ✅";
    else if (msg.text == "/github")
      answer = "https://github.com/rexulec/SmartBrush";
    else
      answer = "Ne dediğini anlayamıyorum. Lütfen /help 'i veya /yardim 'ı kullanmayı dene.";

    bot.sendMessage(msg.chat_id, answer, "Markdown");
  }
}

// Slash Commands ending

void setup() {
  Serial.begin(115200);
  client.setInsecure();

  // Verwendete Pins
  pinMode(buzzerpin, OUTPUT);
  pinMode(13, INPUT); //We Set The Button's Pin
  pinMode(12, INPUT);

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

  bot.sendMessage(userID, "status:on", "");
}

void loop() {

  sendMessageState = digitalRead(13);
  if (sendMessageState) {
    Serial.println("13");
    bot.sendMessage(userID, "Sonuç: Çocuğunuz dişini fırçaladı/fırçalamaya başladı.", "");
  }

  alarmState = digitalRead(12);
  if (alarmState) {
    Serial.println("12");
    delay(10000);
    bot.sendMessage(userID, "Uyarı: Çocuğunuzun Diş Fırçalama Vakti Geldi.", "");
    tone(buzzerpin, 1000, 250);
    delay(250);
    tone(buzzerpin, 600, 250);
    delay(1000);
    tone(buzzerpin, 1000, 250);
    delay(250);
    tone(buzzerpin, 600, 250);
    delay(1000);
    tone(buzzerpin, 1000, 250);
    delay(250);
    tone(buzzerpin, 600, 250);
  }

    if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("warn: new message");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
