#include "genco.h"

int numberString = 0;
char* strings[MAX_STRINGS];

int numberBoolOperations = 0;

int numberArguments = 0;
char* argRegisters[4] = { "edi", "esi", "edx", "ecx" };

void ASMgenerate(FILE* output, char* filename, TAC* tacList) {
    int firstFunc = 0;
    out = output;

    for (int i = 0; i < MAX_STRINGS; ++i)
        strings[i] = NULL;
    numberString = 0;

    fprintf(out, "\t.file \"%s\"\n", filename);

    for (TAC* tac = tacList; tac != NULL; tac = tac->next) {
        switch (tac->type) {
            
            // global assignments
            case TAC_GLOBAL_SCALAR:
            case TAC_GLOBAL_VECTOR:
                ASMGenerateGlobalAssig(tac);
                break;
            case TAC_VECTOR_DECLARATION:   
                ASMGenerateVectorDecl(tac);
                break;     
            
            // binary operations
            case TAC_ADD:
                ASMGenerateAdd(tac);
                break;
            case TAC_SUB:
                ASMGenerateSub(tac);
                break;
            case TAC_MUL:
                ASMGenerateMul(tac);
                break;
            case TAC_DIV:
                ASMGenerateDiv(tac);
                break;
            case TAC_LT:
            case TAC_GT:
            case TAC_LE:
            case TAC_GE:
                ASMGenerateBoolComp(tac);
                break;
            case TAC_EQ:
                ASMGenerateEqual(tac);
                break;
            case TAC_AND:
                ASMGenerateAnd(tac);
                break;
            case TAC_OR:
                ASMGenerateOr(tac);
                break;

            // read vector
            case TAC_VECTOR:
                ASMGenerateReadVector(tac);
                break;
            
            // local assignments
            case TAC_MOVE:
                ASMGenerateMove(tac);
                break;
            case TAC_MOVE_IND:
                ASMGenerateMoveInd(tac);
                break;
            
            // function declaration and parameters
            case TAC_BEGINFUN:
                if (firstFunc == 0) {
                    fprintf(out, "\t.text\n");
                    firstFunc = 1;
                }
                ASMGenerateFuncStart(tac);
                break;
            case TAC_ENDFUN:
                ASMGenerateFuncEnd(tac);
                break;
 
            // control flow
            case TAC_IFZ:
                ASMGenerateIFZ(tac);
                break;
            case TAC_JUMP:
                ASMGenerateJump(tac);
                break;
            
            // function calls
            case TAC_READ:
                ASMGenerateRead(tac);
                break;
            case TAC_CALL: 
                ASMGenerateCall(tac);
                break;
            case TAC_ARG:
                ASMGenerateArg(tac);
                break;
            
            // prints
            case TAC_PRINT:
                ASMGeneratePrint(tac);
                break;

            // return
            case TAC_RET:     
                ASMGenerateRet(tac);
                break;
            
            // label
            case TAC_LABEL:
                ASMGenerateLabel(tac);
                break;
            default:
                break;
        }
    }

    fprintf(out, ".LC0:\n");
    fprintf(out, "\t.string \"%%d\\n\"\n");
    for (int i = 0; strings[i] != NULL; ++i) {
        fprintf(out, ".LC%d:\n", i+1);
        fprintf(out, "\t.string %s\n", strings[i]);
    }
}

long getValue(char* text) {
    if (text[0] == '\'')
        return text[1];
    else
        return atoi(text);
}

void ASMGenerateGlobalAssig(TAC* tac) {
    fprintf(out, "\t.globl %s\n", tac->res->text);
    fprintf(out, "\t.data\n");    
    fprintf(out, "\t.align 4\n");
    fprintf(out, "\t.type %s, @object\n", tac->res->text);
    
    if (tac->type == TAC_GLOBAL_SCALAR) {
        long number = getValue(tac->arg1->text);
        fprintf(out, "\t.size %s, 4\n", tac->res->text);
        fprintf(out, "%s:\n", tac->res->text);
        fprintf(out, "\t.long %ld\n", number);
    }
    else {
        long size = getValue(tac->arg1->text) * 4;
        fprintf(out, "\t.size %s, %ld\n", tac->res->text, size);
        fprintf(out, "%s:\n", tac->res->text);
    }
}

void ASMGenerateVectorDecl(TAC* tac) {
    fprintf(out, "\t.long %ld\n", getValue(tac->res->text));
}

