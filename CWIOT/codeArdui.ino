#include "config.h"

//------------------WIRING------------------
// VCC -> 3.3V or 5V
// TRIG -> Digital pin 12
#define trigPin 27 // define TrigPin
// ECHO -> Digital pin 11
#define echoPin 13 // define EchoPin.
// GND -> GND


// ----------VARIABLES-----------
#define MAX_DISTANCE 200 // Maximum sensor distance is rated at 400-500cm.
// define the timeOut according to the maximum range. timeOut= 2*MAX_DISTANCE /100 /340 *1000000 = MAX_DISTANCE*58.8
float timeOut = MAX_DISTANCE * 60; 
int soundVelocity = 340; // define sound speed=340m/s
// variable pour calculer distance
int distanceActuelle;
int distanceMaximum = 20;
int distanceTouche = 20;
int distanceMaxDoigt = 0;

AdafruitIO_Feed *digital = io.feed("fingers-height");

void setup() {
  pinMode(trigPin,OUTPUT);// set trigPin to output mode
  pinMode(echoPin,INPUT); // set echoPin to input mode
  Serial.begin(9600);    // Open serial monitor at 9600 baud to see ping results.

    // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();

  delay(1000); // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(getDistance()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  distanceActuelle = getDistance();
  if(distanceActuelle < distanceMaximum){
    distanceMaximum = distanceActuelle;
    distanceMaxDoigt = distanceTouche - distanceMaximum;

    Serial.print("nouvelle distance de doigt: ");
    Serial.println(distanceMaxDoigt);

    // sauvegarder dans le feed
    digital->save(distanceMaxDoigt);
  }

}

int getDistance() {
  unsigned long pingTime;
  float distance;
  digitalWrite(trigPin, HIGH); // make trigPin output high level lasting for 10μs to trigger HC_SR04,
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTime = pulseIn(echoPin, HIGH, timeOut); // Wait for HC-SR04 to return to the high level and measure out this waiting time
  distance = (float)pingTime * soundVelocity / 2 / 10000; // calculate the distance according to the time
  int distanceint = int(round(distance)); // translate the distance to an int number
	return distanceint; // return the distance value
}
