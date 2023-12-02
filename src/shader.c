#include <shader.h>
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Shader shaderInit(const char* vertPath, const char* fragPath) {
    char* content = (char*)malloc(128);

    FILE *fp;
    fp = fopen(vertPath, "r");
    char c;
    do {
        c = fgetc(fp);
        int len = strlen(content);
        if (c != EOF) content[len] = c;
    }
    while (c != EOF);

    fclose(fp);
    printf("%s", content);
    free(content);
}