void ASMGenerateAdd(TAC* tac) {  
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg1->text);
    else
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg1->text));

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\taddl %s(%%rip), %%eax\n", tac->arg2->text);
    else
        fprintf(out, "\taddl $%ld, %%eax\n", getValue(tac->arg2->text));

    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateSub(TAC* tac) {
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%edx\n", tac->arg1->text);
    else
        fprintf(out, "\tmovl $%ld, %%edx\n", getValue(tac->arg1->text));

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg2->text);
    else
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg2->text));

    fprintf(out, "\tsubl %%eax, %%edx\n");
    fprintf(out, "\tmovl %%edx, %%eax\n");

    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateMul(TAC* tac) {
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg1->text);
    else
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg1->text));

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\timull %s(%%rip), %%eax\n", tac->arg2->text);
    else
        fprintf(out, "\timull $%ld, %%eax\n", getValue(tac->arg2->text));

    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateDiv(TAC* tac) {
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg1->text);
    else
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg1->text));

    fprintf(out, "\tcltd\n");

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\tidivl %s(%%rip)\n", tac->arg2->text);
    else {
        fprintf(out, "\t.comm _%s_arg2, 4, 4\n", tac->res->text);
        fprintf(out, "\tmovl $%ld, _%s_arg2(%%rip)\n", getValue(tac->arg2->text), tac->res->text);
        fprintf(out, "\tidivl _%s_arg2(%%rip)\n", tac->res->text);
    }

    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateBoolComp(TAC* tac) {
    char jump[16];
    int fst_set, snd_set;

    fst_set = 0;
    snd_set = 1;
    switch (tac->type) {
        case TAC_LT:
            strcpy(jump, "jl");
            break;
        case TAC_GT:
            strcpy(jump, "jg");
            break;
        case TAC_LE:
            strcpy(jump, "jle");
            break;
        case TAC_GE:
            strcpy(jump, "jge");
            break;
    }

    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg1->text);
    else
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg1->text));

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\tcmp %s(%%rip), %%eax\n", tac->arg2->text);
    else
        fprintf(out, "\tcmp $%ld, %%eax\n", getValue(tac->arg2->text));

    fprintf(out, "\t%s _fstlc%d\n", jump, numberBoolOperations);
    fprintf(out, "\tmovl $%d, %s(%%rip)\n", fst_set, tac->res->text);
    fprintf(out, "\tjmp _sndlc%d\n", numberBoolOperations);
    fprintf(out, "_fstlc%d:\n", numberBoolOperations);
    fprintf(out, "\tmovl $%d, %s(%%rip)\n", snd_set, tac->res->text);
    fprintf(out, "_sndlc%d:\n", numberBoolOperations);
    numberBoolOperations++;
}

void ASMGenerateEqual(TAC* tac) {
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg1->text);
    else
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg1->text));

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%edx\n", tac->arg2->text);
    else
        fprintf(out, "\tmovl $%ld, %%edx\n", getValue(tac->arg2->text));

    fprintf(out, "\tcmpl %%eax, %%edx\n");
    
    if (tac->type == TAC_EQ) 
        fprintf(out, "\tsete %%al\n");
    else 
        fprintf(out, "\tsetne %%al\n");
    
    fprintf(out, "\tmovzbl %%al, %%eax\n");
    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateAnd(TAC* tac) {
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tcmpl $0, %s(%%rip)\n", tac->arg1->text);
    else
        fprintf(out, "\tcmpl $0, $%ld\n", getValue(tac->arg1->text));

    fprintf(out, "\tje .ANDFALSE%d\n", numberBoolOperations);

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\tcmpl $0, %s(%%rip)\n", tac->arg2->text);
    else
        fprintf(out, "\tcmpl $0, $%ld\n", getValue(tac->arg2->text));

    fprintf(out, "\tje .ANDFALSE%d\n", numberBoolOperations);

    // True
    fprintf(out, "\tmovl $1, %%eax\n");
    fprintf(out, "\tjmp .UPDATEVALUE%d\n", numberBoolOperations);

    // False
    fprintf(out, ".ANDFALSE%d:\n", numberBoolOperations);
    fprintf(out, "\tmovl $0, %%eax\n");

    fprintf(out, ".UPDATEVALUE%d:\n", numberBoolOperations);
    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);

    numberBoolOperations++;
}

void ASMGenerateOr(TAC* tac) {
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tcmpl $0, %s(%%rip)\n", tac->arg1->text);
    else
        fprintf(out, "\tcmpl $0, $%ld\n", getValue(tac->arg1->text));

    fprintf(out, "\tjne .ORTRUE%d\n", numberBoolOperations);

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\tcmpl $0, %s(%%rip)\n", tac->arg2->text);
    else
        fprintf(out, "\tcmpl $0, $%ld\n", getValue(tac->arg2->text));

    fprintf(out, "\tjne .ORTRUE%d\n", numberBoolOperations);

    // False
    fprintf(out, "\tmovl $0, %%eax\n");
    fprintf(out, "\tjmp .UPDATEVALUE%d\n", numberBoolOperations);

    // True
    fprintf(out, ".ORTRUE%d:\n", numberBoolOperations);
    fprintf(out, "\tmovl $1, %%eax\n");

    fprintf(out, ".UPDATEVALUE%d:\n", numberBoolOperations);
    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);

    numberBoolOperations++;
}

