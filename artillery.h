/**********************************************************************
 * artillery.h
 * Artillery class declaration

 * Authors:
 *    Austin Hilderbrand (creator of functions)
 *    Elijah Harrison (populated functions)
 *
 * The Artillery class describes each projectile. 
 **********************************************************************/

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
   static constexpr const double artilleryV0 = 827.0;          // m/s
   static constexpr const double artilleryMass = 46.7;         // kg
   static constexpr const double artilleryDiameterMm = 154.89; // mm
   static double getArtilleryDiameter() { return artilleryDiameterMm / 1000; } // m

   static double dragForce(double c, double p, double v, double a);
   static double sosToDragCoefficient(double sos);
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
   double      sos;
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
      
      // handle angle
      double angle0_Degrees = Trig::deg(angle0_Rads);
      if (angle0_Degrees > 90 && angle0_Degrees <= 180) angle0_Degrees = 90;
      else if (angle0_Degrees < -90 && angle0_Degrees >= -180) angle0_Degrees = -90;
      
      // initialize angle
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
      mach  = Tables::get("altitudeToSpeedOfSound", getAltitude());
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
      addHangTime(.05); // fps == 30

      // update angle/speed/velocity
      angleDegrees = Trig::deg(Trig::cartesianToAngle(velocity.getDx(), velocity.getDy()));
      speed = velocity.getSpeed();

      // update gravity
      g     = Tables::get("altitudeToGravity", getAltitude());

      // update drag
      
      sos   = Tables::get("altitudeToSpeedOfSound", getAltitude());
      
      mach  = sosToDragCoefficient(sos)*1.1; // convert speed of sound to mach?
      
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
   
   Position textPosition;
   Position valuePosition;
   Position unitsPosition;
   void drawInfo(ogstream & gout) {
      // this method will be called by demo, and will only be called for
      // one single artillery object (the last one in the stack)

      // set positioning/column spacing
      textPosition.setPixels(90, 350);
      valuePosition = textPosition;
      valuePosition.addPixelsX(300);
      unitsPosition = valuePosition;
      unitsPosition.addPixelsX(60);

      // display info
      drawInfo(gout, "Artillery Hang Time", getHangTime(), "s");
      drawInfo(gout, "Artillery Altitude", getAltitude(), "m");
      drawInfo(gout, "Artillery Speed", getSpeed(), "m/s");
      drawInfo(gout, "Artillery Distance Traveled", getDistance(), "m");
      drawInfo(gout, "", 0, ""); // empty line
      drawInfo(gout, "Gravity at Altitude", g, "m/s/s");
      drawInfo(gout, "Air Density at Altitude", p, "kg/m^3");
      drawInfo(gout, "Speed of Sound at Altitude", mach, "m/s");
      drawInfo(gout, "Drag Coefficient at Current Mach", c, "");

      if (landed) {
         gout.setPosition(Position(3500, 4000));
         gout << "LANDED";
      }
   }
   
   void drawInfo(ogstream & gout, string description, double value, string units) {
      
      double dy = -20;
      gout.setPosition(textPosition);
      gout << description << ":";
      textPosition.addPixelsY(dy);
      
      gout.setPosition(valuePosition);
      gout << value;
      valuePosition.addPixelsY(dy);
      
      gout.setPosition(unitsPosition);
      gout << " " << units;
      unitsPosition.addPixelsY(dy);
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
