#ifndef _GENERATE_GUARD
#define _GENERATE_GUARD

#include <fstream>
#include <string>

// **********************************************************************
// GLOBALS
// **********************************************************************
extern std::ofstream outFile; // declared in main program

// values of true and false -------------------------------
extern const std::string TRUE;
extern const std::string FALSE;

// registers ---------------------------------------------
extern const std::string FP;
extern const std::string SP;
extern const std::string RA;

extern const std::string V0;
extern const std::string V1;

extern const std::string A0;
extern const std::string A1;
extern const std::string A2;
extern const std::string A3;

extern const std::string T0;
extern const std::string T1;
extern const std::string T2;
extern const std::string T3;
extern const std::string T4;
extern const std::string T5;
extern const std::string T6;
extern const std::string T7;

extern const std::string S0;
extern const std::string S1;
extern const std::string S2;
extern const std::string S3;
extern const std::string S4;
extern const std::string S5;
extern const std::string S6;
extern const std::string S7;

extern const std::string F0;
extern const std::string F2;
extern const std::string F4;
extern const std::string F6;
extern const std::string F8;
extern const std::string F10;
extern const std::string F12;
extern const std::string F14;

// **********************************************************************
//  Auxiliary functions
// **********************************************************************
void GenerateWithComment(std::string opcode, std::string comment="",
                         std::string arg1= "", std::string arg2 = "",
                         std::string arg3= "");
void Generate(std::string opcode, std::string arg1="", std::string arg2="",
              std::string arg3="");
void Generate(std::string opcode, std::string arg1, std::string arg2, int arg3);
void Generate(std::string opcode, std::string arg1, std::string arg2, float arg3);
void Generate(std::string opcode, std::string arg1, int arg2);
void Generate(std::string opcode, std::string arg1, float arg2);
void Generate(std::string opcode, float arg1);
void GenerateIndexed(std::string opcode, std::string arg1,
                     std::string arg2, int arg3, std::string comment = "");
void GenerateLabeled(std::string label, std::string opcode, std::string comment = "",
                     std::string arg1= "");
void GeneratePush(std::string s);
void GenerateFPush(std::string s);
void GeneratePop(std::string s);
void GenerateFPop(std::string s);
void GenerateLabel(std::string label, std::string comment = "");
std::string IntToStr(int k);
std::string NextLabel();

#endif
