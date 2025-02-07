#ifndef LOCK_H
#define LOCK_H

#include "type.h"

#define LOCKED 1
#define UNLOCKED 0

typedef struct lock{
	volatile u32 hold;
}lock_t;

void lock_init(lock_t *lk);
void lock(lock_t *lk);
void unlock(lock_t *lk);

#endif
