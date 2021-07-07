#include "TM1637.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define LED_CLK 2
#define LED_DIO 3
#define PIN_SENSOR_WATER 7

TM1637 led(LED_CLK, LED_DIO);
OneWire ourWire(PIN_SENSOR_WATER);
DallasTemperature sensor(&ourWire);

unsigned char ledPoint = 1;
int actualTemperature = 0;

void setup()
{
  Serial.begin(9600);
  sensor.begin();
  
  led.init();
  // BRIGHT_TYPICAL = 2, BRIGHT_DARKEST = 0, BRIGHTEST = 7
  led.set(BRIGHT_TYPICAL);
}

void loop()
{
  showIntro();

  getTemperature();

  showTemperature();

  delay(500);  
}

void showIntro()
{  
  for (int i=0; i<10; i++)
  {
    led.point(ledPoint);
    ledPoint = (~ledPoint) & 0x01;
    led.clearDisplay();
    delay(50);
  }

  led.point(POINT_OFF);
  led.clearDisplay();
}

void getTemperature(void)
{
  sensor.requestTemperatures();

  actualTemperature = sensor.getTempCByIndex(0);

  Serial.print("Temperatura: ");
  Serial.print(actualTemperature);
  Serial.println(" *c");
  delay(200);
}

void showTemperature(void)
{
  led.display(3, 12); // C
  led.display(0, actualTemperature / 10); // primeiro digito
  led.display(1, actualTemperature % 10); // segundo digito

  delay(2000);
}
