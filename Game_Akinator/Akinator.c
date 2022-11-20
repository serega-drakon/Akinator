#include "Akinator.h"
#include <stdio.h>
#include <assert.h>

Node* treatQuestion(Node* currPtrNode){
    assert(currPtrNode != NULL);

    int c;
    do {
        //printf("Ваш персонаж ");
        nodePrintMessage(currPtrNode);
        printf(" [Y,y/N,n]\n");
        while((c = getchar()) == '\n')
                ;
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

Node* nameQuestion(Node* currPtrNode){
    assert(currPtrNode != NULL);

    int c;
    do {
        printf("Имя вашего персонажа - ");
        nodePrintMessage(currPtrNode);
        printf("? [Y,y/N,n]\n");
        while((c = getchar()) == '\n')
            ;
        if (c == 'Y' || c == 'y') {
            printf("Я отгадал!\n");
            return NULL;
        }
        else if (c == 'N' || c == 'n') {
            printf("Я прошмандовка азербайджанская...\n");
            return NULL;
        }

    }while(1);
}

char continueQuestion(void){

    int c;
    do {
        printf("Хотите заново? [Y,y/N,n]\n");
        while((c = getchar()) == '\n')
            ;
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
    char continueFlag = 1;

    while(continueFlag){

        currPtrNode = ptrNode;

        while(currPtrNode != NULL) {
            if (currPtrNode != NULL &&
                (currPtrNode->leftSubTree != NULL ||
                currPtrNode->rightSubTree != NULL)) { //не дошли до конца
                currPtrNode = treatQuestion(currPtrNode);

                if(currPtrNode == NULL)
                    printf("Такого персонажа я не знаю...\n");
            }
            else if (currPtrNode != NULL) //дошли до конца
                currPtrNode = nameQuestion(currPtrNode);
        }
        continueFlag = continueQuestion();
    }
    return 0;
}