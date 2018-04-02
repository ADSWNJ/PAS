// ==============================================================
//
//	PAS (Orbiter Interface)
//	=================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
//

#include "PAS_Interface.hpp"

// ====================================================================================================================
// Global variables

PAS_Interface *g_OrbIF = nullptr;
extern PAS_GCore *g_SC;    // points to the static persistence core

static int g_MFDmode;			// holds the mode identifier for our MFD
extern const char *g_moduleName;
extern const char *g_moduleVersion;
extern const char *g_moduleCompileDate;

// ====================================================================================================================
// Orbiter API interface 

/*
 * InitModule called when this module is selected in the launchpad
 */
DLLCLBK void InitModule (HINSTANCE hDLL)
{
  g_OrbIF = new PAS_Interface(hDLL);
  g_SC = nullptr;
  MFDMODESPECEX spec;
  spec.name = (char *) g_moduleName;
  spec.key = OAPI_KEY_S;
  spec.context = NULL;
  spec.msgproc = PAS_Interface::MsgProc;
  g_MFDmode = oapiRegisterMFDMode (spec);
  oapiRegisterModule(g_OrbIF);
  char buf[128];
  sprintf(buf, "   >>> %s module initialized: version %s, compile date %s", g_moduleName, g_moduleVersion, g_moduleCompileDate);
  oapiWriteLog(buf);
}

/*
 * ExitModule called when this module is deselected in the launchpad
 */
DLLCLBK void ExitModule (HINSTANCE hDLL)
{
  char buf[128];
  sprintf(buf, "   >>> %s module exited", g_moduleName);
  oapiWriteLog(buf);
  oapiUnregisterMFDMode (g_MFDmode);
}

/*
 * MsgProc called when Orbiter tells us something has happened (e.g. opening an MFD)
 */
int PAS_Interface::MsgProc (UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam)
{
  switch (msg) {
  case OAPI_MSG_MFD_OPENED:
    return (int)(new PAS (LOWORD(wparam), HIWORD(wparam), (VESSEL*)lparam, mfd));
  }
  return 0;
}

PAS_Interface::PAS_Interface(HINSTANCE hDLL) : oapi::Module( hDLL ) {}
PAS_Interface::~PAS_Interface() {}

/*
 * clbkSimulationStart called when Orbiter launches
 */
void PAS_Interface::clbkSimulationStart(RenderMode mode) {
  char buf[128];
  sprintf(buf, "   >>> %s module sim start", g_moduleName);
  oapiWriteLog(buf);
}

/*
 * clbkSimulationStart called when Orbiter returns to the launchpad or exits to desktop
 */
void PAS_Interface::clbkSimulationEnd() {                                      // When we exit sim back to Launchpad, make sure we tidy things up properly
  if (g_SC != nullptr) {
    g_SC->P.delLC(nullptr);
    g_SC->P.delVC(nullptr);
  }
  char buf[128];
  sprintf(buf, "   >>> %s module sim end", g_moduleName);
  oapiWriteLog(buf);
  return;
}

/*
 * clbkPreStep called before each calculation step
 */
void PAS_Interface::clbkPreStep(double simt, double simdt, double mjd) {      // Called on each iteration of the calc engine (more often than the MFD Update
  if (g_SC) g_SC->corePreStep(simt, simdt, mjd);
  return;
}

/*
 * clbkPostStep called after each calculation step
 */
//void PAS_Interface::clbkPostStep(double simt, double simdt, double mjd) {}

/*
 * clbkDeleteVessel called when a vessel is deleted
 */
void PAS_Interface::clbkDeleteVessel(OBJHANDLE hVessel) {                     // Tidy up when a vessel is deleted (stops clbkPreStep calling a dead vessel)
  VESSEL *vin = oapiGetVesselInterface(hVessel);
  if (g_SC) {
    g_SC->P.delLC(vin);
    g_SC->P.delVC(vin);
  }
}