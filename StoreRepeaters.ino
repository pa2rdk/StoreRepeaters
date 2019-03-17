#include "Arduino.h"
#include <EEPROM.h>
//The setup function is called once at startup of the sketch

typedef struct{
	byte checkByte;
	char call[7];
	char locatie[12];
	byte channel;  // = auto.
	byte txTone;
	byte rxTone;
} repeaterList;


repeaterList repeater[31];
repeaterList Oliebol;
byte offsetEEPROM = 10;
byte chkDigit = '#';

void setup()
{
	repeater[0]= (repeaterList){'#',"PI3UTR","IJsselstein",126,4,0};
	repeater[1]= (repeaterList){'#',"PI3ALK","Alkmaar    ",128,8,8};
	repeater[2]= (repeaterList){'#',"PI3ZVL","Overslag   ",128,0,0};
	repeater[3]= (repeaterList){'#',"PI3TWE","Eibergen   ",128,4,4};
	repeater[4]= (repeaterList){'#',"PI3SRT","Venlo      ",128,2,2};
	repeater[5]= (repeaterList){'#',"PI3APM","Appingendam",129,6,6};
	repeater[6]= (repeaterList){'#',"PI3BOZ","Bergen/Zoom",130,8,8};
	repeater[7]= (repeaterList){'#',"PI3ZOD","Emmen      ",130,0,0};
	repeater[8]= (repeaterList){'#',"PI3AMF","Amersfoort ",130,0,0};
	repeater[9]= (repeaterList){'#',"PI3FRL","Leeuwarden ",131,6,6};
	repeater[10]= (repeaterList){'#',"PI3ZUT","Zutphen    ",131,0,0};
	repeater[11]= (repeaterList){'#',"PI3MEP","Meppel     ",132,6,6};
	repeater[12]= (repeaterList){'#',"PI3BRD","Breda      ",132,2,2};
	repeater[13]= (repeaterList){'#',"PI3VLI","Vlissingen ",133,8,8};
	repeater[14]= (repeaterList){'#',"PI3RTD","Rotterdam  ",134,8,8};
	repeater[15]= (repeaterList){'#',"PI3NOV","'t Harde   ",134,4,4};
	repeater[16]= (repeaterList){'#',"PI3VHP","Vroomshoop ",135,4,4};
	repeater[17]= (repeaterList){'#',"PI3YMD","IJmuiden   ",135,8,8};
	repeater[18]= (repeaterList){'#',"PI3HVN","Heerenveen ",136,6,6};
	repeater[19]= (repeaterList){'#',"PI3EHV","Eindhoven  ",136,2,2};
	repeater[20]= (repeaterList){'#',"PI3DTC","Doetinchem ",136,4,4};
	repeater[21]= (repeaterList){'#',"PI3ZAZ","Wormerveer ",137,8,8};
	repeater[22]= (repeaterList){'#',"PI3GOE","Goes       ",138,8,8};
	repeater[23]= (repeaterList){'#',"PI3APD","Apeldoorn  ",138,4,4};
	repeater[24]= (repeaterList){'#',"PI3ZLB","Geleen     ",138,2,2};
	repeater[25]= (repeaterList){'#',"PI3FLD","Lelystad   ",139,4,4};
	repeater[26]= (repeaterList){'#',"PI3NYM","Nijmegen   ",140,4,4};
	repeater[27]= (repeaterList){'#',"PI3GRN","Groningen  ",140,6,6};
	repeater[28]= (repeaterList){'#',"PI3RAZ","Zoetermeer ",140,8,8};
	repeater[29]= (repeaterList){'#',"PI3ALM","Almere     ",141,0,0};
	repeater[30]= (repeaterList){'#',"PI3ASD","Amsterdam  ",142,8,8};
	Serial.begin(9600);
	Serial.println("Started");
	saveConfig();

	for (int i=0; i<31; i++){
		loadRepeater(i);
		Serial.println(Oliebol.call);
	}
}


void loop()
{


}

void saveConfig() {
	for (unsigned int t = 0; t < sizeof(repeater); t++)
		EEPROM.write(offsetEEPROM + t, *((char*)&repeater + t));
}

void loadRepeater(int i) {
	unsigned int l = i*23;

	if (EEPROM.read(offsetEEPROM + l) == chkDigit)
		for (int t=l; t < l+23; t++)
			*((char*)&Oliebol + (t-l)) = EEPROM.read(offsetEEPROM + t);
}

