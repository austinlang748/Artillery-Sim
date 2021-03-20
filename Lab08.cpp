/*************************************************************
 * 1. Name:
 *      The Key
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include <vector>
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
#include "ground.h"     // for GROUND
#include "howitzer.h"   // for HOWITZER
#include "artillery.h"  // for ARTILLERY
#include "test.h"       // include unit test class
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
private:
   Ground   ground;              // the ground
   Position ptUpperRight;        // size of the screen
   Howitzer howitzer;            // howitzer cannon object
   vector<Artillery> artillery;  // artillery

public:

   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight)
   {
      Position hpos = Position(
         ptUpperRight.getPixelsX() * 0.5,
         ground.getElevationMeters(Position(ptUpperRight.getPixelsX() * 0.5, 0.0))
      );

      // initialize objects
      howitzer = Howitzer(hpos); // howitzer
      ground.reset(hpos);        // ground
      
      // set projectile preview path
      for (int i = 0; i < 20; i++)
         howitzer.setProjectilePathAt(i, Position(
            (double)i * 2.0,
            ptUpperRight.getPixelsY()/1.5
         ));
   }
   
   void update() {

      // advance time by half a second.
      if (artillery.size() > 0) artillery[0].addHangTime(0.5);

      // move the projectile across the screen
      if (artillery.size() > 0) artillery[0].update();
      /*
      for (int i = 0; i < 20; i++)
      {
         double x = howitzer.getProjectilePathAt(i).getPixelsX();
         x -= 1.0;
         if (x < 0)
            x = ptUpperRight.getPixelsX();
         howitzer.getProjectilePathAt(i).setPixelsX(x);
      }
       */
   }
   
   void draw(ogstream & gout) {
      
      // draw the ground first
      ground.draw(gout);

      // draw the howitzer
      gout.drawHowitzer(howitzer.getPosition(), howitzer.getAngle(), howitzer.getTime());

      // draw the projectile
      if (artillery.size() > 0)
         gout.drawProjectile(artillery[0].getPosition());
      
      /*
       // draw projected projectile path
       for (int i = 0; i < 20; i++)
         gout.drawProjectile(howitzer.getProjectilePathAt(i), 0.5 * (double)i);
       */
   
      if (artillery.size() > 0)
         gout.drawProjectile(artillery[0].getPosition(), artillery[0].getHangTime());

      // draw some text on the screen
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      if (artillery.size() > 0)
         gout  << "Time since the bullet was fired: "
               << artillery[0].getHangTime() << "s\n";
   }
   
   void handleInput(const Interface* pUI) {
      
      // move a large amount
      if (pUI->getHeldKey(RIGHT))
         howitzer.addAngle(0.05);
      if (pUI->getHeldKey(LEFT))
         howitzer.addAngle(-0.05);

      // move by a little
      if (pUI->getHeldKey(UP))
         howitzer.addAngle((howitzer.getAngle() >= 0 ? -0.003 : 0.003));
      if (pUI->getHeldKey(DOWN))
         howitzer.addAngle((howitzer.getAngle() >= 0 ? 0.003 : -0.003));

      // fire that gun
      if (pUI->getHeldKey(SPACE)) {
         if (artillery.size() == 0)
            artillery.push_back(Artillery(howitzer.getPosition(), howitzer.getAngle()));
         else
            artillery[0].reset();
      }
      
      // restart demo

      // exit demo window (quit)
      if (pUI->getHeldKey(Q))
         exit(0);
   }

   double time;
   double angle;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pGame = (Demo*)p;
   ogstream gout;

   pGame->update();
   pGame->draw(gout);
   pGame->handleInput(pUI);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
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
   bool runTest = true;
   if (runTest) {
      testRunner();
      return 0; // quick exit
   }

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
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
