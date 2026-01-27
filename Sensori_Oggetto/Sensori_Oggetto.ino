int time = 500;       // delay

int OP_Sensor = 13;   // optical sensor
int IN_Sensor = 12;   // inductive sensor
int OBJ_Led = 4;      // green led for object detected
int MET_Led = 3;      // yellow led for metallic detected
int ERR_Led = 2;      // red led for error status

void setup() {

  Serial.begin(115200);

  // pin mode definition
  pinMode(OP_Sensor, INPUT);
  pinMode(IN_Sensor, INPUT);
  pinMode(OBJ_Led, OUTPUT);
  pinMode(MET_Led, OUTPUT);
  pinMode(ERR_Led, OUTPUT);

}

void loop() {

  delay(time);

  //  read sensor state
  int OP_input = digitalRead(OP_Sensor);
  int IN_input = digitalRead(IN_Sensor);

  if (OP_input == LOW && IN_input == HIGH){                 // op sensor and in sensor both detected

    Serial.println("DETECTED: metallic object");
    digitalWrite(ERR_Led, LOW);
    digitalWrite(OBJ_Led, HIGH);
    digitalWrite(MET_Led, HIGH);

  } else if (OP_input == LOW && IN_input == LOW){           // op sensor detects, in sensor no

    Serial.println("DETECTED: non metallic object");
    digitalWrite(ERR_Led, LOW);
    digitalWrite(OBJ_Led, HIGH);
    digitalWrite(MET_Led, LOW);

  } else if (OP_input == HIGH && IN_input == LOW){          // op sensor and in sensor do not detect

    Serial.println("NOT DETECTED");
    digitalWrite(ERR_Led, LOW);
    digitalWrite(OBJ_Led, LOW);
    digitalWrite(MET_Led, LOW);

  } else if (OP_input == HIGH && IN_input == HIGH){         // ERROR - op sensor not detect, in sensor detects

    Serial.println("ERROR: detected electromagnetic field but no object present");
    digitalWrite(ERR_Led, HIGH);
    digitalWrite(OBJ_Led, LOW);
    digitalWrite(MET_Led, LOW);
    
  } else {                                                  // ERROR - no other option metched

    Serial.println("ERROR: general error, check if everything is correctly connected and functioning");
    digitalWrite(ERR_Led, HIGH);
    digitalWrite(OBJ_Led, LOW);
    digitalWrite(MET_Led, LOW);

  }
}
