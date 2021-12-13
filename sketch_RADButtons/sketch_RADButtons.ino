/* CUSTOM CLASS DEFINITION
 *  
 *  TODO: may want to have multiple LEDs controlled
 *  by one button --> in that case, we can have
 *  an array of LEDs instead, and methods like
 *  turnOnLED can be turnOnLEDs instead
 *  
 *  TODO: does each button need an ID number to
 *  let MaxMSP know which button is sending a signal?
 */
class RAD_Button {

  /* button fields */
  private:
    // connections to Arduino
    byte buttonPin;
    byte ledPin;
    // tracks state of the button
    int buttonState;
    // tracks when the button was last pressed
    unsigned long previousTime;

  /* button functions */
  public:
  
    RAD_Button(byte B_PIN, byte L_PIN) {
      this->buttonPin = B_PIN;
      this->buttonState = LOW;
      this->ledPin = L_PIN;
      this->previousTime = 0;
    }

    // call this in setup()
    void init() {
      pinMode(buttonPin, INPUT_PULLUP);
      pinMode(ledPin, OUTPUT);
    }

    boolean getButtonState() {
      return digitalRead(buttonPin);
    }

    boolean buttonPressed() {
      return (buttonState == HIGH); 
    }

    void reportToMaxMSP() {
      Serial.print(buttonPressed());
      Serial.print(" ");
    }

    void turnOnLED() {
      digitalWrite(ledPin, HIGH);
    }

    void turnOffLED() {
      digitalWrite(ledPin, LOW);
    }

    bool notLit(unsigned long currentTime, const long litTime) {
      return (currentTime - previousTime >= litTime);
    }

    // call this in loop()
    void looping(unsigned long currentTime, const long litTime) {
      buttonState = getButtonState();
      reportToMaxMSP();
      if (notLit(currentTime, litTime)) {
        turnOffLED();
        if (buttonPressed()) {
          previousTime = currentTime;
          turnOnLED();
        }
      }
    }
};

/* ACTUAL PROGRAM */

// a millisecond counter from the start of the program
unsigned long currentTime = 0;
// amount of time for which buttons should be lit
const long litTime = 2000;

/* TODO: make an array of these custom buttons */

// a custom "button" -- push button + LED(s)
//button(BUTTON_PIN, LED_PIN) to initalize button

RAD_Button button1(13, 7);
RAD_Button button2(12, 6);
RAD_Button button3(11, 5);
RAD_Button button4(10, 4);
RAD_Button button5(9, 3);
RAD_Button button6(8, 2);

void setup() {
  Serial.begin(9600);
  button1.init();
  button2.init();
  button3.init();
  button4.init();
  button5.init();
  button6.init();
}

void loop() {
  // set current time the MILLISECOND the program starts
  currentTime = millis() + litTime;
  // perform update actions on the button
  button1.looping(currentTime, litTime);
  button2.looping(currentTime, litTime);
  button3.looping(currentTime, litTime);
  button4.looping(currentTime, litTime);
  button5.looping(currentTime, litTime);
  button6.looping(currentTime, litTime);
  
  Serial.println();
}
