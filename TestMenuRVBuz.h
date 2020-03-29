
#ifndef TestMenuRVBuz_h
#define TestMenuRVBuz_h
#include "Arduino.h"
#include "SoftwareSerial.h"


class TestMenuRVBuz {

	private:
	
		String monTitreMenu;
		String monTitre1;
		String monTitre2;
		String monTitre3;

		uint8_t action;

		int ValMenu;
		
		int received;
		
		// new for the buttons
		int BoutonSelect;  	// BoutonS
		int BoutonBas;		// BoutonB
		int BoutonRouge;	// BoutonR
		int BoutonVert;		// BoutonV
		int BoutonHaut;		// BoutonH
		
		int Buzzer;
		
		boolean EtatBoutonBAS;
		boolean EtatBoutonHAUT; 
		boolean EtatBoutonSELECT;
		boolean EtatBoutonROUGE;
		boolean EtatBoutonVERT;
		
		void(* resetFunc) (void) = 0; 
		
		

	
	public:

		//TestMenuRVBuz::TestMenuRVBuz (String TitreMenu, String Titre1, String Titre2, String Titre3, int BoutonS, int BoutonB, int BoutonH); // (sans boutons Rouge et Vert)
		TestMenuRVBuz::TestMenuRVBuz (String TitreMenu, String Titre1, String Titre2, String Titre3, int BoutonS, int BoutonB, int BoutonH, int BoutonV, int BoutonR, int buz); // (avec boutons Rouge, Vert et buzzer)
		void monSetup(); 	// Used to set the pinMode and other setups

		//Tu peux par exemple changer le void TestMenuRVBuz::monMenuTest() en uint8_t TestMenuRVBuz::monMenuTest()
		uint8_t monMenuTest();
	
		byte FlecheHaut2[8] = {                      
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
		byte FlecheBas2[8] = {
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
		byte FlecheMenu2[8] = {
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
		byte FlecheGauche2[8] = {
			0B00000,
			0B00010,
			0B00110,
			0B01111,
			0B11111,
			0B01111,
			0B00110,
			0B00010
		};
		byte indic2[8] = {
			0B00000,
			0B00000,
			0B00000,
			0B00000,
			0B11111,
			0B11111,
			0B11111,
			0B00000
		};
		byte Validate2[8] = {
			0B00000,
			0B00001,
			0B00011,
			0B10110,
			0B11100,
			0B01000,
			0B00000,
			0B00000,
		};

};

#endif