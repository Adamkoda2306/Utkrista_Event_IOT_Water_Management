#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "#*#*#*"
#define WIFI_PASSWORD "1234543210"

/* 2. Define the API Key */
#define API_KEY "AIzaSyC-6MWzxf_WAUupiJASmkb4mkQTZjJdWWc"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://es-lab-be4bb-default-rtdb.firebaseio.com/" 

#define USER_EMAIL "adam.k23@iiits.in"
#define USER_PASSWORD "29092005"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
unsigned long PreviousMillis = 0;

#define GREEN_LED_PIN D2
#define YELLOW_LED_PIN D3
#define RED_LED_PIN D4

struct MockData {
  float turbidity;
  float ph;
  float dissolvedoxygen;
  float temperature;
  float ec;
};

struct MockData data[15] = {
  {4.0, 8.0, 8.0, 14.2, 1420.0},    // Safe values
  {6.5, 7.8, 5.2, 18.5, 1800.0},    // Warning values
  {10.0, 6.0, 3.8, 28.0, 5000.0},   // Unsafe values
  {3.0, 8.2, 7.6, 23.0, 1300.0},    // Safe values
  {8.0, 7.4, 6.0, 30.0, 1600.0},    // Warning values
  {12.0, 5.8, 2.0, 32.0, 5200.0},   // Unsafe values
  {4.5, 8.0, 6.5, 19.0, 1500.0},    // Safe values
  {5.5, 6.5, 5.0, 22.0, 1700.0},    // Warning values
  {15.0, 5.2, 1.5, 35.0, 5500.0},   // Unsafe values
  {3.2, 7.5, 6.8, 20.5, 1400.0},    // Safe values
  {7.2, 6.9, 4.8, 25.0, 1900.0},    // Warning values
  {18.0, 4.8, 2.5, 37.0, 6000.0},   // Unsafe values
  {4.1, 8.1, 7.0, 15.0, 1400.0},    // Safe values
  {6.8, 7.2, 4.3, 26.0, 2000.0},    // Warning values
};
 
float Turbidity;
float Ph;
float DO;
float Temperature;
float EC;
int i=0;

unsigned long count = 0;

void setup(){

    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);

    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED){
      delay(300);
    }

    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    config.database_url = DATABASE_URL;

    config.token_status_callback = tokenStatusCallback;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Firebase.setDoubleDigits(5);
}

void loop(){
    unsigned long currentMillis_V = millis();

    if(currentMillis_V - PreviousMillis > 30000 || PreviousMillis == 0){
      PreviousMillis = currentMillis_V;

      // Generate random values within specified ranges
      // EC = random(5, 550000) / 100.0;       // Electrical Conductivity in µS/cm
      // Temperature = random(0, 400) / 10.0; // Temperature in °C (0.0 - 40.0)
      // DO = random(0, 140) / 10.0;          // Dissolved Oxygen in mg/L (0.0 - 14.0)
      // Ph = random(65, 85) / 10.0;          // pH level (6.5 - 8.5)
      // Turbidity = random(0, 100) / 1.0;    // Turbidity in NTU (0 - 100)

      EC = data[i].ec;
      Temperature = data[i].temperature;
      DO = data[i].dissolvedoxygen;
      Ph = data[i].ph;
      Turbidity = data[i].turbidity;

      if(i >= 15){
        i=0;
      }else{
        i++;
      }

      checkWaterQuality();
      delay(1000);
    }

    unsigned long currentMillis_D = millis();
    if (Firebase.ready() && (currentMillis_D - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
      sendDataPrevMillis = currentMillis_D;

      Serial.printf("Set Ph Value %s\n", Firebase.setString(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Ph"), Ph) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set Turbidity Value %s\n", Firebase.setFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Turbidity"), Turbidity) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set DO Value %s\n", Firebase.setFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/DO"), DO) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set Temperature Value %s\n", Firebase.setFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Temperature"), Temperature) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set Conductivity Value %s\n", Firebase.setFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Conductivity"), EC) ? "ok" : fbdo.errorReason().c_str());
    }
}

void checkWaterQuality() {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);

    int isTurbiditySafe, isECSafe, isTemperatureSafe, isDOSafe, isPhSafe;
    
    // Turbidity check (0-100)
    isTurbiditySafe = (Turbidity < 5) ? 1 : (Turbidity >= 5 && Turbidity <= 10) ? 2 : 0;

    // EC check (0.05 - 5500)
    isECSafe = (EC < 1500) ? 1 : (EC >= 1500 && EC <= 4000) ? 2 : 0;

    // Temperature check (0.0 - 40.0)
    isTemperatureSafe = (Temperature >= 5 && Temperature <= 25) ? 1 : (Temperature > 25 && Temperature <= 30) ? 2 : 0;

    // DO check (0.0 - 14.0)
    isDOSafe = (DO > 5) ? 1 : (DO >= 3 && DO <= 5) ? 2 : 0;

    // Ph check (0.0 - 14.0)
    isPhSafe = (Ph >= 6.0 && Ph <= 8.5) ? 1 : (Ph < 6.0 || Ph > 8.5) ? 2 : 0;

    if (isTurbiditySafe == 0 || isECSafe == 0 || isTemperatureSafe == 0 || isDOSafe == 0 || isPhSafe == 0) {
        digitalWrite(RED_LED_PIN, HIGH);
    }
    else if (isTurbiditySafe == 2 || isECSafe == 2 || isTemperatureSafe == 2 || isDOSafe == 2 || isPhSafe == 2) {
        digitalWrite(YELLOW_LED_PIN, HIGH);
    }
    else {
        digitalWrite(GREEN_LED_PIN, HIGH);
    }
}
