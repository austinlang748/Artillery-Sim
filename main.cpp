/*****************************************************************************
 * Lab 07
 * Austin Hilderbrand
 * Elijah Harrison
 * Purpose: simulate the projectile motion of artillery at 0.5s increments.
 * Description:
 * Program will prompt for:
 * - initial angle
 * and report:
 * - final horizontal distance
 * - hang time
 * Example:
 * What is the angle of the howitzer where 0 is up? 30
 * Distance:     20093.6m       Hang Time:       97.7s
 *
 * Note: we are supposedly going to run this using code from a .zip file
 * provided in the lab description (see
 * https://content.byui.edu/file/18b1e464-da51-4539-ac78-a1f18e7ae358/1/Ponder/230.07.Ponder.html)
 * however, for the time being the link is broken.
 *****************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

// functions for quick geometric calculations:
double deg(double angleRadians) { return 180 * angleRadians / M_PI; }
double rad(double angleDegrees) { return M_PI * angleDegrees / 180; }
double mag(double x, double y) { return sqrt(x * x + y * y); }
double cartesianToAngle(double x, double y)
{
   return atan2(x, y);
}
double verticalComponent(double magnitude, double angleDegrees)
{
   return magnitude * sin(rad(angleDegrees));
}
double horizontalComponent(double magnitude, double angleDegrees)
{
   return magnitude * cos(rad(angleDegrees));
}


int main() {

   // prompt for initial angle
   cout << "What is the angle of the howitzer where 0 is up? ";
   double angle_0 = 0.0;
   cin >> angle_0;

   // =================================
   /* TODO: calculate hang time based on parabolic equation of height with respect to time */
   // y(t) = ½ g dy t^2 + vy0 t + y0
   // find t where y == 0 and t != 0a
   // =================================

   // vy0 = F0 * sin(angle) / mass

   // dy = drag_y = ½ c ρ v^2 a

   // a = π r^2	
   // a = area of a circle (m2)
   // r = radius of a circle

   // d = force in newtons (N)
   // c = drag coefficient
   // ρ = density of the fluid/gas
   // v = velocity of the projectile
   // y = vertical position
   // g = F_gravity
   // d = drag

   // drag coefficients of air at different given speeds:
   // Mach	            Drag Coefficient
   // 0.300	        0.1629
   // 0.500	        0.1659
   // 0.700	        0.2031
   // 0.890	        0.2597
   // 0.920	        0.3010
   // 0.960	        0.3287
   // 0.980	        0.4002
   // 1.000	        0.4258
   // 1.020	        0.4335
   // 1.060	        0.4483
   // 1.240	        0.4064
   // 1.530	        0.3663
   // 1.990	        0.2897
   // 2.870	        0.2297
   // 2.890	        0.2306
   // 5.000	        0.2656

   // the density of air (ρ) at different given altitudes:
   // Altitude (m)	    Density (kg/m2)
   // 0	            1.2250000
   // 1000	            1.1120000
   // 2000	            1.0070000
   // 3000	            0.9093000
   // 4000	            0.8194000
   // 5000	            0.7364000
   // 6000	            0.6601000
   // 7000	            0.5900000
   // 8000	            0.5258000
   // 9000	            0.4671000
   // 10000	        0.4135000
   // 15000	        0.1948000
   // 20000	        0.0889100
   // 25000	        0.0400800
   // 30000	        0.0184100
   // 40000	        0.0039960
   // 50000	        0.0010270
   // 60000	        0.0003097
   // 70000	        0.0000828
   // 80000	        0.0000185

   // the speed of sound (used to calculate mach based on given velocity)
   // at different given altitudes:
   // Altitude (m)	    Speed of Sound (m/s)
   // 0	            340
   // 1000	            336
   // 2000	            332
   // 3000	            328
   // 4000	            324
   // 5000	            320
   // 6000	            316
   // 7000	            312
   // 8000	            308
   // 9000	            303
   // 10000	        299
   // 15000	        295
   // 20000	        295
   // 25000	        295
   // 30000	        305
   // 40000	        324

   // the slight variations of acceleration due to gravity at different given altitudes:
   // Altitude (m)	    Gravity (m/s2)
   // 0	            9.807
   // 1000	            9.804
   // 2000	            9.801
   // 3000	            9.797
   // 4000	            9.794
   // 5000	            9.791
   // 6000	            9.788
   // 7000	            9.785
   // 8000	            9.782
   // 9000	            9.779
   // 10000	        9.776
   // 15000	        9.761
   // 20000	        9.745
   // 25000	        9.730


   // =================================
   // TODO: calculate horizontal distance based on hang time
   // x(t) = vx0 t + x0; find xn (x0 == 0)
   // =================================

   // vx0 = F0 * cos(angle) / mass


   // =================================
   // test cases for video:
   // up:          angle == 0
   // high:        angle == 30
   // low:         angle == 60
   // backwards:   angle == -45
   // =================================

   return 0;
}