// ==============================================================
//
//	PAS (Vessel Core Header)
//	=============================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include <list>
#include <string>
#include <vector>
#include "windows.h"
#include "orbitersdk.h"
#include "PAS_Buttons.hpp"
#include "MFDPersist.hpp"
#include "PAS_GCore.hpp"
#include "CoordFunctions.hpp"
using namespace std;

#ifndef _PAS_VCORE_H
#define _PAS_VCORE_H

//+++++
// Vessel Persistence core. One of these is instantiated per Vessel flown with this MFD up.
//+++++

class PAS_VCore {
  public:
    void corePreStep(double p_simT,double p_simDT,double p_mjd);

    // Core references ... instantiation, vessel reference and GC.
    PAS_VCore(VESSEL *vin, PAS_GCore* gcin);
    ~PAS_VCore();
    PAS_GCore* GC;


		// Add Vessel data here
    VESSEL *v;                     // vessel pointer
    int logState;                  // 1 if we are logging, 0 if not
    char clName[128];              // class name for vessel

    // Base Location data
    OBJHANDLE ohBase{ nullptr };
    string tgtBaseName{ "" };
    string tgtBaseLoc{ "" };
    double tgtLatDeg{ 0.0 };
    double tgtLonDeg{ 0.0 };
    bool tgtManual{ false };
    bool tgtUnset{ true };


};


#endif // _PAS_VCORE_H




