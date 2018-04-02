// ==============================================================
//
//	PAS (MFD Display Update)
//	==================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include "PAS.hpp"
#include "DisplayEngUnitFunctions.h"
#include <math.h>
#include <stdarg.h>


bool PAS::Update(oapi::Sketchpad *skp)
{
  LC->skp = skp;
  if (LC->showMessage) return DisplayMessageMode();

  skpTitle("PAS MFD");
  int l = 3;

  skpFormatText(2, l++, "Hello world");

  return true;
};