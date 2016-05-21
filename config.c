//
// Created by ruansheng on 16/4/8.
//

#include"config.h"

void loadConfig(const char *filename) {
    char *config;
    char bug[ZOK_CONFIGLINE_MAX + 1];
    if(filename) {
        FILE *fp;
        if(filename[0] == '-' && filename[1] == '\0') {
            fp = __stdinp;
        } else {
            if ((fp = fopen(filename,"r")) == NULL) {
                perror("Fatal error, can't open config file '%s'", filename);
                exit(1);
            }
        }
        while(fgets(buf,REDIS_CONFIGLINE_MAX+1,fp) != NULL) {
            config = stringCat(config, buf);
        }
        if (fp != __stdinp) {
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
    memcpy(newString + sLen, t, lLen);
    return newString;
}

void splitString() {

}