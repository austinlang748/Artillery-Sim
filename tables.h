//
//  tables.hpp
//  Lab08
//
//  Created by Elijah Harrison on 3/6/21.
//

#pragma once

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

