# 1 - Introduzione

Il progetto descrive la progettazione e l'implementazione di un sistema per il rilevamento della presenza e delle proprietà magnetiche di oggetti. L'obiettivo è distinguere la natura dei materiali rilevati (metallici o non metallici) utilizzando due sensori: un sensore ottico a infrarossi, per verificare l'effettiva presenza dell'oggetto, e un sensore induttivo, in grado di rilevarne il magnetismo e stabilirne quindi la composizione metallica. L'integrazione di tre LED consente un'intuitiva comprensione del funzionamento del sistema: verde se è stato rilevato un oggetto, giallo se l'oggetto è metallico, rosso in caso di errori o letture anomale.



# 2 - Componenti e strumenti

| Hardware                      | Software    |
|-------------------------------|-------------|
| Arduino Uno R4 WiFi           | Arduino IDE.|
| sensore infrarossi E18-D80NK  |             |
| sensore induttivo J12A3-4     |             |
| 3x LED (verde, giallo, rosso) |             |
| 3x resistenza 220ohm          |             |
| cavi jumper                   |             |



*IMMAGINI DEI SENSORI, LED, etc... (in base a spazio disponibilenella pagina)*



# 3 - Realizzazione

## 3.1 - Assemblaggio



*IMMAGINE SCHEMA ELETTRICO (easyEda o KiCad)*



### 3.1.1 - Sensore E18-D80NK

Collegare il sensore all'Arduino:

* cavo marrone (BN - fase) a 5V,
* cavo blu (BU - neutro) a GND,
* cavo nero (BK - data) al pin digitale D13.



### 3.1.2 - Sensore LJ12A3-4

Collegare il sensore all'Arduino:

* cavo marrone (BN - fase) a 5V,
* cavo blu (BU - neutro) a GND,
* cavo nero (BK - data) al pin digitale D13.



### 3.1.3 - LED

Collegare i 3 LED in parallelo tra di loro e in serie ognuno con una resistenza.

Per ogni LED collegare:

* anodo al pin digitale (verde-D4, giallo-D3, rosso-D2),
* catodo alla resistenza e GND.



### 3.2 - Codice

### 3.2.1 - Dichiarazione variabili

Vengono dichiarate le variabili per il stabilire il delay di lettura dei sensori e i pin a cui i sensori e i led sono connessi.


```cpp
int time = 500;       // delay

int OP_Sensor = 13;   // optical sensor
int IN_Sensor = 12;   // inductive sensor
int OBJ_Led = 4;      // green led for object detected
int MET_Led = 3;      // yellow led for metallic detected
int ERR_Led = 2;      // red led for error status
```


### 3.2.2 - Setup

Si inizializzano il Serial monitor a 115200 baud, e si definiscono le modalità dei pin, input per i sensori e output per i led.


```cpp
void setup() {
    Serial.begin(115200);
    
    // pin mode definition
    pinMode(OP_Sensor, INPUT);
    pinMode(IN_Sensor, INPUT);
    pinMode(OBJ_Led, OUTPUT);
    pinMode(MET_Led, OUTPUT);
    pinMode(ERR_Led, OUTPUT);
}
```


### 3.2.3 - Loop

All'interno del loop prima di tutto si aspetta il tempo necessario alla lettura dei dati inviati dai sensori tramite il comando 'delay()', successivamente si leggono i dati dei sensori e in base ad essi il ciclo 'if() - else if()' controlla tutte le possibili combinazioni facendo accendere i rispettivi led in base ai dati rilevati dai sensori. Si verificano anche stati di errore (come la rilevazione di magnetismo ma non di un oggetto), infine nella sezione 'else' finale si definisce un errore generale nel caso in cui non si rientri in nessuna delle opzioni possibili, condizione che presuppone problematiche esterne e non verificabili tramite codice.


```cpp
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
        
    } else {                                                      // ERROR - no other option matched
    
        Serial.println("ERROR: general error, check if everything is correctly connected and functioning");
        digitalWrite(ERR_Led, HIGH);
        digitalWrite(OBJ_Led, LOW);
        digitalWrite(MET_Led, LOW);
    }
}
```


# 4 - Conclusione

Il progetto ha permesso di realizzare un sistema funzionante per il rilevamento e la classificazione di oggetti, sfruttando la scheda Arduino Uno R4 WiFi. L'utilizzo di entrambe i sensori ottico E18-D80NK e induttivo LJ12A3-4 si è dimostrata una soluzione efficace per distinguere con sufficiente precisione la natura dei materiali rilevati, differenziando correttamente tra oggetti metallici e non metallici.

Il codice sviluppato ha garantito una buona affidabile del sistema, permettendo non solo l'identificazione corretta delle rilevazioni (segnalate dai LED verde e giallo), ma anche la gestione di eventuali stati di errore e di incongruenze nelle letture (segnalati dal LED rosso).

In conclusione, il sistema progettato soddisfa gli obiettivi prefissati, simulando uno scenario di automazione industriale per il controllo qualità o lo smistamento.

Il progetto rimane aperto a possibili sviluppi futuri, come miglioramenti all'affidabilità tramite un maggiore controllo delle distanze di rilevamento dei due sensori.



# Codice Completo

```cpp
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
        
    } else {                                                      // ERROR - no other option matched
    
        Serial.println("ERROR: general error, check if everything is correctly connected and functioning");
        digitalWrite(ERR_Led, HIGH);
        digitalWrite(OBJ_Led, LOW);
        digitalWrite(MET_Led, LOW);
    }
}
```
