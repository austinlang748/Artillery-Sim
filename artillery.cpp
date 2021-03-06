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
 * 
 **************************************************/
double Artillery::getForce(double mass, double acceleration) {
    /************************************
     * f = m a
     * =================================
     * f = force in newtons (N)
     * m = mass in kilograms (kg)
     * a = acceleration (m/s²)
     ************************************/
    return mass * acceleration;
}

/*************************************************
 * 
 **************************************************/
double Artillery::dragForce(double c, double p, double v, double a) {
    /************************************
     * d = ½ c ρ v² a
     * =================================
     * d = force in newtons (N)
     * c = drag coefficient
     * ρ = density of the fluid/gas
     * v = velocity of the projectile
     * a = surface area
     ************************************/
    return 0.5 * c * p * v * v * a;
}

/*************************************************
 * 
 **************************************************/
double Artillery::circleArea(double radius) {
    /************************************
     * a = π r²
     * =================================
     * a = area of the circle (m²)
     * r = radius of the circle
     ************************************/
    return M_PI * radius * radius;
}

/*************************************************
 * 
 **************************************************/
double Artillery::getAccelerationX(double dragF, double angle) {
    return -(Trig.horizontalComponent(dragF, angle) / artilleryMass);
}

/*************************************************
 * 
 **************************************************/
double Artillery::getAccelerationY(double gravity, double dragF, double angle) {
    return -(Trig.verticalComponent(dragF, angle) / artilleryMass + gravity);
}
