#ifndef NODE_NODE_H
#define NODE_NODE_H

#include <stdio.h>
#include "../DynamicArray/DynamicArray.h"

struct Node_ {
    struct Node_ *leftSubTree;
    struct Node_ *rightSubTree;
    Stack* messageStack;
};

typedef struct Node_ Node;

Node* nodeInit(void);
void nodeDestruct(Node* node);
Node* nodeReadFromFile(FILE* input);
void nodeSaveToFile(FILE* output, Node* ptrNode);
void nodePrintMessage(Node* ptrNode);

#endif //NODE_NODE_H
