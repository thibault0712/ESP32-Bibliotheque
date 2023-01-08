// Importation des librairies
#include <WiFi.h>

//Définition du serveur et des mots de passes wifi
WiFiServer server(80);
const char* ssid = "Thibault";
const char* password = "Bonjour1";
const char* site = "78.233.161.137";

String texte; // Variable qui enregistrera le texte reçu

String request(String idCard){
  texte = "";
  // Conexion au serveur et envoi de la requète
  WiFiClient client;
  const int httpPort = 8999;
  if (!client.connect(site, httpPort)) {
    //return "Connection au serveur echouée.";
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
    }
  }

  // On lit les lignes que le serveur nous envoie
  while(client.available()) {
    texte += client.readStringUntil('\r');
  }
  return(texte);
}

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Démmarrage");

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

}


void loop() {
    if (request("192000") == "true"){
      Serial.println("La carte est reconnu");
    }else if(request("192000") == "false"){
      Serial.println("La carte n'est pas reconnu !");
    }else{
      Serial.println("ERREUR");
    }
}
