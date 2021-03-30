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

class Demo
{
private:
   Ground               ground;        // the ground
   Position             ptUpperRight;  // size of the screen
   Howitzer             howitzer;      // howitzer cannon object
   vector<Artillery*>   artillery;     // artillery

public:
   
   Demo(Position ptUpperRight);
   void update();
   void draw(ogstream & gout);
   void handleInput(const Interface* pUI);
};
