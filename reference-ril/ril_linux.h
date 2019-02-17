#ifndef RIL_LINUX_H_
#define RIL_LINUX_H_

#include <stdio.h>
#include <stdint.h>

#define __unused __attribute__((unused))

#define PROP_VALUE_MAX  92
#define PROP_NAME_MAX   32

const char *resultToString(int result);
const char *requestToString(int request);
uint64_t ril_nano_time();
int property_get(const char *key, char *value, const char *default_value);
int __system_property_get(const char *key, char *value);

#endif /* RIL_LINUX_H_ */
