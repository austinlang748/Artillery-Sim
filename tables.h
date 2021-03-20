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
class Tables
{
private:
   // static private member data: instantiated below under /**STATICS**/
   static map<double, double> csvFileToMap(const char filename[]);
   static map<double, double> machToDrag;
   static map<double, double> altToDensity;
   static map<double, double> altToSos;
   static map<double, double> altToGrav;

   // private helper methods
   static vector<pair<double, double> > mapToSortedVector(map<double, double> &myMap);
   static bool     compare(pair<double, double> a, pair<double, double> b);
   static double   getTableValue(vector<pair<double, double> > v, double value);
   static double   getTableValue(map<double, double> myMap, double value);

   
public:

   /*****************************************************************************
    * FUNCTION: GET
    *
    * - PARAM - which map : string
    *    - a string indicating the values from which to
    *    calculate the return value
    * - PARAM - key value : double
    *    - a number (format double) specifying at which
    *    value on the x-axis to plug into linear interpolation
    *    calculation:
    *    result = y1 + (keyValue - x1) * (y2 - y1) / (x2 - x1);
    *
    * - RETURN : double
    *    - the result of the linear interpolation
    *    (see formula above)
    *****************************************************************************/
   static double get(string whichMap, double keyValue) {
        map<double, double> m;
        if      (whichMap == "machToDrag")      m = machToDrag;
        else if (whichMap == "altToDensity")    m = altToDensity;
        else if (whichMap == "altToSos")        m = altToSos;
        else if (whichMap == "altToGrav")       m = altToGrav;
        else return 0.0;
        return getTableValue(m, keyValue);
   }

   /*****************************************************************************
    * FUNCTION: DISPLAY
    *
    * Displays the map specified by the whichMap (string) parameter.
    *
    * PARAM: which map : string
    *****************************************************************************/
   static void display(string whichMap) {
        cout << "Tables::display(" << whichMap << ")\n";
        
        // choose the map based on the parameter
        map<double, double> m;
        if      (whichMap == "machToDrag")      m = machToDrag;
        else if (whichMap == "altToDensity")    m = altToDensity;
        else if (whichMap == "altToSos")        m = altToSos;
        else if (whichMap == "altToGrav")       m = altToGrav;

        // display error/success
        else {
            cout << " >> ERROR: Unable to identify which table to display.\n";
            return; // quick exit if error
        }
        cout << " >> SUCCESS: " << whichMap << " table identified, displaying:\n";

        // get column 1 name
        string column1;
        if (whichMap == "machToDrag") column1 = "mach";
        else column1 = "altitude";

        // get column 2 name
        string column2;
        if      (whichMap == "machToDrag")   column2 = "drag";
        else if (whichMap == "altToDensity") column2 = "density";
        else if (whichMap == "altToSos")     column2 = "speed of sound";
        else if (whichMap == "altToGrav")    column2 = "gravity";
        
        // 'sort' map to get an iterable version (vector)
        vector<pair<double, double> > sortedMap = mapToSortedVector(m);

        // display columns
        cout        << ' ' << column1
                    << " : " << column2 << endl;
        
         // display header lines
         cout << ' ';
         cout.width(column1.length());
         cout.fill('-');
         cout << " : ";
         cout.width(column2.length());
         cout.fill('-');
         cout << endl;

        // display rows
        for (auto row : sortedMap)
            cout << ' ' << setw(column1.length()) << row.first
                 << " : " << row.second << endl;
   }
};
