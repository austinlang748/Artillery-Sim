/***********************************************************************
 * Header File:
 *    Point : The representation of a position 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen
 *    or the location on the field.
 ************************************************************************/


#pragma once

#include <iostream>
#include <cassert>
#include "velocity.h"

/*********************************************
 * Position
 * A single position on the field in Meters or Pixels
 *********************************************/
class Position
{
public:
   
   // constructors
   Position()            : x(0.0), y(0.0)  {}
   Position(double x, double y); // in meters
   Position(const Position & pt) : x(pt.getMetersX()), y(pt.getMetersY()) {}
   Position& operator = (const Position& pt);

   // getters
   double getMetersX() const { return x;  }
   double getMetersY() const { return y;  }
   double getPixelsX() const { return x / metersFromPixels; }
   double getPixelsY() const { return y / metersFromPixels; }

   bool operator == (const Position& rhs) const;
   bool operator != (const Position& rhs) const;


   // setters
   void setMeters (Position p)         { setMeters(p.getMetersX(), p.getMetersY()); }
   void setMeters (double x, double y) { setMetersX(x); setMetersY(y); }
   void setMetersX(double xMeters)     { this->x = xMeters; }
   void setMetersY(double yMeters)     { this->y = yMeters; }
   void setPixels (Position p)         { setPixels(p.getPixelsX(), p.getPixelsY()); }
   void setPixels (double x, double y) { setPixelsX(x); setPixelsY(y); }
   void setPixelsX(double xPixels)     { this->x = xPixels * metersFromPixels;   }
   void setPixelsY(double yPixels)     { this->y = yPixels * metersFromPixels;   }
   
   // adders (return a copy of *this* for easy reference)
   Position addMeters (Velocity v);
   Position addPixelsX(double dxPixels);
   Position addPixelsY(double dyPixels);
   Position addMetersX(double dxMeters);
   Position addMetersY(double dyMeters);
   
   // deal with the ratio of meters to pixels
   void setZoom(double metersFromPixels) { this->metersFromPixels = metersFromPixels; }
   void zoomIn() { metersFromPixels += 20.0; }
   void zoomOut() { if (metersFromPixels > 20.0) metersFromPixels -= 20.0; }
   double getZoom() const { return metersFromPixels; }

private:
   double x;                 // horizontal position
   double y;                 // vertical position
   static double metersFromPixels;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position& pt);
std::istream & operator >> (std::istream & in, Position& pt);

/*********************************************
 * PT
 * Trivial point, no units implied
 *********************************************/
struct PT
{
   int x;
   int y;
};
