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
  int baseCount = -1;

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
        m_base.push_back(bw.base);
        baseCount++;
        break;
      case runway:
        rw.basename = bw.basename;
        rw.baseskip = bw.baseOK;
        iss >> rw;
        if (!rw.runwayOK) continue;
        m_base[baseCount].runway.push_back(rw.runway);
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
  std::string celbody;
  bw.baseOK = true;
  iss >> std::quoted(celbody) >> std::quoted(bw.basename) >> bw.base.lon >> bw.base.lat;
  if (!(bw.base.ohCelbody = oapiGetObjectByName(const_cast<char *>(celbody.c_str()))) || oapiGetObjectType(bw.base.ohCelbody) != OBJTP_PLANET) {
    char buf[128];
    sprintf_s(buf, 128, "   >>> PAS BaseDef skipped base %s on %s: planet not defined in this run!", bw.basename.c_str(), celbody.c_str());
    oapiWriteLog(buf);
    bw.baseOK = false;
    return iss;
  }
  if (!(bw.base.ohBase = oapiGetBaseByName(bw.base.ohCelbody, const_cast<char *>(bw.basename.c_str()))) || oapiGetObjectType(bw.base.ohBase) != OBJTP_SURFBASE) {
    char buf[128];
    sprintf_s(buf, 128, "   >>> PAS BaseDef skipped base %s on %s: base not defined in this run!", bw.basename.c_str(), celbody.c_str());
    oapiWriteLog(buf);
    bw.baseOK = false;
    return iss;
  }
  return iss;
}


BaseSelect::BaseDef* BaseSelect::GetBase(OBJHANDLE ohBase) {
  for (unsigned int i = 0; i < m_base.size(); i++) {
    if (m_base[i].ohBase == ohBase) {
      m_curBase = i;
      m_curRunway = 0;
      return &(m_base[m_curBase]);
    }
  }
  return nullptr;
}

BaseSelect::BaseDef* BaseSelect::GetNextBase() {
  if (m_curBase == m_base.size() - 1) m_curBase = -1;
  m_curBase++;
  m_curRunway = 0;
  return &(m_base[m_curBase]);
}

BaseSelect::RunwayDef* BaseSelect::GetRunway(std::string runway) {
  if (m_curBase == -1) return nullptr;
  BaseDef& pb = m_base[m_curBase];
  for (unsigned int i = 0; i < pb.runway.size(); i++) {
    if (pb.runway[i].runwayname == runway) {
      m_curRunway = i;
      return &(m_base[m_curBase].runway[m_curRunway]);
    }
  }
  return nullptr;
}

BaseSelect::RunwayDef* BaseSelect::GetNextRunway() {
  if (m_curBase == -1) return nullptr;
  BaseDef& pb = m_base[m_curBase];
  if (m_curRunway == pb.runway.size() - 1) m_curRunway = -1;
  m_curRunway++;
  return &(m_base[m_curBase].runway[m_curRunway]);
}