/***********************************************************************
 * Header File:
 *    Test Howitzer : Test the Howitzer class
 * Authors:
 *    Elijah Harrison and Austin Hilderbrand
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/

#pragma once

#include <iostream>
#include "howitzer.h"
#include <cassert>

using namespace std;

class TestHowitzer
{
public:
   void run() {
      test_howitzer_nonDefault();

      // getters
      test_howitzer_getters();
      test_howitzer_getPosition();
      test_howitzer_getAngle();
      test_howitzer_getTime();
      test_howitzer_getProjectilePathAt();

      // setters
      test_howitzer_setPosition();
      test_howitzer_setAngle();
      test_howitzer_setTime();
      test_howitzer_setProjectilePathAt();
   }

   void test_howitzer_nonDefault()
   {
      //setup
      //exercise
      Howitzer h(Position(4, 5));
      //verfify
      assert(h.getPosition == Position(4, 5));
      //teardown
   }


   void test_howitzer_getters()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }

   void test_howitzer_getPosition()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }

   void test_howitzer_getAngle()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }

   void test_howitzer_getTime()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }

   void test_howitzer_getProjectilePathAt()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }


   void test_howitzer_setPosition()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }

   void test_howitzer_setAngle()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }

   void test_howitzer_setTime()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }

   void test_howitzer_setProjectilePathAt()
   {
      //setup

      //exercise
      //verfify
      //teardown
   }

};
