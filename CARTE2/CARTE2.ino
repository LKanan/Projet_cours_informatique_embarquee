// Declaration des capteurs ultrasoniques
const int trigsPin = 2;
const int echoPin1 = 3;
const int echoPin2 = 4;
const int echoPin3 = 5;
const int echoPin4 = 6;
const int echoPin5 = 7;
const int echoPin6 = 8;



void setup() {
  // Initialisations pour la commmunication série des deux cartes
  Serial.begin(9600);

  // Initialisations pour les capteurs ultasoniques
  pinMode(trigsPin, OUTPUT);
  for (int i = echoPin1; i <= echoPin6; i++) {
    pinMode(i, INPUT);
  }
  digitalWrite(trigsPin, LOW);
}

void loop() {
  // Serial.print("Capteur1 : ");
  // Serial.println(mesureCapeurUltrason(echoPin1));
  // Serial.print("Capteur2 : ");
  // Serial.println(mesureCapeurUltrason(echoPin2));
  // Serial.print("Capteur3 : ");
  // Serial.println(mesureCapeurUltrason(echoPin3));
  // Serial.print("Capteur4 : ");
  // Serial.println(mesureCapeurUltrason(echoPin4));
  // Serial.print("Capteur5 : ");
  // Serial.println(mesureCapeurUltrason(echoPin5));
  // Serial.print("Capteur6 : ");
  // Serial.println(mesureCapeurUltrason(echoPin6));
  // Serial.println("============================================================");
  // Serial.println("");
  boolean priorite1 = prioriteVoie1(echoPin1, echoPin2, echoPin3);
  boolean priorite2 = prioriteVoie2(echoPin4, echoPin5, echoPin6);
  if (priorite1 && priorite2) {
    // Serial.write("priorite1 et priorite2.");
    Serial.println("priorite1 et priorite2.");
  } else if (priorite1) {
    Serial.write("priorite1.");
    // Serial.print("priorite1. " );
    // Serial.print(mesureCapeurUltrason(echoPin1));
    // Serial.print(" ");
    // Serial.print( mesureCapeurUltrason(echoPin2));
    // Serial.print(" ");
    // Serial.println(mesureCapeurUltrason(echoPin3));
  } else if (priorite2) {
    Serial.write("priorite2.");
    // Serial.print("priorite2. " );
    // Serial.print(mesureCapeurUltrason(echoPin4));
    // Serial.print(" ");
    // Serial.print( mesureCapeurUltrason(echoPin5));
    // Serial.print(" ");
    // Serial.println(mesureCapeurUltrason(echoPin6));
  }
  else{
    Serial.println("normal.");
  }
}

long mesureCapeurUltrason(int echoPin) {
  digitalWrite(trigsPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigsPin, LOW);
  delayMicroseconds(2);
  long dureeRenvoyee = pulseIn(echoPin, HIGH);
  long distanceRenvoyee = (dureeRenvoyee * 0.0344) / 2;  // Calcul de la distance en cm
  delay(150);

  return distanceRenvoyee;
}

boolean prioriteVoie1(int echoCapteur1, int echoCapteur2, int echoCapteur3) {
  boolean priorite = false;

  if (mesureCapeurUltrason(echoCapteur1) < 10 && mesureCapeurUltrason(echoCapteur2) < 10 && mesureCapeurUltrason(echoCapteur3) < 10) {
    priorite = true;
    return priorite;
  }
  return priorite;
}

boolean prioriteVoie2(int echoCapteur4, int echoCapteur5, int echoCapteur6) {
  boolean priorite = false;

  if (mesureCapeurUltrason(echoCapteur4) < 10 && mesureCapeurUltrason(echoCapteur5) < 10 && mesureCapeurUltrason(echoCapteur6) < 10) {
    priorite = true;
    return priorite;
  }
  return priorite;
}
