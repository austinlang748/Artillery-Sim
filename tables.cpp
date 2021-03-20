/********************************************************************************
 * SOURCE FILE: tables.cpp
 *
 * Contains all the function implementations prototyped in tables.h
 *
 * AUTHOR: Elijah Harrison
 * AUTHOR: Austin Hilderbrand
 ********************************************************************************/

#include "tables.h"


/********************************************************************************
 * STATICS
 ********************************************************************************/
map<double, double> Tables::machToDrag    = csvFileToMap("machToDragTable");
map<double, double> Tables::altToDensity  = csvFileToMap("altToDensityTable");
map<double, double> Tables::altToSos      = csvFileToMap("altToSosTable");
map<double, double> Tables::altToGrav     = csvFileToMap("altToGravTable");


/********************************************************************************
 * STATIC METHOD:    .csv-file to map
 *
 * FROM CLASS:      Tables
 *
 * Opens the specified csv file and parses/saves contents into map object.
 * Returns empty map if failed.
 *
 * PARAM:       filename : char[]
 * RETURN:      map<double, double>
 ********************************************************************************/
// place function here, throwing errors before
map<double, double> Tables::csvFileToMap(char filename[]) {
   
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
      for (auto c : line) {
            if (c != ',') {
               if (first) str1 += c;
               else str2 += c;
            }
            else first = false;
      }
      double val1 = stod(str1); // stod() parses string into double val
      double val2 = stod(str2);
      myMap[val1] = val2;
   }

   // let's bail
   file.close();
   return myMap;
}

/********************************************************************************
 * STATIC METHOD:   map to sorted vector
 *
 * FROM CLASS:      Tables
 *
 * takes a map, creates a vector and stores the map's sorted contents in that
 * vector, and returns the vector
 *
 * PARAM:           my map : map<double, double>
 *
 * RETURN:          vector<pair<double, double> >
 ********************************************************************************/
vector<pair<double, double> > Tables::mapToSortedVector(map<double, double> &myMap) {
    vector<pair<double, double> > v;
    for (auto& it : myMap) v.push_back(it);
    sort(v.begin(), v.end(), Tables::compare);
    return v;
}

/********************************************************************************
 * STATIC METHOD:   compare
 *
 * FROM CLASS:      Tables
 *
 * compares to pairs (double, double) and returns a boolean value indicating:
 * [key value from a] < [key value from b]
 *
 * PARAM:           a : pair<double, double>
 * PARAM:           b : pair<double, double>
 *
 * RETURN:          boolean
 ********************************************************************************/
bool Tables::compare(pair<double, double> a, pair<double, double> b) {
   return a.first < b.first;
}

/********************************************************************************
 * STATIC METHOD:   get table value
 *
 * FROM CLASS:      Tables
 *
 * takes a sorted 'table' (originally map, read as vector) and solves for the
 * unknown y value using this form of the linear interpolation formula between
 * two points:
 *      value_y = y1 + (value_x - x1) * (y2 - y1) / (x2 - x1)
 * where value_x is param 'value' and value_y is return value
 *
 * PARAM:           v : vector<pair<double, double> >
 *                  (vector representing sorted contents of a map)
 * PARAM:           value : double
 *
 * RETURN:          double
 ********************************************************************************/
double Tables::getTableValue(vector<pair<double, double> > v, double value) {
    double x1 = -1;
    double y1 = -1;
    double x2 = -1;
    double y2 = -1;

    for (auto it : v) {
        x1 = x2;
        x2 = it.first;
        y1 = y2;
        y2 = it.second;
        if (value < it.first) break;
    }

    return y1 + (value - x1) * (y2 - y1) / (x2 - x1);
}

/********************************************************************************
 * STATIC METHOD:   get table value
 *
 * FROM CLASS:      Tables
 *
 * Overloaded function, calls getTableValue(vector<pair<double, double> >, double):
 *
 * takes a sorted 'table' (originally map, read as vector) and solves for the
 * unknown y value using this form of the linear interpolation formula between
 * two points:
 *      value_y = y1 + (value_x - x1) * (y2 - y1) / (x2 - x1)
 * where value_x is param 'value' and value_y is return value
 *
 * PARAM:           any map : map<double, double>
 * PARAM:           value : double
 *
 * RETURN:          double: linear interpolation formula solved for unknown y value:
 *                  [ value_y = y1 + (value_x - x1) * (y2 - y1) / (x2 - x1) ]
 *                  where value_x is param 'value'
 ********************************************************************************/
double Tables::getTableValue(map<double, double> myMap, double value) {
   return Tables::getTableValue(mapToSortedVector(myMap), value);
}

/********************************************************************************
 * STATIC METHOD:   get table value
 *
 * FROM CLASS:      Tables
 *
 * Overloaded function, calls getTableValue(vector<pair<double, double> >, double):
 *
 * takes a sorted 'table' (originally map, read as vector) and solves for the
 * unknown y value using this form of the linear interpolation formula between
 * two points:
 *      value_y = y1 + (value_x - x1) * (y2 - y1) / (x2 - x1)
 * where value_x is param 'value' and value_y is return value
 *
 * PARAM:           any map : map<double, double>
 * PARAM:           value : double
 *
 * RETURN:          double: linear interpolation formula solved for unknown y value:
 *                  [ value_y = y1 + (value_x - x1) * (y2 - y1) / (x2 - x1) ]
 *                  where value_x is param 'value'
 ********************************************************************************/
void Tables::display(string whichMap) {
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
      cout  << ' ' << setw(column1.length()) << row.first
            << " : " << row.second << endl;
}