void ASMGenerateReadVector(TAC* tac) {
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);

    if (tac->arg2->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg2->text);
    else
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg2->text));
            
    fprintf(out, "\tcltq\n");
    fprintf(out, "\tmovl %s(,%%rax,4), %%eax\n", tac->arg1->text);
    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateMove(TAC* tac) {
    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg1->text);
    else 
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg1->text));
        
    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateMoveInd(TAC* tac) {
    if (tac->arg1->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->arg1->text);
    else
        fprintf(out, "\tmovl $%ld, %%eax\n", getValue(tac->arg1->text));

    if (tac->arg2->type == TYPE_SCALAR) 
        fprintf(out, "\tmovl %s(%%rip), %%edx\n", tac->arg2->text);
    else 
        fprintf(out, "\tmovl $%ld, %%edx\n", getValue(tac->arg2->text));

    fprintf(out, "\tcltq\n");
    fprintf(out, "\tmovl %%edx, %s(,%%rax,4)\n", tac->res->text);
}

void ASMGenerateFuncStart(TAC* tac) {
    fprintf(out, "\t.globl %s\n", tac->res->text);
    fprintf(out, "\t.type %s, @function\n", tac->res->text);
    fprintf(out, "%s:\n", tac->res->text);
    fprintf(out, "\t.cfi_startproc\n");
    fprintf(out, "\tpushq %%rbp\n");
    fprintf(out, "\tmovq %%rsp, %%rbp\n");      
    
    int paramCounter = 0;
    for (TAC* param = tac->next; param->type == TAC_PARAM; param = param->next) {
        fprintf(out, "\t.comm %s, 4, 4\n", param->res->text);
        fprintf(out, "\tmovl %%%s, %s(%%rip)\n",
            argRegisters[paramCounter], param->res->text);
        paramCounter++;
    }
}

void ASMGenerateFuncEnd(TAC* tac) {
    fprintf(out, "\tpopq %%rbp\n");
    fprintf(out, "\tret\n");
    fprintf(out, "\t.cfi_endproc\n");
}

void ASMGenerateIFZ(TAC* tac) {
    fprintf(out, "\tcmpl $0, %s(%%rip)\n", tac->arg1->text);
    fprintf(out, "\tje %s\n", tac->res->text);
}

void ASMGenerateJump(TAC* tac) {
    fprintf(out, "\tjmp %s\n", tac->res->text);
}

void ASMGenerateRead(TAC* tac) {
    fprintf(out, "\tmovl $%s, %%edi\n", tac->res->text);
    fprintf(out, "\tcall gets\n");
    fprintf(out, "\tmovl $%s, %%edi\n", tac->res->text);
    fprintf(out, "\tcall atoi\n");
    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateCall(TAC* tac) {
    numberArguments = 0;
    fprintf(out, "\tcall %s\n", tac->arg1->text);
    fprintf(out, "\t.comm %s, 4, 4\n", tac->res->text);
    fprintf(out, "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
}

void ASMGenerateArg(TAC* tac) {
    if (tac->res->type == TYPE_SCALAR)
        fprintf(out, "\tmovl %s(%%rip), %%%s\n", tac->res->text, argRegisters[numberArguments]);
    else
        fprintf(out, "\tmovl $%ld, %%%s\n", getValue(tac->res->text), argRegisters[numberArguments]);

    numberArguments++;
}

void ASMGeneratePrint(TAC* tac) {
    int selectedStr = 0;

    if (tac->res->dataType != DATATYPE_STRING) {
        if (tac->res->type == TYPE_SCALAR)
            fprintf(out, "\tmovl %s(%%rip), %%esi\n", tac->res->text);
        else
            fprintf(out, "\tmovl $%ld, %%esi\n", getValue(tac->res->text));
        
    } else { 
        strings[numberString] = tac->res->text;
        numberString++;
        selectedStr = numberString;

        fprintf(out, "\tmovl %%eax, %%esi\n");
    }

    fprintf(out, "\tmovl $.LC%d, %%edi\n", selectedStr);
    fprintf(out, "\tmovl $0, %%eax\n");
    fprintf(out, "\tcall printf\n");
}

void ASMGenerateRet(TAC* tac) {
    TAC* aux;
    for (aux = tac; aux->type != TAC_ENDFUN; aux = aux->next);
    fprintf(out, "\tmovl %s(%%rip), %%eax\n", tac->res->text);
}

void ASMGenerateLabel(TAC* tac) {
    fprintf(out, "%s:\n", tac->res->text);
}


