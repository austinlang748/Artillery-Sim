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

   void test_howitzer_nonDefault() {
      //setup
      Position p(4, 5);
      Howitzer h(p);
      //verfify
      assert(h.position       == p);
      assert(h.time           == 0.0);
      assert(h.angleRadians   == 0.0);
   }


   void test_howitzer_getPosition() {
      //setup
      Position p(4, 5);
      Howitzer h(p);
      //verify
      assert(h.position == h.getPosition());
   }

   void test_howitzer_getAngle() {
      //setup
      Position p(4, 5);
      Howitzer h(p);
      h.angleRadians = 5.0;
      //verify
      assert(h.angleRadians == h.getAngle());
   }

   void test_howitzer_getTime() {
      //setup
      Position p(4, 5);
      Howitzer h(p);
      h.time = 5.0;
      //verify
      assert(h.time == h.getTime());
   }

   void test_howitzer_getProjectilePathAt() {
      //setup
      Position p(4, 5);
      Position pathP(3, 4);
      Howitzer h(p);
      int index = 5;
      h.projectilePath[index] = pathP;
      //verify
      assert(h.projectilePath[index] == h.getProjectilePathAt(index));
   }


   void test_howitzer_setPosition() {
      //setup
      Position p(4, 5);
      Position newP(6, 7);
      Howitzer h(p);
      //excercise
      h.setPosition(newP);
      //verify
      assert(h.position == newP);
   }

   void test_howitzer_setAngle() {
      //setup
      Position p(4, 5);
      double newAngle = 5.6;
      Howitzer h(p);
      //excercise
      h.setAngle(newAngle);
      //verify
      assert(h.angleRadians == newAngle);
   }

   void test_howitzer_setTime() {
      //setup
      Position p(4, 5);
      double newTime = 5.6;
      Howitzer h(p);
      //excercise
      h.setTime(newTime);
      //verify
      assert(h.time == newTime);
   }

   void test_howitzer_setProjectilePathAt() {
      //setup
      Position p(4, 5);
      double index = 5;
      Position newP(6, 7);
      Howitzer h(p);
      //excercise
      h.setProjectilePathAt(index, newP);
      //verify
      assert(h.projectilePath[index] == newP);
   }

};
