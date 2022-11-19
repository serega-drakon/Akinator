#ifndef NODE_CMDLINETOOLS_H
#define NODE_CMDLINETOOLS_H

struct Args_{
    char customFilePathFlag;
    char* customFilePath;
    char saveToFileFlag;
};

typedef struct Args_ Args;

Args getArgs(int argc, char** args);

#endif //NODE_CMDLINETOOLS_H
