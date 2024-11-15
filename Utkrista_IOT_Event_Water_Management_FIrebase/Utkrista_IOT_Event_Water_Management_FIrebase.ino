#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <WiFiUdp.h>
#include <NTPClient.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org",19800);
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

float Turbidity;
float Ph;
float DO;
float Temperature;
float EC;

unsigned long count = 0;

String getCurrentTimeString(){
    timeClient.update();
    time_t now = timeClient.getEpochTime();
    struct tm *timeinfo;
    timeinfo = localtime(&now);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%A, %Y-%m-%d %H:%M:%S", timeinfo);
    return String(buffer);
}

void setup(){

    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    config.database_url = DATABASE_URL;

    config.token_status_callback = tokenStatusCallback;

    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);

    Firebase.setDoubleDigits(5);

    timeClient.begin();

}

// randval = random(0,100) + (random(0,100)/100.0); //random value from 0.00 to 99.99

void loop(){
    unsigned long currentMillis_V = millis();
    unsigned long currentMillis_D = millis();

    // random values for variables within the range
    if(currentMillis_V - PreviousMillis > 60000 || PreviousMillis == 0){
      PreviousMillis = currentMillis_V;
      // Generate random values within specified ranges
      EC = random(5, 550000) / 100.0;       // Electrical Conductivity in µS/cm
      Temperature = random(0, 400) / 10.0; // Temperature in °C (0.0 - 40.0)
      DO = random(0, 140) / 10.0;          // Dissolved Oxygen in mg/L (0.0 - 14.0)
      Ph = random(65, 85) / 10.0;          // pH level (6.5 - 8.5)
      Turbidity = random(0, 100) / 1.0;    // Turbidity in NTU (0 - 100)

      checkWaterQuality();
    }

    if (Firebase.ready() && (currentMillis_D - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
      sendDataPrevMillis = currentMillis_D;

      Serial.printf("Set Area Name %s\n", Firebase.setString(fbdo, F("/Utkrista_IOT/Devices/device1/AreaName"), "IIIT Sricity") ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Get Area Name %s\n", Firebase.getString(fbdo, F("/Utkrista_IOT/Devices/device1/AreaName")) ? String(fbdo.to<String>()).c_str() : fbdo.errorReason().c_str());

      Serial.printf("Set Ph Value %s\n", Firebase.setString(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Ph"), Ph) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Get Ph Value %s\n", Firebase.getString(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Ph")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());

      Serial.printf("Set Turbidity Value %s\n", Firebase.setFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Turbidity"), Turbidity) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Get Turbidity Value %s\n", Firebase.getFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Turbidity")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());

      Serial.printf("Set DO Value %s\n", Firebase.setFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/DO"), DO) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Get DO Value %s\n", Firebase.getFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/DO")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());

      Serial.printf("Set Temperature Value %s\n", Firebase.setFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Temperature"), Temperature) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Get Temperature Value %s\n", Firebase.getFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Temperature")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());

      Serial.printf("Set Conductivity Value %s\n", Firebase.setFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Conductivity"), EC) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Get Conductivity Value %s\n", Firebase.getFloat(fbdo, F("/Utkrista_IOT/Devices/device1/Sensorvalues/Conductivity")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());


      FirebaseJson json;
      json.set("time",getCurrentTimeString());
      Serial.println();
      count++;
  }
}

void checkWaterQuality() {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);

    int isTurbiditySafe;
    int isECSafe;
    int isTemperatureSafe;
    int isDOSafe;
    int isPhSafe;
    
    // Turbidity check (0-100)
    if (Turbidity < 5) {
        //Safe
        isTurbiditySafe = 1;
    } else if (Turbidity >= 5 && Turbidity <= 10) {
        //Warning
        isTurbiditySafe = 2;
    } else {
        //Unsafe
        isTurbiditySafe = 0;
    }

    // EC check (0.05 - 5500)
    if (EC < 1500) {
        //Safe
        isECSafe = 1;
    } else if (EC >= 1500 && EC <= 4000) {
        //Warning
        isECSafe = 2;
    } else {
        //Unsafe
        isECSafe = 0;
    }

    // Temperature check (0.0 - 40.0)
    if (Temperature >= 5 && Temperature <= 25) {
        //Safe
        isTemperatureSafe = 1;
    } else if (Temperature > 25 && Temperature <= 30) {
        //Warning
        isTemperatureSafe = 2;
    } else {
        //Unsafe
        isTemperatureSafe = 0;
    }

    // DO check (0.0 - 14.0)
    if (DO > 6) {
        //Safe
        isDOSafe = 1;
    } else if (DO >= 4 && DO <= 6) {
        //Warning
        isDOSafe = 2;
    } else {
        //Unsafe
        isDOSafe = 0;
    }

    // pH check (6.5 - 8.5)
    if (Ph >= 6.5 && Ph <= 8.5) {
        //Safe
        isPhSafe = 1;
    } else if ((Ph >= 5 && Ph < 6.5) || (Ph > 8.5 && Ph <= 9)) {
        //Warning
        isPhSafe = 2;
    } else {
        //Unsafe
        isPhSafe = 0;
    }

    // Final determination based on all parameters
    if (isPhSafe == 1 && isDOSafe == 1 && isTemperatureSafe == 1 && isECSafe == 1 && isTurbiditySafe == 1) {
        // All parameters are safe
        digitalWrite(GREEN_LED_PIN, HIGH); 
    } else if (isPhSafe == 0 || isDOSafe == 0 || isTemperatureSafe == 0 || isECSafe == 0 || isTurbiditySafe == 0) {
        // Any parameter is unsafe
        digitalWrite(RED_LED_PIN, HIGH);
    } else {
        // Otherwise, one or more parameters are in warning range
        digitalWrite(YELLOW_LED_PIN, HIGH);
    }
}


