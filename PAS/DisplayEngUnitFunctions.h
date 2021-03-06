//
// Display Eng Unit Helper Functions
//
// Purpose ... factor floating point numbers into engineering format (kilo, mega,etc.)
//
// (c) Andrew Stokes (ADSWNJ) 2012-2018
//
// All rights reserved
//

// DisplayEngUnit  ... Simple conversion of value into engineering format
// DisplayEngUnit2 ... Conversion of value into engineering format, adding metric suffix if units==false , or convert to US units, add US suffix if units == true
// DisplayEngUnit3 ... Simple conversion of value into engineering format, returning sym and pwr to lock the scale for DisplayEngUnit4
// DisplayEngUnit4 ... Fixed conversion of value into engineering format, using sym and pwr set in DisplayEngUnit3
// DisplayEngUnit5 ... Same as DisplayEngUnit2, but with lower bound
// DisplayEngUnit6 ... As DisplayEngUnit2, with extra boolean for displaying value or --- (e.g. for no values)
// DisplayEngUnit7 ... As DisplayEngUnit but with LoBound

void DisplayEngUnit(char* buf, char* fmt, double val);
void DisplayEngUnit2(char* buf, char* metricFmt, char* usFmt, char* metricSfx, char* usSfx, double cnvFactor, bool units, double val);
void DisplayEngUnit3(char* buf, char* fmt, double val, char* sym, int* pwr, int minpwr, int maxpwr);
void DisplayEngUnit4(char* buf, char* fmt, double val, char sym, int pwr);
void DisplayEngUnit5(char* buf, char* metricFmt, char* usFmt, char* metricSfx, char* usSfx, double cnvFactor, bool units, double val, int loB);
void DisplayEngUnit6(char* buf, char* metricFmt, char* usFmt, char* metricSfx, char* usSfx, double cnvFactor, bool units, double val, int loB, bool dispval);
void DisplayEngUnit7(char* buf, char* fmt, char* sfx, double val, int loB);
