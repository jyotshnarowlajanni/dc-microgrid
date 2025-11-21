#define BLYNK_TEMPLATE_ID "TMPL357G79pKS"
#define BLYNK_TEMPLATE_NAME "DC Micro Grid"
#define BLYNK_AUTH_TOKEN "UrTfNgnXg3gJI1WiEIdARCIOQ7_pfujJ"

#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

bool myflag = false;
bool myflag1 = false;
bool myflag2 = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define SOLAR_PIN 33
#define BATTERY_PIN 35
#define WIND_PIN 32

#define RELAY_SOLAR  19
#define RELAY_BATTERY 18
#define RELAY_WIND  5
#define DISHCHARGE 23

#define VOLTAGE_DIVIDER_RATIO 10.0
#define ADC_RESOLUTION 4095.0
#define REF_VOLTAGE 5.0

#define BATTERY_FULL_VOLTAGE 12.6

char ssid[] = "Anand";
char password[] = "Anand123";

char auth[] = BLYNK_AUTH_TOKEN;

float readVoltage(int pin) {
    int adcValue = analogRead(pin);
    float voltage = (adcValue / ADC_RESOLUTION) * REF_VOLTAGE * VOLTAGE_DIVIDER_RATIO;
    return voltage;
}

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);
    Blynk.begin(auth, ssid, password);

    pinMode(RELAY_SOLAR, OUTPUT);
    pinMode(RELAY_BATTERY, OUTPUT);
    pinMode(RELAY_WIND, OUTPUT);
    pinMode(DISHCHARGE, OUTPUT);

    digitalWrite(RELAY_SOLAR, LOW);
    digitalWrite(RELAY_BATTERY, LOW);
    digitalWrite(RELAY_WIND, LOW);
    digitalWrite(DISHCHARGE, LOW);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("DC Microgrid");
    lcd.setCursor(0, 1);
    lcd.print("Battery Mgmt Sys");
    delay(1500);
    lcd.clear();
}

void loop() {
    float solarVoltage = readVoltage(SOLAR_PIN);
    float batteryVoltage = readVoltage(BATTERY_PIN);
    float windVoltage = readVoltage(WIND_PIN);

    lcd.setCursor(0, 0);
    lcd.print("Bat:");
    lcd.print(batteryVoltage);
    lcd.print("V");

    lcd.setCursor(0, 1);
    lcd.print("sol:");
    lcd.print(solarVoltage);
    lcd.print("V");

    lcd.setCursor(0, 2);
    lcd.print("win:");
    lcd.print(windVoltage);
    lcd.print("V");

    if (solarVoltage >= 2 && batteryVoltage < 2 && windVoltage < 2) {
        digitalWrite(RELAY_SOLAR, HIGH);
        lcd.setCursor(11, 1);
        lcd.print("source   ");
        lcd.setCursor(11, 2);
        lcd.print("solar ");
    }

    if (batteryVoltage >= 2 && solarVoltage < 2 && windVoltage < 2) {
        digitalWrite(RELAY_BATTERY, HIGH);
        lcd.setCursor(11, 0);
        lcd.print("source   ");
        lcd.setCursor(11, 1);
        lcd.print("bat    ");
    }

    if (windVoltage >= 2 && solarVoltage < 2 && batteryVoltage < 2) {
        digitalWrite(RELAY_WIND, HIGH);
        lcd.setCursor(11, 0);
        lcd.print("source   ");
        lcd.setCursor(11, 1);
        lcd.print("wind    ");
    }

    if (solarVoltage >= 2 && batteryVoltage >= 2 && windVoltage < 2) {
        digitalWrite(RELAY_SOLAR, HIGH);
        digitalWrite(RELAY_BATTERY, HIGH);
        lcd.setCursor(11, 0);
        lcd.print("source   ");
        lcd.setCursor(11, 1);
        lcd.print("solar&bat");
    }

    if (solarVoltage < 2 && batteryVoltage >= 2 && windVoltage >= 2) {
        digitalWrite(RELAY_WIND, HIGH);
        digitalWrite(RELAY_BATTERY, HIGH);
        lcd.setCursor(11, 0);
        lcd.print("source   ");
        lcd.setCursor(11, 1);
        lcd.print("wind&bat");
    }

    if (solarVoltage > 2 && batteryVoltage < 2 && windVoltage >= 2) {
        digitalWrite(RELAY_SOLAR, HIGH);
        digitalWrite(RELAY_WIND, HIGH);
        lcd.setCursor(11, 0);
        lcd.print("source ");
        lcd.setCursor(11, 1);
        lcd.print("wind&sol");
    }

    if (solarVoltage >= 2 && batteryVoltage >= 2 && windVoltage >= 2) {
        digitalWrite(RELAY_SOLAR, HIGH);
        digitalWrite(RELAY_WIND, HIGH);
        digitalWrite(RELAY_BATTERY, HIGH);
        lcd.setCursor(11, 0);
        lcd.print("source   ");
        lcd.setCursor(11, 1);
        lcd.print("wind&sol");
        lcd.setCursor(11, 2);
        lcd.print("   bat  ");
    }

    if (solarVoltage < 2 && batteryVoltage < 2 && windVoltage < 2) {
        digitalWrite(RELAY_SOLAR, LOW);
        digitalWrite(RELAY_WIND, LOW);
        digitalWrite(RELAY_BATTERY, LOW);
        lcd.setCursor(11, 0);
        lcd.print("Grid fail");
        lcd.setCursor(11, 1);
        lcd.print("                 ");
    }

    if (batteryVoltage > BATTERY_FULL_VOLTAGE) {
        lcd.setCursor(0, 3);
        lcd.print("Battery Charged! ");
        digitalWrite(DISHCHARGE, HIGH);
    }

    if (batteryVoltage <= 1) {
        lcd.setCursor(0, 3);
        lcd.print("                 ");
    }

    if (solarVoltage <= 2 && !myflag) {
        Blynk.logEvent("solar_fail");
        myflag = true;
    }

    if (windVoltage <= 2 && !myflag1) {
        Blynk.logEvent("wind_fail");
        myflag1 = true;
    }

    if (batteryVoltage <= 2 && !myflag2) {
        Blynk.logEvent("battery_fail");
        myflag2 = true;
    }

    if (solarVoltage >= 2 && myflag) {
        myflag = false;
    }

    if (windVoltage >= 2 && myflag1) {
        myflag1 = false;
    }

    if (batteryVoltage >= 2 && myflag2) {
        myflag2 = false;
    }

    Blynk.virtualWrite(V0, solarVoltage);
    Blynk.virtualWrite(V1, batteryVoltage);
    Blynk.virtualWrite(V2, windVoltage);

    Blynk.run();
}
