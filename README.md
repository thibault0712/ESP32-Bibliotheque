
# ESP32-Bibliotheque

Code source permettant de lire l'identifiant d'une carte NFC, de savoir si elle existe ou non dans une base de donnée et ferme/ouvre un antivol

# Branchement

- Module RFID
	-   Vcc <-> 3V3 (ou Vin(5V) selon la version du module)
	-   RST (Reset) <-> D0
	-   GND (Masse) <-> GND
	-   MISO (Master Input Slave Output) <-> 19
	-   MOSI (Master Output Slave Input) <-> 23
	-   SCK (Serial Clock) <-> 18
	-   SS/SDA (Slave select) <-> 5

- Leds
	- Rouge <-> 12
	- Orange <-> 14
	- Vert <-> 27
- Verrain
	- Le branchement du verrain est particulié, nous avons deux relais : le premier s'occupe du négatif et le second pour le positif
	- relai négatif <-> 3
	- relai positif <-> 4

## Futur objectif

- Mieux sécuriser le projet
- Rendre le code plus lisible




ATENTION CODE TRES VIEUX ET ILLISIBLE LE CODE DOIT ETRE REFACTORISER

