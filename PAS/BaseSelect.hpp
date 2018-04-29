#pragma once

//
// Base Selection Helper Functions
//
// Purpose ... Holds base, runway, and pad definitions, and parses base selection data
//
// (c) Andrew Stokes (ADSWNJ) 2018
//
// All rights reserved
//

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include "orbitersdk.h"



class BaseSelect {
public:
  struct BaseDef;

  struct RunwayDef {
    BaseDef *base;
    std::string runwayname;
    double end11, end13, end21, end23;
    double papi, vasi, alt;
    double wid, len, ang;
  };

  struct BaseDef {
    OBJHANDLE ohBase;
    std::string basename;
    double lon, lat;
    std::vector<RunwayDef> runway;
  };

  struct CelDef {
    OBJHANDLE ohCelbody;
    std::string celname;
    std::vector<BaseDef> base;
  };

  BaseSelect(const std::string &baseCfgFile);
  bool initOK();
  int errLineNo();
  const std::string& errMsg();
  const std::string& errLineStr();

  BaseDef* GetFirstBase(OBJHANDLE ohCel);
  BaseDef* GetNextBase(OBJHANDLE ohCel);
  BaseDef* GetPrevBase(OBJHANDLE ohCel);
  RunwayDef* GetFirstRunway(OBJHANDLE ohCel);
  RunwayDef* GetNextRunway(OBJHANDLE ohCel);
  RunwayDef* GetPrevRunway(OBJHANDLE ohCel);

private:



  struct BaseWrapper {
    struct BaseDef base;
    bool baseOK;
    OBJHANDLE ohCel;
    std::string celname;
  };

  struct RunwayWrapper {
    struct RunwayDef runway;
    bool runwayOK;
    bool baseskip;
    std::string basename;
  };


  std::map<std::string, CelDef> m_cel;
  const enum BaseSelectVerbNames { base = 10000, runway = 10001 };
  std::map<std::string, BaseSelectVerbNames> m_baseSelectVerbs;
  bool m_initOK;
  int m_errLineNo;
  std::string m_errMsg;
  std::string m_errLineStr;
  friend std::istream& operator>>(std::istream &iss, RunwayWrapper &rw);
  friend std::istream& operator>>(std::istream &iss, BaseWrapper &bw);

  int m_curBase{ -1 };
  int m_curRunway{ -1 };
  OBJHANDLE m_ohCurCel{ nullptr };
  std::string m_ohCurCelName{ "" };

};