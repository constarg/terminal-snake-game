#ifndef TERMINAL_SNAKE_GAME_MEM_H
#define TERMINAL_SNAKE_GAME_MEM_H 1

#include <malloc.h>

#define ALLOCATE_MEM(VAR, SIZE, SIZE_OF_TYPE) do {  \
        (VAR) = calloc( (SIZE), (SIZE_OF_TYPE ));   \
        if ( (VAR) == NULL) {                       \
            exit(1);                                \
        }                                           \
    } while(0)

#define REALLOCATE_MEM(VAR, NEW_SIZE) do {          \
        (VAR) = realloc( (VAR), (NEW_SIZE) );       \
        if ( (VAR) == NULL) {                       \
            exit(1);                                \
        }                                           \
    } while(0)





#endif
