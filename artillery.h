//
//  artillery.h
//  Lab08
//
//  Created by Austin Hilderbrand on 3/6/21.
//

#pragma once

#include "position.h"
#include "velocity.h"
#include <cmath>
using namespace std;

class Artillery
{
private:
   static const double artilleryV0 = 827.0;           // m/s
   static const double artilleryMass = 46.7;          // kg
   static const double artilleryDiameterMm = 154.89;  // mm
   static double getArtilleryDiameter() { return artilleryDiameterMm / 1000; } // m

   double      angle;
   double      speed;
   Position    position;
   Velocity    velocity;

public:
   
//    // constructor
//    Artillery(Position position_0, double angle_0) : 
//       angle       (angle_0),
//       position    (position_0)
//    {
      
//       // initialize angle/speed
//       angle = 90 - angle;
//       speed = artilleryV0;

//       // initialize velocity
//       velocity = Velocity(
//          Trig.horizontalComponent(speed, angle),
//          Trig.verticalComponenet(speed, angle)
//       );

//       // initialize gravity
//       double g = altitudeToGravity(position.getPixelsY());

//       // initialize drag
//       double c = machToDragCoefficient(speed);
//       double p = altitudeToDensity(y);
//       double artilleryRadius = getArtilleryDiameter() * .5;
//       double a = circleArea(artilleryRadius);
//       double dragF = dragForce(c, p, speed, a);

//       // initialize acceleration
//       double ddx = getAccelerationX(dragF, angle);
//       double ddy = getAccelerationY(g, dragF, angle);
// }

//    void update() {
//       // update angle/speed/velocity
//       angle = Trig.deg(Trig.cartesianToAngle(dx, dy));
//       speed = Trig.mag(dx, dy);
//       dx = Trig.horizontalComponent(speed, angle);
//       dy = Trig.verticalComponent(speed, angle);

//       // update gravity
//       g = -altitudeToGravity(y);

//       // update drag
//       c = machToDragCoefficient(speed);
//       p = altitudeToDensity(y);
//       artilleryRadius = getArtilleryDiameter() * .5;
//       a = circleArea(artilleryRadius);
//       dragF = dragForce(c, p, speed, a);

//       // update x
//       ddx = getAccelerationX(dragF, angle);
//       dx += ddx;
//       x += dx;

//       // update y
//       ddy = getAccelerationY(g, dragF, angle);
//       dy += ddy;
//       y += dy;
//    }

//    static double dragForce(double c, double p, double v, double a)
//    {
//       /************************************
//        * d = ½ c ρ v² a
//        * =================================
//        * d = force in newtons (N)
//        * c = drag coefficient
//        * ρ = density of the fluid/gas
//        * v = velocity of the projectile
//        * a = surface area
//        ************************************/
//       return 0.5 * c * p * v * v * a;
//    }

//    static double circleArea(double radius)
//    {
//       /************************************
//        * a = π r²
//        * =================================
//        * a = area of the circle (m²)
//        * r = radius of the circle
//        ************************************/
//       return M_PI * radius * radius;
//    }

//    static double getForce(double mass, double acceleration)
//    {
//       /************************************
//        * f = m a
//        * =================================
//        * f = force in newtons (N)
//        * m = mass in kilograms (kg)
//        * a = acceleration (m/s²)
//        ************************************/
//       return mass * acceleration;
//    }

//    static double getAccelerationX(double dragF, double angle)
//    {
//       return -(Trig.horizontalComponent(dragF, angle) / artilleryMass);
//    }

//    static double getAccelerationY(double gravity, double dragF, double angle)
//    {
//       return -Trig.verticalComponent(dragF, angle) / artilleryMass + gravity;
//    }


};

class Tables
{

};

typedef struct conversionTable1 {
   double mach;
   double drag;
} machToDrag;

// drag coefficients of air at different given speeds:
machToDrag machToDragTable[] = {
   // Mach     Drag Coefficient
   {  0.300,   0.1629            },
   {  0.500,   0.1659            },
   {  0.700,   0.2031            },
   {  0.890,   0.2957            },
   {  0.920,   0.3010            },
   {  0.960,   0.3287            },
   {  0.980,   0.4002            },
   {  1.000,   0.4258            },
   {  1.020,   0.4335            },
   {  1.060,   0.4483            },
   {  1.240,   0.4064            },
   {  1.530,   0.3663            },
   {  1.990,   0.2897            },
   {  2.870,   0.2297            },
   {  2.890,   0.2306            },
   {  5.000,   0.2656            }
};

double machToDragCoefficient(double mach)
{
   for (int i = 1; i < 15; i++)
      if (mach > machToDragTable[i - 1].mach && mach <= machToDragTable[i].mach)
         return ((
            mach - machToDragTable[i - 1].mach
            ) * ((
               machToDragTable[i - 1].drag - machToDragTable[i].drag
               ) / (
                  machToDragTable[i - 1].mach - machToDragTable[i].mach
                  )) +
            machToDragTable[i - 1].drag
            );

   if (mach > machToDragTable[15].mach) return machToDragTable[15].drag;
   return machToDragTable[0].drag;
}

