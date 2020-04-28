/*
   Контроллер кухни
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  //  библиотека для экрана https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <SI7021.h>  // библиотека для датчика  https://github.com/LowPowerLab/SI7021
LiquidCrystal_I2C lcd(0x27, 20, 4); //  адрес i2c, кол-во символов на строку, кол-во строк
SI7021 sensor;

#define BUTTON_LED 10 //  кнопка для включения LED подсветки
#define RELAY_LED 12   //  реле для включения LED подсветки

boolean value_button_led = false;
boolean flag_button_led = false;
unsigned long time_button_led;

int temperature;
int humidity;
unsigned long time_temp_sensor_SI7021;
unsigned long time_hum_sensor_SI7021;
unsigned int millis_sensor = 10000; //  проверяем датчик темп. и влаж. раз в ... мс


void setup() {
  //Serial.begin(9600);
  lcd.begin();  //  инициализация дисплея
  lcd.backlight();  //  включить подсветку дисплея
  sensor.begin(); //  инициализация датчика температуры и влажности
  pinMode(BUTTON_LED, INPUT_PULLUP);
  pinMode(RELAY_LED, OUTPUT);

  //  статичные элементы дисплея:
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(19, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.setCursor(19, 1);
  lcd.print("%");
}

void loop() {
  /*
     Включаем подсветку столешницы
  */
  value_button_led = digitalRead(BUTTON_LED);
  if (value_button_led == true && millis() - time_button_led > 500) {
    flag_button_led = !flag_button_led;
    digitalWrite(RELAY_LED, flag_button_led);
    time_button_led = millis();
    // Serial.println(flag_button_led);
  }
  /*
     Подключаем датчик температуры и влажности
  */
  //  Получаем температуру:
  temperature = sensor.getCelsiusHundredths();
  temperature = temperature / 100;
  if (temperature && millis() - time_temp_sensor_SI7021 > millis_sensor) {
    //Serial.println(temperature);
    time_temp_sensor_SI7021 = millis();
    lcd.setCursor(17, 0);
    lcd.print(temperature);
  }
  //  Получаем влажность:
  humidity = sensor.getHumidityPercent();
  if (humidity && millis() - time_hum_sensor_SI7021 > millis_sensor) {
    //Serial.println(humidity);
    time_hum_sensor_SI7021 = millis();
    lcd.setCursor(17, 1);
    lcd.print(humidity);
  }
}
