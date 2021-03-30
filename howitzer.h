/**********************************************************************
 * howitzer.h
 * Howitzer class declaration

 * Authors:
 *    Austin Hilderbrand
 *    Elijah Harrison
 *
 * The Howitzer class describes the howitzer.
 **********************************************************************/

#pragma once

#include "position.h"
#include "uiDraw.h"
#include "ground.h"
#include "artillery.h"
#include "uiInteract.h"

class Howitzer
{
private:
   Position position;
   double   angleRadians;
   double   time; // amount of time since the last firing
   
   bool displayControls = true;

public:
   
   Howitzer();
   Howitzer(Position position);

   // update/draw/handle methods
   void draw(ogstream& gout);
   void handleInput(const Interface* pUI);

   // helper methods
   void placeOnGround(Ground* ground);
   Artillery* fire();
   
   // getters
   Position getPosition()  { return position;     }
   double getAngle()       { return angleRadians; }
   
   // setters
   void setPosition(Position position) { this->position = position; }
   void setAngle(double angleRadians)  { this->angleRadians = angleRadians; }
   void incrementTime(double time)     { this->time += time; }

   // adders
   void addAngle(double dAngle)        { angleRadians += dAngle; }

   friend class TestHowitzer;
};

