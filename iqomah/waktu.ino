/* konstanta satuan permenit dalam detik */
const int minutes = 60;

int seconds = 0;

void setCount(int sec) {
  seconds = sec;
}

int getCount(){
  return seconds;
}

int getSeconds() {
  return (int)(seconds - getMinutes() * 60) ;
}

int getMinutes() {
  return (int)floor(seconds/60);
}

