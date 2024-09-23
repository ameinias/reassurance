
/*
reassurance 
g blekkenhorst for creation & computation

Credits:

FSR sensor workshop - pressure meter  https://github.com/DigitalFuturesOCADU/CC2024/blob/main/experiment1/fsrWorkshop_pressureMeter/fsrWorkshop_pressureMeter.ino
fade function via jimmymcknife https://forum.arduino.cc/t/fade-using-millis/440233

TODO: knock fade back down - it got boosted for testing
*/
// Global variables 

bool debugEnableAllLights = false;
bool debugPrintLights = true;
bool debugprintSensors = true;
int sensor_pin1 = A1;  // Analog input pin for the pressure sensor
int sensor_pin2 = A2; // Analog input pin for the pressure sensor

int sensor_value1;
int sensor_value2;

int normalizedSensorValue;
int sensorDifferenceThreshold = 150; // the allowed difference between the two sensors
int sensorStartThreshold = 40; // ignore sensor input below this threshold 
bool sensorMatches; // returns true if both sensors have similar outputs


int mappedSensorValue = 0;

int first_led_pin = 2;
const int num_leds = 4;     // Number of LEDs used for display
int led_pins[num_leds];

// Each pin has it's pin, the threshold where it fades in and fades out, a variable to hold the current brightness, and a bool.
int led1_Pin = 2;  
int thresholdLight1Low = 40;
int thresholdLight1High = 200;
int led1_brightness = 0;
bool led1Active;

int led2_Pin = 3;
int thresholdLight2Low = 100;
int thresholdLight2High = 200;
int led2_brightness = 0;
bool led2Active;

int led3_Pin = 4;
int thresholdLight3Low = 150;
int thresholdLight3High = 1000;
int led3_brightness = 0;
bool led3Active;

int led4_Pin = 5;
int thresholdLight4Low = 200;
int thresholdLight4High = 1000;
int led4_brightness = 0;
bool led4Active = false;


int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by 5
int fadeoutAmount = 5; // how many points to fade the LED by 4
unsigned long previousMillis = 0;
unsigned long interval = 3;

#pragma region SETUP

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
#pragma endregion

void loop(){

  NormalizeSensors();
  DebugSerial();



  if(debugEnableAllLights == true)
  {
      testLights();
  }
  else
  {
    SingleLight1();
    SingleLight2();
    SingleLight3();
    SingleLight4();

   //CalculateBrightnessfromSensors();
   //ControlLights();
  }

  delay(100);
}


#pragma region Regular fuctions
void NormalizeSensors(){

  // Checks that both sensors have similar readings and find a middle value to send to the lights. 

   sensor_value1 = analogRead(sensor_pin1);
   sensor_value2 = analogRead(sensor_pin2);

  if(sensor_value1 - sensor_value2 * 1 <= sensorDifferenceThreshold && sensor_value1 > sensorStartThreshold) 
  {
    
  normalizedSensorValue = (sensor_value1 + sensor_value2) / 2;
  sensorMatches = true;

  } else {
    sensorMatches = false;
    normalizedSensorValue = 0;
  }

}

#pragma region New Lights

void SingleLight1()
{ 

    if (normalizedSensorValue > thresholdLight1Low && normalizedSensorValue < thresholdLight1High)
    FadeIn1();
  else
    FadeOut1();

  analogWrite(led1_Pin, led1_brightness);

if(led1_brightness > 0)
    {
    Serial.print("LIGHT 1: ");
    Serial.print(normalizedSensorValue);
    Serial.print(" ");
    Serial.print(thresholdLight1Low);
    Serial.print(" ");
    Serial.print(thresholdLight1High);
    Serial.print(" p: ");
    Serial.print(analogRead(led1_Pin));
    Serial.print(" b: ");
    Serial.println(led1_brightness);
    }
}

void SingleLight2()
{ 

    if (normalizedSensorValue > thresholdLight2Low && normalizedSensorValue < thresholdLight2High)
    FadeIn2();
  else
    FadeOut2();

  analogWrite(led2_Pin, led2_brightness);

if(led2_brightness > 0)
    {
    Serial.print("LIGHT 2: ");
    Serial.print(normalizedSensorValue);
    Serial.print(" ");
    Serial.print(thresholdLight2Low);
    Serial.print(" ");
    Serial.print(thresholdLight2High);
    Serial.print(" p: ");
    Serial.print(analogRead(led2_Pin));
    Serial.print(" b: ");
    Serial.println(led2_brightness);
    }
}

void SingleLight3()
{ 

    if (normalizedSensorValue > thresholdLight3Low && normalizedSensorValue < thresholdLight3High)
    FadeIn3();
  else
    FadeOut3();

  analogWrite(led3_Pin, led3_brightness);

if(led3_brightness > 0)
    {
    Serial.print("LIGHT 3: ");
    Serial.print(normalizedSensorValue);
    Serial.print(" ");
    Serial.print(thresholdLight3Low);
    Serial.print(" ");
    Serial.print(thresholdLight3High);
    Serial.print(" p: ");
    Serial.print(analogRead(led3_Pin));
    Serial.print(" b: ");
    Serial.println(led3_brightness);
    }
}

void SingleLight4()
{ 

    if (normalizedSensorValue > thresholdLight4Low && normalizedSensorValue < thresholdLight4High)
    FadeIn4();
  else
    FadeOut4();

  analogWrite(led4_Pin, led4_brightness);

if(led4_brightness > 0)
    {
    Serial.print("LIGHT 4: ");
    Serial.print(normalizedSensorValue);
    Serial.print(" ");
    Serial.print(thresholdLight4Low);
    Serial.print(" ");
    Serial.print(thresholdLight4High);
    Serial.print(" p: ");
    Serial.print(analogRead(led4_Pin));
    Serial.print(" b: ");
    Serial.println(led4_brightness);
    }
}

