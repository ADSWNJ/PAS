// ==============================================================
//
//	PAS (MFD Button Management)
//	=====================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==============================================================

#include "MFDButtonPage.hpp"
#include "PAS_Buttons.hpp"
#include "PAS.hpp"


PAS_Buttons::PAS_Buttons() 
{
    static const MFDBUTTONMENU mnu0[] =
    {
      {"Mode", 0, 'M'},
      {"HUD",  0, 'H'}
    };
    RegisterPage(mnu0, sizeof(mnu0) / sizeof(MFDBUTTONMENU));
    RegisterFunction("MOD", OAPI_KEY_M, &PAS::Button_MOD);
    RegisterFunction("HUD", OAPI_KEY_H, &PAS::Button_HUD);

    // Page 2, etc...
    //static const MFDBUTTONMENU mnu1[] =
    //{
    //  { "Mode Select", 0, 'M' }
    //};
    //RegisterPage(mnu1, sizeof(mnu1) / sizeof(MFDBUTTONMENU));
    //RegisterFunction("MOD", OAPI_KEY_M, &PAS::Button_MOD);

    return;
}

bool PAS_Buttons::SearchForKeysInOtherPages() const
{
    return false;
}