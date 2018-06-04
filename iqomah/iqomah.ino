#include <TimedAction.h>

const int countdown = 60;
/* jika 0 berarti running-text On jika 1 maka off */
int flag_start = 0;

void callMatrix() {
  if(getSeconds() > 0) {
    /* Define message / text LED */
    String text = "";
    
    /* Tampilan menitnya */
    text += getMinutes() < 10 ? "0"+String(getMinutes()) : String(getMinutes());
    
    /* Tampilan untuk sparator */
    text += (getSeconds() % 2)==1 ? ":" : " ";
    
    /* Tampilan detiknya */
    text += getSeconds() < 10 ? "0"+String(getSeconds()) : String(getSeconds());

    /* Export to LED Matrix */
    showMatrix(text);

    /* Increment */
    setSeconds(getSeconds() - 1);
  }

  /* Jika sudah mencapai 0 detik */
  if(getSeconds() == 0) {
    /* Set flag */
    if(flag_start == 0) {
      
      /* clear matrix */
      showMatrix("<-");
      
      /* Beep 3x */
      /* Buzzer menyala terlebih dahulu */
      for(int b = 0; b < 7; b++) {
        buzzerOn();
        delay(1000);
      }
 
      /* Selanjutnya di ikuti dengan tampilan waktu sholat */
      for(int j = 0; j < 2; j++) {
        showMatrix("Waktu Sholat",1);
      }
  
      /* clear matrix */
      showMatrix("");

      /* disabled running-text */
      /* agar text waktu sholat tidak muncul kembali ketika looping */
      flag_start = 1;
    }
    
  }

  if(flag_start == 1) {
    showMatrix("  :  ");
    delay(1000);
    showMatrix("");
    delay(1000);
  }
  
}

void callPush() {
  int push = getPush();
  Serial.println(push);
  if(push == 1) {
    /* reset waktu agar kembali ke posisi awal */
    setSeconds(countdown);
    /* reset start agar kembali ke posisi awal lagi */
    flag_start = 0;
  }
}

TimedAction matrixThread = TimedAction(1000,callMatrix);
TimedAction pushThread = TimedAction(100,callPush);

/* ==============================================================
 * START CORE-MAIN ARDUINO
 * ============================================================ */
void setup() {
  Serial.begin(9600);
  /* konfigurasi hitungan mundur dalam satuan detik */
  /* diubah getSeconds()nya langsung disini */
  setSeconds(countdown);
  matrixSetup();
}

void loop() {
  pushThread.check();
  matrixThread.check();
}

/* ==============================================================
 * END CORE-MAIN ARDUINO
 * ============================================================ */
