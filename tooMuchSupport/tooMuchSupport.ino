
/*
Creation & Computation
FSR sensor workshop - pressure meter

This code builds on the basic knightrider setup by mapping the value of a pressure sensor to the number of leds lit up

*1 Connect an FSR using a 10K resistor to pin A0
*2 Open the Serial monitor to view the raw and mapped value from the sensor
*3 Adjust the max_pressure variable to match the value range that represents your sensor

*/
// Global variables 

bool debugLights = true;
int sensor_pin1 = A3;  // Analog input pin for the pressure sensor
int sensor_pin2 = A2; // Analog input pin for the pressure sensor

int sensor_value1;
int sensor_value2;

int normalizedSensorValue;
int sensorDifferenceThreshold = 150; 
int sensorStartThreshold = 40;
bool sensorMatches;

const int num_leds = 4;     // Number of LEDs used for display
int mappedSensorValue = 0;

int first_led_pin = 2;

int led1_Pin = 6;
int thresholdLight1Low = 40;
int thresholdLight1High = 200;
int led1_brightness = 0;
bool led1Active;

int led2_Pin = 5;
int thresholdLight2Low = 100;
int thresholdLight2High = 250;
int led2_brightness = 0;
bool led2Active;

int led3_Pin = 3;
int thresholdLight3Low = 150;
int thresholdLight3High = 1000;
int led3_brightness = 0;
bool led3Active;

int led4_Pin = 2;
int thresholdLight4Low = 250;
int thresholdLight4High = 1000;
int led4_brightness = 0;
bool led4Active = false;


int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by
int fadeoutAmount = 2; // how many points to fade the LED by
unsigned long previousMillis = 0;
unsigned long interval = 3;


int fadeInTime = 1000; // Time for one complete oscillation (milliseconds)
int fadeOutTime = 1000; // Time for one complete oscillation (milliseconds)

// Array to store LED pin numbers
int led_pins[num_leds];

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize LED pins as outputs
  InitPin(led1_Pin, 0);
  InitPin(led2_Pin, 1);
  InitPin(led3_Pin, 2);
  InitPin(led4_Pin, 3);
}

void InitPin(int pin, int place)
{
    led_pins[place] = pin;
    pinMode(led_pins[place], OUTPUT);
}

void loop(){
  // Control the oscillating LED 1
  //int led1_brightness = oscillate(led1_minBrightness, led1_maxBrightness, led1_oscillationTime);
  NormalizeSensors();

  
  DebugEachSensor();

  if(debugLights == true)
  {
      testLights();
  }
  else
  {
    CheckLights();
   runLightsFromSensors();
  }





  //DebugEachSensor();
 // DebugSensors();
  //delay(10);
}

void runLightsFromSensors(){
analogWrite(led4_Pin, led4_brightness);
    analogWrite(led1_Pin, led1_brightness);
  analogWrite(led2_Pin, led2_brightness);
  analogWrite(led3_Pin, led3_brightness);
} 

void testLights(){
  analogWrite(led1_Pin, 255);
  analogWrite(led2_Pin, 255);
  analogWrite(led3_Pin, 255);
   analogWrite(led4_Pin, 255);

}




void CheckLights()
{

  if (normalizedSensorValue > thresholdLight1Low && normalizedSensorValue < thresholdLight1High)
    FadeIn1();
  else
    FadeOut1();


  if (normalizedSensorValue > thresholdLight2Low && normalizedSensorValue < thresholdLight2High)
    FadeIn2();
  else
    FadeOut2();

  if (normalizedSensorValue > thresholdLight3Low && normalizedSensorValue < thresholdLight3High)
    FadeIn3();
  else
    FadeOut3();

  if (normalizedSensorValue > thresholdLight4Low && normalizedSensorValue < thresholdLight4High)
    FadeIn4();
  else
    FadeOut4();




  }




void NormalizeSensors(){
   int sensor_value1 = analogRead(sensor_pin1);
   int sensor_value2 = analogRead(sensor_pin2);

  if(sensor_value1 - sensor_value2 * 1 <= sensorDifferenceThreshold && sensor_value1 > sensorStartThreshold) 
  {
    
  normalizedSensorValue = (sensor_value1 + sensor_value2) / 2;
  
  sensorMatches = true;
  } else {
    sensorMatches = false;
    normalizedSensorValue = 0;
  }

//

}

