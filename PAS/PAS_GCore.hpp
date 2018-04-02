// ==============================================================
//
//	PAS (Global Core Header)
//	========================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include <list>
#include <string>
#include "windows.h"
#include "orbitersdk.h"
#include "PAS_Buttons.hpp"
#include "MFDPersist.hpp"
#include "MMExt2_Advanced.hpp"
using namespace std;

#ifndef _PAS_GCORE_H
#define _PAS_GCORE_H


//+++++
// Global Persistence core. One of these is instantiated for the whole orbiter session, on the first launch of this MFD type
//+++++

class PAS_GCore {
  public:
    void corePreStep(double SimT,double SimDT,double mjd);

    // Global references ... instantiation and a link to the persistence library (running the linked lists)
    PAS_GCore();
    ~PAS_GCore();
    MFDPersist P;
    bool showHUD = true;

  private:
    double coreSimT{ 0.0 };
    double coreSimDT;
    MMExt2::Advanced mma;
    bool mma_ok;
};


#endif // _PAS_GCORE_H