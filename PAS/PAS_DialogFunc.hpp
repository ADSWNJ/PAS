#pragma once
//======================================================
//
//	PAS (Dialog Handling)
//	=====================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ====================================================



#ifndef __PAS_DIALOGFunc
#define __PAS_DIALOGFunc
#include "PAS_LCore.hpp"

class PAS_DialogFunc
{
public:
  static bool clbkENT(void *id, char *str, void *usrdata);
protected:
private:
  static bool skipWS(char **p);
  static bool spanStr(char **p);
};

#endif // PAS_DialogFunc