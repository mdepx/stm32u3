#include <sys/mutex.h>
#include <sys/sem.h>
#include <sys/spinlock.h>

typedef mdx_mutex_t osal_mutex_def_t;
typedef mdx_mutex_t *osal_mutex_t;

#if 0
typedef mdx_sem_t osal_semaphore_def_t;
typedef mdx_sem_t *osal_semaphore_t;
#endif

typedef struct spinlock osal_spinlock_t;
#define OSAL_SPINLOCK_DEF(_name, _int_set) osal_spinlock_t _name

typedef struct {
	uint16_t depth;
	uint16_t item_sz;
	void *buf;
	char const *name;
} osal_queue_def_t;
typedef osal_queue_def_t *osal_queue_t;

/* Mutexes. */

TU_ATTR_ALWAYS_INLINE static inline osal_mutex_t
osal_mutex_create(osal_mutex_def_t *mdef)
{

	return (NULL);
}

TU_ATTR_ALWAYS_INLINE static inline bool
osal_mutex_lock(osal_mutex_t mutex_hdl, uint32_t msec)
{

	return (true);
}

TU_ATTR_ALWAYS_INLINE static inline bool
osal_mutex_unlock(osal_mutex_t mutex_hdl)
{

	return (true);
}


TU_ATTR_ALWAYS_INLINE static inline bool
osal_mutex_delete(osal_mutex_t mutex_hdl)
{

	return (true);
}

/* Semaphores. */

#if 0
TU_ATTR_ALWAYS_INLINE static inline bool
osal_semaphore_delete(osal_semaphore_t semd_hdl)
{

	return (true);
}
#endif

/* Spinlock. */

TU_ATTR_ALWAYS_INLINE static inline void
osal_spin_init(osal_spinlock_t *ctx)
{

}

TU_ATTR_ALWAYS_INLINE static inline void
osal_spin_lock(osal_spinlock_t *ctx, bool in_isr)
{

}

TU_ATTR_ALWAYS_INLINE static inline void
osal_spin_unlock(osal_spinlock_t *ctx, bool in_isr)
{

}

/* Queues. */

#define OSAL_Q_NAME(_name) .name = #_name
/* _int_set is not in use */
#define OSAL_QUEUE_DEF(_int_set, _name, _depth, _type)		\
	static _type _name##_##buf[_depth];			\
	osal_queue_def_t _name = { .depth = _depth,		\
				   .item_sz = sizeof(_type),	\
				   .buf = _name##_##buf,	\
				    OSAL_Q_NAME(_name) }

TU_ATTR_ALWAYS_INLINE static inline osal_queue_t
osal_queue_create(osal_queue_def_t* qdef)
{
	osal_queue_t q;

	q = NULL;

	return (q);
}

TU_ATTR_ALWAYS_INLINE static inline bool
osal_queue_delete(osal_queue_t qhdl)
{

	return (true);
}

TU_ATTR_ALWAYS_INLINE static inline bool
osal_queue_send(osal_queue_t qhdl, void const *data, bool in_isr)
{

	return (true);
}

TU_ATTR_ALWAYS_INLINE static inline bool
osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec)
{

	return (true);
}

TU_ATTR_ALWAYS_INLINE static inline bool
osal_queue_empty(osal_queue_t qhdl)
{

	return (0);
}

/* Misc. */

TU_ATTR_ALWAYS_INLINE static inline void
osal_task_delay(uint32_t msec)
{

}
