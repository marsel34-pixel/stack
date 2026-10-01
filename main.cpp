// typedef double stackType;
// #define STACK_TYPE_DRAW "%zu"
// #define STACK_TYPE_DEFINED

#include "stackM.h"

int main()
{
    stackType empty = 0;
    stack stk1 = {};
    initStackShort(&stk1, 10);
    //initStack(&stk1, 10 ON_DEBUG(, getName(stk1), __FILE__, __func__, __LINE__));
    
    // popStack(&stk1, NULL);
    // pushStack(&stk1, 1488);
    for (int i = 0; i < 100; i++)
    {
        printf("%d",pushStack(&stk1, 10 + i));
    }
    //stackDump(&stk1);
    //popStack(&stk1, &empty);
    //popStack(&stk1);
    // while (1)
    // {
    //     pushStack(&stk1, 1488);
    //     //printf("%lf\n", popStack(&stk1, &empty));
    // }
    //pushStack(&stk1, 20.1);
    //pushStack(&stk1, 30.1);
    //printf("%lf\n", popStack(&stk1));
    //printf("%lf\n", popStack(&stk1));
    //printf("%lf\n", popStack(&stk1));
    //destroyStack(&stk1);
    getchar();
}