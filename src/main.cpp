#include <Arduino.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "";
const char *password = "";

const long utcOffset = 0;

WiFiUDP ntp;
NTPClient timeClient(ntp, "pool.ntp.org", 6 * 3600, 5 * 3600);

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected...");

  timeClient.begin();

  timeClient.setTimeOffset(2 * 3600);
}

int counter = 0;
void loop()
{
  // timeClient.update();

  // Serial.print("Day: ");
  // Serial.print(timeClient.getDay());
  // Serial.print("    Hours: ");
  // Serial.print(timeClient.getHours());
  // Serial.print("    Minutes: ");
  // Serial.print(timeClient.getMinutes());
  // Serial.print("    Seconds: ");
  // Serial.println(timeClient.getSeconds());

  counter += 1;

  if (counter % 5 == 0)
  {
    while (!timeClient.update())
    {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
  }

  Serial.print(timeClient.getFormattedTime());
  if (timeClient.isTimeSet())
    Serial.println(" updated");
  else
    Serial.println(" not updated");

  delay(1000);
}
