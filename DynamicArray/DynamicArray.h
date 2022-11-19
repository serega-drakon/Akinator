#ifndef NODE_DYNAMICARRAY_H
#define NODE_DYNAMICARRAY_H

#include <arm/types.h>

typedef struct Stack_ Stack;

void stackErrorPrint(Stack *ptrStack);
int stackErrorCheck(Stack *ptrStack);
void *stackInit(u_int32_t size);
char stack_r_ch(Stack *ptrStack, u_int32_t x);
int32_t *stack_r_int32(Stack *ptrStack, u_int32_t xOfElement, u_int32_t xOfInt32);
void *stack_r(Stack *ptrStack, u_int32_t x);
void *stack_w(Stack *ptrStack, u_int32_t x, const void *ptrValue);
void *push(Stack *ptrStack, const void *ptrValue);
void *pop(Stack *ptrStack);
void *getLast(Stack *ptrStack);
u_int32_t getsize(Stack *ptrStack);
void stackFree(Stack *ptrStack);

void myMemCpy(const void *toPtr, const void *fromPtr, u_int32_t sizeInBytes);

#endif //NODE_DYNAMICARRAY_H
