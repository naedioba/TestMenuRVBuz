#include <TestMenuRVBuz.h>

#define RST_PIN 8
#define SS_PIN 
#include <avr/wdt.h>
#include <EEPROM.h>               //Library To read and write PICC's UIDs from/to EEPROM
#include <SoftwareSerial.h>
#include <SPI.h>                  //Library  RC522 Module uses SPI protocol
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd2(0x20, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // pour le LCd 20x4 sur boitier principal sans RFID
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

String tm="Titre de mon menu";
String t1="Mon titre 1";
String t2="Mon titre 2";
String t3="Mon titre 3";

TestMenuRVBuz samaMenu(tm, t1, t2, t3, 2, 4, 3, 11, 12, 10); // Boutons OK, Bas, Haut, Rouge, Vert, Buzzer

int DelayBP = 150;
int ValMenu;

int BoutonSELECT=2;
int BoutonHAUT=3;  
int BoutonBAS=4;
int BoutonVERT = 11;
int BoutonROUGE = 12;

char received;

boolean EtatBoutonSELECT;
boolean EtatBoutonBAS;
boolean EtatBoutonHAUT;
boolean EtatBoutonROUGE;
boolean EtatBoutonVERT;
boolean suivant;

byte FlecheHaut[8] = {                      
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

// creation du caractere fleche vers le bas
byte FlecheBas[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b01110,
  0b00100
};
// creation du caractere de menu selectionne
byte FlecheMenu[8] = {
  0b00000,
  0B01000,
  0B01100,
  0B11110,
  0B11111,
  0B11110,
  0B01100,
  0B01000
};
// creation fleche gauche
byte FlecheGauche[8] = {
  0B00000,
  0B00010,
  0B00110,
  0B01111,
  0B11111,
  0B01111,
  0B00110,
  0B00010
};
byte indic[8] = {
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B11111,
  0B11111,
  0B11111,
  0B00000
};
byte Validate[8] = {
  0B00000,
  0B00001,
  0B00011,
  0B10110,
  0B11100,
  0B01000,
  0B00000,
  0B00000,
};

void monAction1();
void monAction2();
void monAction3();

//--------------------
void setup(){

  Serial.begin(9600);                               // Initialisation de la communication serie avec le PC
  lcd2.begin(20,4); 

  pinMode(BoutonSELECT, INPUT_PULLUP);              // definition bouton select en pullup
  pinMode(Buzzer, OUTPUT);

  lcd2.createChar(1, FlecheHaut);
  lcd2.createChar(2, FlecheBas);
  lcd2.createChar(3, FlecheMenu);
  lcd2.createChar(4, FlecheGauche);
  lcd2.createChar(5, indic);
  lcd2.createChar(6, Validate);

  samaMenu.monSetup();
  
}
//--------------------
void loop(){
  
  lcd2.clear();
  lcd2.setCursor(0,0);
  lcd2.print("Appuyer un bouton");
  lcd2.setCursor(0,1);
  lcd2.print("pour tester le Menu3");
  lcd2.setCursor(0,2);
  lcd2.print("--------------------");
  lcd2.setCursor(0,3);
  lcd2.print("Mamadou BA Neige");

  while(1){
    do {
      suivant = false;
      EtatBoutonSELECT = digitalRead(BoutonSELECT);
      EtatBoutonHAUT = digitalRead(BoutonHAUT);
      EtatBoutonBAS = digitalRead(BoutonBAS);
      if (EtatBoutonHAUT == HIGH ||EtatBoutonBAS == HIGH)
      {
        delay(250);
        tone(Buzzer,500,100);
        suivant = true;
        } 
    }
    while (suivant != true);

  Reset:  
    if (samaMenu.monMenuTest()==1){
      monAction1(); goto Reset;
    }
    if (samaMenu.monMenuTest()==2){
      monAction2(); goto Reset;
    }
    if (samaMenu.monMenuTest()==3){
      monAction3(); goto Reset;
    }
  }// fin while
} // fin void
