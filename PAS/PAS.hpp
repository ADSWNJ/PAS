// ==============================================================
//
//	PAS MFD Headers
//	====================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================


#ifndef __PAS_H
#define __PAS_H

#include "PAS_GCore.hpp"   
#include "PAS_VCore.hpp" 
#include "PAS_LCore.hpp" 
#include "EnjoLib\IDrawsHUD.hpp"

extern "C" 
class PAS: public MFD2, EnjoLib::IDrawsHUD
{
public:
	PAS (DWORD w, DWORD h, VESSEL *vessel, UINT mfd);
	~PAS ();

  char *ButtonLabel (int bt);
	int ButtonMenu (const MFDBUTTONMENU **menu) const;
  bool ConsumeKeyBuffered (DWORD key);
  bool ConsumeButton (int bt, int event);
  
  bool Update (oapi::Sketchpad *skp);
  bool DisplayMessageMode();

  // Button Press Handlers
  void Button_MOD();
  void Button_TGT();
  void Button_HUD();
  void Button_OK();
  void Button_NB();
  void Button_PB();
  void Button_NL();
  void Button_PL();
  void Button_MAN();

  // Persistence functions
  void ReadStatus(FILEHANDLE scn);
  void WriteStatus(FILEHANDLE scn) const;

  // EnjoLib::IDrawsHUD methods:
  void DrawHUD(int mode, const HUDPAINTSPEC *hps, oapi::Sketchpad * skp);
  bool ShouldDrawHUD() const { return GC->showHUD; };
  const char * GetModuleName() const { return moduleName; };

  // Module details
  const char *moduleName;
  const char *moduleVersion;
  const char *moduleCompileDate;
  char moduleTitle[32];


protected:
  PAS_GCore* GC;
  PAS_LCore* LC;
  PAS_VCore* VC;

  oapi::IVECTOR2 iv[10000];

  int _Line(const int row );
  int _Col(const int pos );
  int _Col2(const int pos );
  void skpFormatText(const int col, const int line, const char* fmt, ...);
  void skpFmtColText(const int col, const int line, const bool test, const DWORD truecol, const DWORD falsecol, const char* fmt, ...);
  void skpFmtEngText(const int col, const int line, const char* fmt, const char* sfx, const double val, const int dloB = 0);
  void skpFmtEngText(const int col, const int line, const char* fmt, const unsigned char* sfx, const double val, const int dloB = 0);
  void skpTitle(const char* title);
  void skpColor(DWORD col);
  void showMessage();

  //                  R     G           B
  DWORD CLR_WHITE  = 255 + 255 * 256 + 255 * 256 * 256;
  DWORD CLR_RED    = 238 +  32 * 256 +  77 * 256 * 256;
  DWORD CLR_YELLOW = 255 + 255 * 256 +   0 * 256 * 256;

  oapi::Font *font;

};

#endif // !__PAS_H