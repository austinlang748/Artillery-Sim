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
#include <cmath>
using namespace std;

class Artillery
{
private:
   static constexpr const double artilleryV0 = 827.0;           // m/s
   static constexpr const double artilleryMass = 46.7;          // kg
   static constexpr const double artilleryDiameterMm = 154.89;  // mm
   static double getArtilleryDiameter() { return artilleryDiameterMm / 1000; } // m

   Position    position;
   Velocity    velocity;
   Velocity    acceleration;
   double      hangTime;
   double      initialPositionX;
   double      angleDegrees;
   double      speed;
   double      artilleryRadius;
   double      g;       // gravity
   double      c;       // drag constant
   double      p;       // air density
   double      a;       // surface area of artillery
   double      dragF;   // drag force


   static double dragForce(double c, double p, double v, double a);
   static double circleArea(double radius);
   static double getForce(double mass, double acceleration);
   static double getAccelerationX(double dragF, double angle);
   static double getAccelerationY(double gravity, double dragF, double angle);


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
      if (position.getMetersX() < 0) position.setMetersX(0);
      if (position.getMetersY() < 0) position.setMetersY(0);
      initialPositionX = position_0.getMetersX();
      
      // initialize velocity
      velocity = Velocity(
          Trig::horizontalComponent(speed, angleDegrees),
          Trig::verticalComponent(speed, angleDegrees)
      );
      
      // initialize gravity
      g = -Tables::get("altitudeToGravity", position.getMetersY());
      
      // initialize drag
      c = Tables::get("machToDragCoefficient", speed);
      p = Tables::get("altitudeToDensity", position.getMetersY());
      artilleryRadius = getArtilleryDiameter() * .5;
      a = circleArea(artilleryRadius);
      dragF = dragForce(c, p, speed, a);
      
      // initialize acceleration
      acceleration = Velocity(
         Trig::horizontalComponent(speed, angleDegrees),
         Trig::verticalComponent(speed, angleDegrees)
      );
   }

   void update() {
      // update angle/speed/velocity
      angleDegrees = Trig::deg(Trig::cartesianToAngle(velocity.getDx(), velocity.getDy()));
      speed = velocity.getSpeed();

      // update gravity
      g = -Tables::get("altitudeToGravity", position.getMetersY());

      // update drag
      c = Tables::get("machToDragCoefficient", speed);
      p = Tables::get("altitudeToDensity", position.getMetersY());
      artilleryRadius = getArtilleryDiameter() * .5;
      a = circleArea(artilleryRadius);
      dragF = dragForce(c, p, speed, a);

      // update acceleration
      acceleration.set(
         getAccelerationX(dragF, angleDegrees),
         getAccelerationY(g, dragF, angleDegrees)
      );

      // update position
      velocity.add(acceleration);
      position.addMeters(velocity);
   }

   double getAltitude()    const { return position.getMetersY(); }
   double getDistance()    const { return position.getMetersX() - initialPositionX; }
   double getSpeed()       const { return speed; }
   double getHangTime()    const { return hangTime; }
   Position getPosition()  const { return position; }
   
   void reset()                  { hangTime = 0.0; }
   void setAltitude(double y)    { position.setMetersY(y); }
   void addHangTime(double dt)   { hangTime += dt; }

   friend class TestArtillery;
};
