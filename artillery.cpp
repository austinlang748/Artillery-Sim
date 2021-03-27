/**********************************************************************
 * artillery.cpp
 * Artillery class definition

 * Authors:
 *    Austin Hilderbrand
 *    Elijah Harrison
 *
 * The Artillery class describes each projectile.
 **********************************************************************/

#include "artillery.h"

/**********************************************************************
 * Artillery::Artillery
 *
 * PARAM: position_0 : Position
 * PARAM: angle_0    : double
 **********************************************************************/
Artillery::Artillery(Position position_0, double angle0_Rads) {
   
   // Initialize angle and perform error-checking
   setAngle(angle0_Rads);

   // Initialize speed
   speed = artilleryV0;

   // Initialize hang time
   hangTime = 0.00;
   
   // initialize position
   position = position_0;
   initialPositionX = position.getMetersX();
   // handle invalid positions
   if (position.getMetersX() < 0) position.setMetersX(0);
   if (position.getMetersY() < 0) position.setMetersY(0);
   
   // initialize velocity
   velocity = Velocity(
       Trig::horizontalComponent(speed, angleDegrees),
       Trig::verticalComponent(speed, angleDegrees)
   );
   
   // initialize gravity
   g     = Tables::get("altitudeToGravity", getAltitude());
   
   // initialize drag
   mach  = Tables::get("altitudeToSpeedOfSound", getAltitude());
   c     = Tables::get("machToDragCoefficient", mach);
   p     = Tables::get("altitudeToDensity", getAltitude());
   a     = circleArea(getArtilleryDiameter() * .5);
   dragF = dragForce(c, p, speed, a);
   
   // initialize acceleration
   acceleration = Velocity(
      Trig::horizontalComponent(speed, angleDegrees),
      Trig::verticalComponent(speed, angleDegrees)
   );
   
   // initialize projectile path
   for (int i = 0; i < 20; i++) projectilePath[i] = Position();
}

/**********************************************************************
 * Artillery::setAngle
 * 
 * Sets the artillery angle and performs error handling.
 **********************************************************************/
void Artillery::setAngle(double angle) {
   // handle angle
   double angle0_Degrees = Trig::deg(angle);
   if (angle0_Degrees > 90 && angle0_Degrees <= 180) angle0_Degrees = 90;
   else if (angle0_Degrees < -90 && angle0_Degrees >= -180) angle0_Degrees = -90;

   // initialize angle
   angleDegrees = angle0_Degrees >= 0 ? 90 - angle0_Degrees : -90 - angle0_Degrees;

   // save initial angle as howitzer angle for display
   howitzerAngle = angleDegrees;
}

/**********************************************************************
 * Artillery::update
 *
 * Call this periodically to update the artillery attributes.
 **********************************************************************/
void Artillery::update() {

   // quick update
   if (!updateTrue) return;
   
   // update hang time
   addHangTime(.05); // fps == 30

   // update angle/speed/velocity
   angleDegrees = Trig::deg(Trig::cartesianToAngle(velocity.getDx(), velocity.getDy()));
   speed = velocity.getSpeed();

   // update gravity
   g     = Tables::get("altitudeToGravity", getAltitude());

   // update drag
   sos   = Tables::get("altitudeToSpeedOfSound", getAltitude());
   mach  = sosToDragCoefficient(sos);
   c     = Tables::get("machToDragCoefficient", mach);
   p     = Tables::get("altitudeToDensity", getAltitude());
   a     = circleArea(getArtilleryDiameter() * .5);
   dragF = dragForce(c, p, speed, a);

   // update acceleration
   acceleration.set(
      getAccelerationX(dragF, angleDegrees),
      getAccelerationY(g, dragF, angleDegrees)
   );

   // update position
   velocity.add(acceleration);
   position.addMeters(velocity);
   
   // update projectile path
   for (int i = 19; i > 0; --i)
      setProjectilePathAt(i, projectilePath[i-1]);
   setProjectilePathAt(0, position);
}

/**********************************************************************
 * Artillery::draw
 *
 * Draws the artillery to the screen.
 **********************************************************************/
void Artillery::draw(ogstream & gout) {
   
   // draw main projectile
   gout.drawProjectile(position);
   
   // draw path traveled
   if (updateTrue) // only draw when projectile is moving
      for (int i = 0; i < 20; i++)
         gout.drawProjectile(projectilePath[i], (double)i*.5);
}

/**********************************************************************
 * Artillery::drawInfo
 *
 * PARAM: gout : ogstream&
 **********************************************************************/
