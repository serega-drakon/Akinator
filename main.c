#include <stdio.h>
#include "DynamicArray/DynamicArray.h"
#include "Node/Node.h"
#include "Game_Akinator/Akinator.h"
#include "CommandLineTools/CmdLineTools.h"

int main(int argc, char** args) {

    Args mainArg = getArgs(argc, args);

    Node *ptrNode = NULL;

    FILE* inputFile;
    if(mainArg.customFilePathFlag)
        inputFile = fopen(mainArg.customFilePath, "r");
    else
        inputFile = fopen("../text.txt", "r");

    if(inputFile != NULL)
        ptrNode = nodeReadFromFile(inputFile);

    if(ptrNode != NULL)
        gameStart(ptrNode);

    nodeDestruct(ptrNode);
    return 0;
}
