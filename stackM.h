#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ON_DEBUG(...) __VA_ARGS__
#define getName(var) #var

#ifndef STACK_M
#define STACK_M

typedef int stackType;
#define STACK_TYPE_DRAW "%d"
#define initStackShort(stkPointer, capacity) initStack(stkPointer, capacity ON_DEBUG(, getName(stk1), __FILE__, __func__, __LINE__))
const int multiplayCapacity = 2;

const int canaryLeftStackNum = 0x0BEDAEDA;
const int canaryRightStackNum = 0xC0FFEE;
const int canaryLeftStructNum = 0x67691488;
const int canaryRightStructNum = 0x993B022;
const int posionNumber = 0xEBA912DA;

struct stack
{
    long long int leftStructCanary;
    stackType* stackPointer;
    size_t size;
    size_t capacity;
    size_t startCapacity;
    ON_DEBUG(const char* name; 
            const char* file;
            const char* function;
            int line;)
    long long int rightStructCanary;
};
bool isCanaryAlive(stack *stk);

int checkStack(stack* stk);

void stackDump(stack* stk);

int initStack(stack* stk, size_t capacity ON_DEBUG(, const char* name, const char* file, const char* function, int line));

int pushStack(stack* stk, stackType element);

int popStack(stack* stk, stackType *returnNumber);

int destroyStack(stack* stk);

stackType* getLeftCanary(stack *stk);

stackType* getRightCanary(stack *stk);

#endif