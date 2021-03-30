/**********************************************************************
 * howitzer.cpp
 * Howitzer class definition

 * Authors:
 *    Austin Hilderbrand
 *    Elijah Harrison
 *
 * The Howitzer class describes the howitzer.
 **********************************************************************/

#include "howitzer.h"

/**********************************************************************
* Howitzer::Howitzer
*
* Howitzer constructors: initialize position, time, and angle
**********************************************************************/
// Default Constructor
Howitzer::Howitzer() : time(0.0), angleRadians(0.0) { }

// Conversion Contstructor: pass Position obj
Howitzer::Howitzer(Position position) : Howitzer() { // use default as delegate constructor
   this->position = position;
   assert(position.getPixelsY() > 0.0);
}

/**********************************************************************
 * Howitzer::draw
 *
 * Draw the howitzer to the screen.
 **********************************************************************/
void Howitzer::draw(ogstream & gout) {

   // draw cannon
   gout.drawHowitzer(position, angleRadians, time);

   //
   // draw some text
   // 

   // howitzer angle
   gout.setPosition(Position(4000, 31000));
   gout << "Howitzer Angle: " << Trig::deg(angleRadians);

   // initial instructions for controls
   if (displayControls) {
      Position displayPosition(3500, 11500);
      gout.setPosition(displayPosition);
      gout << "Controls";
      gout.setPosition(displayPosition.addPixelsY(-40));
      gout << "LEFT/RIGHT";
      gout.setPosition(displayPosition.addPixelsY(-20));
      gout << "- change howitzer angle by large amount";
      gout.setPosition(displayPosition.addPixelsY(-20));
      gout << "UP/DOWN";
      gout.setPosition(displayPosition.addPixelsY(-20));
      gout << "- change howitzer angle by a small amount";
   }
}

/**********************************************************************
 * Howitzer::handleInput
 *
 * Hide controls instructions on any key press.
 **********************************************************************/
void Howitzer::handleInput(const Interface* pUI) {
   if (displayControls)
      if (pUI->keysAreHeld()) displayControls = false;
}

/**********************************************************************
 * Howitzer::fire
 *
 * Fire the howitzer. Returns a new artillery object and resets the
 * time (since last firing) to 0.
 **********************************************************************/
Artillery* Howitzer::fire() {
   time = 0.00;
   return new Artillery(position, angleRadians);
}

/**********************************************************************
 * Howitzer::placeOnGround
 *
 * Configures the elevation of the howitzer to be on the surface of
 * the ground at the given x location.
 **********************************************************************/
void Howitzer::placeOnGround(Ground* ground) {
   position.setMetersY(ground->getElevationMeters(position));
}
