#include "Node.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

///Инициализация вершины дерева
Node* nodeInit(void){
    Node* node = (Node*) malloc(sizeof(Node));
    if(node == NULL)
        return NULL;

    node->messageStack = stackInit(sizeof(char));
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
    stackFree(node->messageStack);
    if (node->leftSubTree != NULL)
        nodeDestruct(node->leftSubTree);
    if (node->rightSubTree != NULL)
        nodeDestruct(node->rightSubTree);
    free(node);
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

///Подфункция nodeReadFromFile
Node* nodeReadFromStack(Stack* ptrStack, unsigned int start){
    assert(ptrStack != NULL);

    Node* ptrNode = nodeInit();

    unsigned int i = start; //позиция считывания
    unsigned int countOfDisclosed = 0; //кол-во незакрытых скобок {}

    if(stack_r_ch(ptrStack, ++i) == '{') { //наткнулись на левое дерево
        ptrNode->leftSubTree = nodeReadFromStack(ptrStack, i);
        countOfDisclosed++;
    }

    while(countOfDisclosed > 0){ //скип левого дерева
        i++;
        if(stack_r_ch(ptrStack, i) == '{')
            countOfDisclosed++;
        else if(stack_r_ch(ptrStack, i) == '}')
            countOfDisclosed--;
    }

    if(ptrNode->leftSubTree != NULL) //те здесь по алгоритму должна быть закрывающая скобка
        i++;
    char c;

    for(; (c = stack_r_ch(ptrStack, i)) != '{' && c != '}'; i++)
        push(ptrNode->messageStack, &c);
    c = '\0';
    push(ptrNode->messageStack, &c);

    if(stack_r_ch(ptrStack, i) == '{') { //наткнулись на правое
        ptrNode->rightSubTree = nodeReadFromStack(ptrStack, i);
    }
    return ptrNode;
}
#pragma clang diagnostic pop

///Инициализирует массив, заполняет его и возвращает ссылку на него \n
///Подфункция nodeReadFromFile
Stack* readToArrayFromFile(FILE* input) {
    assert(input != NULL);

    Stack *ptrStack = stackInit(sizeof(char));
    int c;

    while ((c = getc(input)) != EOF)
        push(ptrStack, &c);
    return ptrStack;
}

///Читает дерево из данного файла и возвращает указатель на неё
Node* nodeReadFromFile(FILE* input){

    Stack* ptrStack = readToArrayFromFile(input);
    Node* node;

    if(*(char*)stack_r(ptrStack, 0) == '{')
        node = nodeReadFromStack(ptrStack, 0);
    else
        node = NULL;

    return node;
}

///Печатает сообщение из данной вершины дерева
void nodePrintMessage(Node* ptrNode){

    if(ptrNode == NULL){
        printf("nodePrintMessage: error NULL ptrNode\n");
        return;
    }

    for(int i = 0; stack_r_ch(ptrNode->messageStack, i) != '\0'; i++)
        printf("%c", stack_r_ch(ptrNode->messageStack, i));
}