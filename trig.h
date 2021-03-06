/**********************************************************************
 * trig.h
 * Trig class declaration

 * Authors:
 *    Elijah Harrison
 *
 * The Trig class contains trig math and conversion helper functions.
 **********************************************************************/

#pragma once

#ifndef M_PI
   #define M_PI 3.141592653589793238
#endif

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
