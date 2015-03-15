int i;
int a[4];
void setup() {
  Serial.begin(9600);
  interrupts(); // put your setup code here, to run once:
  for (i = 2; i <= 7; i++) {
    pinMode(i, INPUT);
  }
  attachInterrupt(1, ki, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void ki() {
  Serial.println("Interrupcion exitosa");
  int j = 0;
  for (i = 3; i <= 6; i++)
  { if (digitalRead(i) == HIGH) {
      a[j] = 1;
    }    else {
      a[j] = 0;
    } j = j + 1;
  }
  Serial.print(a[0]); Serial.print(a[1]); Serial.print(a[2]); Serial.print(a[3]);
  Serial.write("\n \n \n");
}
