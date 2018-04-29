// ==============================================================
//
//	PAS (Dialog Functions)
//	======================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include "PAS_DialogFunc.hpp"
#include "PAS_LCore.hpp"

bool PAS_DialogFunc::clbkENT(void *id, char *str, void *usrdata) {
  double lat, lon;
  char latNS, lonEW;

  if (strlen(str) == 0) return true;
  if (sscanf(str, "%c%lf %c%lf", &latNS, &lat, &lonEW, &lon) != 4) return false;
  PAS_LCore* LC = (PAS_LCore *)usrdata;
  PAS_VCore* VC = LC->VC;

  if (latNS != 'N' && latNS != 'n' && latNS != 'S' && latNS != 's') return false;
  if (lonEW != 'E' && lonEW != 'e' && lonEW != 'W' && lonEW != 'w') return false;
  if (latNS == 'S' || latNS == 's') lat *= -1.0;
  if (lonEW == 'W' || lonEW == 'w') lon *= -1.0;
  if (lon == -180.0) lon = 180.0;
  if (lat<-90.0 || lat>90.0) return false;
  if (lon<=-180.0 || lon>180.0) return false;
  VC->tgtLLAD = _V(lon, lat, 0.0);
  VC->tgtManual = true;
  VC->tgtUnset = false;

  return true;
}