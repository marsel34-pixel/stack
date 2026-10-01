#include "stackM.h"
#include <assert.h>

int initStack(stack* stk, size_t capacity ON_DEBUG(, const char* name, const char* file, const char* function, int line))
{
    assert(stk);
    assert(capacity);
   
    //ON_DEBUG(printf("svo giod\n");)
    if (stk->size != 0 || stk->capacity != 0 || stk->startCapacity != 0 
        ON_DEBUG(|| stk->file != NULL || stk->name != NULL || stk->line > 0 || stk->function != NULL))
    {
        printf("Error: initialize used stack");
        return 1;
    }
    stk->stackPointer = (stackType*)calloc(capacity + 2, sizeof(stackType)) + 1;

    if (stk->stackPointer)
    {
        
        //printf("right = %d\n", rightCanary(stk->stackPointer, stk->capacity));
        ON_DEBUG(stk->name = name; 
                 stk->file = file;
                 stk->function = function;
                 stk->line = line;)

        stk->capacity = capacity;
        stk->startCapacity = capacity;
        *getLeftCanary(stk) = canaryLeftStackNum;
        *getRightCanary(stk) = canaryRightStackNum;
        
        for (int i = 0; i < stk->capacity; i++)
        {
            stk->stackPointer[i] = posionNumber;
        }
        stk->leftStructCanary = canaryLeftStructNum;
        stk->rightStructCanary = canaryRightStructNum;
        return 0;
    }
    else 
    {
        return 1;
    }
    return 0;
}

int pushStack(stack* stk, stackType element)
{
    ON_DEBUG(if (checkStack(stk)) {return 1;})

    //printf("right = %d\n", rightCanary(stk->stackPointer, stk->capacity));  
    if (stk->size + 1 > stk->capacity)
    {
        stackType* buf = (stackType*)realloc(stk->stackPointer - 1, (stk->capacity  * multiplayCapacity  + 2) * sizeof(stackType));
        if (buf)
        {
        
            stk->stackPointer = buf + 1;
            stk->capacity *= multiplayCapacity;
            *getRightCanary(stk) = canaryRightStackNum;

            for (int i = stk->size; i < stk->capacity; i++)
            {
                stk->stackPointer[i] = posionNumber;
            }
            //printf("size increase %zu", stk->capacity);
        }
        else
        {
            return 1;
        }
    }

    stk->stackPointer[stk->size++] = element;

    return 0;
}

int popStack(stack* stk, stackType *returnNumber)
{
    ON_DEBUG(if (checkStack(stk)) {return 1;} )

    ON_DEBUG(
    if (stk->size == 0) 
    {
        stackDump(stk); 
        fprintf(stderr, "pop zero size stack"); 
        return 1;
    })

    //printf("right = %d\n", rightCanary(stk->stackPointer, stk->capacity));
    if (stk->size == 0)
    {
        return 1;
    }
    if(stk->size * multiplayCapacity * multiplayCapacity < stk->capacity && stk->capacity > stk->startCapacity)
    {
        
        stk->stackPointer = (stackType*)realloc(stk->stackPointer - 1, (stk->capacity / multiplayCapacity + 2) * sizeof(stackType)) + 1;
        stk->capacity /= multiplayCapacity;
        *getRightCanary(stk) = canaryRightStackNum;
        //printf("size lower %zu\n", stk->capacity);
    }
    *returnNumber = stk->stackPointer[stk->size-1];
    
    stk->stackPointer[stk->size-1] = 0xBEDA;
    stk->size--;
    return 0;
}

int destroyStack(stack* stk)
{
    ON_DEBUG(checkStack(stk);)

    free(stk->stackPointer);
    ON_DEBUG(stk->name = NULL; 
                 stk->file = NULL;
                 stk->line = -1;
                 stk->function = NULL;)
    stk->size = 0;
    stk->capacity = 0;
    stk->startCapacity = 0;
    return 0;
}

void stackDump(stack* stk)
{
    ON_DEBUG(
    printf("stack \"%s\" [%p] created by = %s() at %s:%d\n", stk->name, stk->stackPointer, stk->function, stk->file, stk->line);

    printf("Struct Left canary = %#x (%s)  ", stk->leftStructCanary, stk->leftStructCanary == canaryLeftStructNum ? "ALive" : "Die");
    printf("Right canary = %#x (%s)\n", stk->rightStructCanary, stk->rightStructCanary == canaryRightStructNum ? "ALive" : "Die");

    printf("capacity = %zu;\n", stk->capacity);
    printf("size = %zu;\n", stk->size);

    printf("Left canary = %#x (%s)  ", *getLeftCanary(stk), *getLeftCanary(stk) == canaryLeftStackNum ? "ALive" : "Die");
    printf("Right canary = %#x (%s)\n", *getRightCanary(stk), *getRightCanary(stk) == canaryRightStackNum ? "ALive" : "Die");

    printf("data\n");
    for (size_t i = 0; i < stk->capacity; i++)
    {
        if (stk->size > i)
        {
            printf("*[%zu] = " STACK_TYPE_DRAW "%s\n", i, stk->stackPointer[i], stk->stackPointer[i] == posionNumber ? "(POISON)" : "");
        }   
        else
        {
            printf("[%zu] = " STACK_TYPE_DRAW "%s\n", i, stk->stackPointer[i], stk->stackPointer[i] == posionNumber ? "(POISON)" : "");
        }
    }
    )
}

int checkStack(stack* stk)
{
    if (stk == NULL)
    {
        printf("stack struct is NULL");
        return 1;
    }
    if (stk->leftStructCanary != canaryLeftStructNum || stk->rightStructCanary != canaryRightStructNum)
    {
        stackDump(stk); 
        printf("StructCanaryIsDie\n");
        return 1;
    }
    if (stk->stackPointer == NULL)
    {
        printf("stack pointer is NULL");
        stackDump(stk);
        return 1;
    }
    if (stk->size > stk->capacity)
    {
        printf("size of stack bigger than capacity");
        stackDump(stk);
        return 1;
    }
    if (isCanaryAlive(stk)) 
    {
        stackDump(stk); 
        printf("StackCanaryIsDie\n");
        return 1;
    }
    return 0;
}

bool isCanaryAlive(stack *stk)
{
    return *getRightCanary(stk) != canaryRightStackNum || *getLeftCanary(stk) != canaryLeftStackNum;
}

stackType* getLeftCanary(stack *stk)
{
    return stk->stackPointer - 1;
}

stackType* getRightCanary(stack *stk)
{
    return stk->stackPointer + stk->capacity;
}