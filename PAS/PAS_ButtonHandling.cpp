// ==============================================================
//
//	PAS (Button Handling Code)
//	===============================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include "PAS.hpp"
#include <math.h>

// ==============================================================
// MFD button hooks to Button Page library
//
char* PAS::ButtonLabel (int bt)
{
	return LC->B.ButtonLabel(bt);
}

// Return button menus
int PAS::ButtonMenu (const MFDBUTTONMENU **menu) const
{
	return LC->B.ButtonMenu(menu);
}

// Return clicked button
bool PAS::ConsumeButton (int bt, int event) {
  return LC->B.ConsumeButton(this, bt, event);
}

// Return pressed keystroke
bool PAS::ConsumeKeyBuffered (DWORD key) {
  return LC->B.ConsumeKeyBuffered(this, key);
}



// ==============================================================
// MFD Button Handler Callbacks
//

void PAS::Button_MOD() {
  return;
}

void PAS::Button_TGT() {
  LC->mode = 1;
  LC->B.SelectPage(this, 1);
  return;
}

void PAS::Button_HUD() {
  GC->showHUD = !GC->showHUD;

  return;
}

void PAS::Button_OK() {
  LC->mode = 0;
  LC->B.SelectPage(this, 0);
  return;
}

void PAS::Button_NB() {
  OBJHANDLE ohCel = VC->v->GetGravityRef();
  char cel[128];
  oapiGetObjectName(ohCel, cel, 127);
  BaseSelect::BaseDef *b = GC->bs.GetNextBase(ohCel);
  if (b) {
    BaseSelect::RunwayDef *r = GC->bs.GetFirstRunway(VC->v->GetGravityRef());
    VC->ohBase = b->ohBase;
    VC->tgtBaseName = b->basename;
    VC->tgtBaseLoc = r->runwayname;
    VC->tgtLatDeg = b->lat;
    VC->tgtLonDeg = b->lon;
    VC->tgtManual = false;
    VC->tgtUnset = false;
  }
  return;
}

void PAS::Button_PB() {
  BaseSelect::BaseDef *b = GC->bs.GetPrevBase(VC->v->GetGravityRef());
  if (b) {
    BaseSelect::RunwayDef *r = GC->bs.GetFirstRunway(VC->v->GetGravityRef());
    VC->ohBase = b->ohBase;
    VC->tgtBaseName = b->basename;
    VC->tgtBaseLoc = r->runwayname;
    VC->tgtLatDeg = b->lat;
    VC->tgtLonDeg = b->lon;
    VC->tgtManual = false;
    VC->tgtUnset = false;
  }
  return;
}

void PAS::Button_NL() {
  BaseSelect::RunwayDef *r = GC->bs.GetNextRunway(VC->v->GetGravityRef());
  VC->tgtBaseLoc = r->runwayname;
  return;
}

void PAS::Button_PL() {
  BaseSelect::RunwayDef *r = GC->bs.GetPrevRunway(VC->v->GetGravityRef());
  VC->tgtBaseLoc = r->runwayname;
  return;
}

void PAS::Button_MAN() {
  return;
}
