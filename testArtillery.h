/**********************************************************************
 * testArtillery.h
 * TestArtillery class declaration

 * Authors:
 *    Austin Hilderbrand
 *
 * The TestArtillery class contains all the unit tests for the
 * Artillery class.
 **********************************************************************/

#pragma once

#include <iostream>
#include <cassert>
#include "artillery.h"

using namespace std;

class TestArtillery
{
public:
   void run()
   {
      // Constructors
      test_initialize_valid();
      test_initialize_invalidPoint();
      test_initialize_invalidAngle1();
      test_initialize_invalidAngle2();

      // Getters
      test_getAltitude_initial(); 
      test_getAltitude_valid();
      test_getSpeed_initial(); 
      test_getSpeed_valid();
      test_getDistance_initial();
      test_getSpeed_valid();
      test_getHangTime_initial(); 
      test_getHangTime_valid();
      test_getProjectilePathAt();
      
      // setters
      test_setProjectilePathAt();
   }

   void test_initialize_valid() {
      //setup
      Position point0(0, 0);
      //exercise
      Artillery artillery(point0, M_PI / 4);
      //verfify
      assert(artillery.position.getMetersX() == 0);
      assert(artillery.position.getMetersY() == 0);
      assert(artillery.angleDegrees == 45);
      //teardown
   }

   void test_initialize_invalidPoint() {
      //setup
      Position point0(-1, 0);
      //exercise
      Artillery artillery(point0, M_PI / 4);
      //verfify
      assert(artillery.position.getMetersX() == 0);
      assert(artillery.position.getMetersY() == 0);
      //teardown
   }

   void test_initialize_invalidAngle1() {
      //setup
      Position point0(0, 0);
      //exercise
      Artillery artillery(point0, M_PI);
      //verfify
      assert(artillery.angleDegrees == 0.00);
      //teardown
   }

   void test_initialize_invalidAngle2() {
      //setup
      Position point0(0, 0);
      //exercise
      Artillery artillery(point0, -M_PI);
      //verfify
      assert(artillery.angleDegrees == 0.00);
      //teardown
   }

   void test_getAltitude_initial() {
      //setup
      Position point0(0, 0);
      Artillery artillery(point0, M_PI / 4);
      //exercise
      double altitude = artillery.getAltitude();
      //verfify
      assert(altitude == 0);
      //teardown
   }

   void test_getAltitude_valid() {
      //setup
      Position point0(0, 1000);
      Artillery artillery(point0, M_PI / 4);
      //exercise
      double altitude = artillery.getAltitude();
      //verfify
      assert(altitude == 1000);
      //teardown
   }

   void test_getSpeed_valid() {
      //setup
      Position point0(0, 0);
      Artillery artillery(point0, M_PI / 4);
      artillery.velocity.setDx(300);
      artillery.velocity.setDy(400);
      artillery.update();
      //exercise
      double speed = artillery.getSpeed();
      //verfify
      assert(speed == 500);
      //teardown
   }

   void test_getSpeed_initial() {
      //setup
      Position point0(0, 0);
      Artillery artillery(point0, M_PI / 4);
      //exercise
      double speed = artillery.getSpeed();
      //verfify
      assert(speed == 827.0);
      //teardown
   }

   void test_getDistance_invalidTime() {
      //setup
      Position point0(100, 0);
      Artillery artillery(point0, M_PI / 4);
      //exercise
      double distance = artillery.getDistance();
      //verfify
      assert(distance == 100);
      //teardown
   }

   void test_getDistance_initial() {
      //setup
      Position point0(50, 100);
      Artillery artillery(point0, 30);
      //exercise
      double distance = artillery.getDistance();
      //verfify
      assert(distance == 0);
      //teardown
   }

   void test_getHangTime_valid() {
      //setup
      Position point0(0, 0);
      Artillery artillery(point0, M_PI / 4);
      artillery.hangTime = 100;
      //exercise
      double time = artillery.getHangTime();
      //verfify
      assert(time == 100);
      //teardown
   }

   void test_getHangTime_initial() {
      //setup
      Position point0(0, 0);
      Artillery artillery(point0, M_PI / 4);
      //exercise
      double time = artillery.getHangTime();
      //verfify
      assert (time == 0);
      //teardown
   }
   
   void test_getProjectilePathAt() {
      //setup
      Artillery artillery(Position(10, 10), 0);
      artillery.projectilePath[0] = Position(20, 20);
      //exercise
      Position projectilePosition = artillery.getProjectilePathAt(0);
      //verfify
      assert(projectilePosition == Position(20, 20));
      //teardown
   }

   void test_setProjectilePathAt() {
      //setup
      Artillery artillery(Position(10, 10), 0);
      Position newPosition(30, 30);
      int index = 5;
      artillery.projectilePath[index] = Position(20, 20);
      //exercise
      artillery.setProjectilePathAt(index, newPosition);
      //verfify
      assert(artillery.projectilePath[index] == newPosition);
      //teardown
   }


};

