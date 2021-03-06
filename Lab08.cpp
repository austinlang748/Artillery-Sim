/**********************************************************************
 * 1. Names:
 *      Austin Hilderbrand
 *      Elijah Harrison
 * 2. Assignment Name:
 *      Artillery Simulator - Final Draft
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      The most difficult part was working through persistent 
 *      compiler and behavioral bugs. 
 * 5. How long did it take for you to complete the assignment?
 *      6 weeks
 **********************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
#include "demo.h"       // main class for simulator
#include "test.h"       // include unit test class
using namespace std;

#define  SCREEN_WIDTH   600
#define  SCREEN_HEIGHT  500

/**********************************************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **********************************************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pGame = (Demo*)p;
   ogstream gout;
   
   // handle some opengl things
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);
   gout.setScreenDimensions(Position(SCREEN_WIDTH, SCREEN_HEIGHT));

   // update game (methods defined in demo.cpp) (should be the last thing done in callback)
   pGame->update();
   pGame->draw(gout);
   pGame->handleInput(pUI);
}

double Position::metersFromPixels = 40.0;

/**********************************************************************
 * Initialize the simulation and set it in motion
 **********************************************************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // run test
   bool runTest = false;
   if (runTest) {
      testRunner();
      return 0; // quick exit
   }

   // Initialize OpenGL
   Position ptUpperRight(SCREEN_WIDTH, SCREEN_HEIGHT);
   ptUpperRight.setPixelsX(ptUpperRight.getMetersX());
   ptUpperRight.setPixelsY(ptUpperRight.getMetersY());
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}
