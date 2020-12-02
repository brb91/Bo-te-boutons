//------------------------------------------------------------
// Boite a boutons
// Pour Arduino Micro.
//
// By Luzo91
// 2020-12-02 - v1.0 - Boutons poussoirs et interrupteurs a bascule lumineux ou non fonctionnels
//------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick;

//------------------------------------------------------------
// Definir le nombre de boutons poussoirs
// ex: const int pushNumb = 10;
//------------------------------------------------------------
const int pushNumb = 10;

//------------------------------------------------------------
// Definir les pins connectés a des boutons poussoirs
// ex: int pushButton[pushNumb] = {4,5,6,7,8,9,10,14,15,16};
//------------------------------------------------------------
int pushButton[pushNumb] = {4,5,6,7,8,9,10,14,15,16};

//------------------------------------------------------------
// Definir le nombre d interrupteur a bascule
// ex: const int switchNumb = 2;
//------------------------------------------------------------
const int switchNumb = 2;

//------------------------------------------------------------
// Definir les pins connectés a des interrupteurs a bascule
// ex: int switchButton[switchNumb] = {2,3};
//------------------------------------------------------------
int switchButton[switchNumb] = {2,3};

//------------------------------------------------------------
// Definir le cablage utilise pour les interrupteurs a bascule
// true = cablage lumineux
// false = cablage standard
//------------------------------------------------------------
bool reverseSwitch = true;

//------------------------------------------------------------
// CODE
// Ne pas changer
//------------------------------------------------------------

void setup() {
  // Init boutons poussoirs
  for (int i = 0; i < pushNumb; i++)
  {
    pinMode(pushButton[i], INPUT_PULLUP);
  }

  // Init interrupteurs a bascule
  for (int i = 0; i < switchNumb; i++)
  {
    if (reverseSwitch == true)
    {
      pinMode(switchButton[i], INPUT);
    }
    else
    {
      pinMode(switchButton[i], INPUT_PULLUP);
    }
  
  
  }

  // Init Joystick
  Joystick.begin();
}

// Reg dernier statut
int lastButtonState[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void loop() {

  // Lecture des poutons poussoirs
  int currentButtonState;
  for (int i = 0; i < pushNumb; i++)
  {
    currentButtonState = !digitalRead(pushButton[i]);
    if (currentButtonState != lastButtonState[i])
    {
      Joystick.setButton(i, currentButtonState);
      lastButtonState[i] = currentButtonState;
    }
  }

  // Lecture des interrupteurs a bascule
  for (int i = 0; i < switchNumb; i++)
  {
    if (reverseSwitch == true)
    {
      currentButtonState = digitalRead(switchButton[i]);
    }
    else
    {
      currentButtonState = !digitalRead(switchButton[i]);
    }
    
    if (currentButtonState != lastButtonState[i + pushNumb])
    {
      Joystick.setButton(i + pushNumb, currentButtonState);
      lastButtonState[i + pushNumb] = currentButtonState;
    }
  }

  delay(50);
}
