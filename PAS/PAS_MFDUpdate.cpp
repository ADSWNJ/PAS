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
      sprintf_s(locStr, 32, "%c%.2f %c%.2f", (VC->tgtLLAD.y >= 0.0) ? 'N' : 'S', abs(VC->tgtLLAD.y), (VC->tgtLLAD.x >= 0.0) ? 'E' : 'W', abs(VC->tgtLLAD.x));
      skpFormatText(0, l++, "Lat/Lon: %s", locStr);

      skpFormatText(0, l++, "Azimuth: %.2f", VC->ofsAHDD.x);
      skpFormatText(0, l++, "Range:   %.2f", VC->ofsAHDD.y);
      skpFormatText(0, l++, "North:   %.2f", VC->ofsNED.x);
      skpFormatText(0, l++, "East:    %.2f", VC->ofsNED.y);
      skpFormatText(0, l++, "Down:    %.2f", VC->ofsAHDD.z);
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
      sprintf_s(locStr, 32, "%c%.2f %c%.2f", (VC->tgtLLAD.y >= 0.0) ? 'N' : 'S', abs(VC->tgtLLAD.y), (VC->tgtLLAD.x >= 0.0) ? 'E' : 'W', abs(VC->tgtLLAD.x));
      skpFormatText(0, l++, "Lat/Lon: %s", locStr);
    }
    break;
  }


  return true;
};