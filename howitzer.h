//
//  howitzer.h
//  Lab08
//
//  Created by Austin Hilderbrand on 3/6/21.
//

#pragma once

#include "position.h"
#include "uiDraw.h"
#include "ground.h"

class Howitzer
{
private:
   Position position;
   double   angleRadians;
   double   time;    // amount of time since the last firing

public:
   
   Howitzer() : time(0.0), angleRadians(0.0) { }
   Howitzer(Position position) : Howitzer() { // use default as delegate constructor
      this->position = position;
   }
   
   void draw(ogstream & gout) {
      gout.drawHowitzer(position, angleRadians, time);
      
      gout.setPosition(Position(4000, 31000));
      gout << "Howitzer Angle: " << Trig::deg(angleRadians);
   }
   
   // getters
   Position getPosition()  const { return position; }
   double   getAngle()     const { return angleRadians; }

   // setters
   void setPosition(Position position) { this->position = position;  }
   void setAngle(double angleRadians)  { this->angleRadians = angleRadians; }
   void setTime(double time)           { this->time = time; }
   
   void placeOnGround(Ground * ground) {
      position.setMetersY(ground->getElevationMeters(position));
   }

   // adders
   void addAngle(double dAngle)        { angleRadians += dAngle; }

   friend class TestHowitzer;

};

