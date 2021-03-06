/***********************************************************************
 * Header File:
 *    Test Velocity : Test the Velocity class
 * Authors:
 *    Elijah Harrison and Austin Hilderbrand
 * Summary:
 *    All the unit tests for Velocity
 ************************************************************************/

#pragma once

#include <iostream>
#include "velocity.h"
#include <cassert>

using namespace std;

class TestVelocity
{
public:
   void run()
   {
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
         test_add_invalid();           
         test_add_valid();           
         test_addMagnitude_invalid();           
         test_addMagnitude_valid();           
   }

   void test_setDx_invalid()
   {
      //setup
      Velocity vel;
      vel.getDx() = 100;
      //exercise
      vel.setDx("string");
      //verfify
      assert(vel.getDx() == 100)
      //teardown
   }

   void test_setDx_valid()
   {
      //setup
      Velocity vel;
      vel.setDx(100);
      //exercise
      vel.setDx(200);
      //verfify
      assert(vel.getDx() == 200)
      //teardown
      }

   void test_setDy_invalid()
   {
      //setup
      Velocity vel;
      vel.setDx(100);
      //exercise
      vel.setDy("string");
      //verfify
      assert(vel.getDy() == 100);
      //teardown
   }

   void test_setDy_valid()
   {
      //setup
      Velocity vel;
      vel.getDy() == 100;
      //exercise
      vel.setDy(200);
      //verfify
      assert(vel.getDy() == 200);
      //teardown
   }

   void test_set_invalidDy()
   {
      //setup
      Velocity vel;
      vel.setDx(100);
      vel.setDy(100);
      //exercise
      vel.set(200, "string");
      //verfify
      assert(vel.getDx() == 200);
      assert(vel.getDy() == 100);
      //teardown
   }

   void test_set_invalidDx()
   {
      //setup
      Velocity vel;
      vel.getDx() = 100;
      vel.getDy() = 100;
      //exercise
      vel.set("string", 200);
      //verfify
      assert(vel.getDx() == 100);
      assert(vel.getDy() == 200);
      //teardown
   }

   void test_set_valid()
   {
      //setup
      Velocity vel;
      vel.getDx() = 100;
      vel.getDy() = 100;
      //exercise
      vel.set(200, 200);
      //verfify
      assert(vel.getDx() == 200);
      assert(vel.getDy() == 200);
      //teardown
   }

   void test_addDx_invalid()
   {
      //setup
      Velocity vel;
      vel.setDx(100);
      //exercise
      vel.addDx(50);
      //verfify
      assert(vel.getDx() == 150);
      //teardown
   }

   void test_addDx_valid()
   {
      //setup
      //exercise
      //verfify
      //teardown
   }

   void test_addDy_invalid()
   {
      //setup
      //exercise
      //verfify
      //teardown
   }

   void test_addDy_valid()
   {
      //setup
      //exercise
      //verfify
      //teardown
   }

   void test_add_invalid()
   {
      //setup
      //exercise
      //verfify
      //teardown
   }

   void test_add_valid()
   {
      //setup
      //exercise
      //verfify
      //teardown
   }

   void test_addMagnitude_invalid()
   {
      //setup
      //exercise
      //verfify
      //teardown
   }

   void test_addMagnitude_valid()
   {
      //setup
      //exercise
      //verfify
      //teardown
   }
   
};

/**************************************************************************************
Class under test : Velocity       Input parameters                       Output
test_setDx_invalid(�string�)                             ERROR : invalid
test_setDx_valid(-100.00)                              dx = -100.00
test_setDy_invalid(�string�)                             ERROR : invalid
test_setDy_valid(-100.00)                              dy = -100.00
test_set_invalid(�string�, 100)                        ERROR : invalid
test_set_valid(100, 100)                             dx = 100, dy = 100
test_addDx_invalid(�string�)                             ERROR : invalid
test_addDx_valid(40)                                   dx += 40
test_addDy_invalid(�string�)                             Error : invalid
test_addDy_valid(-40)                                  dy += -40
test_add_invalid(�string�, 40)                         ERROR : invalid
test_add_valid(40, 40)                               dx += 40, dy += 40
test_addMagnitude_invalid(2, -100)                              ERROR : invalid
test_addMagnitude_valid(2, 100)                               dx += 100cos(2), dy += 100sin(2)
*********************************************************************************************/
