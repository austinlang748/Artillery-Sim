/**********************************************************************
 * testVelocity.h
 * TestVelocity class declaration

 * Authors:
 *    Austin Hilderbrand
 *
 * The TestVelocity class contains all the unit tests for the
 * Velocity class.
 **********************************************************************/

#pragma once

#include <iostream>
#include "velocity.h"
#include <cassert>
#include <math.h>

using namespace std;

class TestVelocity
{
public:
   void run()
   {
      // Constructor
      test_constructorDefault();
      test_constructorNotDefault1();
      test_constructorNotDefault2();  

      // Setters
      test_setDx_valid();           
      test_setDy_valid();           
      test_set_valid();    

      // Adders
      test_addDx_valid();                     
      test_addDy_valid();           
      test_add_valid();           
      test_addMagnitude_negmag();
   }

   void test_constructorDefault()
   {
      //setup
      //exercise
      Velocity vel;
      //verfify
      assert(vel.dx == 0.00);
      assert(vel.dy == 0.00);
      //teardown
   }

   void test_constructorNotDefault1()
   {
      //setup
      //exercise
      Velocity vel(100, 100);
      //verfify
      assert(vel.dx == 100);
      assert(vel.dy == 100);
      //teardown
   }

   void test_constructorNotDefault2()
   {
      //setup
      //exercise
      Velocity vel1(100, 100);
      Velocity vel2(vel1);
      //verfify
      assert(vel2.dx == 100 && vel1.dx == 100);
      assert(vel2.dy == 100 && vel1.dy == 100);
      //teardown
   }

   void test_setDx_valid()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      //exercise
      vel.setDx(200);
      //verfify
      assert(vel.dx == 200);
      //teardown
      }

   void test_setDy_valid()
   {
      //setup
      Velocity vel;
      vel.dy = 100;
      //exercise
      vel.setDy(200);
      //verfify
      assert(vel.dy == 200);
      //teardown
   }

   void test_set_valid()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      vel.dy = 100;
      //exercise
      vel.set(200, 200);
      //verfify
      assert(vel.dx == 200);
      assert(vel.dy == 200);
      //teardown
   }

   void test_addDx_valid()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      //exercise
      vel.addDx(50);
      //verfify
      assert(vel.dx == 150);
      //teardown
   }

   void test_addDy_valid()
   {
      //setup
      Velocity vel;
      vel.dy = 100;
      //exercise
      vel.addDy(50);
      //verfify
      assert(vel.dy == 150);
      //teardown
   }

   void test_add_valid()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      vel.dy = 100;
      //exercise
      vel.add(50, 50);
      //verfify
      assert(vel.dx == 150);
      assert(vel.dy == 150);
      //teardown
   }

   void test_addMagnitude_negmag()
   {
      //setup
      double x_init = 100;
      double y_init = 100;
      double angleDegrees = 30;
      double magnitudeToAdd = -100;
      
      Velocity vel;
      vel.set(x_init, y_init);

      //exercise
      vel.addMagnitude(angleDegrees, magnitudeToAdd);
      
      //verfify
      assert(vel.dx == x_init + std::abs(magnitudeToAdd) * cos(Trig::rad(angleDegrees)));
      assert(vel.dy == y_init + std::abs(magnitudeToAdd) * sin(Trig::rad(angleDegrees)));
      
      //teardown
   }   
};
