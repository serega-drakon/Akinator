#include <stdio.h>
#include "DynamicArray/DynamicArray.h"
#include "Node/Node.h"
#include "Game_Akinator/Akinator.h"

struct Args_{
    char customFilePathFlag;
    char* customFilePath;
    char saveToFile;
};

typedef struct Args_ Args;

Args getArguments(int argc, char** args){

}

int main(int argc, char** args) {

    Args mainArg = getArguments(argc, args);



    Node *ptrNode = NULL;

    FILE* inputFile;
    inputFile = fopen("../text.txt", "r");

    if(inputFile != NULL)
        ptrNode = nodeReadFromFile(inputFile);

    if(ptrNode != NULL)
        gameStart(ptrNode);

    nodeDestruct(ptrNode);
    return 0;
}
