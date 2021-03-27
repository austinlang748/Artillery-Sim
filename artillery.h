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
   static constexpr const double artilleryV0 = 827.0;           // m/s
   static constexpr const double artilleryMass = 46.7;          // kg
   static constexpr const double artilleryDiameterMm = 154.89;  // mm
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
   bool        updateTrue;

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
      
      // set update to true
      setUpdate(true);
   }

   void update() {

      // quick update
      if (!updateTrue) return;

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
   
   void setUpdate(bool value) { updateTrue = value; }
   
   void draw(ogstream & gout) {
      double posx = 5000;

      gout.setPosition(Position(posx, 10000));
      gout  << "Artillery Hang Time :           " << getHangTime() << "s";
   
      gout.setPosition(Position(posx, 9000));
      gout  << "Artillery Altitude:             " << getAltitude() << "m";
      
      gout.setPosition(Position(posx, 8000));
      gout  << "Artillery Speed:                " << getSpeed() << " m/s";
      
      gout.setPosition(Position(posx, 7000));
      gout  << "Artillery Distance Traveled:    " << getDistance() << "m";
      
      gout.setPosition(Position(posx, 6000));
      gout  << "Gravity at Altitude:            " << g << "m/s/s";
      
      gout.setPosition(Position(posx, 5000));
      gout  << "Air Density at Altitude:        " << p << "kg/m^3";
      
      gout.setPosition(Position(posx, 4000));
      gout  << "Speed of Sound at Altitude:     " << mach << "m/s";
      
      gout.setPosition(Position(posx, 3000));
      gout  << "Drag Coefficient at current mach:  " << mach;
   }
   
   // getters
   double getAltitude()    const { return position.getMetersY(); }
   double getSpeed()       const { return speed; }
   double getDistance()    const { return position.getMetersX() - initialPositionX; }
   double getHangTime()    const { return hangTime; }
   Position getPosition()  const { return position; }
   
   Position getProjectilePathAt(int index) {
      return projectilePath[index];
   }
   
   // setters
   void setAltitude(double y)    { position.setMetersY(y); }
   void addHangTime(double dt)   { hangTime += dt; }

   void setProjectilePathAt(int index, Position p) {
      projectilePath[index] = p;
   }
   
   friend class TestArtillery;
};
