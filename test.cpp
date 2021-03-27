/**********************************************************************
 * test.cpp
 * testRunner function definition

 * Authors:
 *    Elijah Harrison (populated functions)
 *
 * The testRunner is the wrapper for the unit tests.
 **********************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testVelocity.h"
#include "testHowitzer.h"
#include "testArtillery.h"

/**********************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 **********************************************************************/
void testRunner()
{
   TestPosition().run();
   TestVelocity().run(); 
   TestHowitzer().run();
   TestArtillery().run();
}
