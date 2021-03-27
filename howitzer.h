//
//  howitzer.h
//  Lab08
//
//  Created by Austin Hilderbrand on 3/6/21.
//

#pragma once

#include "position.h"

class Howitzer
{
private:
   Position position;
   double   angleRadians;
   double   time;    // amount of time since the last firing

public:
   
   Howitzer() {
      time = 0.0;
      angleRadians = 0.0;
      //assert(position.getPixelsY() > 0.0);
   }

   Howitzer(Position position) : Howitzer() { // use default as delegate constructor
      this->position = position;
      assert(position.getPixelsY() > 0.0);
   }
   
   // getters
   Position getPosition()  { 
      assert(position.getPixelsY() > 0.0);
      return position; 
   }
   double getAngle()       { return angleRadians; }
   double getTime()        { return time; }
   
   // setters
   void setPosition(Position position) { 
      assert(position.getPixelsY() > 0.0);
      this->position = position;  
   }
   void setAngle(double angleRadians)  { this->angleRadians = angleRadians; }
   void setTime(double time)           { this->time = time; }

   // adders
   void addAngle(double dAngle)        { angleRadians += dAngle; }

   friend class TestHowitzer;

};

