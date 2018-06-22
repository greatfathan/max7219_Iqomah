#include <TimedAction.h>

const int countdown = 420; // 7 menit
const int countdown2 = 600; // 10 menit

/* jika 0 berarti running-text On jika 1 maka off */
int flag_start = 0;

int trigger = 0;
int flag_trigger = 0;

int flag_on = 0;

void callMatrix() {  

  /* untuk menyalakannya tahan tombol power selama 1 detik 
   * agar flag On mempunyai nilai 1 karena harus menunggu 
   * timing dari callMatrix */
  if(flag_on == 0) {
    showMatrix("  :  ");
    delay(1000);
    showMatrix("");
    delay(1000);
    return;
  }

  if(trigger > 0) {
    if(trigger > 2) {
        setCount(countdown2);
    }

    if(trigger < 3) {
      setCount(countdown);
    }

    flag_start = 0;
  }
  
  trigger = 0;
  flag_trigger = 0;
  
  if(getCount() > 0) {    
    
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
    setCount(getCount() - 1);
  }

  /* Jika sudah mencapai 0 detik */
  if(getSeconds() == 0 && getMinutes() == 0) {
    /* Set flag */
    if(flag_start == 0) {
      
      /* clear matrix */
      showMatrix("-");
      
      /* Beep 3x */
      /* Buzzer menyala terlebih dahulu */

        for(int b = 6; b > 0; b--) {
          for (int x = 0 ; x <2; x++) {
            buzzerOn();
            delay(250*b+150); 
          }       
        }
 
      /* Selanjutnya di ikuti dengan tampilan waktu sholat */
      for(int j = 0; j < 5; j++) {
        showMatrix("Waktu Sholat",1);
      }
  
      /* clear matrix */
      showMatrix("-");

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

void incTrigger(){
  trigger = trigger + 1;
}

void callPush() {
  int push = getPush();
  flag_trigger = 0;

  if(push == 1 && flag_trigger == 0) {
    if(flag_trigger == 0) {
      Serial.print("Trigger value is : ");
      Serial.println(trigger);
      incTrigger();
      flag_trigger = 1;
      flag_on = 1;
    }
  }
}

TimedAction matrixThread = TimedAction(1000,callMatrix);
TimedAction pushThread = TimedAction(70,callPush);

/* ==============================================================
 * START CORE-MAIN ARDUINO
 * ============================================================ */
void setup() {
  Serial.begin(9600);
  /* konfigurasi hitungan mundur dalam satuan detik */
  /* diubah getSeconds()nya langsung disini */
  setCount(countdown);
  matrixSetup();
}

void loop() {
  pushThread.check();
  matrixThread.check();
}

/* ==============================================================
 * END CORE-MAIN ARDUINO
 * ============================================================ */
