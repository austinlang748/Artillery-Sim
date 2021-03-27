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
   // constants
   static constexpr const double artilleryV0 = 827.0;                          // m/s
   static constexpr const double artilleryMass = 46.7;                         // kg
   static constexpr const double artilleryDiameterMm = 154.89;                 // mm
   static double getArtilleryDiameter() { return artilleryDiameterMm / 1000; } // m

   // static calculation helper methods
   static double dragForce(double c, double p, double v, double a);
   static double sosToDragCoefficient(double sos);
   static double circleArea(double radius);
   static double getForce(double mass, double acceleration);
   static double getAccelerationX(double dragF, double angle);
   static double getAccelerationY(double gravity, double dragF, double angle);

   // attributes for artillery calculations/positioning
   Position position;            // current position (m, m)
   Velocity velocity;            // current change in position (m/s, m/s)
   Velocity acceleration;        // current change in velocity (m/s², m/s²)
   double   hangTime;            // current amount of time artillery has been airborne (s)
   double   speed;               // current artillery speed value (m/s)
   double   sos;                 // current speed of sound value (m/s)
   double   mach;                // current mach value
   double   g;                   // current gravity value (m/s²)
   double   c;                   // current drag constant value
   double   p;                   // current air density value (kg/m³)
   double   a;                   // surface area of artillery (m²)
   double   dragF;               // drag force (N)
   double   initialPositionX;    // initial x pos of artillery (used for calculation of horiz. distance) (m)
   double   angleDegrees;        // current direction which artillery is traveling in (degrees°)
   double   howitzerAngle;       // angle at which artillery was launched (angle of howitzer) (degrees°)
   Position projectilePath[20];  // traversed path of the projectile (m, m)
   
   // booleans for Demo class logic
   bool     updateTrue  = true;
   bool     landed      = false;
   
   // specific for ui elements
   Position textPosition;
   Position valuePosition;
   Position unitsPosition;

   // helper methods for ui
   void drawInfo(ogstream & gout, string description, double value, string units);

public:
   
   // constructors
   Artillery(Position position_0, double angle0_Rads);

   // public update methods
   void update();
   void draw(ogstream & gout);
   
   // used by Artillery::draw and Demo::draw
   void drawInfo(ogstream & gout);
   
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
   void setAngle(double angle);
   void setProjectilePathAt(int index, Position p) {
      projectilePath[index] = p;
   }
   
   // Make the test class a friend
   friend class TestArtillery;
};
