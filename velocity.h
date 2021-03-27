//
//  velocity.h
//  Lab08
//
//  Created by Elijah Harrison on 3/6/21.
//

#pragma once

#include <iostream>
#include <cmath>
#include "trig.h"

/**
 * Velocity Class
 **/
class Velocity
{
private:
   double dx; // change of position in metersX
   double dy; // change of position in metersY

public:

   // constructors
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy) { set(dx, dy); }
   Velocity(const Velocity& v) : dx(v.dx), dy(v.dy) {}
   Velocity& operator = (const Velocity& v) {
      set(v);
      return *this;
   }

   // getters
   double getDx()    const { return dx; }
   double getDy()    const { return dy; }
   double getSpeed() const { return Trig::mag(dx, dy); }

   bool operator == (const Velocity& rhs) const;
   bool operator != (const Velocity& rhs) const;

   // setters
   void setDx(double dx) { this->dx = dx; }
   void setDy(double dy) { this->dy = dy; }

   void set(const Velocity& v) {
      set(v.getDx(), v.getDy());
   }

   void set(double dx, double dy) {
      setDx(dx);
      setDy(dy);
   }

   // adders
   void addDx(double ddx) { dx += ddx; }
   void addDy(double ddy) { dy += ddy; }

   void add(Velocity a) { add(a.getDx(), a.getDy()); }
   void add(double ddx, double ddy) {
      addDx(ddx);
      addDy(ddy);
   }

   void addMagnitude(double angleDegrees, double magnitude) {
      addDx(Trig::horizontalComponent( std::abs(magnitude), angleDegrees));
      addDy(Trig::verticalComponent(   std::abs(magnitude), angleDegrees));
   }

   friend class TestVelocity;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Velocity& vel);
std::istream & operator >> (std::istream & in, Velocity& vel);
