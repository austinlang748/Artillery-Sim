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
}

void Demo::update() {

   for (auto projectile : artillery) {
      
      // update each projectile
      projectile->update();
      
      // stop updating artillery when it hits the ground
      if (projectile->getPosition().getMetersY() < ground.getElevationMeters(projectile->getPosition())) {
         projectile->setUpdate(false);
         
         // if artillery has hit ground and stopped updating, check to see if it has hit the target
         if (ground.hasHitTarget(projectile->getPosition()))
            projectile->setLanded(true);
      }
   }
}

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
   textPos.setPixels(90, 380);
   gout.setPosition(textPos);
   gout << "Press 'Q' to quit\n";
   
   // how to reset
   textPos.setPixelsX(290);
   gout.setPosition(textPos);
   gout << "Press 'R' to reset terrain\n";
}

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
