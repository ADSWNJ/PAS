// ====================================================================================================================//
//	PAS MFD
//	=======
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	Description:
//
//	This is the Precision Approach System MFD and HUD
//
//	Copyright Notice: 
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	For full licencing terms, pleaserefer to the GNU General Public License
//	(gpl-3_0.txt) distributed with this release, or see
//	http://www.gnu.org/licenses/.
//
//
//	Credits:
//	
//	Orbiter Simulator	(c) 2003-2018 Martin (Martins) Schweiger
// 	MFDButtonPage		(c) 2012-2018 Szymon (Enjo) Ender
//	
//
//	Release History:
//
//  V1.00	Initial Release
// ====================================================================================================================

#define STRICT
#define ORBITER_MODULE

#include "windows.h"
#include "orbitersdk.h"
#include "PAS.hpp"
#include "PAS_GCore.hpp"
#include "PAS_VCore.hpp"
#include "PAS_LCore.hpp"
#include "ParseFunctions.h"
#include "MFDPersist.hpp"


// ====================================================================================================================
// Global variables

PAS_GCore *g_SC = nullptr;    // points to the static persistence core
const char *g_moduleName = "PAS";
const char *g_moduleVersion = "0.1e";
const char *g_moduleCompileDate = __DATE__;

// ====================================================================================================================
// MFD class implementation

// Constructor executes on any F8, any resize of an ExtMFD, or any vessel switch
PAS::PAS (DWORD w, DWORD h, VESSEL *vessel, UINT mfd)
: MFD2 (w, h, vessel), moduleName(g_moduleName), moduleVersion(g_moduleVersion), moduleCompileDate(g_moduleCompileDate) {
  if (g_SC == nullptr) {
    g_SC = new PAS_GCore();
    GC = g_SC;
  }
  GC = g_SC;


  VC = (PAS_VCore*) GC->P.findVC(vessel);		  // Locate our vessel core
  if (!VC) {
    VC = new PAS_VCore(vessel, GC);				    // ... if missing, initialize it.
    GC->P.addVC(vessel, VC);
  }

  LC = (PAS_LCore*) GC->P.findLC(vessel, mfd);	// Locate our local (vessl+MFD position) core
  if (!LC) {
    LC = new PAS_LCore(vessel, mfd, GC);			  // ... if missing, initialize it.
    GC->P.addLC(vessel, mfd, LC);
  }

  // Any construction for the display side of this MFD instance
  font = oapiCreateFont (h/25, true, "Fixed", FONT_NORMAL, 0);

  sprintf_s(moduleTitle, 32, "PAS MFD %s", moduleVersion);
  return;
}

PAS::~PAS ()
{
  oapiReleaseFont(font);
  //for (int i = 0; i < 12; i++) oapiReleasePen(pen[i]);
  return;
}


// ====================================================================================================================
// Save/load from .scn functions
void PAS::ReadStatus(FILEHANDLE scn) {

  char *line;
  char *ll;
  char *key;
  int pI;
  bool pB;

  while (oapiReadScenario_nextline(scn, line)) {

    ll = line;
    if (!ParseString(&ll, &key)) break;
    if (!_stricmp(key, "END_MFD")) break;

    if (!_stricmp(key, "LOG_MODE")) {
      if (!ParseInt(&ll, &pI)) continue;
      if (pI == 0) {
        if (VC->logState == 1) {
        }
      } else if (pI == 1) {
        if (VC->logState == 0) {
        }
      }
      continue;
    }
    if (!_stricmp(key, "HUD_MODE")) {
      if (!ParseBool(&ll, &pB)) continue;
      GC->showHUD = pB;
      continue;
    }


  }

  return;
  
}

void PAS::WriteStatus(FILEHANDLE scn) const {

  oapiWriteScenario_int(scn, (char *) "LOG_MODE", VC->logState);
  oapiWriteScenario_string(scn, (char *) "HUD_MODE", GC->showHUD? (char *) "TRUE" : (char *) "FALSE");

  return;
}
