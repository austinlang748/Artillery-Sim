/**********************************************************************
 * tables.h
 * Tables class declaration

 * Authors:
 *    Austin Hilderbrand
 *    Elijah Harrison
 *
 * The Tables class describes the conversion tables.

 * private:
 *    static map<double, double> machToDrag;
 *    static map<double, double> altToDensity;
 *    static map<double, double> altToSos;
 *    static map<double, double> altToGrav;
 * public:
 *    get(whichMap : string, keyValue : double)
 **********************************************************************/

#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

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

   // Getters
   static double get(string whichMap, double keyValue);
   static map<double, double> getAltToSos() { return altToSos; }

   // Display
   static void display(string whichMap);
};