void Artillery::drawInfo(ogstream & gout) {
   // this method will be called by demo, and will only be called for
   // one single artillery object (the last one in the stack)

   // set positioning/column spacing
   textPosition.setPixels(200, 450);
   valuePosition = textPosition;
   valuePosition.addPixelsX(240);
   unitsPosition = valuePosition;
   unitsPosition.addPixelsX(70);

   // display info
   drawInfo(gout, "Artillery Hang Time", getHangTime(), "s");
   drawInfo(gout, "Artillery Altitude", getAltitude(), "m");
   drawInfo(gout, "Artillery Speed", getSpeed(), "m/s");
   drawInfo(gout, "Artillery Distance Traveled", getDistance(), "m");
   drawInfo(gout, "Howitzer Angle", howitzerAngle, "º");

   if (landed) {
      gout.setPosition(Position(3500, 4000));
      gout << "LANDED";
   }
}

/**********************************************************************
 * Artillery::drawInfo
 *
 * PARAM: gout        : ogstream&
 * PARAM: description : String
 * PARAM: value       : Double
 * PARAM: units       : String
 **********************************************************************/
void Artillery::drawInfo(ogstream & gout, string description, double value, string units) {
   
   double dy = -20;
   gout.setPosition(textPosition);
   gout << description << ":";
   textPosition.addPixelsY(dy);
   
   gout.setPosition(valuePosition);
   gout << value;
   valuePosition.addPixelsY(dy);
   
   gout.setPosition(unitsPosition);
   gout << " " << units;
   unitsPosition.addPixelsY(dy);
}

/**********************************************************************
 * STATIC METHODS
 **********************************************************************/

/**********************************************************************
 * STATIC METHOD: get force
 *
 * calculates and returns force based on given mass and acceleration
 *
 * PARAM: mass : double
 * PARAM: acceleration : double
 *
 * force formula: f = m a
 *
 * where
 * f = force in newtons (N)
 * m = mass in kilograms (kg)
 * a = acceleration (m/s²)
 **********************************************************************/
double Artillery::getForce(double mass, double acceleration) {
    return mass * acceleration;
}

/**********************************************************************
 * STATIC METHOD: speed of sound to drag coefficient
 *
 * calculates and returns drag coefficient based on current 
 * sos/reference sos
 *
 * PARAM: speed of sound : double
 *
 * drag coefficient formula: c = current sos / reference sos
 *
 * where
 * c = current drag coefficient
 * current sos = current speed of sound
 * reference sos = speed of sound in dry air at 20 ºC
 * speed of sound in dry air at 20 °C = 343 m / s
 **********************************************************************/
double Artillery::sosToDragCoefficient(double sos) {
   double sosReference = 343;
   return sos/sosReference;
}

/**********************************************************************
 * STATIC METHOD: drag force
 *
 * calculates and returns drag force given the following parameters:
 *
 * PARAM: c : double
 * PARAM: ρ (p) : double
 * PARAM: v : double
 * PARAM: a : double
 *
 * drag force formula: d = ½ c ρ v² a
 *
 * where
 * d = force in newtons (N)
 * c = drag coefficient
 * ρ = density of the fluid/gas (kg/m^3)
 * v = velocity of the projectile (m/s)
 * a = surface area (m^2)
 **********************************************************************/
double Artillery::dragForce(double c, double p, double v, double a) {
    return 0.5 * c * p * v * v * a;
}

/**********************************************************************
 * STATIC METHOD: circle area
 *
 * calculates and returns area of a circle
 *
 * PARAM: r : double
 *
 * area of a circle formula: a = π r²
 *
 * where
 * a = area of the circle (m²)
 * r = radius of the circle (m)
 **********************************************************************/
double Artillery::circleArea(double radius) {
    return M_PI * radius * radius;
}

/**********************************************************************
 * STATIC METHOD: get acceleration x
 *
 * calculates and returns the horizontal acceleration to be
 * applied on projectile based on the following parameters
 *
 * PARAM: dragF : double
 * PARAM: angle : double
 *
 * horizontal acceleration formula: 
 *    accelerationX = -dragF * cos(angle) / artilleryMass
 *
 * where
 * dragF = drag force (directional force applied on projectile 
           due to drag) (N)
 * angle = direction of drag force applied on projectile (degrees)
 **********************************************************************/
double Artillery::getAccelerationX(double dragF, double angle) {
    return -(Trig::horizontalComponent(dragF, angle) / artilleryMass);
}

/**********************************************************************
 * STATIC METHOD: get acceleration y
 *
 * calculates and returns the vertical acceleration to be
 * applied on projectile based on the following parameters
 *
 * PARAM: gravity : double
 * PARAM: dragF : double
 * PARAM: angle : double
 *
 * horizontal acceleration formula: 
 *    accelerationY = - (gravity + dragF * sin(angle) / artilleryMass)
 *
 * where
 * gravity = acceleration due to gravity at given altitude (m/s/s)
 * dragF = drag force (directional force applied on projectile 
           due to drag) (N)
 * angle = direction of drag force applied on projectile (degrees)
 * artilleryMass = mass of artillery (kg)
 **********************************************************************/
double Artillery::getAccelerationY(double gravity, double dragF, double angle) {
    return -(gravity + Trig::verticalComponent(dragF, angle) / artilleryMass);
}