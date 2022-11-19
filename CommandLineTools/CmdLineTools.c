#include <printf.h>
#include "CmdLineTools.h"

char strCompare(const char a[], const char b[]){
    int i;
    for(i = 0; a[i] == b[i] && a[i] != '\0' && b[i] != '\0'; i++)
        ;
    if(a[i] == '\0' && b[i] == '\0')
        return 1;
    else
        return 0;
}

Args getArgs(int argc, char** args){
    Args arguments;
    arguments.customFilePath = NULL;
    arguments.customFilePathFlag = 0;
    arguments.saveToFileFlag = 0;
    for(int i = 0; i < argc; i++){
        if(strCompare(args[i], "-file_path")) {
            arguments.customFilePathFlag = 1;
            if(++i < argc) {
                arguments.customFilePath = args[i];
            }
            else{
                printf("getArgs: error file path does not exist\n");
                return arguments;
            }
        }
        else if(strCompare(args[i], "-save")){
            //FIXME
        }
    }
}

