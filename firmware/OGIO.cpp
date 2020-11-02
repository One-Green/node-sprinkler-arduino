//
// Created by jkl on 02/11/2020.
//

#include "Arduino.h"
#include "OGIO.h"

#define SOIL_MOISTURE_PIN  34
#define WATER_VALVE_PIN 19


void OGIO::initR() {
	pinMode(WATER_VALVE_PIN, OUTPUT);
}

float OGIO::getMoistureLevelADC() {
	return analogRead(SOIL_MOISTURE_PIN);
}


float OGIO::getMoistureLevel(float in_min, float in_max, float out_min, float out_max) {
	return  map(getMoistureLevelADC(), in_min, in_max, out_min, out_max);
}

void OGIO::openWaterValve(){
	digitalWrite(WATER_VALVE_PIN, HIGH);
}

void OGIO::closeWaterValve(){
	digitalWrite(WATER_VALVE_PIN, LOW);
}

String OGIO::generateInfluxLineProtocol(){}
