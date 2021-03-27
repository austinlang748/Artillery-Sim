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
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
#include "ground.h"     // for GROUND
#include "howitzer.h"   // for HOWITZER
#include "artillery.h"  // for ARTILLERY
#include "test.h"       // include unit test class
using namespace std;

#define  SCREEN_WIDTH   1000
#define  SCREEN_HEIGHT  800

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
private:
   Ground      ground;        // the ground
   Position    ptUpperRight;  // size of the screen
   Howitzer    howitzer;      // howitzer cannon object
   Artillery*  artillery;     // artillery
   
   int keyDownTimer = 0;

public:
   
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight)
   {
      Position hpos = Position(ptUpperRight.getMetersX() * 0.5, 0);
      ground.reset(hpos);
      hpos = Position(
         ptUpperRight.getMetersX() * 0.5,
         ground.getElevationMeters(hpos));


      // initialize objects
      howitzer = Howitzer(hpos); // howitzer
      ground.reset(hpos);        // ground
      artillery = NULL;
   }
   
   void update() {

      if (artillery) {
         
         // advance time one frame's worth of time elapsed
         artillery->addHangTime(1/30);

         // move the projectile across the screen
         artillery->update();
         
         // stop updating artillery when it hits the ground
         if (artillery->getPosition().getMetersY() < ground.getElevationMeters(artillery->getPosition())) {
            artillery->setUpdate(false);
         }
      }
   }
   
   void draw(ogstream & gout) {
      
      // draw the ground first
      ground.draw(gout);

      // draw the howitzer
      gout.drawHowitzer(howitzer.getPosition(), howitzer.getAngle(), howitzer.getTime());
      
      if (artillery) {
         gout.drawProjectile(artillery->getPosition(), artillery->getHangTime());
         for (int i = 0; i < 20; i++)
            gout.drawProjectile(artillery->getProjectilePathAt(i), (double)i * .5);
      }
      // draw some text on the screen
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      
      // artillery info
      if (artillery) artillery->draw(gout);
      
      // other text
      gout.setPosition(Position(22000, 19000));
      gout << "Press 'Q' to quit\n";
      
      gout.setPosition(Position(22000, 18000));
      gout << "Press 'R' to reset\n";
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
      if (pUI->getHeldKey(SPACE))
         artillery = new Artillery(howitzer.getPosition(), howitzer.getAngle());
      
      // restart artillery
      if (pUI->getHeldKey(R))
         artillery = NULL;

      // exit demo window (quit)
      if (pUI->getHeldKey(Q))
         exit(0);
   }
   
   Position getScreenDims() const { return ptUpperRight; }
   void setKeyDownTimer() { setKeyDownTimer(10); }
   void setKeyDownTimer(int value) { keyDownTimer = value; }
   bool keyDownTimerIsNonzero() { return keyDownTimer > 0; }
   void updateKeyDownTimer(bool debug=false) {
      if (debug) cout << keyDownTimer << endl;
      keyDownTimer--;
   }

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
   
   // zoom in/out on up/down press
   if (pGame->keyDownTimerIsNonzero()) pGame->updateKeyDownTimer();
   else if (pUI->getHeldKey(UP) || pUI->getHeldKey(DOWN)) {
      pGame->setKeyDownTimer(10);
      if       (pUI->getHeldKey(UP))   Position().zoomIn();
      else if  (pUI->getHeldKey(DOWN)) Position().zoomOut();
   }
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
   
   // cout << demo.getScreenDims() << endl;

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}
