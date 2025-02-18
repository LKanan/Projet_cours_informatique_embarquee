// Bibliothèque pour les cartes LCD
#include <LiquidCrystal.h>

// Bibliothèque pour le servo moteur
#include <Servo.h>

// Définition des broches pour les LCD
// Broches partagées
#define D4 2
#define D5 3
#define D6 4
#define D7 5

// Définition des broches spécifiques pour chaque écran
#define E1 6   // Enable pour l'écran 1
#define RS1 7  // Register Select pour l'écran 1
#define E2 8   // Enable pour l'écran 2
#define RS2 9  // Register Select pour l'écran 2

// Initialisation des écrans LCD avec broches partagées
LiquidCrystal lcd1(RS1, E1, D4, D5, D6, D7);
LiquidCrystal lcd2(RS2, E2, D4, D5, D6, D7);

// Declaration des pins des leds des feux
int ledsVR = 10;
int ledsJ = 11;

// Declaration de l'objet Servo
int servoPin = 12;
Servo moteur;

// unsigned long dureeMaxTemporisatonFeuRV = 0;
// unsigned long dureeMaxTemporisatonFeuJ = 0;
unsigned long tempsMillis = 0;

 String priorite;

void setup() {
  // Initialisations pour la commmunication série des deux cartes
  Serial.begin(9600);

  // Initialisation pour les LCD
  lcd1.begin(16, 2);  // Configuration de l'écran 1 (16 colonnes, 2 lignes)
  lcd2.begin(16, 2);
  // lcd2.blink()

  // Initialisation du servo moteur
  // moteur.attach(servoPin, 650, 2662);

  moteur.attach(servoPin, 550, 2662);

  // Initialisation des pins des leds du feu
  pinMode(ledsVR, OUTPUT);
  pinMode(ledsJ, OUTPUT);
  digitalWrite(ledsVR, 1);
  digitalWrite(ledsJ, 1);
}

void loop() {
  if (Serial.available() > 1) {
    priorite = Serial.readStringUntil('.');

    Serial.println(priorite);
  }
  afficherMessage(lcd1, "hello", 10);
  afficherMessage(lcd2, "coucou", 10);

  if (priorite == "normal"){
    allumerFeu(1000, 500,true);
  }
  else if(priorite == "priorite1"){
    allumerFeu(1000, 500,false);
    tournerServo(90, moteur);
  }
  else if(priorite == "priorite2"){
    allumerFeu(1000, 500,false);
    tournerServo(0, moteur);
  }
  
  // Test LCD
  // for (int i = duree; i >= 0; i--) {
  //   afficherMessage(lcd1, "STOP", i);
  //   afficherMessage(lcd2, "PASS", i);
  //   delay(1000);
  // }

  // for (int i = duree; i >= 0; i--) {
  //   afficherMessage(lcd1, "PASS", i);
  //   afficherMessage(lcd2, "STOP", i);
  //   delay(1000);
}


// Fonction d'affichage du message avec compte à rebours
void afficherMessage(LiquidCrystal &lcd, String message, int duree) {
  lcd.clear();          // Efface l'écran avant l'affichage
  lcd.setCursor(0, 0);  // Positionne le curseur en haut à gauche
  lcd.print(message);   // Affiche le message sur la première ligne
  lcd.setCursor(0, 1);  // Positionne le curseur sur la deuxième ligne
  lcd.print("Temps : ");
  lcd.print(duree);
  lcd.print("s    ");  // Espaces pour éviter les chiffres résiduels
}

void tournerServo(int angle, Servo servomoteur) {
  // 79 pour 90 deg
  // 170 pour 11730 deg
  servomoteur.write(angle);
}

void allumerFeu(int dureeMaxTemporisatonFeuRV, int dureeMaxTemporisatonFeuJ, boolean modeAutomatique) {
  if ((millis() - tempsMillis) < dureeMaxTemporisatonFeuRV) {
    digitalWrite(ledsVR, 0);
    digitalWrite(ledsJ, 1);
    if (modeAutomatique) {
      tournerServo(90, moteur);
    }
  } else if (((SoustraireMillis() > dureeMaxTemporisatonFeuRV) && (SoustraireMillis() < dureeMaxTemporisatonFeuRV + dureeMaxTemporisatonFeuJ)) || ((SoustraireMillis() > dureeMaxTemporisatonFeuRV + dureeMaxTemporisatonFeuJ * 2) && (SoustraireMillis() < dureeMaxTemporisatonFeuRV + dureeMaxTemporisatonFeuJ * 3)) || ((SoustraireMillis() > dureeMaxTemporisatonFeuRV + dureeMaxTemporisatonFeuJ * 4) && (SoustraireMillis() < dureeMaxTemporisatonFeuRV + dureeMaxTemporisatonFeuJ * 5))) {
    digitalWrite(ledsVR, 1);
    digitalWrite(ledsJ, 0);
  } else if (((SoustraireMillis() > dureeMaxTemporisatonFeuRV + dureeMaxTemporisatonFeuJ * 5) && (SoustraireMillis() < (dureeMaxTemporisatonFeuRV * 2) + dureeMaxTemporisatonFeuJ * 6))) {
    digitalWrite(ledsVR, 0);
    digitalWrite(ledsJ, 1);
    if (modeAutomatique) {
    tournerServo(0, moteur);
    }
  } else {
    digitalWrite(ledsVR, 1);
    digitalWrite(ledsJ, 1);
  }
  if ((SoustraireMillis() > (dureeMaxTemporisatonFeuRV * 2) + dureeMaxTemporisatonFeuJ * 6)) {
    tempsMillis = millis();
  }
}
long SoustraireMillis() {
  return millis() - tempsMillis;
  tournerServo(90, moteur);
}
