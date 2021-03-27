/********************************************************************************
 * HEADER FILE: tables.cpp 
 *
 * Contains all the functions and prototypes needed for the Tables class
 *
 * AUTHOR: Elijah Harrison
 * AUTHOR: Austin Hilderbrand
 ********************************************************************************/

#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

/********************************************************************************
 * TABLES
 * private:
 * static map<double, double> machToDrag;
 * static map<double, double> altToDensity;
 * static map<double, double> altToSos;
 * static map<double, double> altToGrav;
 * public:
 * get(whichMap : string, keyValue : double)
 ********************************************************************************/
class Tables {
private:
   // static private member data: instantiated below under /**STATICS**/
   static map<double, double> machToDrag;
   static map<double, double> altToDensity;
   static map<double, double> altToSos;
   static map<double, double> altToGrav;
   
   // private helper methods
   static map<double, double> csvFileToMap(const char filename[]);
   static vector<pair<double, double> > mapToSortedVector(map<double, double> &myMap);
   static bool     compare(pair<double, double> a, pair<double, double> b);
   static double   getTableValue(vector<pair<double, double> > v, double value);
   static double   getTableValue(map<double, double> myMap, double value);


public:
  static double get(string whichMap, double keyValue) {
     map<double, double> m;
     if      (whichMap == "machToDragCoefficient")    m = machToDrag;
     else if (whichMap == "altitudeToDensity")        m = altToDensity;
     else if (whichMap == "altitudeToSpeedOfSound")   m = altToSos;
     else if (whichMap == "altitudeToGravity")        m = altToGrav;
     else return 0.0;
     return getTableValue(m, keyValue);
  }
   
   static map<double, double> getAltToSos() { return altToSos; }

   static void display(string whichMap);
};
