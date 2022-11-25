#ifndef NODE_DYNAMICARRAY_H
#define NODE_DYNAMICARRAY_H

#include <arm/types.h>

typedef struct Stack_ Stack;

void stackErrorPrint(Stack *ptrStack);
int stackErrorCheck(Stack *ptrStack);
void *stackInit(unsigned size);
char stack_r_ch(Stack *ptrStack, unsigned x);
int stack_r_int(Stack* ptrStack, unsigned x);
int32_t *stack_r_int32(Stack *ptrStack, unsigned xOfElement, unsigned xOfInt32);
void *stack_r(Stack *ptrStack, unsigned x);
void *stack_w(Stack *ptrStack, unsigned x, const void *ptrValue);
void *push(Stack *ptrStack, const void *ptrValue);
void *pop(Stack *ptrStack);
void *getLast(Stack *ptrStack);
unsigned getsize(Stack *ptrStack);
void stackFree(Stack *ptrStack);

void myMemCpy(const void *toPtr, const void *fromPtr, unsigned sizeInBytes);

#endif //NODE_DYNAMICARRAY_H
