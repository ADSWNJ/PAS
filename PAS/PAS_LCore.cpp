// ==========================================================================
//
//	PAS (Local (Vessel+MFD Panel) Core Persistence)
//	=========================================================
//
//	Copyright (C) 2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See PAS.cpp
//
// ==========================================================================

#include <string>
#include "PAS_GCore.hpp"
#include "PAS_VCore.hpp"
#include "PAS_LCore.hpp"

PAS_LCore::PAS_LCore(VESSEL *vin, UINT mfdin, PAS_GCore* gcin) {
  GC = gcin;
  v = vin;
  m = mfdin;
  VC = (PAS_VCore*)GC->P.findVC(v);

  if (!GC->bs.initOK()) {
    showMessage = true;
    std::stringstream ss;
    ss << "Error in BaseDefs.cfg load.\r\nError Line: " << GC->bs.errLineNo() << "\r\nError msg: " << GC->bs.errMsg() << "\r\n\r\nError data:\r\n" << GC->bs.errLineStr();
    Message = ss.str();
  }
  return;
}
