/********************************************************************************
 * SOURCE FILE: demo.cpp
 *
 * Contains the implementations of the methods defined in demo.h
 *
 * AUTHOR: Elijah Harrison
 * AUTHOR: Austin Hilderbrand
 ********************************************************************************/

#include "demo.h"

 /**********************************************************************
  * Non-Default Constructor
  *
  * CLASS: Demo
  *
  * Initialize the ground and the howitzer.
  **********************************************************************/
Demo::Demo(Position ptUpperRight) :
   ptUpperRight(ptUpperRight),
   ground(ptUpperRight)
{
   Position hpos(ptUpperRight.getMetersX() * 0.2, 10);

   // initialize howitzer
   howitzer = Howitzer(hpos);
   
   // initialize ground
   ground.reset(hpos);
   
   // now that ground is initialized, reset howitzer y position
   howitzer.placeOnGround(&ground);
}

/**********************************************************************
 * METHOD: update
 *
 * CLASS: Demo
 *
 * Call this periodically to update the simulation.
 **********************************************************************/
void Demo::update() {

   howitzer.incrementTime(0.5);

   for (auto projectile : artillery) {
      // update each projectile
      projectile->update();
      
      // check for collisions
      projectile->checkCollisionsWith(&ground);
   }
}

/**********************************************************************
 * METHOD: draw
 *
 * CLASS: Demo
 *
 * Draw all objects to the screen.
 **********************************************************************/
void Demo::draw(ogstream & gout) {
   
   ground.draw(gout);                  // draw the ground first
   howitzer.draw(gout);                // draw the howitzer
   for (auto projectile : artillery)   // draw projectile (if it exists)
      projectile->draw(gout);
   if (artillery.size() > 0)           // display projectile info (for last projectile in stack)
      artillery.back()->drawInfo(gout);

   // draw some text on the screen
   
   // how to quit
   Position textPos;
   textPos.setPixels(90, 480);
   gout.setPosition(textPos);
   gout << "Press 'Q' to quit\n";
   
   // how to reset
   gout.setPosition(textPos.addPixelsX(300));
   gout << "Press 'R' to reset terrain\n";
}

/**********************************************************************
 * METHOD: handleInput
 *
 * CLASS: Demo
 *
 * Handle user input, including:
 *    Q:     quit
 *    R:     reset
 *    RIGHT: adjust aim, fast
 *    LEFT:  adjust aim, fast
 *    UP:    adjust aim, slow
 *    DOWN:  adjust aim, slow
 *    SPACE: fire howitzer
 **********************************************************************/
void Demo::handleInput(const Interface* pUI) {
   
   // move a large amount
   if ( pUI->getHeldKey(RIGHT) ) howitzer.addAngle( 0.05);
   if ( pUI->getHeldKey(LEFT)  ) howitzer.addAngle(-0.05);

   // move by a little
   if (pUI->getHeldKey(UP))
      howitzer.addAngle((howitzer.getAngle() >= 0 ? -0.003 : 0.003));
   if (pUI->getHeldKey(DOWN))
      howitzer.addAngle((howitzer.getAngle() >= 0 ? 0.003 : -0.003));

   // fire that gun
   if (pUI->getHeldKey(SPACE))
      artillery.push_back(howitzer.fire());
   
   // reset ground
   if (pUI->getHeldKey(R)) {
      Position hpos(howitzer.getPosition());
      ground.reset(hpos);
      howitzer.placeOnGround(&ground);
      artillery.clear();
   }

   // exit demo window (quit)
   if (pUI->getHeldKey(Q))
      exit(0);
   
   howitzer.handleInput(pUI);
}

/**********************************************************************
 * METHOD: Check collisions with (ground)
 *
 * CLASS: Demo
 *
 * Handles certain game logic by setting specific Artillery obj boolean values:
 * - stop updating when artillery projectile hits the ground
 * - indicate that the projectile has hit the target by setting landed -> true
 *
 * PARAM: Ground : ground object pointer (Ground*)
 **********************************************************************/
void Artillery::checkCollisionsWith(Ground * ground) {
   
   // stop updating artillery when it hits the ground
   if (getAltitude() < ground->getElevationMeters(this->position)) {
      setUpdate(false);
      
      // if artillery has hit ground and stopped updating, check to see if it has hit the target
      if (ground->hasHitTarget(this->position))
         setLanded(true);
   }
}
