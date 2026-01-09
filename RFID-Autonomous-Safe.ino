#include <SPI.h>
#include <MFRC522.h>
#include <Stepper.h>

#define PIN_RST 2
#define PIN_SS 10

#define PIN_LED_ROUGE 3
#define PIN_LED_VERTE 4
#define PIN_LED_BLEUE 5

#define PIN_BUZZER 11
#define PIN_POWER_1 A0
#define PIN_POWER_2 A1

const int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution, 6, 8, 7, 9);
MFRC522 mfrc522(PIN_SS, PIN_RST);

const int MAX_CARTES = 10;
const int TAILLE_UID = 4;

byte utilisateurs[MAX_CARTES][TAILLE_UID];
byte nombreInscrits = 0;

byte masterCard[TAILLE_UID] = { 42, 90, 175, 36 };
byte carteLue[TAILLE_UID];

enum Etat {
  STARTUP,
  ATTENTE,
  INVALIDE,
  VALIDE,
  MODE_MASTER,
  AJOUT_CARTE,
  SUPPR_CARTE
};

Etat etatActuel = STARTUP;
unsigned long tempsEtat = 0;
unsigned long dureeTimer = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(PIN_POWER_1, OUTPUT);
  pinMode(PIN_POWER_2, OUTPUT);
  digitalWrite(PIN_POWER_1, HIGH);
  digitalWrite(PIN_POWER_2, HIGH);

  pinMode(PIN_LED_BLEUE, OUTPUT);
  pinMode(PIN_LED_ROUGE, OUTPUT);
  pinMode(PIN_LED_VERTE, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  myStepper.setSpeed(0.15 * 64);

  changerEtat(STARTUP);
}

void loop() {
  if (etatActuel != ATTENTE && dureeTimer > 0) {
    if (millis() > tempsEtat + dureeTimer) {
      changerEtat(ATTENTE);
    }
  }

  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  analyserCarte();
}

void analyserCarte() {
  for (byte i = 0; i < TAILLE_UID; i++) {
    carteLue[i] = mfrc522.uid.uidByte[i];
  }

  if (memcmp(carteLue, masterCard, TAILLE_UID) == 0) {
    changerEtat(MODE_MASTER);
    return;
  }

  if (nombreInscrits == 0) {
    changerEtat(INVALIDE);
    return;
  }

  boolean connue = false;
  for (byte i = 0; i < nombreInscrits; i++) {
    if (memcmp(carteLue, utilisateurs[i], TAILLE_UID) == 0) {
      connue = true;
      break;
    }
  }

  if (connue) {
    changerEtat(VALIDE);
  } else {
    changerEtat(INVALIDE);
  }
}

void gererBaseDeDonnees(boolean ajouter) {
  if (ajouter) {
    if (nombreInscrits < MAX_CARTES) {
      for (byte i = 0; i < TAILLE_UID; i++) utilisateurs[nombreInscrits][i] = carteLue[i];
      nombreInscrits++;
      changerEtat(AJOUT_CARTE);
    } else {
      tone(PIN_BUZZER, 200, 500);
    }
  } else {
    int index = -1;
    for (byte i = 0; i < nombreInscrits; i++) {
      if (memcmp(carteLue, utilisateurs[i], TAILLE_UID) == 0) index = i;
    }

    if (index != -1) {
      for (byte i = index; i < nombreInscrits - 1; i++) {
        for (byte j = 0; j < TAILLE_UID; j++) utilisateurs[i][j] = utilisateurs[i + 1][j];
      }
      nombreInscrits--;
      changerEtat(SUPPR_CARTE);
    }
  }
}

void changerEtat(Etat nouvelEtat) {
  if (etatActuel == MODE_MASTER) {
    if (nouvelEtat == INVALIDE) {
      gererBaseDeDonnees(true);
      return;
    }
    if (nouvelEtat == VALIDE) {
      gererBaseDeDonnees(false);
      return;
    }
  }

  etatActuel = nouvelEtat;
  tempsEtat = millis();

  switch (etatActuel) {
    case STARTUP:
      dureeTimer = 2000;
      tone(PIN_BUZZER, 1000, 100);
      delay(200);
      tone(PIN_BUZZER, 2000, 100);
      break;

    case ATTENTE:
      dureeTimer = 0;
      digitalWrite(PIN_LED_ROUGE, LOW);
      digitalWrite(PIN_LED_VERTE, LOW);
      digitalWrite(PIN_LED_BLEUE, LOW);
      break;

    case INVALIDE:
      dureeTimer = 2000;
      digitalWrite(PIN_LED_ROUGE, HIGH);
      tone(PIN_BUZZER, 2000, 500);
      break;

    case VALIDE:
      dureeTimer = 0;
      digitalWrite(PIN_LED_VERTE, HIGH);
      tone(PIN_BUZZER, 500, 100);
      delay(150);
      tone(PIN_BUZZER, 500, 100);

      digitalWrite(PIN_POWER_1, LOW);
      digitalWrite(PIN_POWER_2, LOW);
      myStepper.step(-stepsPerRevolution / 4);
      delay(2000);
      myStepper.step(stepsPerRevolution / 4);
      digitalWrite(PIN_POWER_1, HIGH);
      digitalWrite(PIN_POWER_2, HIGH);

      changerEtat(ATTENTE);
      break;

    case MODE_MASTER:
      dureeTimer = 5000;
      digitalWrite(PIN_LED_BLEUE, HIGH);
      digitalWrite(PIN_LED_VERTE, HIGH);
      tone(PIN_BUZZER, 1000, 300);
      break;

    case AJOUT_CARTE:
      dureeTimer = 1000;
      digitalWrite(PIN_LED_VERTE, HIGH);
      tone(PIN_BUZZER, 2000, 100);
      delay(100);
      tone(PIN_BUZZER, 2000, 100);
      break;

    case SUPPR_CARTE:
      dureeTimer = 1000;
      digitalWrite(PIN_LED_ROUGE, HIGH);
      tone(PIN_BUZZER, 500, 300);
      break;
  }
}