#pragma endregion

void CalculateBrightnessfromSensors()
{

  // Compares each lights threshold against the normalized sensor data to decide if it should fade in or out. 

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

void ControlLights() 
{
   // Continuously updates the _brightness varaibles, which are 
   // calculated in CheckLights()

  analogWrite(led4_Pin, led4_brightness);
  analogWrite(led1_Pin, led1_brightness);
  analogWrite(led2_Pin, led2_brightness);
  analogWrite(led3_Pin, led3_brightness);
} 


#pragma endregion

#pragma region Fades
/////////////////////////////////////// FADES /////////////////////////////

// The following fuctions were created because for some reason, creating a single function 
// for fade in and fade out and passing in parameters for each light didn't work - it would 
// only play for a frame. This is a work around. 


void FadeIn1() {
unsigned long currentMillis = millis(); // grab current time


if (currentMillis - previousMillis >= interval && led1_brightness < 255){
led1_brightness = led1_brightness + fadeAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led1_brightness > 255)
  led1_brightness = 255;
}

int FadeOut1() {
unsigned long currentMillis = millis(); // grab current time


if (currentMillis - previousMillis >= interval && led1_brightness > 0){
led1_brightness = led1_brightness - fadeoutAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led1_brightness < 0)
  led1_brightness = 0;

}


void FadeIn2() {
unsigned long currentMillis = millis(); // grab current time


if (currentMillis - previousMillis >= interval && led2_brightness < 255){
led2_brightness = led2_brightness + fadeAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led2_brightness > 255)
  led2_brightness = 255;
}

int FadeOut2() {
unsigned long currentMillis = millis(); // grab current time


if (currentMillis - previousMillis >= interval && led2_brightness > 0){
led2_brightness = led2_brightness - fadeoutAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led2_brightness < 0)
  led2_brightness = 0;


}

void FadeIn3() {
unsigned long currentMillis = millis(); // grab current time


if (currentMillis - previousMillis >= interval && led3_brightness < 255){
led3_brightness = led3_brightness + fadeAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led3_brightness > 255)
  led3_brightness = 255;
}

int FadeOut3() {
unsigned long currentMillis = millis(); // grab current time


if (currentMillis - previousMillis >= interval && led3_brightness > 0){
led3_brightness = led3_brightness - fadeoutAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led3_brightness < 0)
  led3_brightness = 0;


}

void FadeIn4() {
unsigned long currentMillis = millis(); // grab current time


if (currentMillis - previousMillis >= interval && led4_brightness < 255){
led4_brightness = led4_brightness + fadeAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led4_brightness > 255)
  led4_brightness = 255;
}

int FadeOut4() {
unsigned long currentMillis = millis(); // grab current time


if (currentMillis - previousMillis >= interval && led4_brightness > 0){
led4_brightness = led4_brightness - fadeoutAmount; // change the brightness for next time through the loop:
previousMillis = millis();
}
if (led4_brightness < 0)
  led4_brightness = 0;


}

#pragma endregion

#pragma region DEBUGS
/////////////////////////////////////// DEBUGS /////////////////////////////

void DebugSerial()
{


  if(debugPrintLights)
    DebugLightBrightness();

  //DebugEachSensorPin();
  
  //DebugSensorsAgain();
  if(debugprintSensors)
    DebugSensors();

  Serial.println("---------------------------");

}

void testLights(){
  // A debug function that ignored sensors and turns all lights on to full brightness. 
  // 2 3 5 6 (test light)

  //analogWrite(1, 50);

  analogWrite(led1_Pin, 50);
  analogWrite(led2_Pin, 50);
  analogWrite(led3_Pin, 50);
  analogWrite(led4_Pin, 50);
 
}


 void DebugLightBrightness(){

    Serial.print(" L1: ");
  Serial.print(analogRead(led1_brightness));
    Serial.print(" L2: ");
  Serial.print(analogRead(led2_brightness));
      Serial.print(" L3: ");
  Serial.print(analogRead(led3_brightness));
      Serial.print(" L4: ");
  Serial.println(analogRead(led4_brightness));

 }
void DebugEachSensorPin(){

  // debug logs for all potential pin inputs. 

  Serial.print(" A0: ");
  Serial.print(analogRead(A0));
    Serial.print(" A1: ");
  Serial.print(analogRead(A1));
    Serial.print(" A2: ");
  Serial.print(analogRead(A2));
    Serial.print(" A3: ");
  Serial.print(analogRead(A3));
  //   Serial.print(" 5: ");
  // Serial.print(analogRead(A4));
  //   Serial.print(" 6: ");
  // Serial.println(analogRead(A5));
  /*
    Serial.print(" Normal: ");
  Serial.println(normalizedSensorValue);
   Serial.print(" Match: ");
    Serial.print(sensorMatches);
    */
}

void DebugSensors()
{

   //int sensor_value1 = analogRead(sensor_pin1);
   //int sensor_value2 = analogRead(sensor_pin2);
  
    Serial.print(" S1: ");
  Serial.print(analogRead(sensor_pin1));
    Serial.print(" S2: ");
  Serial.print(analogRead(sensor_pin2)); 
  Serial.print(" Normal: ");
  Serial.print(normalizedSensorValue);
    Serial.print(" Match: ");
    Serial.println(sensorMatches);
    }

    void DebugSensorsAgain(){
          Serial.print(" v_sensor: ");
  Serial.print(analogRead(A3));
    Serial.print(" v_sensor: ");
  Serial.print(analogRead(sensor_pin1));
    Serial.print(" v_value: ");
      Serial.println(sensor_value1);

    }

#pragma endregion

