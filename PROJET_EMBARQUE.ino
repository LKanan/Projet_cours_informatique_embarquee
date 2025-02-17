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
  for (int i=echoPin1; i<=echoPin6; i++) {
  pinMode(i, INPUT);
  }
  digitalWrite(trigsPin, LOW);
}

void loop() {

  Serial.print("Capteur1 : ");
  Serial.println(mesureCapeurUltrason(echoPin1));
  Serial.print("Capteur2 : ");
  Serial.println(mesureCapeurUltrason(echoPin2));
  Serial.print("Capteur3 : ");
  Serial.println(mesureCapeurUltrason(echoPin3));
  Serial.print("Capteur4 : ");
  Serial.println(mesureCapeurUltrason(echoPin4));
  Serial.print("Capteur5 : ");
  Serial.println(mesureCapeurUltrason(echoPin5));
  Serial.print("Capteur6 : ");
  Serial.println(mesureCapeurUltrason(echoPin6));
  Serial.println("============================================================");
  Serial.println("");
}

long mesureCapeurUltrason(int echoPin){
  digitalWrite(trigsPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigsPin, LOW);
  delayMicroseconds(2);
  long dureeRenvoyee = pulseIn(echoPin, HIGH);
  long distanceRenvoyee = (dureeRenvoyee * 0.0344) / 2; // Calcul de la distance en cm
  delay(150);

  return distanceRenvoyee;
}