typedef struct conversionTable2 {
   double altitude;
   double density;
} altToDensity;

// the density of air (ρ) at different given altitudes:
altToDensity altToDensityTable[] = {
   // Altitude (m),  Density (kg/m2)
   {  0,             1.2250000      },
   {  1000,          1.1120000      },
   {  2000,          1.0070000      },
   {  3000,          0.9093000      },
   {  4000,          0.8194000      },
   {  5000,          0.7364000      },
   {  6000,          0.6601000      },
   {  7000,          0.5900000      },
   {  8000,          0.5258000      },
   {  9000,          0.4671000      },
   {  10000,         0.4135000      },
   {  15000,         0.1948000      },
   {  20000,         0.0889100      },
   {  25000,         0.0400800      },
   {  30000,         0.0184100      },
   {  40000,         0.0039960      },
   {  50000,         0.0010270      },
   {  60000,         0.0003097      },
   {  70000,         0.0000828      },
   {  80000,         0.0000185      }
};

double altitudeToDensity(double altitude)
{
   for (int i = 1; i < 15; i++)
      if (altitude > altToDensityTable[i - 1].altitude && altitude <= altToDensityTable[i].altitude)
         return ((
            altitude - altToDensityTable[i - 1].altitude
            ) * ((
               altToDensityTable[i - 1].density - altToDensityTable[i].density
               ) / (
                  altToDensityTable[i - 1].altitude - altToDensityTable[i].altitude
                  )) +
            altToDensityTable[i - 1].density
            );

   if (altitude > altToDensityTable[15].altitude) return altToDensityTable[15].density;
   return altToDensityTable[0].density;
}

typedef struct conversionTable3 {
   double altitude;
   double speedOfSound;
} altToSoS;

// the speed of sound (used to calculate mach based on given velocity)
// at different given altitudes:
altToSoS altToSosTable[] = {
   // Altitude (m)   Speed of Sound (m/s)
   {  0,               340                  },
   {  1000,            336                  },
   {  2000,            332                  },
   {  3000,            328                  },
   {  4000,            324                  },
   {  5000,            320                  },
   {  6000,            316                  },
   {  7000,            312                  },
   {  8000,            308                  },
   {  9000,            303                  },
   {  10000,         299                  },
   {  15000,         295                  },
   {  20000,         295                  },
   {  25000,         295                  },
   {  30000,         305                  },
   {  40000,         324                  }
};

double altitudeToSpeedOfSound(double altitude)
{
   for (int i = 1; i < 15; i++)
      if (altitude > altToSosTable[i - 1].altitude && altitude <= altToSosTable[i].altitude)
         return ((
            altitude - altToSosTable[i - 1].altitude
            ) * ((
               altToSosTable[i - 1].speedOfSound - altToSosTable[i].speedOfSound
               ) / (
                  altToSosTable[i - 1].altitude - altToSosTable[i].altitude
                  )) +
            altToSosTable[i - 1].speedOfSound
            );

   if (altitude > altToSosTable[15].altitude) return altToSosTable[15].speedOfSound;
   return altToSosTable[0].speedOfSound;
}

typedef struct conversionTable4 {
   double altitude;
   double gravity;
} altToGrav;

// the slight variations of acceleration due to gravity at different given altitudes:
altToGrav altToGravTable[] = {
   // Altitude (m)   Gravity (m/s2)
   {  0,             9.807          },
   {  1000,          9.804          },
   {  2000,          9.801          },
   {  3000,          9.797          },
   {  4000,          9.794          },
   {  5000,          9.791          },
   {  6000,          9.788          },
   {  7000,          9.785          },
   {  8000,          9.782          },
   {  9000,          9.779          },
   {  10000,         9.776          },
   {  15000,         9.761          },
   {  20000,         9.745          },
   {  25000,         9.730          }
};

double altitudeToGravity(double altitude)
{
   for (int i = 1; i < 15; i++)
      if (altitude > altToGravTable[i - 1].altitude && altitude <= altToGravTable[i].altitude)
         return ((
            altitude - altToGravTable[i - 1].altitude
            ) * ((
               altToGravTable[i - 1].gravity - altToGravTable[i].gravity
               ) / (
                  altToGravTable[i - 1].altitude - altToGravTable[i].altitude
                  )) +
            altToGravTable[i - 1].gravity
            );

   if (altitude > altToGravTable[13].altitude) return altToGravTable[13].gravity;
   return altToGravTable[0].gravity;
}


int oldmain()
{
   // // prompt for initial angle
   // double angle_0 = promptFloat("What is the angle of the howitzer where 0 is up? (degrees)");
   
   }

   return 0;
}
