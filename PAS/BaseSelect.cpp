#include <exception>
#include "BaseSelect.hpp"


BaseSelect::BaseSelect(const std::string & baseCfgFile) {

  m_baseSelectVerbs = { {"BASE", base}, {"RUNWAY", runway} };

  std::ifstream ifs(baseCfgFile);
  std::string line, tok, planetname, basename;

  m_initOK = false;
  BaseWrapper bw;
  RunwayWrapper rw;
  int baseCfgLine = 0;
  int b{0};

  try {
    while (std::getline(ifs, line), !ifs.eof()) {
      ++baseCfgLine;
      if (line.length() == 0) continue;
      std::istringstream iss(line);
      iss.exceptions(std::ifstream::badbit | std::ifstream::failbit);
      iss >> tok;
      switch (m_baseSelectVerbs[tok]) {
      case base:
        iss >> bw;
        if (!bw.baseOK) continue;
        m_cel[bw.celname].base.push_back(bw.base);
        m_cel[bw.celname].celname = bw.celname;
        break;
      case runway:
        rw.basename = bw.base.basename;
        rw.baseskip = !bw.baseOK;
        iss >> rw;
        if (!rw.runwayOK) continue;
        b = m_cel[bw.celname].base.size() - 1;
        m_cel[bw.celname].base[b].runway.push_back(rw.runway);
        break;
      default:
        if (tok.length() != 0 && tok[0] != ';') {
          throw std::exception("Unknown token - expected BASE or RUNWAY!");;
        }
      }
    }
  }
  catch (std::istringstream::failure e) {
    m_errLineNo = baseCfgLine;
    m_errMsg = "Parameter parse error!";
    m_errLineStr = line;
    return;
  }
  catch (std::exception e) {
    m_errLineNo = baseCfgLine;
    m_errMsg = e.what();
    m_errLineStr = line;
    return;
  }
  catch (...) {
    m_errLineNo = baseCfgLine;
    m_errMsg = "General parse failure!";
    m_errLineStr = line;
    return;
  }
  m_initOK = true;
  return;
}

bool BaseSelect::initOK()
{
  return m_initOK;
}

int BaseSelect::errLineNo()
{
  return m_errLineNo;
}

const std::string& BaseSelect::errLineStr()
{
  return m_errLineStr;
}


const std::string & BaseSelect::errMsg()
{
  return m_errMsg;
}

std::istream & operator>>(std::istream & iss, BaseSelect::RunwayWrapper & rw)
{
  std::string basename;
  iss >> std::quoted(basename) >> std::quoted(rw.runway.runwayname) >> rw.runway.end11 >> rw.runway.end13 >> rw.runway.end21
      >> rw.runway.end23 >> rw.runway.papi >> rw.runway.vasi >> rw.runway.alt >> rw.runway.wid >> rw.runway.len >> rw.runway.ang;
  if (basename != rw.basename) throw std::exception("Runway's base must match the previous BASE line!");
  rw.runwayOK = !rw.baseskip;
  return iss;
}

std::istream & operator>>(std::istream & iss, BaseSelect::BaseWrapper & bw)
{
  bw.baseOK = true;
  iss >> std::quoted(bw.celname) >> std::quoted(bw.base.basename) >> bw.base.lon >> bw.base.lat;
  bw.ohCel = nullptr;
  if (!(bw.ohCel = oapiGetObjectByName(const_cast<char *>(bw.celname.c_str()))) || oapiGetObjectType(bw.ohCel) != OBJTP_PLANET) {
    char buf[128];
    sprintf_s(buf, 128, "   >>> PAS BaseDef skipped base %s on %s: planet not defined in this run!", bw.base.basename.c_str(), bw.celname.c_str());
    oapiWriteLog(buf);
    bw.baseOK = false;
    return iss;
  }
  if (!(bw.base.ohBase = oapiGetBaseByName(bw.ohCel, const_cast<char *>(bw.base.basename.c_str()))) || oapiGetObjectType(bw.base.ohBase) != OBJTP_SURFBASE) {
    char buf[128];
    sprintf_s(buf, 128, "   >>> PAS BaseDef skipped base %s on %s: base not defined in this run!", bw.base.basename.c_str(), bw.celname.c_str());
    oapiWriteLog(buf);
    bw.baseOK = false;
    return iss;
  }
  return iss;
}


BaseSelect::BaseDef* BaseSelect::GetFirstBase(OBJHANDLE ohCel) {
  if (ohCel != m_ohCurCel) {
    m_ohCurCel = ohCel;
    char celname[128];
    oapiGetObjectName(ohCel, celname, 127);
    m_ohCurCelName = celname;
    m_curBase = -1;
    m_curRunway = -1;
  }
  if (m_cel[m_ohCurCelName].base.size() == 0) return nullptr;
  m_curBase = 0;
  m_curRunway = 0;
  return &(m_cel[m_ohCurCelName].base[m_curBase]);
}

BaseSelect::BaseDef* BaseSelect::GetNextBase(OBJHANDLE ohCel) {
  if (ohCel != m_ohCurCel) return GetFirstBase(ohCel);
  int bs = m_cel[m_ohCurCelName].base.size();
  if (!bs) return nullptr;
  if (m_curBase == bs - 1) m_curBase = -1;
  m_curBase++;
  m_curRunway = 0;
  return &(m_cel[m_ohCurCelName].base[m_curBase]);
}

BaseSelect::BaseDef* BaseSelect::GetPrevBase(OBJHANDLE ohCel) {
  if (ohCel != m_ohCurCel) return GetFirstBase(ohCel);
  int bs = m_cel[m_ohCurCelName].base.size();
  if (!bs) return nullptr;
  if (m_curBase == 0) m_curBase = bs;
  m_curBase--;
  m_curRunway = 0;
  return &(m_cel[m_ohCurCelName].base[m_curBase]);
}

BaseSelect::RunwayDef* BaseSelect::GetFirstRunway(OBJHANDLE ohCel) {
  m_curRunway = -1;
  if (m_curBase == -1) return nullptr;
  BaseDef& pb = m_cel[m_ohCurCelName].base[m_curBase];
  int rs = pb.runway.size();
  if (rs == 0) return nullptr;
  m_curRunway = 0;
  return &(pb.runway[m_curRunway]);
}

BaseSelect::RunwayDef* BaseSelect::GetNextRunway(OBJHANDLE ohCel) {
  if (ohCel != m_ohCurCel) return nullptr;
  if (m_curBase == -1) return nullptr;
  BaseDef& pb = m_cel[m_ohCurCelName].base[m_curBase];
  int rs = pb.runway.size();
  if (m_curRunway == rs - 1) m_curRunway = -1;
  m_curRunway++;
  return &(pb.runway[m_curRunway]);
}

BaseSelect::RunwayDef* BaseSelect::GetPrevRunway(OBJHANDLE ohCel) {
  if (ohCel != m_ohCurCel) return nullptr;
  if (m_curBase == -1) return nullptr;
  BaseDef& pb = m_cel[m_ohCurCelName].base[m_curBase];
  int rs = pb.runway.size();
  if (m_curRunway == 0) m_curRunway = rs;
  m_curRunway--;
  return &(pb.runway[m_curRunway]);
}