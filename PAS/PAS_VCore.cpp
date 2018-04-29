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


PAS_VCore::PAS_VCore(VESSEL *vin, PAS_GCore* gcin) : cf(vin) {
	// Vessel core constructor
  GC = gcin;
	v = vin;
  strcpy_s(clName, 128, v->GetClassName());
  return;
};

PAS_VCore::~PAS_VCore() {

}


void PAS_VCore::corePreStep(double p_simT,double p_simDT,double p_mjd) {
  VECTOR3 vgp;
  oapiGetGlobalPos(v->GetHandle(), &vgp);
  vesLLAD = cf.cnv(LLAD, GPOS, vgp);
  vesECEF = cf.cnv(ECEF, LLAD, vesLLAD);
  ofsNED = cf.cnv(NED, ECEF, vesECEF, ECEF, tgtECEF);
  double vCOGe = v->GetCOG_elev();
  bool ground_contact = v->GroundContact();
  if (ofsNED.z < vCOGe || ground_contact) ofsNED.z = 0.0;
  if (abs(ofsNED.x) < 0.01) ofsNED.x = 0.0;
  if (abs(ofsNED.y) < 0.01) ofsNED.y = 0.0;
  ofsAHDD = cf.cnv(AHDD, NED, ofsNED);
  return;
}