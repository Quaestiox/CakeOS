#include "lock.h"
#include "thread.h"
#include "print.h" 

extern u32 atomic_exchange(volatile u32* dst, u32 src);

void lock_init(lock_t *lk){
	lk->hold = UNLOCKED;
}

void lock(lock_t *lk){
	while (atomic_exchange(&lk->hold , LOCKED) != UNLOCKED) {
		schedule();
	}
}


void unlock(lock_t *lk){
	lk->hold = UNLOCKED;
}


