int ledPin = 13; //Don't use this

int baseChip = 0;
int counter = 0;

int latchPin = 11;

int clock1Pin = 8;
int clock2Pin = 9;
int clock3Pin = 10;
//first 8 (pins 0-7, from basechip): y
//clocks (pins 8-10): x
//otherPins (12,13...,A5): z

int otherPins[] = {12,13,A0,A1,A2,A3,A4,A5};
//byte[8][8][8] isOn;
int curLayer;

/*Turn voltage to a pin on/off,
 *depending on the argument "output"
 */
void bto(int pin, int output)
{
  if (output != 0)
    digitalWrite(pin,HIGH);
  else
    digitalWrite(pin,LOW);
}
/*
void clearAll()
{
  int i,j,k;
  for (i=0; i < 8; i++)
    for (j=0; j < 8; j++)
      for (k=0; k < 8; k++)
        isOn[i][j][k] = 0;        
}
*/
void setup()
{
  curLayer = 0;
  int i = 0;
  pinMode(latchPin, OUTPUT);
  pinMode(clock1Pin,OUTPUT);
  pinMode(clock2Pin,OUTPUT);
  pinMode(clock3Pin,OUTPUT);
  
  for (i = baseChip; i < baseChip + 8; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  
  digitalWrite(clock1Pin,LOW);
  digitalWrite(clock2Pin,LOW);
  digitalWrite(clock3Pin,LOW);
  for (i = 0; i < 8; i++)
  {
    pinMode(otherPins[i], OUTPUT);
    digitalWrite(otherPins[i], LOW);
  }
  //digitalWrite(latchPin,LOW);
  digitalWrite(curLayer,HIGH);
}

void loop()
{
  if (curLayer == 8)
    return;
  delay(300);
  /*Cycle the clocks.  Will iterate from 0 to 7, then
   *switch to a new layer and repeat.
   */
  bto(clock1Pin, counter & 1);
  bto(clock2Pin, counter & 2);
  bto(clock3Pin, counter & 4);
  counter++;
  if (counter >= 8)
  {
    counter = 0;
    /*Will only turn on one column at a time,
     *instead of continuously lighting new columns.*/
    //digitalWrite(curLayer,LOW);
    curLayer++;
    curLayer = curLayer % 8;
    digitalWrite(curLayer,HIGH);
  }
  /*
  counter++;
  if (counter > 1000)
  {
    digitalWrite(i,HIGH);
    counter = 0;
  }
  else if (counter <= 5)
  {
    digitalWrite(i,LOW);
  }
  */
}
