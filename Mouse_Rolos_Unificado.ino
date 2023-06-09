/**
  Versão de para testes. 08/05/2023
 */

#include <Mouse.h>
#define MOVIMENTO 10
#define DEBOUNCING 30     



/* Cilindro Vertical (y)    */
const int CLK1 = 9;         //16; // no pino 16 não funciona, não sei porque
const int DT1 = 10;

/* Cilindro Horizontal (x)  */
const int CLK2 = 2;
const int DT2 = 3;

/* Cilindro fixado utiliza  a roda */
const int CLK3 = 9;
const int DT3 = 10;

const int mouseButton = 5;
const int rightmouseButton = 6;
const int leftLong = 8;
const int doubleleft = 7;
const int scrollLock = 4; 
const int changeRangeBtn = 13;

int counter1 = 0;
int counter2 = 0;
int counter4Whell=0;

int currentStateCLK1 = 0;
int lastStateCLK1 = 0;

int currentStateCLK2 = 0;
int lastStateCLK2 = 0;

int currentStateCLK3 = 0;
int lastStateCLK3 = 0;


int ultimoX = 0;
int ultimoY = 0;  

int atualX = 0;
int atualY = 0;

// flags
bool fixScroll;
bool changeRange;

// multiplicador do movimento do mouse em X e Y, quanto maior o numero mais rapido fica o mouse
int range = 2;  

// flags para controle 
boolean variavel = 0, variavel2 = 1, variavel3 = 1, variavel4 = 1, variavel5 = 1, variavel6 = 1, variavel20 = 0, variavel21 = 0;

int d = 0;

unsigned long espaco = 0, a = 0;

float  t = 0.01;

void setup() 
{
  pinMode(CLK1, INPUT_PULLUP);
  pinMode(DT1, INPUT_PULLUP);

  pinMode(CLK2, INPUT_PULLUP);
  pinMode(DT2, INPUT_PULLUP);

  pinMode(mouseButton, INPUT_PULLUP);
  pinMode(leftLong, INPUT_PULLUP);
  pinMode(doubleleft, INPUT_PULLUP);
  pinMode(rightmouseButton, INPUT_PULLUP);
  pinMode(scrollLock, INPUT_PULLUP);
  pinMode(changeRangeBtn, INPUT_PULLUP);

  lastStateCLK1 = digitalRead(CLK1);
  lastStateCLK2 = digitalRead(CLK2);
  lastStateCLK3 = digitalRead(CLK3);
  
  ultimoX = encoder2();
  ultimoY = encoder1();

  fixScroll= false;
  changeRange =false;

  Mouse.begin();
}

