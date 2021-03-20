/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"

/******************************************
* POINT : non-default constructor
* create a point in x,y in meters
*****************************************/
Position::Position(double x, double y) : x(0.0), y(0.0)
{
   setMetersX(x);
   setMetersY(y);
}

/******************************************
 * POINT : ASSIGNMENT
 * Assign a point
 *****************************************/
Position& Position::operator = (const Position& pt)
{
   x = pt.x;
   y = pt.y;
   return *this;
}

/******************************************
 * POSITION insertion
 *       Display position on the screen
 *****************************************/
std::ostream& operator << (std::ostream& out, const Position& pt)
{
   out << "(" << pt.getMetersX() << "m , " << pt.getMetersY() << "m)";
   return out;
}

/*******************************************
* POSITION extraction
*       Prompt for coordinates
******************************************/
std::istream& operator >> (std::istream& in, Position& pos)
{
   double x;
   double y;
   in >> x >> y;

   pos.setMetersX(x);
   pos.setMetersY(y);

   return in;
}

/*******************************************
 * POSITION : comparison operator
 * param: rhs:Position
 * return bool: is equivalent
 ******************************************/
bool Position::operator == (const Position & rhs) const {
    return x == rhs.getMetersX() && y == rhs.getMetersY();
}

/*******************************************
 * POSITION : not comparison operator
 * param: rhs:Position
 * return bool: is not equivalent
 ******************************************/
bool Position::operator != (const Position & rhs) const {
    return x != rhs.getMetersX() || y != rhs.getMetersY();
}
