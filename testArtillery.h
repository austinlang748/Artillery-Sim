/***********************************************************************
 * Header File:
 *    Test Artillery : Test the Artillery class
 * Authors:
 *    Elijah Harrison and Austin Hilderbrand
 * Summary:
 *    All the unit tests for Artillery
 ************************************************************************/

#pragma once

#include <iostream>
#include "artillery.h"
#include <cassert>

using namespace std;

class TestArtillery
{
public:
   void run()
   {
      test_initialize_invalidPoint();
      test_initialize_invalidVel();
      test_initialize_invalidTime(); 
      test_initialize_valid();
      test_getAltitude_invalidTime(); 
      test_getAltitude_validTime(); 
      test_getSpeed_invalidTime(); 
      test_getSpeed_validTime(); 
      test_getDistance_invalidTime(); 
      test_getDistance_validTime(); 
      test_getHangTime_invalidTime(); 
      test_getHangTime_validTime(); 
   }

   void test_initialize_invalidPoint()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_initialize_invalidVel()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_initialize_invalidTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_initialize_valid()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_getAltitude_invalidTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_getAltitude_validTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_getSpeed_invalidTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_getSpeed_validTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_getDistance_invalidTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_getDistance_validTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_getHangTime_invalidTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

   void test_getHangTime_validTime()
   {
      //setup
      Artillery() artillery;
      //exercise
      //verfify
      //teardown
   }

};

/*********************************************************************************************
test_initialize_invalidPoint     point = (-1, 1)                        ERROR: invalid point
test_initialize_invalidVel       velocity = (1, 1)                      ERROR : starting velocity should be 0
test_initialize_invalidTime      time = 10                              ERROR : starting hang time should be 0
test_initialize_valid((150, 200), (800, 800), (0, 0), 0)  point = (150, 200) ScreenTopRight = (800, 800) velocity = (0, 0) time = 0
test_getAltitude_invalidTime     at t = -1                              point.gety = 0
test_getAltitude_validTime       at t = 10                              point.gety >= 0
test_getSpeed_invalidTime        at t = -1                              velocity.getSpeed = 0
test_getSpeed_validTime          at t = 10                              velocity.getSpeed >= 0
test_getDistance_invalidTime     at t = -1                              point.getx = 0
test_getDistance_validTime       at t = 10                              point.getx >= 0
test_getHangTime_invalidTime     at t = -1                              time = 0
test_getHangTime_validTime       at t = 10                              time >= 0
*************************************************************************************************/

