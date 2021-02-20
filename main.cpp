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
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

// projectile motion constants
const double artilleryV0         = 827.0;    // m/s
const double artilleryMass       = 46.7;     // kg
const double artilleryDiameterMm = 154.89;   // mm
double getArtilleryDiameter() { return artilleryDiameterMm / 1000; } // m

// drag coefficients of air at different given speeds:
//    Mach	        Drag Coefficient
//    0.300	        0.1629
//    0.500	        0.1659
//    0.700	        0.2031
//    0.890	        0.2597
//    0.920	        0.3010
//    0.960	        0.3287
//    0.980	        0.4002
//    1.000	        0.4258
//    1.020	        0.4335
//    1.060	        0.4483
//    1.240	        0.4064
//    1.530	        0.3663
//    1.990	        0.2897
//    2.870	        0.2297
//    2.890	        0.2306
//    5.000	        0.2656
typedef struct conversionTable1 {
   double mach;
   double drag;
} machToDrag;

machToDrag machToDragTable[] = {
   {0.300, 0.1629},
   {0.500, 0.1659},
   {0.700, 0.2031},
   {0.890, 0.2957},
   {0.920, 0.3010},
   {0.960, 0.3287},
   {0.980, 0.4002},
   {1.000, 0.4258},
   {1.020, 0.4335},
   {1.060, 0.4483},
   {1.240, 0.4064},
   {1.530, 0.3663},
   {1.990, 0.2897},
   {2.870, 0.2297},
   {2.890, 0.2306},
   {5.000, 0.2656}
};

double machToDragCoefficient(double mach)
{
   for (int i = 1; i < 15; i++)
      if (mach > machToDragTable[i-1].mach && mach <= machToDragTable[i].mach)
         return machToDragTable[i].drag;

   if (mach > machToDragTable[15].mach) return machToDragTable[15].drag;
   return machToDragTable[0].drag;
}

// the density of air (ρ) at different given altitudes:
//    Altitude (m)   Density (kg/m2)
//    0	            1.2250000
//    1000	         1.1120000
//    2000	         1.0070000
//    3000	         0.9093000
//    4000	         0.8194000
//    5000	         0.7364000
//    6000	         0.6601000
//    7000	         0.5900000
//    8000	         0.5258000
//    9000	         0.4671000
//    10000	         0.4135000
//    15000	         0.1948000
//    20000	         0.0889100
//    25000	         0.0400800
//    30000	         0.0184100
//    40000	         0.0039960
//    50000	         0.0010270
//    60000	         0.0003097
//    70000	         0.0000828
//    80000	         0.0000185
typedef struct conversionTable2 {
   double altitude;
   double density;
} altToDensity;

altToDensity altToDensityTable[] = {
   {0    , 1.2250000},
   {1000 , 1.1120000},
   {2000 , 1.0070000},
   {3000 , 0.9093000},
   {4000 , 0.8194000},
   {5000 , 0.7364000},
   {6000 , 0.6601000},
   {7000 , 0.5900000},
   {8000 , 0.5258000},
   {9000 , 0.4671000},
   {10000, 0.4135000},
   {15000, 0.1948000},
   {20000, 0.0889100},
   {25000, 0.0400800},
   {30000, 0.0184100},
   {40000, 0.0039960},
   {50000, 0.0010270},
   {60000, 0.0003097},
   {70000, 0.0000828},
   {80000, 0.0000185}
};

double altitudeToDensity(double altitude)
{
   for (int i = 1; i < 15; i++)
      if (altitude > altToDensityTable[i-1].altitude && altitude <= altToDensityTable[i].altitude)
         return altToDensityTable[i].density;

   if (altitude > altToDensityTable[15].altitude) return altToDensityTable[15].density;
   return altToDensityTable[0].density;
}

// the speed of sound (used to calculate mach based on given velocity)
// at different given altitudes:
//    Altitude (m)	   Speed of Sound (m/s)
//    0	               340
//    1000	            336
//    2000	            332
//    3000	            328
//    4000	            324
//    5000	            320
//    6000	            316
//    7000	            312
//    8000	            308
//    9000	            303
//    10000	            299
//    15000	            295
//    20000	            295
//    25000	            295
//    30000	            305
//    40000	            324
typedef struct conversionTable3 {
   double altitude;
   double speedOfSound;
} altToSoS;

altToSoS altToSosTable[] = {
   {0	   , 340},
   {1000	, 336},
   {2000	, 332},
   {3000	, 328},
   {4000	, 324},
   {5000	, 320},
   {6000	, 316},
   {7000	, 312},
   {8000	, 308},
   {9000	, 303},
   {10000, 299},
   {15000, 295},
   {20000, 295},
   {25000, 295},
   {30000, 305},
   {40000, 324}
};

double altitudeToSpeedOfSound(double altitude)
{
   for (int i = 1; i < 15; i++)
      if (altitude > altToSosTable[i-1].altitude && altitude <= altToSosTable[i].altitude)
         return altToSosTable[i].speedOfSound;

   if (altitude > altToSosTable[15].altitude) return altToSosTable[15].speedOfSound;
   return altToSosTable[0].speedOfSound;
}

// the slight variations of acceleration due to gravity at different given altitudes:
//    Altitude (m)	Gravity (m/s2)
//    0	            9.807
//    1000	         9.804
//    2000	         9.801
//    3000	         9.797
//    4000	         9.794
//    5000	         9.791
//    6000	         9.788
//    7000	         9.785
//    8000	         9.782
//    9000	         9.779
//    10000	         9.776
//    15000	         9.761
//    20000	         9.745
//    25000	         9.730
typedef struct conversionTable4 {
   double altitude;
   double gravity;
} altToGrav;

