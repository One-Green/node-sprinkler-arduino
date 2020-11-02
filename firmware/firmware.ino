/*
 * Sprinkler ESP32 Arduino Firmware
 * https://github.com/One-Green/node-sprinkler-arduino
 *
 *
 * Work with this framework
 * One-Green : open source framework for plant cultivation including web server and microcontroller framework
 * https://github.com/One-Green/plant-keeper-master
 *
 * License : Creative Commons Legal Code - CC0 1.0 Universal
 * Author: Shanmugathas Vigneswaran
 * mail: shanmugathas.vigneswaran@outlook.fr
 *
 *
 * */

#include "OGDisplay.h"
#include "OGApiHandler.h"
#include "OGIO.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <EspMQTTClient.h>

char *NODE_TYPE = "sprinkler";
char *NODE_TAG = "orchid";
bool CHECK_NODE_TAG_DUPLICATE = false;

char *WIFI_SSID = "*";
char *WIFI_PASSWORD = "*";

char *API_GATEWAY_URL = "http://api.af120153-db6a-4fdd-a81b-6d902b00e936.nodes.k8s.fr-par.scw.cloud";
char *API_GATEWAY_BASIC_AUTH_USER = "";
char *API_GATEWAY_BASIC_AUTH_PASSWORD = "";

char *MQTT_SERVER = "af120153-db6a-4fdd-a81b-6d902b00e936.nodes.k8s.fr-par.scw.cloud";
int MQTT_PORT = 32500;

// ADC to MAX = 100% and ADC tp MIN = 0% calibration
// Used for mapping
int SOIL_MOISTURE_ADC_MAX = 2330;
int SOIL_MOISTURE_ADC_MIN = 1390;

bool registered = false;


DisplayLib displayLib;
OGApiHandler apiHandler;
OGIO io_handler;



void setup(void) {

	Serial.begin(115200);
	displayLib.initR();
	// set pin mode etc ...
	io_handler.initR();

	delay(1000);
	Serial.println("\n");

	displayLib.initWifi();
	Serial.print("Connecting to wifi ");
	Serial.print(WIFI_SSID);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);


	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(100);
	}

	Serial.println("\n");
	displayLib.connectedWifi();
	Serial.println("Connected ");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	displayLib.printHeader(WIFI_SSID, WiFi.localIP(), NODE_TYPE, NODE_TAG);


	if (WiFi.status() == WL_CONNECTED) {

		if (CHECK_NODE_TAG_DUPLICATE) {
			registered = apiHandler.registerNodeTag(
					NODE_TAG,
					API_GATEWAY_URL,
					API_GATEWAY_BASIC_AUTH_USER,
					API_GATEWAY_BASIC_AUTH_PASSWORD
			);

		} else {
			registered = true;
		}

	}
}

void loop() {

	if (registered) {
		int rawSoilMoisture = io_handler.getMoistureLevelADC();
		int soilMoisture = io_handler.getMoistureLevel(
				SOIL_MOISTURE_ADC_MIN, SOIL_MOISTURE_ADC_MAX,
				100, 0);
		Serial.println("Soil moisture ADC=" + String(rawSoilMoisture) + "/" + "LEVEL=" + String(soilMoisture));

	} else {
		Serial.println("Not registered, tag is already in database, remove it first");
		displayLib.printRegistryError();
	}

	delay(500);
}
