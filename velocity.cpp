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
   setDx(dx);
   setDy(dy);
}

/******************************************
 * POINT : ASSIGNMENT
 * Assign a point
 *****************************************/
Velocity& Velocity::operator = (const Velocity& v)
{
   dx = v.dx;
   dy = v.dy;
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
