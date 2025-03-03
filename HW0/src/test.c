#include "../include/test.h"
#include "../include/lex.yy.h"

extern FILE *yyin, *yyout;

int main(int argc, char * argv[]) {
    char filename[50];

    if (argc != 1) {
        for (int i = 1; i < argc; ++i) {
            sprintf(filename, "tests/test%s", argv[i]);
            test(filename);
        }
        return 0;
    }

    for (int i = 1; i < TEST_COUNT + 1; ++i) {
        sprintf(filename, "tests/test%d", i);
        test(filename);
    }
}

int test(const char * filename) {
    FILE * fd = fopen(filename, "r");
    if (!fd) {
        perror("Не удалось открыть файл\n");
        return 0;
    }
    printf("%s\n", filename);
    printContest(fd);
    fseek(fd, 0, SEEK_SET);
    yyin = fd;
    syntax_analyzer_t * sa = syntax_analyzerCtor(LR0);
    syntax_analysis(sa);
    syntax_analyzerDtor(sa);
    fclose(fd);
}

void printContest(FILE * fd) {
    int ch = getc(fd);
    while (ch != '$') {
        putchar(ch);
        ch = getc(fd);
    }
    putchar('\n');
}