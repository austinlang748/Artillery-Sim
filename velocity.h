//
//  velocity.h
//  Lab08
//
//  Created by Elijah Harrison on 3/6/21.
//

#pragma once

#include <cmath>
#include "trig.h"

/**
 * Velocity Class
 **/
class Velocity
{
private:
   double dx; // change of position in pixelsX
   double dy; // change of position in pixelsY

public:

   // constructors
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy) { set(dx, dy); }
   Velocity(const Velocity& v) : dx(v.dx), dy(v.dy) {}
   Velocity& operator = (const Velocity& v);

   // getters
   double getDx()    const { return dx; }
   double getDy()    const { return dy; }
   double getSpeed() const { return Trig::mag(dx, dy); }

   bool operator == (const Velocity& rhs) const;
   bool operator != (const Velocity& rhs) const;

   // setters
   void setDx(double dx) { this->dx = dx; }
   void setDy(double dy) { this->dy = dy; }

   void set(const Velocity& v);
   void set(double dx, double dy);

   // adders
   void addDx(double ddx) { dx += ddx; }
   void addDy(double ddy) { dy += ddy; }

   void add(Velocity v);
   void add(double ddx, double ddy);
   void addMagnitude(double angleRadians, double magnitude);

   friend class TestVelocity;
};
