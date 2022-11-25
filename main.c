#include <stdio.h>
#include "DynamicArray/DynamicArray.h"
#include "Node/Node.h"
#include "Game_Akinator/Akinator.h"
#include "CommandLineTools/CmdLineTools.h"

int main(int argc, char** args) {

    Args mainArg = getArgs(argc, args);

    Node *ptrNode = NULL;

    FILE* inputFile;
    if(mainArg.customFilePathFlag) {
        inputFile = fopen(mainArg.customFilePath, "r");
        if(inputFile == NULL) {
            printf("This file does not exist: %s\n Opening the default file \"text.txt\"...", mainArg.customFilePath);
            inputFile = fopen("../text.txt", "r");
        }
    }
    else
        inputFile = fopen("../text.txt", "r");

    if(inputFile != NULL)
        ptrNode = nodeReadFromFile(inputFile);
    else
        printf("Error reading file\n");

    if(ptrNode != NULL){
        if(mainArg.saveToFileFlag == 1){
            FILE* outputFile = fopen("../output.txt", "w");
            nodeSaveToFile(outputFile, ptrNode);
            fclose(outputFile);
        }
        gameStart(ptrNode);
    }
    else
        printf("Node error, cannot run the game...\n");

    nodeDestruct(ptrNode);
    return 0;
}
