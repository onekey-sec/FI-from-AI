
float i,j,k,cnt;
void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    if (Serial.read() == 'A')
    {
      digitalWrite(2, HIGH);   // start of trigger
      cnt = 0;
      for(i=0; i<500; i++){   // some loop adding the value of cnt
        for(j=0; j<500; j++){
            cnt++;
        }
      }
      digitalWrite(2, LOW);   // end of trigger
      Serial.println(cnt);
    }
}
}
