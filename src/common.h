#ifndef COMMON_H
#define COMMON_H

typedef int (*fp_match)(const void *key1, const void *key2);
typedef int (*fp_compare)(const void *key1, const void *key2);
typedef void (*fp_destroy)(void *data);
typedef int (*fp_hash)(const void *key);
typedef void (*fp_dump)(const void *data);

#endif /* COMMON_H */
