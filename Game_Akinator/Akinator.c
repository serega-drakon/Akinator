#include "Akinator.h"
#include <stdio.h>
#include <assert.h>

int getUserInput(void){

    int c;

    c = getchar();
    if(c != '\n')
        while(getchar() != '\n')
            ;
    return c;
}

///Stack размером не менее sizeof(int)!
void getUserInputStack(Stack* ptrStack){

    int c;
    int i;

    for(i = 0; (c = getchar()) != '\n'; i++)
        push(ptrStack, &c);

    c = '\0';
    push(ptrStack, &c);
}

Node* treatQuestion(Node* currPtrNode){
    assert(currPtrNode != NULL);

    int c;
    do {
        printf("Ваш персонаж ");
        nodePrintMessage(currPtrNode);
        printf(" [Y,y/N,n]\n");
        c = getUserInput();
        if (c == 'Y' || c == 'y') {
            if(currPtrNode->leftSubTree != NULL)
                return currPtrNode->leftSubTree;
            else
                return NULL;
        }
        else if (c == 'N' || c == 'n') {
            if(currPtrNode->rightSubTree != NULL)
                return currPtrNode->rightSubTree;
            else
                return NULL;
        }
    }while(1);
}

void newCharacter(Node* previousQuestion, Node* previousCharacter){
    assert(previousQuestion != NULL); //FIXME:доработать
    printf("Я прошмандовка азербайджанская...\n");

    Node* newQuestion = nodeInit();

    printf("Чем ваш персонаж отличается от данного?\n");

    getUserInputStack(newQuestion->messageStack);

    Node* newCharacter = nodeInit();

    printf("Как зовут вашего персонажа?\n");

    getUserInputStack(newCharacter->messageStack);

    int c;

    do{
        printf("Ваш персонаж отвечает этому признаку? [Y,y/N,n]\n");

        c = getUserInput();

        if(c == 'Y' || c == 'y'){
            if(previousQuestion->leftSubTree == previousCharacter)
                previousQuestion->leftSubTree = newQuestion;
            else if(previousQuestion->rightSubTree == previousCharacter)
                previousQuestion->rightSubTree = newQuestion;
            else
                assert(0);
            newQuestion->leftSubTree = newCharacter;
            newQuestion->rightSubTree = previousCharacter;
        }
        else if(c == 'N' || c == 'n'){
            if(previousQuestion->leftSubTree == previousCharacter)
                previousQuestion->leftSubTree = newQuestion;
            else if(previousQuestion->rightSubTree == previousCharacter)
                previousQuestion->rightSubTree = newQuestion;
            else
                assert(0);
            newQuestion->rightSubTree = newCharacter;
            newQuestion->leftSubTree = previousCharacter;
        }

    }while(c != 'Y' && c != 'y' && c != 'N' && c != 'n');
}

Node* nameQuestion(Node* currPtrNode, Node* prevPtrNode){
    assert(currPtrNode != NULL);

    int c;
    do {
        printf("Имя вашего персонажа - ");
        printf("Ваш язык - ");
        nodePrintMessage(currPtrNode);
        printf("? [Y,y/N,n]\n");
        c = getUserInput();
        if (c == 'Y' || c == 'y') {
            printf("Я отгадал!\n");
            return NULL;
        }
        else if (c == 'N' || c == 'n') {
            newCharacter(prevPtrNode, currPtrNode);
            return NULL;
        }

    }while(1);
}

char continueQuestion(void){

    int c;

    do {
        printf("Хотите заново? [Y,y/N,n]\n");
        c = getUserInput();
        if (c == 'Y' || c == 'y') {
            printf("Будет сделано!\n");
            return 1;
        }
        else if (c == 'N' || c == 'n') {
            printf("До встречи!\n");
            return 0;
        }
    }while(1);
}

int gameStart(Node* ptrNode){

    if(ptrNode == NULL) {
        printf("game: error NULL node");
        return 1;
    }

    Node* currPtrNode;
    Node* prevPtrNode = NULL;
    char continueFlag = 1;

    while(continueFlag){

        currPtrNode = ptrNode;

        while(currPtrNode != NULL) {
            if (currPtrNode != NULL &&
                (currPtrNode->leftSubTree != NULL ||
                currPtrNode->rightSubTree != NULL)) { //не дошли до конца

                prevPtrNode = currPtrNode;

                currPtrNode = treatQuestion(currPtrNode);

                if(currPtrNode == NULL) //FIXME
                    printf("Такого персонажа я не знаю...\n");
            }
            else if (currPtrNode != NULL) //дошли до конца
                currPtrNode = nameQuestion(currPtrNode, prevPtrNode);

        }
        continueFlag = continueQuestion();
    }
    return 0;
}