void loop() 
{

  if (digitalRead(changeRangeBtn)==LOW)
  {
    // while no lugar do delay pareceu ser mais efetivo
    while(digitalRead(changeRangeBtn)==LOW);
    changeRange = !changeRange;  
  }

  if (digitalRead(scrollLock) == LOW)
  {
    
    while(digitalRead(scrollLock) == LOW) ;
    fixScroll = !fixScroll;   
  }

  if (changeRange)
    range = 5;
  else
    range = 1;

  
  movimentoMouse();
    
    //se o botao esquerdo for  apertado
    // input com pullup

    if (digitalRead(mouseButton) == LOW) 
    {
      if (variavel2 == 1) 
      {
        delay(DEBOUNCING);
        if (digitalRead(mouseButton) == LOW) 
        {
          Mouse.press(MOUSE_LEFT);
          variavel2 = 0;
        }
      }
    } 
    else 
    {
      variavel2 = 1;
    }

    // se o botao direito for apertado
    if (digitalRead(rightmouseButton) == LOW) 
    {
      if (variavel3 == 1) 
      {
        delay(DEBOUNCING);
        if (digitalRead(rightmouseButton) == LOW) 
        {
          Mouse.press(MOUSE_RIGHT);
          variavel3 = 0;
        }
      }
    } 
    else 
    {
      Mouse.release(MOUSE_RIGHT);
      variavel3 = 1;
    }

  //se o botao de clique duplo for apertado
  if (digitalRead(doubleleft) == LOW) 
  {
    if (variavel4 == 1) 
    {
      delay(DEBOUNCING);
        if (digitalRead(doubleleft) == LOW) 
        {
          // muda o estado l?gico do bot?o
          if (!Mouse.isPressed(MOUSE_LEFT)) 
          {
            Mouse.click(MOUSE_LEFT);
            delay(200);
            Mouse.click(MOUSE_LEFT);
            delay(500);
            variavel4 = 0;
          }
        }
    }
  } 
  else 
  {
      variavel4 = 1;
  }
  //se o botao de clique longo ? apertado
  if (digitalRead(leftLong) == LOW) 
  {
    delay(DEBOUNCING);
    if (digitalRead(leftLong) == LOW && variavel == 1) 
    {
      // muda o estado l?gico do bot?o
      Mouse.press(MOUSE_LEFT);
      variavel = !variavel;
      variavel5 = !variavel5;
    }
  } 
  else 
  {
    variavel = 1;
  }
  if (variavel2 == 0 || variavel6 == 0) 
  {
    variavel5 = 1;
  }
  if (variavel2 == 1 && variavel5 == 1 && variavel6 == 1) 
  {
    Mouse.release(MOUSE_LEFT);
  }
  //Serial.println(encoderForWhell());
}

int encoder1() 
{
  currentStateCLK1 = digitalRead(CLK1);
  if (currentStateCLK1 != lastStateCLK1  && currentStateCLK1 == 1) 
  {
    if (digitalRead(DT1) != currentStateCLK1) {
      counter1--;
    } 
    else 
    {
      counter1++;
    }
  }
  lastStateCLK1 = currentStateCLK1;
  if ((counter1 > 20000) || (counter1 < -20000)) 
  {
    counter1 = 0;
  }
  return counter1;
}

int encoderForWhell() 
{
  currentStateCLK3 = digitalRead(CLK3);

  if (currentStateCLK3 != lastStateCLK3  && currentStateCLK3 == 1) {
    if (digitalRead(DT3) != currentStateCLK3) {
      counter4Whell -=1;
    } 
    else {
      counter4Whell +=1;
    }
  }

  lastStateCLK3 = currentStateCLK3;

  if ((counter4Whell > 1) || (counter4Whell < -1)) {
    counter4Whell = 0;
  }
  return counter4Whell;
}


int encoder2() 
{
  currentStateCLK2 = digitalRead(CLK2);
  
  if (currentStateCLK2 != lastStateCLK2  && currentStateCLK2 == 1) {
    
    if (digitalRead(DT2) != currentStateCLK2) {
      counter2--;
    } else {
      counter2++;
    }
  }
  lastStateCLK2 = currentStateCLK2;

  if ((counter2 > 20000) || (counter2 < -20000)) {
    counter2 = 0;
  }
  return counter2;
}

void movimentoMouse() 
{
  float  xDistance = 0;
  float  yDistance = 0;

  atualX = encoder2();
  atualY = encoder1();

  if (atualX != ultimoX) 
  {
    if ((atualX - ultimoX) >= 1) 
    {
      xDistance = xDistance + (MOVIMENTO * range);
    } else 
    {
      xDistance = xDistance - (MOVIMENTO * range );
    }
    ultimoX = atualX;
  }
  if (atualY != ultimoY) 
  {
    if ((atualY - ultimoY) >= 1) 
    {
      yDistance = yDistance - (MOVIMENTO * range);
    }
    else 
    {
      yDistance = yDistance + (MOVIMENTO * range);
    }
    ultimoY = atualY;
  }
  if (fixScroll)
  {
    Mouse.move(xDistance, 0,encoderForWhell()*range);
    counter4Whell = 0;
  }
  else
    Mouse.move(xDistance, yDistance,0);
 
  delay(1);
}
