/* konstanta satuan permenit dalam detik */
const int minutes = 60;

int seconds = 0;

void setSeconds(int sec) {
  seconds = sec;
}

int getMinutes() {
  return floor(seconds/minutes);
}

int getSeconds() {
  return (seconds % minutes);
}
