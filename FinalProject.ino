#include <SPI.h>
#include <RFID.h>
#include <stdio.h>
#include <WiFi.h>

//Définition du serveur et des mots de passes wifi
WiFiServer server(80);
const char* ssid = "Thibault";
const char* password = "Bonjour1";
const char* site = "78.233.161.137";

//Définition des leds
int Red = 12;
int Orange = 14;
int Green = 27;

String texte; // Variable qui enregistrera le texte reçu
RFID monModuleRFID(5,0);
int AdminUID = 766; //Ici L'UID admin de la carte pour débloquer tous les antivoles
int UID[5]={};
int SaveUID = 0; //Ici l'UID qui est enregistré dans l'antivol quand il est fermé
int Card = 0;
bool isClosed = false; //Ici vérifie si l'entivol est fermé ou ouvert

String request(String idCard){
  texte = "";
  // Conexion au serveur et envoi de la requète
  WiFiClient client;
  const int httpPort = 8999;
  if (!client.connect(site, httpPort)) {
    return "Connection au serveur echouée.";
    digitalWrite(RED, LOW);
    digitalWrite(Orange, HIGH);
    digitalWrite(Green, LOW);
  }
  // Maintenant on envoie la requete au serveur
  client.print(String("GET http://78.233.161.137:8999/Request/request.php?identifiant=" + idCard + "&HTTPversion="));
  client.println(String("HTTP/1.1"));
  client.print(String("Host: "));
  client.println(String(site));
  client.println(String("Connection: close"));
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {  // Si timeout
      client.stop();
      return "Timeout du client !";
      digitalWrite(RED, LOW);
      digitalWrite(Orange, HIGH);
      digitalWrite(Green, LOW);
    }
  }

  // On lit les lignes que le serveur nous envoie
  while(client.available()) {
    texte += client.readStringUntil('\r');
  }
  return(texte);
}

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  monModuleRFID.init();

    Serial.println("");
  Serial.println("Démmarrage");

  //On active les leds et on allume la led orange
  pinMode(Red, OUTPUT);
  pinMode(Orange, OUTPUT);
  pinMode(Green, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(Orange, HIGH);
  digitalWrite(Green, LOW);
  
  // On commence par se connecter au réseau WiFi
  Serial.print("Connexion au réseau WiFi ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connexion au WiFi réussie !");
  Serial.print("Adresse IP locale de l'ESP : ");
  Serial.println(WiFi.localIP());
  
  digitalWrite(Red, LOW);
  digitalWrite(Orange, LOW);
  digitalWrite(Green, HIGH);
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
          Card = 0;
          Card = UID[0] + UID[1] + UID[2] + UID[3];

          if (request(String(Card)) == "true" || Card == AdminUID)
          {
              if (isClosed == false) //Vérifie si l'antivol est ouvert
              {
                //Lance la fermeture du système
                SaveUID = Card; //Enregistre l'UID de la carte
                Serial.println(F("Fermé"));//On signal l'utilisateur
                digitalWrite(Red, HIGH);
                digitalWrite(Orange, LOW);
                digitalWrite(Green, LOW);
                isClosed = true; //Définit la fermeture sur oui
              }else if (Card == SaveUID || Card == AdminUID){ //vérfie si la carte est la bonne pour ouvrir l'antivol ou que c'est la carte Admin
                //Lance l'ouverture du système
                SaveUID = 0; //Supprime l'UID enregistré
                Serial.println(F("Ouvert"));
                digitalWrite(RED, LOW);
                digitalWrite(Orange, LOW);
                digitalWrite(Green, HIGH);
                isClosed = false; //Définit la fermeture sur non
              }else{ //Une fois toutes les conditions passés cela veut dire que la carte n'est pas bonne
                Serial.println(F("Cette carte n'est pas la bonne"));
                var = 0;
                while(var <= 3){  //Permet de faire clignoter la led rouge
                  digitalWrite(Red, HIGH);
                  delay(150);
                  digitalWrite(Red, LOW);
                  delay(150);
                  var++; // incrémente la variable
                }
              }
          }
          else
          {
            Serial.print(Card);
            var = 0;
            while(var <= 3){  //Permet de faire clignoter la led rouge
              digitalWrite(Red, HIGH);
              delay(150);
              digitalWrite(Red, LOW);
              delay(150);
              var++; // incrémente la variable
            }
          }          
          monModuleRFID.halt();
    }
    delay(500);
}
