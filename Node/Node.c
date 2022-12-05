#include "Node.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

///Инициализация вершины дерева
Node* nodeInit(void){

    Node* node = (Node*) malloc(sizeof(Node));
    if(node == NULL)
        return NULL;

    node->messageStack = stackInit(sizeof(int));
    if(stackErrorCheck(node->messageStack))
        return NULL;

    node->leftSubTree = NULL;
    node->rightSubTree = NULL;
    return node;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

///Деструктор дерева (и всех поддеревьев)
void nodeDestruct(Node* node){

    if(node != NULL) {
        stackFree(node->messageStack);
        nodeDestruct(node->leftSubTree);
        nodeDestruct(node->rightSubTree);
        free(node);
    }
}
#pragma clang diagnostic pop

///Подфункция nodeReadFromStack
void pushMessage(Node* ptrNode, Stack* ptrStack, unsigned int* i){

    int c;

    for(; (c = stack_r_int(ptrStack, *i)) != '{' && c != '}'; (*i)++)
        push(ptrNode->messageStack, &c);
    c = '\0';
    push(ptrNode->messageStack, &c);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

///Подфункция nodeReadFromFile
Node* nodeReadFromStack(Stack* ptrStack, unsigned int *i){
    assert(ptrStack != NULL);

    Node* ptrNode = nodeInit();

    if(stack_r_int(ptrStack, ++(*i)) == '{') { //наткнулись на левое дерево
        ptrNode->leftSubTree = nodeReadFromStack(ptrStack, i);
        (*i)++;
    }

    pushMessage(ptrNode, ptrStack, i);

    if(stack_r_int(ptrStack, *i) == '{') { //наткнулись на правое
        ptrNode->rightSubTree = nodeReadFromStack(ptrStack, i);

        if(stack_r_int(ptrStack, ++(*i)) != '}')
            printf("Ошибка ввода, после правого поддерева символы!\n");
    }

    return ptrNode;
}

#pragma clang diagnostic pop

///Инициализирует массив, заполняет его и возвращает ссылку на него \n
///Подфункция nodeReadFromFile
Stack* readToArrayFromFile(FILE* input) {
    assert(input != NULL);

    Stack *ptrStack = stackInit(sizeof(int));
    int c;

    while((c = getc(input)) == ' ' || c == '\n' || c == '\t')
        ;

    do {
        push(ptrStack, &c);
    } while ((c = getc(input)) != EOF);

    return ptrStack;
}

int getCountOfDisclosed(Stack* ptrStackNode){
    assert(ptrStackNode != NULL);

    int countOfDisclosed = 0; //кол-во незакрытых скобок {}

    for(int i = 0; i < getsize(ptrStackNode); i++){
        if(stack_r_int(ptrStackNode, i) == '{')
            countOfDisclosed++;
        else if(stack_r_int(ptrStackNode, i) == '}')
            countOfDisclosed--;
    }
    return countOfDisclosed;
}

///Читает дерево из данного файла и возвращает указатель на неё
Node* nodeReadFromFile(FILE* input){

    Stack* ptrStack = readToArrayFromFile(input);
    Node* node;
    unsigned int i = 0;

    if(!stackErrorCheck(ptrStack) && getCountOfDisclosed(ptrStack) == 0 && stack_r_int(ptrStack, i) == '{')
        node = nodeReadFromStack(ptrStack, &i);
    else
        node = NULL;

    stackFree(ptrStack);
    return node;
}

///Печатает сообщение из данной вершины дерева
void nodePrintMessage(Node* ptrNode){

    if(ptrNode == NULL){
        printf("nodePrintMessage: error NULL ptrNode\n");
        return;
    }

    for(int i = 0; stack_r_int(ptrNode->messageStack, i) != '\0'; i++)
        printf("%c", stack_r_int(ptrNode->messageStack, i));
}

void printFromStackToFile(FILE* output, Stack* ptrStack){

    int c;

    for(int i = 0; (c = stack_r_int(ptrStack, i)) != '\0'; i++)
        putc(c, output);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

void nodePushToFile(FILE* output, Node* ptrNode){
    assert(output != NULL && ptrNode != NULL);

    if(ptrNode->leftSubTree != NULL) {
        fprintf(output, "\"");
        printFromStackToFile(output, ptrNode->messageStack);
        fprintf(output, "\" -> \"");
        printFromStackToFile(output, ptrNode->leftSubTree->messageStack);
        fprintf(output, "\"\n");
    }

    if(ptrNode->rightSubTree != NULL){
        fprintf(output, "\"");
        printFromStackToFile(output, ptrNode->messageStack);
        fprintf(output, "\" -> \"");
        printFromStackToFile(output, ptrNode->rightSubTree->messageStack);
        fprintf(output, "\"\n");
    }

    if(ptrNode->leftSubTree != NULL)
        nodePushToFile(output, ptrNode->leftSubTree);

    if(ptrNode->rightSubTree != NULL)
        nodePushToFile(output, ptrNode->rightSubTree);
}

#pragma clang diagnostic pop

void nodeSaveToFile(FILE* output, Node* ptrNode){

    if(output != NULL){
        fprintf(output, "digraph Cock{\nnode[color=blue,fontsize=14, style=filled,fillcolor=lightgrey]\n\"");
        printFromStackToFile(output, ptrNode->messageStack);
        fprintf(output, "\" [shape=rectangle]\n");

        nodePushToFile(output, ptrNode);

        fprintf(output, "}\n");
    }
    else
        printf("save to file fail\n");
}