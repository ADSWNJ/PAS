// ==============================================================
//
//	PAS (MFD Display Update)
//	==================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include "PAS.hpp"
#include "DisplayEngUnitFunctions.h"
#include <math.h>
#include <stdarg.h>
#include <string>


bool PAS::Update(oapi::Sketchpad *skp)
{
  LC->skp = skp;
  if (LC->showMessage) return DisplayMessageMode();
  skpTitle(moduleTitle);
  int l = 3;
  l = 5;

  switch (LC->mode) {
  case 0:
    // Main screen
    if (VC->tgtUnset) {
      skpFormatText(0, l++, "Target:  Unset");
    } else {
      if (VC->tgtManual) {
        skpFormatText(0, l++, "Target:  Manual");
      } else {
        skpFormatText(0, l++, "Target:  %s", VC->tgtBaseName.c_str());
        skpFormatText(0, l++, "Landing: %s", VC->tgtBaseLoc.c_str());
      }
      char locStr[33];
      sprintf_s(locStr, 32, "%c%.2f %c%.2f", (VC->tgtLatDeg >= 0.0) ? 'N' : 'S', abs(VC->tgtLatDeg), (VC->tgtLonDeg >= 0.0) ? 'E' : 'W', abs(VC->tgtLonDeg));
      skpFormatText(0, l++, "Lat/Lon: %s", locStr);
    }

    break;
  case 1:
    //Targeting screen
    skpFormatText(0, l++, "Target Selection");
    l++;
    // Main screen
    if (VC->tgtUnset) {
      skpFormatText(0, l++, "Target:  Unset");
    } else {
      if (VC->tgtManual) {
        skpFormatText(0, l++, "Target:  Manual");
      } else {
        skpFormatText(0, l++, "Target:  %s", VC->tgtBaseName.c_str());
        skpFormatText(0, l++, "Landing: %s", VC->tgtBaseLoc.c_str());
      }
      char locStr[33];
      sprintf_s(locStr, 32, "%c%.2f %c%.2f", (VC->tgtLatDeg >= 0.0) ? 'N' : 'S', abs(VC->tgtLatDeg), (VC->tgtLonDeg >= 0.0) ? 'E' : 'W', abs(VC->tgtLonDeg));
      skpFormatText(0, l++, "Lat/Lon: %s", locStr);
    }
    break;
  }


  return true;
};