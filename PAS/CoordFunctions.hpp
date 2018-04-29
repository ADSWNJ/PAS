#pragma once

//
// Coordinate Helper Functions
//
// Purpose ... work on matrices and vectors, linear interpolation, etc
//
// (c) Andrew Stokes (ADSWNJ) 2012-2018
//
// All rights reserved
//


// Six coordinate systems are used...
// "llad" means longitude [deg], latitude [deg], altitude [m]... defining our 3D point relative to the planet core as a function of lon and lat angles and the local altitude from the elevation functions
// "lla" means longitude [rad], latitude [rad], altitude [m] ... defining our 3D point relative to the planet core as a function of lon and lat angles and the local altitude from the elevation functions
// "llr" means longitude [rad], latitude [rad], radius [m] ... defining our 3D point relative to the planet core as a function of lon and lat angles and a radius from core
// "gpos" global position, in global frame (ecliptic equinox J2000.0 frame)
// "rpos" relative position to main gravity source, in global frame (ecliptic equinox J2000.0 frame)
// "ecef" means ECEF Cartesian coordinates [m] from the core (X-axis is core to 0-lat 0-lon, Y-axis is core to 0-lat 90E-lon, Z-axis is North Pole 90N)
//
// Three relative vector systems are used...
// "ned" means north, east, down [m] ... i.e. on a flattened out map, this distance north, this distance east, this distance down (simplified spherical model, good for say 200km x 200km)
// "ahd" means azimuth [rad], horizontal-offset [m], down-offset range [m] ... i.e. this bearing for this horizontal distance, and this vertical down disatance
// "ahdd" means azimuth [deg], horizontal-offset [m], down-offset range [m] ... i.e. this bearing for this horizontal distance, and this vertical down disatance
//
// Conversion paths are as follows:
// LLAD <> LLA <> LLR <> ECEF <> RPOS <> GPOS
// ECEF tgt + ECEF ref -> NED
// NED + ECEF ref -> ECEF tgt
// NED <> AHD <> AHDD
// 
// The cnv function automatically does intermediate transforms to deliver any to any conversions.
// Examples:
// VECTOR3 ecef_target = cf.cnv(ECEF, RPOD, 
//

#include "orbitersdk.h"
#include <limits>

#ifndef _COORD_FUNCTIONS_H
#define _COORD_FUNCTIONS_H
enum cf_type {LLAD = 0, LLA = 1, LLR = 2, GPOS = 10, RPOS = 11, ECEF = 20, NED = 30, AHD = 31, AHDD = 32};

class CoordFunctions {
public:
  CoordFunctions(VESSEL *vin);
  VECTOR3 cnv(const cf_type etype, const cf_type stype, ...);

private:
  VECTOR3 gpos_to_rpos(const VECTOR3 &gpos);
  VECTOR3 rpos_to_ecef(const VECTOR3 &rpos);
  VECTOR3 ecef_to_rpos(const VECTOR3 &ecef);
  VECTOR3 rpos_to_gpos(const VECTOR3 &rpos);
  VECTOR3 ecef_to_llr(const VECTOR3 &ecef);
  VECTOR3 llr_to_ecef(const VECTOR3 &llr);
  VECTOR3 llr_to_lla(const VECTOR3 &llr);
  VECTOR3 lla_to_llr(const VECTOR3 &lla);
  VECTOR3 ned_to_ecef(const VECTOR3 &ecef_s, const VECTOR3 &ned);
  VECTOR3 ecef_to_ned(const VECTOR3 &ecef_s, const VECTOR3 &ecef_e);
  VECTOR3 ned_to_ahd(const VECTOR3 &ned);
  VECTOR3 ahd_to_ned(const VECTOR3 &ahd);
  VECTOR3 lla_to_llad(const VECTOR3 &lla);
  VECTOR3 ahd_to_ahdd(const VECTOR3 &ahd);
  VECTOR3 llad_to_lla(const VECTOR3 &llad);
  VECTOR3 ahdd_to_ahd(const VECTOR3 &ahdd);
  MATRIX3 ecef_to_mat(const VECTOR3 &ecef);
  double to_rad(const double deg);
  double to_deg(const double rad, const bool plusonly = false);
  VESSEL *v;
};
#endif // __COORD_FUNCTIONS_H
