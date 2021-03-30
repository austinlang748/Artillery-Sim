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

/*******************************************
 * ADDERS
 * For convenience, let's return a referenced value for this*
 * This will make ui positioning easier to read
 ******************************************/

/*******************************************
 * METHOD: add meters
 * PARAM: v : Velocity
 * RETURN: Position (reference to this)
 ******************************************/
Position Position::addMeters (Velocity v) {
   addMetersX(v.getDx());
   addMetersY(v.getDy());
   return *this;
}

/*******************************************
 * METHOD: add meters
 * PARAM: v : Velocity
 * RETURN: Position (reference to this)
 ******************************************/
Position Position::addPixelsX(double dxPixels) {
   setPixelsX(getPixelsX() + dxPixels);
   return *this;
}

/*******************************************
 * METHOD: add meters
 * PARAM: v : Velocity
 * RETURN: Position (reference to this)
 ******************************************/
Position Position::addPixelsY(double dyPixels) {
   setPixelsY(getPixelsY() + dyPixels);
   return *this;
}

/*******************************************
 * METHOD: add meters
 * PARAM: v : Velocity
 * RETURN: Position (reference to this)
 ******************************************/
Position Position::addMetersX(double dxMeters) {
   setMetersX(getMetersX() + dxMeters);
   return *this;
}

/*******************************************
 * METHOD: add meters
 * PARAM: v : Velocity
 * RETURN: Position (reference to this)
 ******************************************/
Position Position::addMetersY(double dyMeters) {
   setMetersY(getMetersY() + dyMeters);
   return *this;
}
