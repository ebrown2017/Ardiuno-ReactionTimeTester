//Define Pins
#define RED 6
#define GREEN 5
#define BUTTON 12

void setup() {
  //Allow for outputs to COM
  Serial.begin(9600);
  //Setup Random Generator
  randomSeed(analogRead(0));

  //Set pin modes
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

  //Declare variables
  int rVal;
  int gVal;

  int endGameTimer = 5000;
  int fadeSpeed = 2;
  
  int timeLight;
  
  unsigned long reactionSpeed;
  unsigned long startTime;
  unsigned long endTime;
  unsigned long totalTime;
  
  byte timerRunning;

void loop() {
  //Generate random time for variance in LED indication
  timeLight = random(2000,10000);

  //Delays program while retaining exact millis() timing
  totalTime = millis();
  while (millis() < totalTime + timeLight){
  } 

  //Starts timer and gets millisecond started  
  if (timerRunning == 0 && digitalRead(BUTTON) == HIGH){
    timerRunning = 1;
    startTime = millis();
  }

  //Light up lED indicator green to signal to push
  rVal = 0;
  gVal = 255;
  analogWrite(GREEN, gVal);
  analogWrite(RED, rVal);

  //While test is underway (waiting for button press)
  while(timerRunning == 1 && digitalRead(BUTTON) == HIGH){
    //If light has turned red, display fail message and restart
    if(rVal == 255 || gVal == 0){
      noButtonPress();
    }

    //Refresh current color and change it after
    analogWrite(GREEN, gVal);
    analogWrite(RED, rVal);
    gVal -= 1;
    rVal += 1;

  //Delay program to ensure a gradual change in LED color, check if button is pressed during delay  
  totalTime = millis();
  while (millis() < totalTime + fadeSpeed){
        if(digitalRead(BUTTON) == LOW){
         buttonPress();
      }
    }
  }
}

void buttonPress(){
    //Get endTime and calculate reaction speed
    endTime = millis();
    reactionSpeed = endTime - startTime;
    
    //Turn off timer, turn off LED
    timerRunning = 0;
    rVal = 0;
    gVal = 0;
    analogWrite(GREEN, gVal);
    analogWrite(RED, rVal);
    
    //Display message with reaction speed
    Serial.print("Your reaction time was: ");
    Serial.print(reactionSpeed);
    Serial.print(" milliseconds.");
    Serial.println();

  //Delay at end of game 
  totalTime = millis();
  while(millis() < totalTime + endGameTimer){
  }
}

void noButtonPress(){
    //Turn off timer, turn off LED
    timerRunning = 0;
    rVal = 0;
    gVal = 0;
    analogWrite(GREEN, gVal);
    analogWrite(RED, rVal);
    //Display failure message
    Serial.print("Button failed to be pressed. You need to work on your reaction time!");
    Serial.println();

  //Delay at end of game
  totalTime = millis();
  while(millis() < totalTime + endGameTimer){
  }
}
