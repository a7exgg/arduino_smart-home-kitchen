/*
 * Контроллер кухни
 */
#define BUTTON_LED 10 //  кнопка для включения LED подсветки
#define RELAY_LED 12   //  реле для включения LED подсветки

boolean value_button_led = false;
boolean flag_button_led = false;
unsigned long time_button_led;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_LED, INPUT_PULLUP);
  pinMode(RELAY_LED, OUTPUT);
}

void loop() {
  /*
   * Включаем подсветку столешницы
   */
  value_button_led = digitalRead(BUTTON_LED);
  if(value_button_led == true && millis() - time_button_led > 500) {
    flag_button_led = !flag_button_led;
    digitalWrite(RELAY_LED, flag_button_led);
    time_button_led = millis();
    Serial.println(flag_button_led);
  }
}
