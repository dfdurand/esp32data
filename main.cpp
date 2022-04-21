#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>


// parametre wifi
const char *ssid = "altwifi";
const char *password = "wifi2371";

//pin de la led
#define led 2

String state = " ";

// capteur de temperature 
#define A0 36
#define refV 3300 
#define bits 4096.0

// serveur asynchrone 

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(A0, INPUT);
//******************************* vérification des fichiers dans la mémoire **********
  if(!SPIFFS.begin())
  {
    Serial.println("Erreur SPIFFS...");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  //************** connexion au wifi **************
  WiFi.begin(ssid, password);
	Serial.print("Tentative de connexion...");
	
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(100);
	}
	
	Serial.println("\n");
	Serial.println("Connexion etablie!");
	Serial.print("Adresse IP: ");
	Serial.println(WiFi.localIP());

  //************************  chargement des fichiers ****************** 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/home.html", "text/html");
  });

 // server.on("/votre.css", HTTP_GET, [](AsyncWebServerRequest *request)
  //{
  //  request->send(SPIFFS, "/votrecss.css", "text/css");
  //});

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

//******************** réponses aux requetes du client ************

  server.on("/lireTemperature", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   int val  = analogRead(A0);

  float temp_celcius = val*(refV/bits);

    Serial.println(temp_celcius);
    String temp = String(temp_celcius/10.0);
    request->send(200, "text/plain", temp);
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    digitalWrite(led, HIGH);
    state = "allumée";
    request->send(200);
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    digitalWrite(led, LOW);
    state ="eteinte";
    request->send(200);
  });

  server.on("/lirEtat", HTTP_GET, [](AsyncWebServerRequest *request)
  {
   
    request->send(200, "text/plain", state );
  });

  server.begin();
  Serial.println("Serveur actif!");
}

void loop() {

  
}