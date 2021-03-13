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
      // Constructor
      test_howitzer_nonDefault();

      // Getters
      test_howitzer_getPosition();
      test_howitzer_getAngle();
      test_howitzer_getTime();
      test_howitzer_getProjectilePathAt();

      // Setters
      test_howitzer_setPosition();
      test_howitzer_setAngle();
      test_howitzer_setTime();
      test_howitzer_setProjectilePathAt();
   }

   void test_howitzer_nonDefault()
   {
      //setup
      //exercise
      Howitzer howitzer(Position(10, 10));
      //verfify
      assert(howitzer.position == Position(10, 10));
      assert(howitzer.time == 0.00);
      assert(howitzer.angleRadians == 0.00);
      //teardown
   }

   void test_howitzer_getPosition()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      //exercise
      Position position = howitzer.getPosition();
      //verfify
      assert(position == Position(10, 10));
      //teardown
   }

   void test_howitzer_getAngle()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      howitzer.angleRadians = 2.00;
      //exercise
      double angle = howitzer.getAngle();
      //verfify
      assert(angle == 2.00);
      //teardown
   }

   void test_howitzer_getTime()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      howitzer.time = 50.00;
      //exercise
      double time = howitzer.getTime();
      //verfify
      assert(time == 50.00);
      //teardown
   }

   void test_howitzer_getProjectilePathAt()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      howitzer.projectilePath[0] = Position(20, 20);
      //exercise
      Position projectilePosition = howitzer.getProjectilePathAt[0];
      //verfify
      assert(projectilePosition == Position(20, 20));
      //teardown
   }


   void test_howitzer_setPosition()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      //exercise
      howitzer.setPosition(Position(20, 20));
      //verfify
      assert(howitzer.position == Position(20, 20));
      //teardown
   }

   void test_howitzer_setAngle()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      howitzer.angleRadians = 0.00;
      //exercise
      howitzer.setAngle(2.00);
      //verfify
      assert(howitzer.angleRadians == 2.00);
      //teardown
   }

   void test_howitzer_setTime()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      howitzer.time = 0.00;
      //exercise
      howitzer.setTime(50.00);
      //verfify
      assert(howitzer.time == 50.00);
      //teardown
   }

   void test_howitzer_setProjectilePathAt()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      howitzer.projectilePath[0] = Position(10, 10);
      //exercise
      howitzer.setProjectilePathAt(0, Position(20, 20));
      //verfify
      assert(howitzer.projectilePath[0] == Position(20, 20));
      //teardown
   }

};
