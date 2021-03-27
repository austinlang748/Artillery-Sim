/**********************************************************************
 * demo.h
 * Demo class declaration

 * Authors:
 *    Austin Hilderbrand (creator of functions)
 *    Elijah Harrison (populated functions)
 *
 * The Demo class describes the basic gameplay elements.
 **********************************************************************/

#pragma once

#include "uiDraw.h"
#include "uiInteract.h"
#include "ground.h"     // for GROUND
#include "howitzer.h"   // for HOWITZER
#include "artillery.h"  // for ARTILLERY

/********************************************************************************
 * CLASS: Demo
 * Test structure to capture the LM that will move around the screen
 ********************************************************************************/
class Demo
{
private:
   Ground               ground;        // the ground
   Position             ptUpperRight;  // size of the screen
   Howitzer             howitzer;      // howitzer cannon object
   vector<Artillery*>   artillery;     // artillery
   
   int keyDownTimer = 0;

public:
   
   Demo(Position ptUpperRight);
   void update();
   void draw(ogstream & gout);
   void handleInput(const Interface* pUI);
   
   Position getScreenDims() const { return ptUpperRight; }
   void setKeyDownTimer() { setKeyDownTimer(10); }
   void setKeyDownTimer(int value) { keyDownTimer = value; }
   bool keyDownTimerIsNonzero() { return keyDownTimer > 0; }
   void updateKeyDownTimer(bool debug=false) { keyDownTimer--; }
};
