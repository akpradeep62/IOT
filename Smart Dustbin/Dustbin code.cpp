#define BLYNK_TEMPLATE_ID "TMPL3TUqA7E_0"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "ANtFazdBiGsvstEl5D4F3AhVppyM_dvX"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "DARK_SPACE";
char pass[] = "11331@Sv";

BlynkTimer timer;

#define echoPin D2
#define trigPin D1

long duration;
int distance; 
int binLevel=0;

void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    binLevel=map(distance, 21, 4, 0,100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V0, distance);
    Blynk.virtualWrite(V1, binLevel);

    // Check if bin level is below a certain threshold
    if (binLevel < 20) {
        // Send a message to your Telegram bot
        Blynk.virtualWrite(V2, "Bin level is low! Please empty the bin.");
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    Blynk.begin(auth, ssid, pass);
    delay(2000);
    timer.setInterval(1000L, ultrasonic);
}

void loop() 
{
    Blynk.run();
    timer.run();
}
