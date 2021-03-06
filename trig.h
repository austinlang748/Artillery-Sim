//
//  Trig::hpp
//  Lab08
//
// static functions for quick geometric calculations
//

#pragma once

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
