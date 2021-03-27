/*************************************************
 * Artillery.h
 * Artillery class header file
 * Authors:
 *      Austin Hilderbrand (creator of functions)
 *      Elijah Harrison (populated functions)
 *************************************************/

#pragma once

#include "position.h"
#include "velocity.h"
#include "tables.h"
#include "uiDraw.h"
#include <cmath>
#include <iostream>
using namespace std;

class Artillery
{
private:
   static constexpr const double artilleryV0 = 827.0*.5;       // m/s
   static constexpr const double artilleryMass = 46.7;         // kg
   static constexpr const double artilleryDiameterMm = 154.89; // mm
   static constexpr const double dt = 1/30;                    // s
   static double getArtilleryDiameter() { return artilleryDiameterMm / 1000; } // m

   static double dragForce(double c, double p, double v, double a);
   static double circleArea(double radius);
   static double getForce(double mass, double acceleration);
   static double getAccelerationX(double dragF, double angle);
   static double getAccelerationY(double gravity, double dragF, double angle);

   Position    position;
   Velocity    velocity;
   Velocity    acceleration;
   double      hangTime;
   double      initialPositionX;
   double      angleDegrees;
   double      speed;
   double      mach;
   double      g;       // gravity
   double      c;       // drag constant
   double      p;       // air density
   double      a;       // surface area of artillery
   double      dragF;   // drag force

   Position    projectilePath[20]; // path already traveled of the projectile
   bool        updateTrue           = true;
   bool        landed               = false;

public:
   
   /*************************************************
    * ARTILLERY : Constructor
    * param: position_0 : Position
    * param: angle_0    : double
    *************************************************/
   Artillery(Position position_0, double angle0_Rads) {
      
      // initialize angle
      double angle0_Degrees = Trig::deg(angle0_Rads);
      if (angle0_Degrees > 90 && angle0_Degrees <= 180) angle0_Degrees = 90;
      else if (angle0_Degrees < -90 && angle0_Degrees >= -180) angle0_Degrees = -90;
      angleDegrees = angle0_Degrees >= 0 ? 90 - angle0_Degrees : -90 - angle0_Degrees;

      // Initialize speed
      speed = artilleryV0;

      // Initialize hang time
      hangTime = 0.00;
      
      // initialize position
      position = position_0;
      initialPositionX = position.getMetersX();
      // handle invalid positions
      if (position.getMetersX() < 0) position.setMetersX(0);
      if (position.getMetersY() < 0) position.setMetersY(0);
      
      // initialize velocity
      velocity = Velocity(
          Trig::horizontalComponent(speed, angleDegrees),
          Trig::verticalComponent(speed, angleDegrees)
      );
      
      // initialize gravity
      g     = Tables::get("altitudeToGravity", getAltitude());
      
      // initialize drag
      mach  = Tables::get("altitudeToSos", getAltitude());
      c     = Tables::get("machToDragCoefficient", mach);
      p     = Tables::get("altitudeToDensity", getAltitude());
      a     = circleArea(getArtilleryDiameter() * .5);
      dragF = dragForce(c, p, speed, a);
      
      // initialize acceleration
      acceleration = Velocity(
         Trig::horizontalComponent(speed, angleDegrees),
         Trig::verticalComponent(speed, angleDegrees)
      );
      
      // initialize projectile path
      for (int i = 0; i < 20; i++) projectilePath[i] = Position();
   }

