//
//  velocity.h
//  Lab08
//
//  Created by Elijah Harrison on 3/6/21.
//

#pragma once
#include <cmath>

/**
 * Velocity Class
 **/
class Velocity
{
private:
   double dx; // change of position in pixelsX
   double dy; // change of position in pixelsY

public:

   // constructors
   Velocity() : dx(0.0), dy(0.0)  {}
   Velocity(double dx, double dy) { set(dx, dy); }
   Velocity(const Velocity & v) : dx(v.dx), dy(v.dy) {}
   Velocity& operator = (const Velocity& v);

   // getters
   double getDx();
   double getDy();
   double getSpeed();
   
   bool operator == (const Velocity & rhs) const {
      return dx == rhs.dx && dy == rhs.dy;
   }
   
   bool operator != (const Velocity & rhs) const {
      return dx != rhs.dx || dy != rhs.dy;
   }
};

   void set(const Velocity &v);
   void set(double dx, double dy);
   
   // adders
   void addDx(double ddx) { dx += ddx; }
   void addDy(double ddy) { dy += ddy; }
   
   void add(Velocity v);
   void add(double ddx, double ddy);
   void addMagnitude(double angleRadians, double magnitude);
};

// functions for quick geometric calculations:
class Trig
{
public:
   static double deg(double angleRadians) { return 180 * angleRadians / M_PI; }
   static double rad(double angleDegrees) { return M_PI * angleDegrees / 180; }
   static double mag(double x, double y)  { return sqrt(x * x + y * y); }

   static double cartesianToAngle(double x, double y) {
      return atan2(y, x);
   }

   static double verticalComponent(double magnitude, double angleDegrees) {
      return magnitude * sin(rad(angleDegrees));
   }

   static double horizontalComponent(double magnitude, double angleDegrees) {
      return magnitude * cos(rad(angleDegrees));
   }

};
