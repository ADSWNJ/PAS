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
      {"Target", 0, 'T' },
      {"HUD",  0, 'H'}
    };
    RegisterPage(mnu0, sizeof(mnu0) / sizeof(MFDBUTTONMENU));
    RegisterFunction("MOD", OAPI_KEY_M, &PAS::Button_MOD);
    RegisterFunction("TGT", OAPI_KEY_T, &PAS::Button_TGT);
    RegisterFunction("HUD", OAPI_KEY_H, &PAS::Button_HUD);

    static const MFDBUTTONMENU mnu1[] =
    {
      { "OK", 0, 'K' },
      { "NB", 0, 'N' },
      { "PB", 0, 'P' },
      { "NL", 0, 'F' },
      { "PL", 0, 'B' },
      { "MAN", 0, 'M' }
    };
    RegisterPage(mnu1, sizeof(mnu1) / sizeof(MFDBUTTONMENU));
    RegisterFunction("OK", OAPI_KEY_O, &PAS::Button_OK);
    RegisterFunction("NB", OAPI_KEY_N, &PAS::Button_NB);
    RegisterFunction("PB", OAPI_KEY_P, &PAS::Button_PB);
    RegisterFunction("NL", OAPI_KEY_F, &PAS::Button_NL);
    RegisterFunction("PL", OAPI_KEY_B, &PAS::Button_PL);
    RegisterFunction("MAN", OAPI_KEY_M, &PAS::Button_MAN);

    return;
}

bool PAS_Buttons::SearchForKeysInOtherPages() const
{
    return false;
}