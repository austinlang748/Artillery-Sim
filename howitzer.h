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
   double   time;    // amount of time since the last firing
   
   bool displayControls = true;

public:
   
   Howitzer() : time(0.0), angleRadians(0.0) { }
   Howitzer(Position position) : Howitzer() { // use default as delegate constructor
      this->position = position;
      assert(position.getPixelsY() > 0.0);
   }
   
   void draw(ogstream & gout) {
      
      // draw cannon
      gout.drawHowitzer(position, angleRadians, time);
      
      // draw some text
      
      // howitzer angle
      gout.setPosition(Position(4000, 31000));
      gout << "Howitzer Angle: " << Trig::deg(angleRadians);
      
      // initial instructions for controls
      if (displayControls) {
         gout.setPosition(Position(3500, 11500));
         gout << "Controls";
         gout.setPosition(Position(3500, 10000));
         gout << "LEFT/RIGHT";
         gout.setPosition(Position(3500, 9000));
         gout << "- change howitzer angle by large amount";
         gout.setPosition(Position(3500, 8000));
         gout << "UP/DOWN";
         gout.setPosition(Position(3500, 7000));
         gout << "- change howitzer angle by a small amount";
      }
   }
   
   void handleInput(const Interface* pUI) {
      if (displayControls) // hide controls instructions on any key press
         if (pUI->keysAreHeld()) displayControls = false;
   }
   
   Artillery* fire() { 
      time = 0.00;
      return new Artillery(position, angleRadians); }
   
   // getters
   Position getPosition()  { 
      assert(position.getPixelsY() > 0.0);
      return position; 
   }
   double getAngle()       { return angleRadians; }
   
   // setters
   void setPosition(Position position) { 
      assert(position.getPixelsY() > 0.0);
      this->position = position;  
   }
   void setAngle(double angleRadians)  { this->angleRadians = angleRadians; }
   void incrementTime(double time)           { this->time += time; }
   
   void placeOnGround(Ground * ground) {
      position.setMetersY(ground->getElevationMeters(position));
   }

   // adders
   void addAngle(double dAngle)        { angleRadians += dAngle; }

   friend class TestHowitzer;

};

