/*************************************************
 * Artillery.cpp
 * Artillery class source file
 * Authors:
 *      Austin Hilderbrand (creator of functions)
 *      Elijah Harrison (populated functions)
 *************************************************/

#include "artillery.h"

/*************************************************
 * STATIC METHODS
 *************************************************/

/*************************************************
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
 **************************************************/
double Artillery::getForce(double mass, double acceleration) {
    return mass * acceleration;
}

/*************************************************
 * STATIC METHOD: speed of sound to drag coefficient
 *
 * calculates and returns drag coefficient based on current sos/reference sos
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
 **************************************************/
double Artillery::sosToDragCoefficient(double sos) {
   double sosReference = 343;
   return sos/sosReference;
}

/*************************************************
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
 **************************************************/
double Artillery::dragForce(double c, double p, double v, double a) {
    return 0.5 * c * p * v * v * a;
}

/*************************************************
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
 **************************************************/
double Artillery::circleArea(double radius) {
    return M_PI * radius * radius;
}

/*************************************************
 * STATIC METHOD: get acceleration x
 *
 * calculates and returns the horizontal acceleration to be
 * applied on projectile based on the following parameters
 *
 * PARAM: dragF : double
 * PARAM: angle : double
 *
 * horizontal acceleration formula: accelerationX = -dragF * cos(angle) / artilleryMass
 *
 * where
 * dragF = drag force (directional force applied on projectile due to drag) (N)
 * angle = direction of drag force applied on projectile (degrees)
 **************************************************/
double Artillery::getAccelerationX(double dragF, double angle) {
    return -(Trig::horizontalComponent(dragF, angle) / artilleryMass);
}

/*************************************************
 * STATIC METHOD: get acceleration y
 *
 * calculates and returns the vertical acceleration to be
 * applied on projectile based on the following parameters
 *
 * PARAM: gravity : double
 * PARAM: dragF : double
 * PARAM: angle : double
 *
 * horizontal acceleration formula: accelerationY = - (gravity + dragF * sin(angle) / artilleryMass)
 *
 * where
 * gravity = acceleration due to gravity at given altitude (m/s/s)
 * dragF = drag force (directional force applied on projectile due to drag) (N)
 * angle = direction of drag force applied on projectile (degrees)
 * artilleryMass = mass of artillery (kg)
 **************************************************/
double Artillery::getAccelerationY(double gravity, double dragF, double angle) {
    return -(gravity + Trig::verticalComponent(dragF, angle) / artilleryMass);
}
