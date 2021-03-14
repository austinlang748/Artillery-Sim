//
//  tables.hpp
//  Lab08
//
//  Created by Elijah Harrison on 3/6/21.
//

#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// csv parse function
map<double, double> csvFileToMap(char filename[]) {

   // initialize map
   map<double, double> myMap;

   // open file, represent as 'file'
   ifstream file(filename);
   if (file.fail()) {
      cout << "ERROR: file read error\nfilename: " << filename << endl;
      return myMap;
   }

   // parse through each line in file
   string line;
   while (getline(file, line)) {
      bool first = true;
      string str1, str2;
      for (int i = 0; i < line.length(); i++) {
            if (line[i] != ',') {
               if (first) str1 += line[i];
               else str2 += line[i];
            }
            else first = false;
      }
      double val1 = stod(str1);
      double val2 = stod(str2);
      myMap[val1] = val2;
   }

   // let's bail
   file.close();
   return myMap;
}

/**
 * TABLES
 * static map<double, double> machToDrag;
 * static map<double, double> altToDensity;
 * static map<double, double> altToSos;
 * static map<double, double> altToGrav;
 **/
class Tables
{
public:
   static map<double, double> machToDrag;
   static map<double, double> altToDensity;
   static map<double, double> altToSos;
   static map<double, double> altToGrav;
   /*
   // TODO: implement 'get' function:
   double get(string whichMap, keyValue):
      RETURN   mapped value which corresponds
               to keyValue - using interpolation
               (see functions commented out below)
    */
};

/**
 * STATICS
 **/
map<double, double> Tables::machToDrag    = csvFileToMap("machToDragTable.csv");
map<double, double> Tables::altToDensity  = csvFileToMap("altToDensityTable.csv");
map<double, double> Tables::altToSos      = csvFileToMap("altToSosTable.csv");
map<double, double> Tables::altToGrav     = csvFileToMap("altToGravTable.csv");


/**
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

**/