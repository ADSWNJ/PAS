// ==============================================================
//
//	PAS (Button Handling Headers)
//	==================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================



#ifndef _PAS_BUTTON_CLASS
#define _PAS_BUTTON_CLASS
#include "MFDButtonPage.hpp"

class PAS;

class PAS_Buttons : public MFDButtonPage<PAS>
{
  public:
    PAS_Buttons();
  protected:
    bool SearchForKeysInOtherPages() const;
  private:
};
#endif // _PAS_BUTTON_CLASS

