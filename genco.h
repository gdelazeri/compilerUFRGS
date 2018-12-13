#ifndef GENCO_H
#define GENCO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

#define MAX_STRINGS 100

void ASMgenerate(FILE* output, char* filename, TAC* tacList);
void ASMGenerateGlobalAssig(TAC* tac);
void ASMGenerateVectorDecl(TAC* tac);
void ASMGenerateAdd(TAC* tac);
void ASMGenerateSub(TAC* tac);
void ASMGenerateMul(TAC* tac);
void ASMGenerateDiv(TAC* tac);
void ASMGenerateBoolComp(TAC* tac);
void ASMGenerateEqual(TAC* tac);
void ASMGenerateAnd(TAC* tac);
void ASMGenerateOr(TAC* tac);
void ASMGenerateReadVector(TAC* tac);
void ASMGenerateMove(TAC* tac);
void ASMGenerateMoveInd(TAC* tac);
void ASMGenerateFuncStart(TAC* tac);
void ASMGenerateFuncEnd(TAC* tac);
void ASMGenerateIFZ(TAC* tac);
void ASMGenerateJump(TAC* tac);
void ASMGenerateRead(TAC* tac);
void ASMGenerateCall(TAC* tac);
void ASMGenerateArg(TAC* tac);
void ASMGeneratePrint(TAC* tac);
void ASMGenerateRet(TAC* tac);
void ASMGenerateLabel(TAC* tac);
long getValue(char* text);


FILE* out;

#endif