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
   Position projectilePath[20];  // path of the projectile
   Position position;
   double   angleRadians;
   double   time;    // amount of time since the last firing

public:
   
   Howitzer() {
      time = 0.0;
      angleRadians = 0.0;
   }

   Howitzer(Position position) : Howitzer() { // use default as delegate constructor
      this->position = position;
   }
   
   // getters
   Position getPosition()  { return position; }
   double getAngle()       { return angleRadians; }
   double getTime()        { return time; }
   
   Position getProjectilePathAt(int index) {
      return projectilePath[index];
   }
   
   // setters
   void setPosition(Position position) { this->position = position;  }
   void setAngle(double angleRadians)  { this->angleRadians = angleRadians; }
   void setTime(double time)           { this->time = time; }

   void setProjectilePathAt(int index, Position p) {
      projectilePath[index] = p;
   }

   friend class TestHowitzer;

};

