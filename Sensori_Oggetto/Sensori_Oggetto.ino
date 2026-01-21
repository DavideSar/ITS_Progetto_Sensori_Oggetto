//pin definition
int OP_Sensor = 13;
int IN_Sensor = 12;
int OBJ_Led = 4;
int MET_Led = 3;
int ERR_Led = 2;

void setup() {

  Serial.begin(115200);
  pinMode(OP_Sensor, INPUT);
  pinMode(IN_Sensor, INPUT);
  pinMode(OBJ_Led, OUTPUT);
  pinMode(MET_Led, OUTPUT);
  pinMode(ERR_Led, OUTPUT);

}

void loop() {

  delay(500);

  int OP_input = digitalRead(OP_Sensor);
  int IN_input = digitalRead(IN_Sensor);

  if (OP_input == LOW && IN_input == HIGH){

    Serial.println("DETECTED: metallic object");
    digitalWrite(ERR_Led, LOW);
    digitalWrite(OBJ_Led, HIGH);
    digitalWrite(MET_Led, HIGH);

  } else if (OP_input == LOW && IN_input == LOW){

    Serial.println("DETECTED: non metallic object");
    digitalWrite(ERR_Led, LOW);
    digitalWrite(OBJ_Led, HIGH);
    digitalWrite(MET_Led, LOW);

  } else if (OP_input == HIGH && IN_input == LOW){

    Serial.println("NOT DETECTED");
    digitalWrite(ERR_Led, LOW);
    digitalWrite(OBJ_Led, LOW);
    digitalWrite(MET_Led, LOW);

  } else if (OP_input == HIGH && IN_input == HIGH){

    Serial.println("ERROR: detected electromagnetic field but no object present");
    digitalWrite(ERR_Led, HIGH);
    digitalWrite(OBJ_Led, LOW);
    digitalWrite(MET_Led, LOW);
    
  } else {

    Serial.println("ERROR: general error. check if everything is correctly connected");
    digitalWrite(ERR_Led, HIGH);
    digitalWrite(OBJ_Led, LOW);
    digitalWrite(MET_Led, LOW);

  }
}
