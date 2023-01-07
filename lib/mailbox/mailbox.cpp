#include "mailbox.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>


ADC_MODE(ADC_VCC);

ESP8266WebServer server(80);
WiFiClient espClient;
IPAddress MQTTserver(192, 100, 100, 1);

const char *host = "HOST";
const char *ssid = "SSID";
const char *password = "PWD";

const uint16_t mqttport = 1883;
const char *mqttusr = "MQTTUSER";
const char *mqttpwd = "MQTTPWD";

float calculatedVoltage;
//MQTT Client
PubSubClient client(MQTTserver, mqttport, espClient);


void getBatteryVoltage(void)
{
  const uint16_t rawVoltage = ESP.getVcc();
  calculatedVoltage = ((float)rawVoltage/1024.0F);
  
  // Check for low battery
  if (calculatedVoltage < 2.5F)
  {
    ESP.deepSleep(0); //Safe Modus for low Voltage
  }
}

uint8_t newMailArrived(void)
{
  const rst_info* resetInfo = system_get_rst_info(); // Read last reset cause
  uint8_t status = 0U;

  if ((resetInfo->reason) == REASON_DEEP_SLEEP_AWAKE)
  {
    status = 1U;
  }
  return status;
}

void enterSleepmode()
{
  //Sleep until reset or POR
  ESP.deepSleep(0, WAKE_RF_DEFAULT);
}

void wifiCon(void)
{
  WiFi.persistent(false);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }
}

void wifiDiscon(void)
{
  WiFi.disconnect();
}

void mqttCon(void)
{
  client.setServer(MQTTserver, mqttport);
  
  while (!client.connected())
  {
    client.connect("ESP8266Client", mqttusr, mqttpwd);
  }
}

void mqttRun(void)
{
  if(newMailArrived() > 0U)
  {
    client.publish("/mailbox/state", "1");
  }
  else
  {
    client.publish("/mailbox/state", "0");    
  }
  
  char msg[10];
  dtostrf(calculatedVoltage, 4, 2, msg);
  client.publish("/mailbox/volt", msg);

  espClient.stop();
}
