#ifndef _DISTUTLY_H
#define _DISTUTLY_H
/*! \defgroup DistUtly Distance and Map Utility
 *  \brief Provides a number of useful distance functions
 *  and other useful map handling functions and constants.
 *
 *  @{
*/

/*!	\file DistUtly.h
 *
*/
#include <cmath>


#ifndef _MY_ANGLEINFO
#define _MY_ANGLEINFO
const double DEGTORADFACTOR = (long double) M_PI / (long double) 180.0;
const double RADTODEGFACTOR = (long double) 180.0 / (long double) M_PI;
#endif

#ifndef EARTH_RADIUS_m
#define EARTH_RADIUS_m  6367470.0      // from the GRIB format specifications under the resolution and
                                        // component flags for the Grid Definition Section (GDS).
#endif


double Distance(const int &X1, const int &Y1, const int &X2, const int &Y2);
double Distance(const double &X1, const double &Y1, const double &X2, const double &Y2);
double Distance(const double &X1, const double &Y1, const double &Z1, const double &X2, const double &Y2, const double &Z2);

// Note: the distance is given in km!!!!
double GreatCircleDist(double Lon1, double Lat1, double Lon2, double Lat2);


double AngleMod(const double &Numerator, const double &Denominator);
double ConvertAngleSystemRadians(double OrigAngle);
double ConvertAngleSystemDegrees(double OrigAngle);

double Bearing(double Lon1, double Lat1, double Lon2, double Lat2);
void LatLonFrom(double Lat1, double Lon1, double Dist, double Dir, double &Lat2, double &Lon2);

/*! @} */	// end DistUtly group

#endif
