//
// Created by ruansheng on 16/5/21.
//

#include "../log.h"

#define LOG_DEBUG "debug"
#define LOG_INFO "info"
#define LOG_WARNING "warning"
#define LOG_ERROR "error"

int main(int argc, char *argv[]) {
    logger(1, __LINE__, LOG_DEBUG, "params is loss");
    return 0;
}