void DebugEachSensor(){

/*
  Serial.print(" L1: ");
  Serial.print(analogRead(led1_brightness));
    Serial.print(" L2: ");
  Serial.print(analogRead(led2_brightness));
      Serial.print(" L3: ");
  Serial.print(analogRead(led3_brightness));
      Serial.print(" L4: ");
  Serial.print(analogRead(led4_brightness));
*/


  Serial.print(" 1: ");
  Serial.print(analogRead(A0));
    Serial.print(" 2: ");
  Serial.print(analogRead(A1));
    Serial.print(" 1: ");
  Serial.print(analogRead(A2));
    Serial.print(" 2: ");
  Serial.print(analogRead(A3));
    Serial.print(" 1: ");
  Serial.print(analogRead(A4));
    Serial.print(" 2: ");
  Serial.println(analogRead(A5));
  /*
    Serial.print(" Normal: ");
  Serial.println(normalizedSensorValue);
   Serial.print(" Match: ");
    Serial.print(sensorMatches);
    */
}

void DebugSensors()
{

  Serial.print(" Normal: ");
  Serial.print(normalizedSensorValue);
    Serial.print(" Match: ");
    Serial.print(sensorMatches);
        Serial.print(" L1: ");
            Serial.print(led1_brightness);
                    Serial.print(" L2: ");
            Serial.print(led2_brightness);
                    Serial.print(" L3: ");
            Serial.print(led3_brightness);
                    Serial.print(" L4: ");
            Serial.println(led4_brightness);
    }



void FadeIn1() {
unsigned long currentMillis = millis(); // grab current time
//analogWrite(led, brightness); // set the brightness of ledPin:

if (currentMillis - previousMillis >= interval && led1_brightness < 255){
led1_brightness = led1_brightness + fadeAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led1_brightness > 255)
  led1_brightness = 255;
}

int FadeOut1() {
unsigned long currentMillis = millis(); // grab current time
//analogWrite(led, brightness); // set the brightness of ledPin:

if (currentMillis - previousMillis >= interval && led1_brightness > 0){
led1_brightness = led1_brightness - fadeoutAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led1_brightness < 0)
  led1_brightness = 0;

}


void FadeIn2() {
unsigned long currentMillis = millis(); // grab current time
//analogWrite(led, brightness); // set the brightness of ledPin:

if (currentMillis - previousMillis >= interval && led2_brightness < 255){
led2_brightness = led2_brightness + fadeAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led2_brightness > 255)
  led2_brightness = 255;
}

int FadeOut2() {
unsigned long currentMillis = millis(); // grab current time
//analogWrite(led, brightness); // set the brightness of ledPin:

if (currentMillis - previousMillis >= interval && led2_brightness > 0){
led2_brightness = led2_brightness - fadeoutAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led2_brightness < 0)
  led2_brightness = 0;


}

void FadeIn3() {
unsigned long currentMillis = millis(); // grab current time
//analogWrite(led, brightness); // set the brightness of ledPin:

if (currentMillis - previousMillis >= interval && led3_brightness < 255){
led3_brightness = led3_brightness + fadeAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led3_brightness > 255)
  led3_brightness = 255;
}

int FadeOut3() {
unsigned long currentMillis = millis(); // grab current time
//analogWrite(led, brightness); // set the brightness of ledPin:

if (currentMillis - previousMillis >= interval && led3_brightness > 0){
led3_brightness = led3_brightness - fadeoutAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led3_brightness < 0)
  led3_brightness = 0;


}

void FadeIn4() {
unsigned long currentMillis = millis(); // grab current time
//analogWrite(led, brightness); // set the brightness of ledPin:

if (currentMillis - previousMillis >= interval && led4_brightness < 255){
led4_brightness = led4_brightness + fadeAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led4_brightness > 255)
  led4_brightness = 255;
}

int FadeOut4() {
unsigned long currentMillis = millis(); // grab current time
//analogWrite(led, brightness); // set the brightness of ledPin:

if (currentMillis - previousMillis >= interval && led4_brightness > 0){
led4_brightness = led4_brightness - fadeoutAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led4_brightness < 0)
  led4_brightness = 0;


}


