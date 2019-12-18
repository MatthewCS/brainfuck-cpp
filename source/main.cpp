#include "Brainfuck.h"


int main(int argc, char** argv)
{
    char * filepath;
    if(argc == 2)
        filepath = argv[1];
    else
        return 1;

    Brainfuck bf(filepath);
    bf.run();

    return 0;
}
