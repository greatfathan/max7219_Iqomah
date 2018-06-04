/* 
 *  KONFIGURASI PIN BUZZER
 */
#define PIN_BUZZER 8

void buzzerOn() {
  tone(PIN_BUZZER, 1200, 600);
}



