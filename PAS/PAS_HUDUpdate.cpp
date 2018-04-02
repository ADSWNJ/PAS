// ==============================================================
//
//	PAS (HUD Update)
//	==================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include "PAS.hpp"


void PAS::DrawHUD(int mode, const HUDPAINTSPEC *hps, oapi::Sketchpad * skp) {

  if (!GC->showHUD) return;

  bool normalScreen = (hps->W > 512);   // for 3D cockpit views, the screen is much smaller
  int CX = (normalScreen ? (int)(hps->W * 0.50) : (int)(hps->W * 0.50));
  int CY = (normalScreen ? (int)(hps->H * 0.50) : (int)(hps->H * 0.60));
  oapi::Font *HUDFont, *oldFont; 

  if (normalScreen) {
    HUDFont = oapiCreateFont(20, true, "Fixed", FONT_BOLD, 0);
  } else {
    HUDFont = oapiCreateFont(20, true, "Fixed", FONT_NORMAL, 0);
  }
  oldFont = skp->SetFont(HUDFont);

  DWORD skpcsHW = skp->GetCharSize();           // GetCharSize delivers to numbers bit-shifted in the same DWORD.
  DWORD skpcsCH = skpcsHW & 0xFFFF;             // Char height is in the lower 16
  DWORD skpcsCW = skpcsHW >> 16;	              // Char width in the upper 16

  int xPix, yPix, yPixInc;
  int xOfs, yOfs;

  yPixInc = (normalScreen ? skpcsCH + 2 : skpcsCH);
  xOfs = (normalScreen ? (int)(hps->Markersize*5.5) : (int)(hps->Markersize*4.0));     // x offset used for left right positioning
  yOfs = (int)(hps->Markersize*4.25);                                                  // y offset used for up down positioning

  xPix = (normalScreen ? (int)(CX - xOfs * 1.68) : (int)(CX - xOfs * 2.35));
  yPix = (normalScreen ? (int)(CY - yOfs * 1.75) : (int)(CY - yOfs * 2.10));

  char buf[128];

  sprintf_s(buf, 128, "Hello HUD world!");
  skp->Text(xPix, yPix, buf, strlen(buf));

  skp->SetFont(oldFont);
  oapiReleaseFont(HUDFont);
  return;
};