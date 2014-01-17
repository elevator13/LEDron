int ledPin = 13; //Don't use this

int baseChip = 0;
int counter = 0;
int curRandPin;

int clockPin = 11;
int frame = 0;

//first 8 (pins 0-7, from basechip): y
//clocks (pins 8-10): x
//otherPins (12,13...,A5): z


//Lighting up column (z-wise): hit all otherPins with LOW,
//and choose a random pin from 0-7 to HIGH (all others LOW).

//Rows in x,y: hit all but one otherPins with HIGH,
//then (???) choose all pins from 0-7 to HIGH.
//Clocks must figure into this somehow...

int otherPins[] = {12,13,A0,A1,A2,A3,A4,A5};
int reality[] = {2,4,3,5,1,7,0,6};


int xPins[] = {8,9,10};
int yPins[] = {0,1,2,3,4,5,6,7};
int zPins[] = {A0,A2,A1,A3,13,A5,12,A4};
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

void negate(int pin, int output)
{
  if (output == 0)
    digitalWrite(pin,HIGH);
  else
    digitalWrite(pin,LOW);
}

void setXpins(int num)
{
 num = num %8;
 digitalWrite(xPins[0],num & 1);
 digitalWrite(xPins[1],num & 2);
 digitalWrite(xPins[2],num & 4);
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
 int cubedata[8][8][8];

void setup()
{
//  Serial.begin(9600);
  curLayer = 0;
  int i = 0;
  pinMode(clockPin, OUTPUT);
  for (i = 0; i < 3; i++)
  {
    pinMode(xPins[i],OUTPUT);
    digitalWrite(xPins[i],LOW);
  }
  
  for (i = 0; i < 8; i++)
  {
    pinMode(yPins[i],OUTPUT);
    digitalWrite(yPins[i],LOW);
  }
  
  for (i = 0; i < 8; i++)
  {
    pinMode(zPins[i], OUTPUT);
    digitalWrite(zPins[i], HIGH);
  }
  //initializa cube
  for (i=0; i<8;i++)
  {
      for (int j=0; j<8;j++)
      {
            for (int k=0; k<8;k++){
              {
                cubedata[i][j][k] = 0;
              }
            }
      }
  }
}

void clearZpins()
{
 for(int i = 0; i<8; i++)
 {
  digitalWrite(zPins[i],HIGH);
  } 
}

void clearYpins()
{
 for(int i = 0; i<8; i++)
 {
  digitalWrite(yPins[i],LOW);
  } 
}

 
                    
void writeData(int data[8][8][8])
{
 for(int i=0; i<8; i++)
 {
     setXpins(i);
     clearYpins();
     clearZpins();
  
     for (int j=0; j<8;j++)
     {
       for( int k=0;k<8;k++)
       {
         if (data[i][j][k] == 1)
         {
           digitalWrite(zPins[k],LOW);
         }
         else
         {
           digitalWrite(zPins[k],HIGH);
         }
         digitalWrite(yPins[j],data[i][j][k]);
         
       }

     }
 }  
  
}

 int i =0;
 int j = 0;
 int k = 7;
int count = 0;

int pattern[][3] = 
  {//snake across 72 steps 
  {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{0,1,0},
   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{0,1,0},
   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{0,1,0},
   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{0,1,0},   
   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{0,1,0},
   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{0,1,0},
   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{0,1,0},
   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
   //spiral 28 steps
   {0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},
   {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
   {0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},
   {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},
   {0,-1,0},{0,-1,0},{0,-1,0},
   {1,0,0},{1,0,0},
   {0,1,0},
   //reset 7 steps
   {0,-1,0},{0,-1,0},{0,-1,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0}
    };
   int lenpat = 106;
void loop()
{
  int stepsize = 25;
delay(1);
  digitalWrite(clockPin,LOW);
    
  writeData(cubedata);

  cubedata[i][j][k] = 0;
  if (count %stepsize == 0)
  {
    int stepnum = (count/stepsize)% lenpat;
    i += pattern[stepnum][0];
    j += pattern[stepnum][1];
    k = 7;
 //   k += pattern[stepnum][3];
    
  }
    
/*    Serial.print(i);
    Serial.print(",");
    Serial.print(j);
    Serial.print(",");
    Serial.print(k);
    Serial.print("\n");
    delay(1);
   */
  count++;
  cubedata[i][j][k] = 1;

 digitalWrite(clockPin,HIGH);
 
}

/*
void loop()
{
  int i,j1,j2,j3,k;
  i = random(0,8);
  j1 = random(0,2);
  j2 = random(0,2);
  j3 = random(0,2);
  k = random(0,8);
  negate(xPins[i],digitalRead(xPins[i]));
digitalWrite(yPins[0],HIGH);
digitalWrite(yPins[1],HIGH);
digitalWrite(yPins[2],LOW);

//negate(yPins[0],digitalRead(yPins[0]));
//  negate(yPins[2],digitalRead(yPins[2]));
  negate(zPins[k],digitalRead(zPins[k]));
  delay(100);
}*/



/*
void loop()
{
  int i,j,k;
  for (i= 0; i < 3; i++)
  {
    bto(yPins[i],HIGH);
    delay(100);
    bto(yPins[i],LOW);   
  }
  for (i= 0; i < 8; i++)
  {
    bto(xPins[i],HIGH);
    delay(100);
    bto(xPins[i],LOW);
  }
  for(i = 0; i < 8; i++)
  {
    bto(zPins[i],LOW);
    delay(100);
    bto(zPins[i],HIGH);
  }
*/
  /*
  for (i = 0; i < 8; i++)
  {
    for( j1 = 0; j1 < 3; j1++)
    {
         for (k = 0; k < 8; k++)
         {
            negate(xPins[i],digitalRead(xPins[i]));
            negate(yPins[j1],digitalRead(yPins[j1]));
            negate(zPins[k],digitalRead(zPins[k]));
            delay(100);
         }
    }
  }
} */
