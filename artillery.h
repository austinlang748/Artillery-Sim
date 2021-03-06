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
#include "trig.h"
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
   double      angle;
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
   Artillery(Position position_0, double angle_0) : 
      // initialize angle/speed
      angle             (90 - angle_0),
      speed             (artilleryV0),

      // initialize position
      position          (position_0),
      initialPositionX  (position_0.getMetersX()),

      // initialize veloicty
      velocity (Velocity(
         Trig::horizontalComponent(speed, angle),
         Trig::verticalComponent(speed, angle)
      )),

      // initialize gravity
      g                 (altitudeToGravity(position.getMetersY())),

      // initialize drag
      c                 (machToDragCoefficient(speed)),
      p                 (altitudeToDensity(position.getMetersY())),
      artilleryRadius   (getArtilleryDiameter() * .5),
      a                 (circleArea(artilleryRadius)),
      dragF             (dragForce(c, p, speed, a)),

      // initialize acceleration
      acceleration      (Velocity(
         getAccelerationX(dragF, angle),
         getAccelerationY(g, dragF, angle)
      ))
   { }

   void update() {
      // update angle/speed/velocity
      angle = Trig::deg(Trig::cartesianToAngle(velocity.getDx(), velocity.getDy()));
      speed = velocity.getSpeed();

      // update gravity
      g = -altitudeToGravity(position.getMetersY());

      // update drag
      c = machToDragCoefficient(speed);
      p = altitudeToDensity(position.getMetersY());
      artilleryRadius = getArtilleryDiameter() * .5;
      a = circleArea(artilleryRadius);
      dragF = dragForce(c, p, speed, a);

      // update acceleration
      acceleration.set(
         getAccelerationX(dragF, angle),
         getAccelerationY(g, dragF, angle)
      );

      // update position
      velocity.add(acceleration);
      position.addMeters(velocity);
   }

   double getAltitude() const { return position.getMetersY(); }
   double getSpeed()    const { return speed; }
   double getDistance() const { return position.getMetersX() - initialPositionX; }
   double getHangTime() const { return position.getMetersY(); }

   friend class TestArtillery;
};
