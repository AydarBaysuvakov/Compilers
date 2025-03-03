#include <stdio.h>
#include "../include/syntax.h"

int main(int argc, char * argv[]) {
    syntax_analyzer_t * sa;
    if (argc < 2) {
        sa = syntax_analyzerCtor(LR0);
    }
    else {
        switch (argv[1][0])
        {
        case '0':
            sa = syntax_analyzerCtor(LR0);
            break;
        case '1':
            sa = syntax_analyzerCtor(LR1);
            break;
        
        default:
            sa = syntax_analyzerCtor(NONE);
            break;
        }
    }
    syntax_analysis(sa);
    syntax_analyzerDtor(sa);
}