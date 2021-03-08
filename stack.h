#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef _STACK_H_
#define _STACK_H_

#define DEBUG_MODE
#define UNIT_TEST

static const int POISON = -2147483648;

static const unsigned long long left_canary = 0xDEADBEEF;
static const unsigned long long right_canary = 0xBADDCAFE;

// stucture declaration
typedef struct _stack {

    unsigned long long left_canary;

    int*  buf;        // pointer to allocated memory 
    int   size;       // count of date in memory
    int   capacity;   // capacity of memory

    unsigned int hash; // hash of all elements

    unsigned long long right_canary;

} stack;

static char* ErrorNames[] = {
    "ERROR 1\n"
    "pointer \'stk\' is NULL\n",

    "ERROR 2\n"
    "pointer \'buf\' is nullptr\n",

    "ERROR 3\n"
    "size > capacity\n",

    "ERROR 4\n"
    "empty cell of memory hadn't be poisoned\n",

    "ERROR 5\n"
    "destroided left canary\n",

    "ERROR 6\n"
    "destroided right canary\n",

    "ERROR 7\n"
    "cell with data is poisoned\n",

    "ERROR 8\n"
    "hash of data has been crashed\n"
};
 
enum Errors {
    STK_IS_NULL = 1,
    BUF_IS_NULL,
    OUT_OF_CAPACITY,
    EMPTY_CELL_NOT_POISOEND,
    FAIL_LEFT_CANARY,
    FAIL_RIGHT_CANARY,
    POISONED_CELL, 
    FAILED_HASH
};

int stack_construct(stack* stk, int Capacity);

int stack_distruct(stack* stk);

int stack_push(stack* stk, int element);

int stack_realloc_up(stack* stk);

int stack_realloc_down(stack* stk);

int stack_pop(stack* stk);

int stack_dump(stack* stk, FILE* log);

int stack_control(stack* stk);

void stack_work(stack* stk, int select_act, int element, int pop);

unsigned int hash(stack* stk);

//*--------------------------------------------------------------------

#ifdef DEBUG_MODE

    #define STACK_OK(stk) \
    {\
        int error_type = stack_control(stk); \
        FILE* log = fopen("log.txt", "a"); \
        switch(error_type) { \
            case STK_IS_NULL : \
            case BUF_IS_NULL : {\
                fprintf(log, "error type: %s\n file: %s\n line: %d\n", ErrorNames[error_type - 1], __FILE__, __LINE__); \
                printf("ERROR!\n information had been writen to the log file\n"); \
                abort(); \
            } \
            case OUT_OF_CAPACITY : \
            case EMPTY_CELL_NOT_POISOEND : \
            case FAIL_LEFT_CANARY : \
            case FAIL_RIGHT_CANARY : \
            case FAILED_HASH: \
            case POISONED_CELL : {\
                fprintf(log, "error type: %s\n file: %s\n line: %d\n", ErrorNames[error_type - 1], __FILE__, __LINE__); \
                DUMP(stk); \
                printf("ERROR!\n information had been writen to the log file\n"); \
                abort(); \
            } \
            default : { \
                printf("NO ERROR\n"); \
            } \
        } \
        fclose(log); \
    }
#else
    #define STACK_OK
#endif

//*--------------------------------------------------------------------

#define DUMP(stack_name) {\
    FILE* log_txt = fopen("log.txt", "a"); \
    assert(log_txt != NULL); \
    stack_dump((stack_name), log_txt); \
    fclose(log_txt);\
}

//*--------------------------------------------------------------------

#ifndef UNIT_TEST
    #define STACK_WORK(stack_name, select_act, push, pop) \
        stack_work(&(stack_name), (select_act), (push), (pop));
        
#else
    #define STACK_WORK
#endif

//*--------------------------------------------------------------------

#endif /* _STACK_H_ */