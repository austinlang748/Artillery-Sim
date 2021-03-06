/***********************************************************************
 * Header File:
 *    Test Velocity : Test the Velocity class
 * Authors:
 *    Austin Hilderbrand
 * Summary:
 *    All the unit tests for Velocity
 ************************************************************************/

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
      test_constructorDefault();
      test_constructorNotDefault1();
      test_constructorNotDefault2();
      test_constructorNotDefault1_invalid();
      test_constructorNotDefault2_invalid();
      test_setDx_invalid();           
      test_setDx_valid();           
      test_setDy_invalid();           
      test_setDy_valid();           
      test_set_invalidDy(); 
      test_set_invalidDx();
      test_set_valid();           
      test_addDx_invalid();           
      test_addDx_valid();           
      test_addDy_invalid();           
      test_addDy_valid();           
      test_add_invalidDy();    
      test_add_invalidDx();
      test_add_valid();           
      test_addMagnitude_negMag();    
      test_addMagnitude_negAngle();
      test_addMagnitude_largeAngle();
      test_addMagnitude_valid();           
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
      assert(vel2.dx == vel1.dx == 100);
      assert(vel2.dy == vel1.dy == 100);
      //teardown
   }

   void test_constructorNotDefault1_invalid()
   {
      //setup
      //exercise
      Velocity vel("string", 100);
      //verfify
      assert(vel.dx == 0);
      assert(vel.dy == 100);
      //teardown
   }

   void test_constructorNotDefault2_invalid()
   {
      //setup
      //exercise
      Velocity vel1("string", 100);
      Velocity vel2(vel1);
      //verfify
      assert(vel2.dx == vel1.dx == 0);
      assert(vel2.dy == vel1.dy == 100);
      //teardown
   }

   void test_setDx_invalid()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      //exercise
      vel.setDx("string");
      //verfify
      assert(vel.dx == 100);
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

   void test_setDy_invalid()
   {
      //setup
      Velocity vel;
      vel.dy = 100;
      //exercise
      vel.setDy("string");
      //verfify
      assert(vel.dy == 100);
      //teardown
   }

   void test_setDy_valid()
   {
      //setup
      Velocity vel;
      vel.dy == 100;
      //exercise
      vel.setDy(200);
      //verfify
      assert(vel.dy == 200);
      //teardown
   }

   void test_set_invalidDy()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      vel.dy = 100;
      //exercise
      vel.set(200, "string");
      //verfify
      assert(vel.dx == 200);
      assert(vel.dy == 100);
      //teardown
   }

   void test_set_invalidDx()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      vel.dy = 100;
      //exercise
      vel.set("string", 200);
      //verfify
      assert(vel.dx == 100);
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

   void test_addDx_invalid()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      //exercise
      vel.addDx("string");
      //verfify
      assert(vel.dx == 100);
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

   void test_addDy_invalid()
   {
      //setup
      Velocity vel;
      vel.dy = 100;
      //exercise
      vel.addDy("string");
      //verfify
      assert(vel.dy == 100);
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

   void test_add_invalidDy()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      vel.dy = 100;
      //exercise
      vel.add(50, "string");
      //verfify
      assert(vel.dx == 150);
      assert(vel.dy == 100);
      //teardown
   }

   void test_add_invalidDx()
   {
      //setup
      Velocity vel;
      vel.dx = 100;
      vel.dy = 100;
      //exercise
      vel.add("string", 50);
      //verfify
      assert(vel.dx == 100);
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

   void test_addMagnitude_negMag()
   {
      //setup
      Velocity vel;
      vel.set(100, 100);
      //exercise
      vel.addMagnitude(2, -100);
      //verfify
      assert(vel.dx == 100 + 100 * cos(2 - M_PI));
      assert(vel.dy == 100 + 100 * sin(2 - M_PI));
      //teardown
   }

   void test_addMagnitude_negAngle()
   {
      //setup
      Velocity vel;
      vel.set(100, 100);
      //exercise
      vel.addMagnitude(-M_PI, 100);
      //verfify
      assert(vel.dx == 100 + 100 * cos(-M_PI + 2 * M_PI));
      assert(vel.dy == 100 + 100 * sin(-M_PI + 2 * M_PI));
      //teardown
   }

   void test_addMagnitude_largeAngle()
   {
      //setup
      Velocity vel;
      vel.set(100, 100);
      //exercise
      vel.addMagnitude(3 * M_PI, 100);
      //verfify
      assert(vel.dx == 100 + 100 * cos(3 * M_PI - 2 * M_PI));
      assert(vel.dy == 100 + 100 * sin(3 * M_PI - 2 * M_PI));
      //teardown
   }

   void test_addMagnitude_valid()
   {
      //setup
      Velocity vel;
      vel.set(100, 100);
      //exercise
      vel.addMagnitude(M_PI, 100);
      //verfify
      assert(vel.dx == 100 + 100 * cos(M_PI));
      assert(vel.dy == 100 + 100 * sin(M_PI));
      //teardown
   }
   
};