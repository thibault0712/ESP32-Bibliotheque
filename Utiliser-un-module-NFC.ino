#include <SPI.h>
#include <RFID.h>
#include <stdio.h>

const char DOUT_LED_ROUGE = 2;
const char DOUT_LED_VERTE = 3;

RFID monModuleRFID(10,9);

int AdminUID = 766; //Ici L'UID admin de la carte pour débloquer tous les antivoles
int UID[5]={};
int SaveUID = 0; //Ici l'UID qui est enregistré dans l'antivol quand il est fermé
int Card = 0;
int MASTERKEY[3] = {832, 630 };
bool isInUsers = false;
bool isClosed = false; //Ici vérifie si l'entivol est fermé ou ouvert

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  monModuleRFID.init();

}

void loop()
{
    if (monModuleRFID.isCard()) {  
          if (monModuleRFID.readCardSerial()) {        
            for(int i=0;i<=4;i++)
            {
              UID[i]=monModuleRFID.serNum[i];
            }
          }
          
          Card = UID[0]+UID[1]+UID[2]+UID[3]+UID[4];

          int i=0; //Pour la boucle for
          isInUsers = false; //Permet de reset la détection
          for (i = 0 ; i < 4 ; i++){
            if (MASTERKEY[i] == Card){
              isInUsers = true;
            }
          }
          
          if (isInUsers == true || Card == AdminUID)
          {
              if (isClosed == false) //Vérifie si l'antivol est ouvert
              {
                //Lance la fermeture du système
                SaveUID = Card; //Enregistre l'UID de la carte
                Serial.println(F("Fermeture en cours...")); 
                Serial.println(F("Fermé"));
                isClosed = true; //Définit la fermeture sur oui
                delay(1000);
              }else if (Card == SaveUID || Card == AdminUID){ //vérfie si la carte est la bonne pour ouvrir l'antivol ou que c'est la carte Admin
                //Lance l'ouverture du système
                SaveUID = 0; //Supprime l'UID enregistré
                Serial.println(F("Ouverture en cours..."));
                Serial.println(F("Ouvert"));
                isClosed = false; //Définit la fermeture sur non
                delay(1000);
              }else{ //Une fois toutes les conditions passés cela veut dire que la carte n'est pas bonne
                Serial.println(F("Cette carte n'est pas la bonne"));
                delay(1000);
              }
          }
          else
          {
            Serial.print(Card);
          }          
          monModuleRFID.halt();
    }
    delay(100);    
}
