/**********************************************************************
 * testHowitzer.h
 * TestHowitzer class declaration

 * Authors:
 *    Elijah Harrison (creater of methods)
 *    Austin Hilderbrand (populator of methods)
 *
 * The TestHowitzer class contains all the unit tests for the
 * Howitzer class.
 **********************************************************************/

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

      // Setters
      test_howitzer_setPosition();
      test_howitzer_setAngle();
      test_howitzer_incrementTime();
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

   void test_howitzer_incrementTime()
   {
      //setup
      Howitzer howitzer(Position(10, 10));
      howitzer.time = 0.00;
      //exercise
      howitzer.incrementTime(0.50);
      //verfify
      assert(howitzer.time == 0.50);
      //teardown
   }

};
