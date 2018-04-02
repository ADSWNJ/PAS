// ==============================================================
//
//	PAS (Orbiter Interface)
//	============================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
//

#ifndef SCRAM_ATT_INTERFACE
#define SCRAM_ATT_INTERFACE

#include "windows.h"
#include "orbitersdk.h"
#include "PAS.hpp"


class PAS_Interface : public oapi::Module {
public:
  PAS_Interface(HINSTANCE hDLL);
  ~PAS_Interface();
  void clbkSimulationStart(RenderMode mode);
  void clbkSimulationEnd();
  void clbkPreStep (double simt, double simdt, double mjd);
  //void clbkPostStep (double simt, double simdt, double mjd);
  void clbkDeleteVessel (OBJHANDLE hVessel);
  static int MsgProc (UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam);

};
#endif // SCRAM_ATT_INTERFACE