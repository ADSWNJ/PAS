// ==============================================================
//
//	PAS (Vessel Core Persistence)
//	=======================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "PAS_GCore.hpp"
#include "PAS_VCore.hpp"
#include "ParseFunctions.h"


PAS_VCore::PAS_VCore(VESSEL *vin, PAS_GCore* gcin) {
	// Vessel core constructor
  GC = gcin;
	v = vin;
  strcpy_s(clName, 128, v->GetClassName());
  return;
};

PAS_VCore::~PAS_VCore() {

}


void PAS_VCore::corePreStep(double p_simT,double p_simDT,double p_mjd) {

  return;
}