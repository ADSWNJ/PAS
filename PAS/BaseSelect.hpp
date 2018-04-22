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
  struct RunwayDef {

    std::string runwayname;
    double end11, end13, end21, end23;
    double papi, vasi, alt;
    double wid, len, ang;
  };

  struct BaseDef {
    OBJHANDLE ohCelbody;
    OBJHANDLE ohBase;
    double lon, lat;
    std::vector<RunwayDef> runway;
  };

  BaseSelect(const std::string &baseCfgFile);
  bool initOK();
  int errLineNo();
  const std::string& errMsg();
  const std::string& errLineStr();

  BaseDef* GetBase(OBJHANDLE ohBase);
  BaseDef* GetNextBase();
  RunwayDef* GetRunway(std::string runway);
  RunwayDef* GetNextRunway();

private:



  struct BaseWrapper {
    struct BaseDef base;
    bool baseOK;
    std::string basename;
  };

  struct RunwayWrapper {
    struct RunwayDef runway;
    bool runwayOK;
    bool baseskip;
    std::string basename;
  };


  std::vector<BaseDef> m_base;
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

};