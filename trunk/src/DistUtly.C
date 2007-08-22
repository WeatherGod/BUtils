#ifndef _DISTUTLY_C
#define _DISTUTLY_C

using namespace std;

/*	DistUtly.C
	These functions are related to various distance calculations that are needed
*/

#include <cmath>	// for sqrt(), pow(), acos(), cos(), sin(), M_PI
#include "DistUtly.h"


double Distance(const int &X1, const int &Y1, const int &X2, const int &Y2)
{
	return(hypot((double) (X1 - X2), (double) (Y1 - Y2)));
}

double Distance(const double &X1, const double &Y1, const double &X2, const double &Y2)
{
        return(hypot(X1 - X2, Y1 - Y2));
}

double Distance(const double &X1, const double &Y1, const double &Z1, const double &X2, const double &Y2, const double &Z2)
{
	return(hypot(hypot(X1 - X2, Y1 - Y2), Z1 - Z2));
}


double GreatCircleDist(double Lon1, double Lat1, double Lon2, double Lat2)
//   assumes the values are in Degrees.  Negative for West, positive for East.  Negative for South, positive for North
//   distance given in kilometers
{
//	convert to radians
	Lon1 *= DEGTORADFACTOR;
	Lat1 *= DEGTORADFACTOR;
	Lon2 *= DEGTORADFACTOR;
	Lat2 *= DEGTORADFACTOR;

//  This equation is subject to rounding errors for small distances
//	return(EarthRadius*acos(cos(Lat1)*cos(Lat2)*cos(Lon2 - Lon1) + sin(Lat1)*sin(Lat2)));

//  This equation is not as subject to rounding errors for small distances, but I have no clue about large distances
	return((EARTH_RADIUS_m / 1000.0)*2.0*asin(sqrt(pow(sin((Lat2-Lat1)/2.0), 2.0) + cos(Lat1)*cos(Lat2)*pow(sin((Lon2-Lon1)/2.0), 2.0))));
}


double AngleMod(const double &Numerator, const double &Denominator)
// This function is meant to take an angle and convert it to its equivalent in the normal range of 0 to Denominator.
//  This works fine so long as the Denominator is positive.
{
	double tempmod = fmod(Numerator, Denominator);

	if (tempmod < 0)
	{
		tempmod = tempmod + Denominator;
	}

	return(tempmod);
}

double ConvertAngleSystemRadians(double OrigAngle)
// flips the system between map (meteo) angles and math angles, assuming angles in radians
{
	OrigAngle = (-1*OrigAngle) + (M_PI*2.5);

	return(AngleMod(OrigAngle, 2.0*M_PI));
}


double ConvertAngleSystemDegrees(double OrigAngle)
// flips the system between map (meteo) angles and math angles, assuming angles in degrees
{
	OrigAngle = (-1*OrigAngle) + 450.0;

	return(AngleMod(OrigAngle, 360.0));
}

double Bearing(double Lon1, double Lat1, double Lon2, double Lat2)
//	returns value in radians using the map coordinate system, not the math coordinate system
{
// convert from Degrees to Radians
	Lon1 = Lon1 * DEGTORADFACTOR;
        Lat1 = Lat1 * DEGTORADFACTOR;
        Lon2 = Lon2 * DEGTORADFACTOR;
        Lat2 = Lat2 * DEGTORADFACTOR;

	return(AngleMod(atan2(sin(Lon2-Lon1)*cos(Lat2), 
                              cos(Lat1)*sin(Lat2)-sin(Lat1)*cos(Lat2)*cos(Lon2-Lon1)),
                    2.0*M_PI));
}

void LatLonFrom(double Lat1, double Lon1, double Dist, double Dir, double &Lat2, double &Lon2)
// assumes the direction is using the map (0 degrees is north) coordinate system and that direction is in degrees
//  The direction is actually the bearing (0 is north)
{
	const double EarthRadius = EARTH_RADIUS_m / 1000.0;           // in km
        const double RadianDist = Dist/EarthRadius;

	Lon1 = Lon1 * DEGTORADFACTOR;
	Lat1 = Lat1 * DEGTORADFACTOR;
	Dir = Dir * DEGTORADFACTOR;
        
	Lat2 = asin(sin(Lat1)*cos(RadianDist) + cos(Lat1)*sin(RadianDist)*cos(Dir));
	double dlon = atan2(-sin(Dir)*sin(RadianDist)*cos(Lat1), cos(RadianDist)-sin(Lat1)*sin(Lat2));
	Lon2 = AngleMod(Lon1-dlon + M_PI, 2.0*M_PI) - M_PI;

	Lon2 = Lon2 * RADTODEGFACTOR;
        Lat2 = Lat2 * RADTODEGFACTOR;
}

#endif
