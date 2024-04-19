//sets highest level
const int MAX_LEVEL  = 100;

//sets array to accept a LED sequence to highest level amount
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
//initiate start level
int level  = 1;

//initiate LED pins
int green = 2;
int red = 3;
int yellow = 4;
int blue = 5;
//initalize buttons
int blueBtn = A0;
int yellowBtn = A1;
int redBtn = A2;
int greenBtn = A3;
int startBtn = A4;

//set speed of light flash
int velocity = 1000;

//Initalize LED pins, Button pins and set LEDs to low to make sure they are off
void setup() 
{
  pinMode(blueBtn, INPUT);
  pinMode(yellowBtn,  INPUT);
  pinMode(redBtn, INPUT);
  pinMode(greenBtn, INPUT);

  pinMode(green, OUTPUT);
  pinMode(red,  OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);

  digitalWrite(green, LOW);
  digitalWrite(red,  LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
}

void loop()
{
  if  (level == 1)
    generate_sequence();//generate a sequence;

    if (digitalRead(startBtn)  == LOW || level != 1) //If start button is pressed or you're winning
    {
      show_sequence();    //show the sequence
      get_sequence();     //wait for your sequence
    }
}

//Shows generated sequence
void  show_sequence()
{
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  digitalWrite(yellow,  LOW);
  digitalWrite(blue, LOW);

  for (int i = 0; i < level; i++)
  {
    digitalWrite(sequence[i],  HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(velocity);
  }
}

//Gets user input and compares to generated sequence
//if correct sequence entered jumps to right_sequence
//if incorrect jumps to wrong sequence
void  get_sequence()
{
  int flag = 0; //this flag indicates if the sequence is correct

  for  (int i = 0; i < level; i++)
  {
    flag = 0;
    while(flag == 0)
    {
      if (digitalRead(blueBtn)  == LOW)
      {
        digitalWrite(blue, HIGH);
        your_sequence[i] = blue;
        flag = 1;
        delay(200);
    
        if(your_sequence[i] != sequence[i])
        {
          wrong_sequence();
          return;
        }
        
        digitalWrite(blue,  LOW);
      } 

      if (digitalRead(yellowBtn) == LOW)
      {
        digitalWrite(yellow, HIGH);
        your_sequence[i]  = yellow;
        flag = 1;
        delay(200);
        
        if (your_sequence[i] != sequence[i])
        {
          wrong_sequence();
          return;
        }
          digitalWrite(yellow,  LOW);
      }

      if (digitalRead(redBtn) == LOW)
      {
        digitalWrite(red, HIGH);
        your_sequence[i]  = red;
        flag = 1;
        delay(200);
    
        if (your_sequence[i] != sequence[i])
        {
          wrong_sequence();
          return;
        }
          digitalWrite(red,  LOW);
      }

      if (digitalRead(greenBtn) == LOW)
      {
        digitalWrite(green, HIGH);
        your_sequence[i]  = green;
        flag = 1;
        delay(200);
    
        if (your_sequence[i] != sequence[i])
        {
          wrong_sequence();
          return;
        }
          digitalWrite(green,  LOW);
      }

    }
  }
  right_sequence();
}

//Generates a random sequence by generating a random number between 2 and 6
void generate_sequence()
{
  randomSeed(millis());  //in this way is really random!!!

  for (int i = 0; i < MAX_LEVEL; i++)
  {
    sequence[i]  = random(2,6);
  }
}

//Flashes lights 3 times and resets level back to 1 and resets speed
void wrong_sequence()
{
  for (int i = 0; i < 3;  i++)
  {
    digitalWrite(green, HIGH);
    digitalWrite(red, HIGH);
    digitalWrite(yellow,  HIGH);
    digitalWrite(blue, HIGH);
    delay(250);
    
    digitalWrite(green, LOW);
    digitalWrite(red,  LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(blue, LOW);
    delay(250);
  }

level  = 1;
velocity = 1000;
}

//Flashes all LEDS when sequence is correct
//Adds +1 to level and increases sequence speed
void right_sequence()
{
  digitalWrite(green,  LOW);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  delay(250);

  digitalWrite(green,  HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(yellow, HIGH);
  digitalWrite(blue, HIGH);
  delay(500);

  digitalWrite(green,  LOW);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  delay(500);

  if  (level < MAX_LEVEL);
  level++;

  velocity -= 55; //increase difficulty
}