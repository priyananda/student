#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "generate.h"

// Code-generation operations --------------------------------------

// values of true and false -------------------------------
const std::string TRUE = "-1";
const std::string FALSE = "0";

// registers ---------------------------------------------
const std::string FP = "$fp";
const std::string SP = "$sp";
const std::string RA = "$ra";

const std::string V0 = "$v0";
const std::string V1 = "$v1";

const std::string A0 = "$a0";
const std::string A1 = "$a1";
const std::string A2 = "$a2";
const std::string A3 = "$a3";

const std::string T0 = "$t0";
const std::string T1 = "$t1";
const std::string T2 = "$t2";
const std::string T3 = "$t3";
const std::string T4 = "$t4";
const std::string T5 = "$t5";
const std::string T6 = "$t6";
const std::string T7 = "$t7";

const std::string S0 = "$s0";
const std::string S1 = "$s1";
const std::string S2 = "$s2";
const std::string S3 = "$s3";
const std::string S4 = "$s4";
const std::string S5 = "$s5";
const std::string S6 = "$s6";
const std::string S7 = "$s7";

const std::string F0 = "$f0";
const std::string F2 = "$f2";
const std::string F4 = "$f4";
const std::string F6 = "$f6";
const std::string F8 = "$f8";
const std::string F10 = "$f10";
const std::string F12 = "$f12";
const std::string F14 = "$f14";

static const int MAXLEN = 6;

// **********************************************************************
// GenerateWithComment (std::string args -- perhaps empty)
//    given:  op code, and args
//    do:     write nicely formatted code (ending with new line)
// **********************************************************************
void GenerateWithComment(std::string opcode, std::string comment, std::string arg1,
                         std::string arg2, std::string arg3)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << "\t" << opcode;
  if (arg1 != "") {
    for (int k = 1; k <= space; k++) outFile << ' ';
    outFile << arg1;
    if (arg2 != "") {
      outFile << ", " << arg2;
      if (arg3 != "") outFile << ", " << arg3;
    }
  }
  if (comment != "") outFile << "\t\t#" << comment;
  outFile << std::endl;

}


// **********************************************************************
// Generate (std::string args -- perhaps empty)
//    given:  op code, and args
//    do:     write nicely formatted code (ending with new line)
// **********************************************************************
void Generate(std::string opcode, std::string arg1, std::string arg2, std::string arg3)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << "\t" << opcode;
  if (arg1 != "") {
    for (int k = 1; k <= space; k++) outFile << ' ';
    outFile << arg1;
    if (arg2 != "") {
      outFile << ", " << arg2;
      if (arg3 != "") outFile << ", " << arg3;
    }
  }
  outFile << std::endl;

}


// **********************************************************************
// Generate (two std::string args, one int)
//    given:  op code and args
//    do:     write nicely formatted code (ending with new line)
// **********************************************************************
void Generate(std::string opcode, std::string arg1, std::string arg2, int arg3)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << "\t" << opcode;
  for (int k = 1; k <= space; k++) outFile << ' ';
  outFile << arg1 << ", " << arg2 << ", " << arg3 << std::endl;

}


// **********************************************************************
// Generate (two std::string args, one float)
//    given:  op code and args
//    do:     write nicely formatted code (ending with new line)
// **********************************************************************
void Generate(std::string opcode, std::string arg1, std::string arg2, float arg3)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << "\t" << opcode;
  for (int k = 1; k <= space; k++) outFile << ' ';
  outFile << arg1 << ", " << arg2 << ", ";
  outFile.setf(std::ios::scientific, std::ios::floatfield);
  outFile << arg3 << std::endl;
  outFile.setf(std::ios::fixed, std::ios::floatfield);
}


// **********************************************************************
// Generate (one std::string arg, one int)
//    given:  op code and args
//    do:     write nicely formatted code (ending with new line)
// **********************************************************************
void Generate(std::string opcode, std::string arg1, int arg2)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << "\t" << opcode;
  for (int k = 1; k <= space; k++) outFile << ' ';
  outFile << arg1 << ", " << arg2 << std::endl;

}

// **********************************************************************
// Generate (one std::string arg, one float)
//    given:  op code and args
//    do:     write nicely formatted code (ending with new line)
// **********************************************************************
void Generate(std::string opcode, std::string arg1, float arg2)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << "\t" << opcode;
  for (int k = 1; k <= space; k++) outFile << ' ';
  outFile << arg1 << ", ";
  outFile.setf(std::ios::scientific, std::ios::floatfield);
  outFile << arg2 << std::endl;
  outFile.setf(std::ios::fixed, std::ios::floatfield);
}


