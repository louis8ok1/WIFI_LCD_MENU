#define BUTTON 2
int buttonState;
int prevState = HIGH;
long btDebounce    = 30;
long btMultiClick  = 600;
long btLongClick   = 500;
long btLongerClick = 2000;
long btTime = 0, btTime2 = 0;
int clickCnt = 1;
int readButton()
{
  int state = digitalRead(BUTTON);
  if( state == LOW && prevState == HIGH ) { btTime = millis(); prevState = state; return 0; } // button just pressed
  if( state == HIGH && prevState == LOW ) { // button just released
    prevState = state;
    if( millis()-btTime >= btDebounce && millis()-btTime < btLongClick ) { 
      if( millis()-btTime2<btMultiClick ) clickCnt++; else clickCnt=1;
      btTime2 = millis();
      
      return clickCnt; 
    } 
  }
  if( state == LOW && millis()-btTime >= btLongerClick ) { prevState = state; return -2; }
  if( state == LOW && millis()-btTime >= btLongClick ) { prevState = state; return -1; }
  return 0;
}
int prevButtonState=0;
int handleButton()
{
  prevButtonState = buttonState;
  buttonState = readButton();
  return buttonState;
}


void handleMenu(){
 handleButton();
  if(buttonState>0) {
    Serial.println(buttonState);
  }
}
void setup(){
  Serial.begin(9600);
  pinMode( BUTTON,INPUT_PULLUP );
}
void loop(){
  handleMenu();
}

