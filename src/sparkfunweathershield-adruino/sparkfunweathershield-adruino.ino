/*
 SparkFun Weather Shield - Arduino
 By: Bartlomiej Mika
 Mikaponics
 Date: July 3ed, 2021
 License: BSD 3-Clause License

 The source code which powers the Arduino device that collects time-series data
 that will be outputed to the USB serial device.

 The following data will be recorded:
 (1) Humidity/Temperature Sensor --- Si7021
 (2) Barometric Pressure --- MPL3115A2
 (3) Light Sensor --- ALS-PT19

 This code based on utilizing the following Arduino shields / external sensor(s):
 - SparkFun Weather Shield (DEV-13956)
*/

#include <ArduinoJson.h>
#include <Wire.h> //I2C needed for sensors
#include "SparkFunMPL3115A2.h" //Pressure sensor - Search "SparkFun MPL3115" and install from Library Manager
#include "SparkFun_Si7021_Breakout_Library.h" //Humidity sensor - Search "SparkFun Si7021" and install from Library Manager

// Create instance of our sensors.
MPL3115A2 myPressure;
Weather myHumidity;

// Hardware pin definitions
const byte REFERENCE_3V3 = A3;
const byte LIGHT = A1;

// Set variables used by our application
int id_incr_count = 1; // Variable used to keep track of the output count.
char rx_byte = 0;

/**
 * The main entry point into our application.
 */
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // SETUP OUR INSTRUMENTS
  //------------------------------------
  // --- Weather Shield ---
  pinMode(REFERENCE_3V3, INPUT);
  pinMode(LIGHT, INPUT);

  //Configure the pressure sensor
  myPressure.begin(); // Get sensor online
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags

  //Configure the humidity sensor
  myHumidity.begin();

  // FINISH SETTING UP
  // We must print this JSON string to let our service computer know this
  // code is ready to be polled.
  // Create our JSON object.
  StaticJsonDocument<200> doc;

  // Add system values in the document
  doc["status"] = "READY";
  doc["runtime"] = millis();
  doc["id"] = id_incr_count++;

  // Add an array.
  JsonArray data = doc.createNestedArray("sensors");
  data.add("humidity"); // relative humidity
  data.add("temperature");
  data.add("pressure"); // barometric pressure
  data.add("illuminance");

  // Generate the minified JSON and send it to the Serial port.
  serializeJson(doc, Serial);

  // Start a new line
  Serial.println();
}

/**
 * The main runtime loop of our application.
 */
void loop() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character

    // check if a number was received
    if ((rx_byte >= '0') && (rx_byte <= '9')) {
      poll_all_instruments();
    }
  }
}


void poll_all_instruments() {
  //Check Humidity Sensor
  float humidity = myHumidity.getRH();

  if (humidity == 998) //Humidty sensor failed to respond
  {
    Serial.println("I2C communication to sensors is not working. Check solder connections.");

    //Try re-initializing the I2C comm and the sensors
    myPressure.begin();
    myPressure.setModeBarometer();
    myPressure.setOversampleRate(7);
    myPressure.enableEventFlags();
    myHumidity.begin();
  }
  else
  {
    // Create our JSON object.
    StaticJsonDocument<511> doc;

    // Add system values in the document
    doc["status"] = "RUNNING";
    doc["runtime"] = millis();
    doc["id"] = id_incr_count++;

    // HUMIDITY
    doc["humidity_value"] = humidity;
    doc["humidity_unit"] = "%";

    // TEMPERATURE (FROM HUMIDITY INSTRUMENT)
    float temp_h = myHumidity.getTempF();
    doc["temperature_primary_value"] = temp_h;
    doc["temperature_primary_unit"] = "F";

    // PRESSURE
    float pressure = myPressure.readPressure();
    doc["pressure_value"] = pressure;
    doc["pressure_unit"] = "Pa";

    // TEMPERATURE (FROM PRESSURE INSTRUMENT)
    float temp_p = myPressure.readTempF();
    doc["temperature_secondary_value"] = temp_p;
    doc["temperature_secondary_unit"] = "F";

    // ALTITUDE
    float altitude = myPressure.readAltitudeFt();
    doc["altitude_value"] = altitude;
    doc["altitude_unit"] = "ft";

    // ILLUMINANCE
    float light_lvl = get_light_level();
    doc["illuminance_value"] = light_lvl;
    doc["illuminance_unit"] = "V";

    // Generate the minified JSON and send it to the Serial port.
    serializeJson(doc, Serial);

    // Start a new line
    Serial.println();
  }
}

//Returns the voltage of the light sensor based on the 3.3V rail
//This allows us to ignore what VCC might be (an Arduino plugged into USB has VCC of 4.5 to 5.2V)
// https://learn.sparkfun.com/tutorials/arduino-weather-shield-hookup-guide-v12
float get_light_level()
{
  float operatingVoltage = analogRead(REFERENCE_3V3);

  float lightSensor = analogRead(LIGHT);

  operatingVoltage = 3.3 / operatingVoltage; //The reference voltage is 3.3V

  lightSensor = operatingVoltage * lightSensor;

  return (lightSensor);
}