// **********************************************************************
// Generate (one float arg)
//    given:  op code and arg
//    do:     write nicely formatted code (ending with new line)
// **********************************************************************
void Generate(std::string opcode, float arg1)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << "\t" << opcode;
  for (int k = 1; k <= space; k++) outFile << ' ';
  outFile.setf(std::ios::scientific, std::ios::floatfield);
  outFile << arg1 << std::endl;
  outFile.setf(std::ios::fixed, std::ios::floatfield);
}


// **********************************************************************
// GenerateIndexed
//    given:  op code, target register T1 (as std::string), indexed register T2
//            (as std::string), - offset xx (int), and optional comment
//    do:     write nicely formatted code (ending with new line):
//                 op T1, xx(T2) #comment
// **********************************************************************
void GenerateIndexed(std::string opcode, std::string arg1,
                     std::string arg2, int arg3, std::string comment)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << "\t" << opcode;
  for (int k = 1; k <= space; k++) outFile << ' ';
  outFile << arg1 << ", " << arg3 << "(" << arg2 << ")";
  if (comment != "") outFile << "\t#" << comment;
  outFile << std::endl;

}

// **********************************************************************
// GenerateLabeled (std::string args -- perhaps empty)
//    given:  label, op code, comment, and arg
//    do:     write nicely formatted code (ending with new line)
// **********************************************************************
void GenerateLabeled(std::string label, std::string opcode, std::string comment, std::string arg1)
{
  int space = MAXLEN - opcode.length() + 2;

  outFile << label << ':';
  outFile << "\t" << opcode;
  if (arg1 != "") {
    for (int k = 1; k <= space; k++) outFile << ' ';
    outFile << arg1;
  }
  if (comment != "") outFile << "\t# " << comment;
  outFile << std::endl;

}

// **********************************************************************
// GeneratePush
//    generate code to push the value of the given register onto the stack
// **********************************************************************
void GeneratePush(std::string s)
{
  GenerateIndexed("sw", s, SP, 0, "PUSH");
  Generate("subu", SP, SP, 4);
}

// **********************************************************************
// GenerateFPush
//    generate code to push the value of the given float register onto the stack
// **********************************************************************
void GenerateFPush(std::string s)
{
  GenerateIndexed("s.s", s, SP, 0, "FPUSH");
  Generate("subu", SP, SP, 4);
}

// **********************************************************************
// GeneratePop
//    generate code to pop the value on the top of the stack
//    into the given register
// **********************************************************************
void GeneratePop(std::string s)
{
  GenerateIndexed("lw", s, SP, 4, "POP");
  Generate("addu", SP, SP, 4);
}

// **********************************************************************
// GenerateFPop
//    generate code to pop the value on the top of the stack
//    into the given floating-point register
// **********************************************************************
void GenerateFPop(std::string s)
{
  GenerateIndexed("l.s", s, SP, 4, "FPOP");
  Generate("addu", SP, SP, 4);
}

// **********************************************************************
// GenerateLabel
//   given:    label L and optional comment
//   generate: L:    # comment
// **********************************************************************
void GenerateLabel(std::string label, std::string comment)
{
  outFile << label << ':';
  if (comment != "") outFile << "\t\t#" << comment;
  outFile << std::endl;
}

//**********************************************************************
// IntToStr
//   convert the given (non-negative) int to a std::string
// **********************************************************************
std::string IntToStr(int k)
{ int digit;
  std::string tmp = "";

  assert(k >= 0);
  if (k == 0) return("0");
  while (k>0) {
    digit = k % 10;
    k = k / 10;
    switch (digit) {
    case 0:
      tmp = "0" + tmp;
      break;
    case 1:
      tmp = "1" + tmp;
      break;
    case 2:
      tmp = "2" + tmp;
      break;
    case 3:
      tmp = "3" + tmp;
      break;
    case 4:
      tmp = "4" + tmp;
      break;
    case 5:
      tmp = "5" + tmp;
      break;
    case 6:
      tmp = "6" + tmp;
      break;
    case 7:
      tmp = "7" + tmp;
      break;
    case 8:
      tmp = "8" + tmp;
      break;
    case 9:
      tmp = "9" + tmp;
      break;
    }
  }
  return(tmp);
}

// **********************************************************************
// Return a different label each time:
//        ._L0 ._L1 ._L2, etc.
// **********************************************************************
std::string NextLabel()
{
  static int currLabel = 0;

  std::string tmp = "._L" + IntToStr(currLabel++);
  return(tmp);
}
