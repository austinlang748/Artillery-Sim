/**********************************************************************
 * Source File:
 *      Velocity : The representation of velocity (change of position)
 * Authors:
 *      Elijah Harrison and Austin Hilderbrand
 **********************************************************************/

#include "velocity.h"

/******************************************
* VELOCITY : non-default constructor
* create a new velocity obj in dx,dy in position_meters/s
*****************************************/
Velocity::Velocity(double dx_init, double dy_init) : dx(0.0), dy(0.0)
{
   set(dx, dy);
}

/******************************************
 * POINT : ASSIGNMENT
 * Assign a point
 *****************************************/
Velocity& Velocity::operator = (const Velocity& v)
{
   set(v);
   return *this;
}

/******************************************
 * VELOCITY insertion
 *       Display velocity on the screen
 *****************************************/
std::ostream& operator << (std::ostream& out, const Velocity& v)
{
   out << "v(" << v.getDx() << ", " << v.getDy() << ")";
   return out;
}

/*******************************************
* VELOCITY extraction
*       Prompt for coordinates
******************************************/
std::istream& operator >> (std::istream& in, Velocity& v)
{
   double dx;
   double dy;
   in >> dx >> dy;

   pos.setDx(dx);
   pos.setDy(dy);

   return in;
}

/*******************************************
 * VELOCITY comparison operators
 ******************************************/

/*******************************************
 * VELOCITY : comparison operator
 * param: rhs:Velocity
 * return bool: is equivalent
 ******************************************/
bool Velocity::operator == (const Velocity & rhs) const {
    return dx == rhs.dx && dy == rhs.dy;
}

/*******************************************
 * VELOCITY : not comparison operator
 * param: rhs:Velocity
 * return bool: is not equivalent
 ******************************************/
bool Velocity::operator != (const Velocity & rhs) const {
    return dx != rhs.dx || dy != rhs.dy;
}

/*******************************************
 * VELOICTY SETTERS
 ******************************************/

/*******************************************
 * VELOCITY : set
 * param: v:Velocity
 ******************************************/
void set(const Velocity &v) {
    set(v.getDx(), v.getDy());
}

/*******************************************
 * VELOCITY : set
 * param: dx:double
 * param: dy:double
 ******************************************/
void set(double dx, double dy) {
    setDx(dx);
    setDy(dy);
}


/**
 * VELOCITY : ADDERS
 ***/

/**
 * VELOCITY : add
 ***/
void Velocity::add(Velocity a) {
    add(a.getDx(), a.getDy());
}

/**
 * VELOCITY : add
 ***/
void Velocity::add(double ddx, double ddy) {
    addDx(ddx);
    addDy(ddy);
}

/**
 * VELOCITY : add magnitude
 ***/
void Velocity::addMagnitude(double angleRadians, double magnitude) {
    addDx(Trig.horizontalComponent(  magnitude, Trig.deg(angleRadians)));
    addDx(Trig.verticalComponent(    magnitude, Trig.deg(angleRadians)));
}
