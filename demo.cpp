/********************************************************************************
 * SOURCE FILE: demo.cpp
 *
 * Contains the implementations of the methods defined in demo.h
 *
 * AUTHOR: Elijah Harrison
 * AUTHOR: Austin Hilderbrand
 ********************************************************************************/

#include "demo.h"

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

   // artillery shouldn't exist (yet)
   artillery = NULL;
}

void Demo::update() {

   if (artillery) {
      
      // advance time one frame's worth of time elapsed
      artillery->addHangTime(1/30);

      // move the projectile across the screen
      artillery->update();
      
      // stop updating artillery when it hits the ground
      if (artillery->getPosition().getMetersY() < ground.getElevationMeters(artillery->getPosition())) {
         artillery->setUpdate(false);
      }
   }
}

void Demo::draw(ogstream & gout) {
   
   ground.draw(gout);                     // draw the ground first
   howitzer.draw(gout);                   // draw the howitzer
   if (artillery) artillery->draw(gout);  // draw projectile (if it exists)

   // draw some text on the screen
   gout.setPosition(Position(22000, 19000));
   gout << "Press 'Q' to quit\n";
   
   gout.setPosition(Position(22000, 18000));
   gout << "Press 'R' to reset\n";
}

void Demo::handleInput(const Interface* pUI) {
   
   // move a large amount
   if (pUI->getHeldKey(RIGHT))
      howitzer.addAngle(0.05);
   if (pUI->getHeldKey(LEFT))
      howitzer.addAngle(-0.05);

   // move by a little
   if (pUI->getHeldKey(UP))
      howitzer.addAngle((howitzer.getAngle() >= 0 ? -0.003 : 0.003));
   if (pUI->getHeldKey(DOWN))
      howitzer.addAngle((howitzer.getAngle() >= 0 ? 0.003 : -0.003));

   // fire that gun
   if (pUI->getHeldKey(SPACE))
      artillery = new Artillery(howitzer.getPosition(), howitzer.getAngle());
   
   // restart artillery
   if (pUI->getHeldKey(R)) {
      Position hpos(howitzer.getPosition());
      ground.reset(hpos);
      howitzer.placeOnGround(&ground);
      artillery = NULL;
   }

   // exit demo window (quit)
   if (pUI->getHeldKey(Q))
      exit(0);
}