   void update() {

      // quick update
      if (!updateTrue) return;
      
      // update hang time
      hangTime += dt;

      // update angle/speed/velocity
      angleDegrees = Trig::deg(Trig::cartesianToAngle(velocity.getDx(), velocity.getDy()));
      speed = velocity.getSpeed();

      // update gravity
      g     = Tables::get("altitudeToGravity", getAltitude());

      // update drag
      mach  = Tables::get("altitudeToSos", getAltitude());
      c     = Tables::get("machToDragCoefficient", mach);
      p     = Tables::get("altitudeToDensity", getAltitude());
      a     = circleArea(getArtilleryDiameter() * .5);
      dragF = dragForce(c, p, speed, a);

      // update acceleration
      acceleration.set(
         getAccelerationX(dragF, angleDegrees),
         getAccelerationY(g, dragF, angleDegrees)
      );
      
      // cout << "gravity: " << g << endl;

      // update position
      velocity.add(acceleration);
      position.addMeters(velocity);
      
      // update projectile path
      for (int i = 19; i > 0; --i)
         setProjectilePathAt(i, projectilePath[i-1]);
      setProjectilePathAt(0, position);
   }
   
   void draw(ogstream & gout) {
      
      // draw main projectile
      gout.drawProjectile(position);
      
      // draw path traveled
      if (updateTrue) // only draw when projectile is moving
         for (int i = 0; i < 20; i++)
            gout.drawProjectile(projectilePath[i], (double)i*.5);
   }
   
   void drawInfo(ogstream & gout) {
      // this method will be called by demo, and will only be called for
      // one single artillery object (the last one in the stack)

      if (false) return; // toggle display

      int i = 0;
      int textX = 5000;
      int numbersX = textX + 11000;
      int dy = 1000;
      int y = 12250;

      gout.setPosition(Position(textX, y - dy*i));
      gout  << "Artillery Hang Time:";
      gout.setPosition(Position(numbersX, y - dy*i++));
      gout  << getHangTime() << " s";
   
      gout.setPosition(Position(textX, y - dy*i));
      gout  << "Artillery Altitude:";
      gout.setPosition(Position(numbersX, y - dy*i++));
      gout  << getAltitude() << " m";
      
      gout.setPosition(Position(textX, y - dy*i));
      gout  << "Artillery Speed:";
      gout.setPosition(Position(numbersX, y - dy*i++));
      gout  << getSpeed() << " m/s";
      
      gout.setPosition(Position(textX, y - dy*i));
      gout  << "Artillery Distance Traveled:";
      gout.setPosition(Position(numbersX, y - dy*i++));
      gout  << getDistance() << " m";
      
      gout.setPosition(Position(textX, y - dy*i));
      gout  << "Gravity at Altitude:";
      gout.setPosition(Position(numbersX, y - dy*i++));
      gout  << g << " m/s/s";
      
      gout.setPosition(Position(textX, y - dy*i));
      gout  << "Air Density at Altitude:";
      gout.setPosition(Position(numbersX, y - dy*i++));
      gout  << p << " kg/m^3";
      
      gout.setPosition(Position(textX, y - dy*i));
      gout  << "Speed of Sound at Altitude:";
      gout.setPosition(Position(numbersX, y - dy*i++));
      gout  << mach << "m/s";
      
      gout.setPosition(Position(textX, y - dy*i));
      gout  << "Drag Coefficient at current mach:";
      gout.setPosition(Position(numbersX, y - dy*i++));
      gout  << c << "m/s";
      
      if (landed) {
         gout.setPosition(Position(3500, 4000)
           //Position(gout.getCenterPoint().getPixelsX()-1000,
           //         gout.getCenterPoint().getPixelsY())
         );
         gout << "LANDED";
      }
   }
   
   // getters
   double   getAltitude()  const { return position.getMetersY(); }
   double   getSpeed()     const { return speed; }
   double   getDistance()  const { return position.getMetersX() - initialPositionX; }
   double   getHangTime()  const { return hangTime; }
   Position getPosition()  const { return position; }
   
   Position getProjectilePathAt(int index) {
      return projectilePath[index];
   }
   
   // setters
   void setAltitude(double y)    { position.setMetersY(y); }
   void addHangTime(double dt)   { hangTime += dt; }
   void setLanded(bool value)    { landed = value; }
   void setUpdate(bool value)    { updateTrue = value; }
   
   void setProjectilePathAt(int index, Position p) {
      projectilePath[index] = p;
   }
   
   friend class TestArtillery;
};
