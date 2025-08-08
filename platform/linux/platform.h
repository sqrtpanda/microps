#ifndef PLATFORM_H
#define PLATFORM_H

#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define INTR_IRQ_BASE (SIGRTMIN + 1)
#define INTR_IRQ_SHARED 0x0001

#define INTR_IRQ_SOFTIRQ SIGUSR1
#define INTR_IRQ_EVENT SIGUSR2

/*
 * Memory
 */

static inline void *
memory_alloc(size_t size)
{
    return calloc(1, size);
}

static inline void
memory_free(void *ptr)
{
    free(ptr);
}

/*
 * Mutex
 */

typedef pthread_mutex_t mutex_t;

#define MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

/*
 * Scheduler
 */

struct sched_ctx {
    pthread_cond_t cond;
    int interrupted;
    int wc; /* wait count */
};

#define SCHED_CTX_INITIALIZER {PTHREAD_COND_INITIALIZER, 0, 0}

int sched_ctx_init(struct sched_ctx *ctx);
int sched_ctx_destroy(struct sched_ctx *ctx);
int sched_sleep(struct sched_ctx *ctx, mutex_t *mutex, const struct timespec *abstime);
int sched_wakeup(struct sched_ctx *ctx);
int sched_interrupt(struct sched_ctx *ctx);

static inline int mutex_init(mutex_t *mutex)
{
    return pthread_mutex_init(mutex, NULL);
}

static inline int mutex_lock(mutex_t *mutex)
{
    return pthread_mutex_lock(mutex);
}

static inline int mutex_unlock(mutex_t *mutex)
{
    return pthread_mutex_unlock(mutex);
}

int intr_init(void);
int intr_request_irq(unsigned int irq, int (*handler)(unsigned int irq, void *dev), int flags, const char *name, void *dev);
int intr_run(void);
void intr_shutdown(void);
int intr_raise_irq(unsigned int irq);

#endif
