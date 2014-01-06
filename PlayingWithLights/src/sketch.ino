// Set the Digital PIN numbers
const int RGB_RED_LED_PIN = 9;
const int RGB_GREEN_LED_PIN = 10;
const int RGB_BLUE_LED_PIN = 11;
const int BLUE_LED_PIN = 2;

// Init RGB LED color intensity values
int redIntensity = 0;
int greenIntensity = 0;
int blueIntensity = 0;

// Color change time in ms
const int DISPLAY_TIME = 100;

void setup() {
  // Setup pin mode for the blue LED's pin
  pinMode(BLUE_LED_PIN,OUTPUT);
}

// Simple function used to blink the blue LED
void blinkblue(int count){
  for (int i=0; i<count; i++){
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(DISPLAY_TIME);
    digitalWrite(BLUE_LED_PIN, LOW);
    delay(DISPLAY_TIME);
  }
}

// Main loop function
void loop() {
  
  blinkblue(5);

  // Cycle color from red through to green
  // (In this loop we move from 100% red, 0% green to 0% red, 100% green)
  for (greenIntensity = 0; greenIntensity <= 255; greenIntensity+=5) {
        redIntensity = 255-greenIntensity;
        analogWrite(RGB_GREEN_LED_PIN, greenIntensity);
        analogWrite(RGB_RED_LED_PIN, redIntensity);
        delay(DISPLAY_TIME);
  }

  blinkblue(5);

  // Cycle color from green through to blue
  // (In this loop we move from 100% green, 0% blue to 0% green, 100% blue)  
  for (blueIntensity = 0; blueIntensity <= 255; blueIntensity+=5) {
        greenIntensity = 255-blueIntensity;
        analogWrite(RGB_BLUE_LED_PIN, blueIntensity);
        analogWrite(RGB_GREEN_LED_PIN, greenIntensity);
        delay(DISPLAY_TIME);
  }

  blinkblue(5);

  // Cycle cycle from blue through to red
  // (In this loop we move from 100% blue, 0% red to 0% blue, 100% red)    
  for (redIntensity = 0; redIntensity <= 255; redIntensity+=5) {
        blueIntensity = 255-redIntensity;
        analogWrite(RGB_RED_LED_PIN, redIntensity);
        analogWrite(RGB_BLUE_LED_PIN, blueIntensity);
        delay(DISPLAY_TIME);
  }

}



