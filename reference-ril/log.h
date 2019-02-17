#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

#define RLOGD(format, ...) fprintf(stdout, format, ## __VA_ARGS__)
#define RLOGW(format, ...) fprintf(stdout, format, ## __VA_ARGS__)
#define RLOGI(format, ...) fprintf(stdout, format, ## __VA_ARGS__)
#define RLOGE(format, ...) fprintf(stderr, format, ## __VA_ARGS__)

#define ALOGE(format, ...) fprintf(stderr, format, ## __VA_ARGS__)

#endif /* LOG_H_ */
