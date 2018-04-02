// ==============================================================
//
//	PAS (Core Persistence)
//	================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include "PAS_GCore.hpp"
#include "PAS_VCore.hpp"

PAS_GCore::PAS_GCore() {
  return;
}

PAS_GCore::~PAS_GCore() {
  return;
}


void PAS_GCore::corePreStep(double simT,double simDT,double mjd) {
  if (coreSimT == 0) {
    coreSimT = simT;
    return;
  }
  if (coreSimT == simT) return;

  if (P.firstVC() == NULL) return; // No vessels interested in PAS yet

  coreSimDT = simT - coreSimT;
  coreSimT = simT;
  //sprintf(oapiDebugString(),"GCORE PRESTEP: %15.15f", coreSimDT);

  // Once per update - call vessel corePreSteps
  for (PAS_VCore* VC = (PAS_VCore*) P.firstVC(); VC != NULL; VC = (PAS_VCore*) P.nextVC()) {
    VC->corePreStep(coreSimT, coreSimDT, mjd);
  }

}
