/**********************************************************************
 * Source File:
 *      Velocity : The representation of velocity (change of position)
 * Authors:
 *      Elijah Harrison and Austin Hilderbrand
 **********************************************************************/

#include "velocity.h"

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

   v.setDx(dx);
   v.setDy(dy);

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
    return dx == rhs.getDx() && dy == rhs.getDy();
}

/*******************************************
 * VELOCITY : not comparison operator
 * param: rhs:Velocity
 * return bool: is not equivalent
 ******************************************/
bool Velocity::operator != (const Velocity & rhs) const {
    return dx != rhs.getDx() || dy != rhs.getDy();
}