altToGrav altToGravTable[] = {
   {0	   , 9.807},
   {1000	, 9.804},
   {2000	, 9.801},
   {3000	, 9.797},
   {4000	, 9.794},
   {5000	, 9.791},
   {6000	, 9.788},
   {7000	, 9.785},
   {8000	, 9.782},
   {9000	, 9.779},
   {10000, 9.776},
   {15000, 9.761},
   {20000, 9.745},
   {25000, 9.730}
};

double altitudeToGravity(double altitude)
{
   for (int i = 1; i < 14; i++)
      if (altitude > altToGravTable[i-1].altitude && altitude <= altToGravTable[i].altitude)
         return altToGravTable[i].gravity;

   if (altitude > altToGravTable[13].altitude) return altToGravTable[13].gravity;
   return altToGravTable[0].gravity;
}

// functions for quick geometric calculations:
double deg(double angleRadians)  { return 180 * angleRadians / M_PI; }
double rad(double angleDegrees)  { return M_PI * angleDegrees / 180; }
double mag(double x, double y)   { return sqrt(x * x + y * y); }

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

double dragForce(double c, double p, double v, double a)
{
   /************************************
    * d = ½ c ρ v² a
    * =================================
    * d = force in newtons (N)
    * c = drag coefficient
    * ρ = density of the fluid/gas
    * v = velocity of the projectile
    * a = surface area
    ************************************/
   return 0.5 * c * p * v*v * a;
}

double circleArea(double radius)
{
   /************************************
    * a = π r²
    * =================================
    * a = area of the circle (m²)
    * r = radius of the circle
    ************************************/
   return M_PI * radius*radius;
}

double getForce(double mass, double acceleration)
{
   /************************************
    * f = m a	
    * =================================
    * f = force in newtons (N)
    * m = mass in kilograms (kg)
    * a = acceleration (m/s²)
    ************************************/
   return mass * acceleration;
}

double getAccelerationX(double dragF, double angle)
{
   return -horizontalComponent(dragF, angle)/artilleryMass;
}

double getAccelerationY(double gravity, double dragF, double angle)
{
   return verticalComponent(dragF, angle)/artilleryMass + gravity;
}


// prompt
float promptFloat(string prompt)
{
   try {
      cout << prompt << " ";
      float result;
      cin >> result;
      cout << endl;
      return result;
   }
   // error handling
   catch(const exception& e) {
      cerr << e.what() << '\n';
      return -1.0;
   }
}

// quadratic formula
float quadraticFormula(float a, float b, float c, bool debug = false)
{
   if (debug)
      cout  << "[debug] Quadratic formula(" 
            << a << ", "
            << b << ", "
            << c << ")\n";

   float discriminant = b*b - 4*a*c;
   if (debug) cout << "Discriminant == " << discriminant << endl;

   if (discriminant == 0) return -b/(2*a);

   int error = -1;

   float x1 = (-b + sqrt(discriminant)) / (2*a);
   float x2 = (-b - sqrt(discriminant)) / (2*a);
   
   if (debug) cout << "roots: x1 == " << x1 << ", x2 == " << x2 << endl;

   // for our situation, return an error for purely negative results
   // TODO: remove this and write an assert in the calculation itself once calculation is more correct
   if (x1 < 0 || x2 < 0) return error;
   else return max(x1, x2);

   return error;
}



int main()
{
   // prompt for initial angle
   double angle_0 = promptFloat("What is the angle of the howitzer where 0 is up? (degrees)");

   // initialize angle/speed
   double angle            = angle_0;
   double speed            = artilleryV0;

   // initialize position
   double x                = 0;
   double y                = 0;

   // initialize velocity
   double dx               = horizontalComponent(speed, angle);
   double dy               = verticalComponent(speed, angle);

   // initialize gravity
   double g                = altitudeToGravity(y);

   // initialize drag
   double c                = machToDragCoefficient(speed);
   double p                = altitudeToDensity(y);
   double artilleryRadius  = getArtilleryDiameter() * .5;
   double a                = circleArea(artilleryRadius);
   double dragF            = dragForce(c, p, speed, a);

   // initialize acceleration
   double ddx              = getAccelerationX(dragF, angle);
   double ddy              = getAccelerationY(g, dragF, angle);


   // set up loop 
   double t = 0.0;
   double fps = 60;
   double dt = 1000/fps;
   bool debug = true;
   while (y >= 0)
   {
      // increment time by deltaTime (predefined)
      t += dt;

      // update angle/speed/velocity
      angle             = cartesianToAngle(dx, dy);
      speed             = mag(dx, dy);
      dx                = horizontalComponent(speed, angle);
      dy                = verticalComponent(speed, angle);

      // update gravity
      g                 = -altitudeToGravity(y);

      // update drag
      c                 = machToDragCoefficient(speed);
      p                 = altitudeToDensity(y);
      artilleryRadius   = getArtilleryDiameter() * .5;
      a                 = circleArea(artilleryRadius);
      dragF             = dragForce(c, p, speed, a);

      // update x
      ddx               = getAccelerationX(dragF, angle);
      dx               += ddx;
      x                += dx;

      // update y
      ddy               = getAccelerationY(g, dragF, angle);
      dy               += ddy;
      y                += dy;

      cout.precision(1);
      if (debug)
         cout  << "x, y("  << setw(7) << fixed 
               << x << "," << setw(6) << y << ")\n";
   }

   // distance
   cout << "Distance:" << setw(12) << x << "m" << setw(18);

   // total hang time
   cout << "Hang Time: " << setw(10) << t << "s\n";

   return 0;
}
