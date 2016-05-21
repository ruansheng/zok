//
// Created by ruansheng on 16/4/8.
//

#include"config.h"

void loadConfig(const char *filename) {
    char *config;
    char buf[ZOK_CONFIGLINE_MAX + 1];
    if(filename) {
        FILE *fp;
        if(filename[0] == '-' && filename[1] == '\0') {
            fp = stdin;
        } else {
            if ((fp = fopen(filename, "r")) == NULL) {
                printf("Fatal error, can't open config file '%s'", filename);
                exit(1);
            }
        }
        printf("1---%s \n", buf);
        while(fgets(buf, ZOK_CONFIGLINE_MAX + 1, fp) != NULL) {
            printf("2---%s \n", buf);
            config = stringCat(config, buf);
        }
        if (fp != stdin) {
            fclose(fp);
        }
        printf("%s \n", config);
    }
}

char * stringCat(char *s, char *t) {
    int sLen = strlen(s);
    int lLen = strlen(t);
    char *newString = (char *)malloc(sLen + lLen);
    memcpy(newString, s, sLen);
    printf("%s\n", newString);
    memcpy(newString + sLen, t, lLen);
    printf("%s\n", newString);
    return newString;
}

void splitString() {

}