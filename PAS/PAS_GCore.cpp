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

#include <string>
#include "PAS_GCore.hpp"
#include "PAS_VCore.hpp"
//#include "AutoPatch.hpp"

// ====================================================================================================================
// Global variables

extern const char *g_moduleName;
extern const char *g_moduleVersion;
extern const char *g_moduleCompileDate;

PAS_GCore::PAS_GCore()
  : mma("PAS"),
    bs(".\\Config\\MFD\\PAS\\BaseDefs.cfg") {
  string mma_ver;
  mma_ok = mma.GetVersion(&mma_ver);

  char buf[128];
  sprintf(buf, "   >>> %s connected to MMExt version %s", g_moduleName, mma_ver.c_str());
  oapiWriteLog(buf);
  //AutoPatch::Execute();
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

//AUTOPATCH_TGT("Plugin\\PAS.dll");
