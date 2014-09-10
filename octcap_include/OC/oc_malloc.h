/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file OC/oc_malloc.h
 *
 * opencall declarations of memory management routines
 *
 * This file first declares opencall replacements for the usual ANSI C memory
 * allocation functions:
 *
 * @li oc_malloc standard memory allocation.  lazy allocation is allowed by
 *               default (like the system malloc).
 *
 * @li oc_calloc memory allocation.  allocated blocks are set to '\0'.  lazy
 *               allocation is forbidden.
 *
 * @li oc_free free memory area allocated by one of the previous functions.
 *
 * system versions of these primitives are provided by the libc.  allocated
 * memory can either be located in the process heap (for small & medium areas)
 * or by mmap'ed pseudo files, in case the required size is large or the
 * process is running low in heap-size.
 *
 * additionally, oc_malloc provides ways to set preferences on memory
 * allocation, muich like the HP-UX mallopt() library call.
 *
 * The current version of the memory allocation package relies on the system
 * functions.  Single difference: oc_malloc falls back on oc_calloc & allocated
 * pages are locked in physical memory (cannot be swapped-out).
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_malloc.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_malloc.h>
 * @endverbatim
 * 
 * this header can be included from both user-space & kernel-space code
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _OC_MALLOC_H
#define _OC_MALLOC_H

#include <OC/oc_config.h>	/* OS/compiler portability */

#if !defined(__KERNEL__) && !defined(_KERNEL)
#include <stdlib.h>		/* malloc, calloc, free */
#include <errno.h>		/* errno, strerror */
#include <string.h>		/* memcpy */

#if defined(_POSIX_MEMLOCK)
#include <sys/mman.h>		/* mlock */
#endif /* _POSIX_MEMLOCK */

#elif defined(__linux__) && defined(__KERNEL__)

#include <linux/slab.h>		/* kmalloc */
/* FIXME : Need this declaration. Ideally, should include <asm/processor.h>
 * to get the extern declaration. But that doesn't seem to work. So
 * explicitly declared here for now. But the header include is a safer
 * way, since it protects us against name changes in future.
 */
extern struct cpuinfo_x86 boot_cpu_data;
#include <linux/vmalloc.h>	/* vmalloc */
#include <linux/string.h>	/* memcpy, ...etc. */

#elif defined(__hpux) && defined(_KERNEL)

#include <malloc.h>		/* the one of "/usr/conf/h" */

#endif

#if !defined(__KERNEL__) && !defined(_KERNEL)

/**
 * @func oc_calloc
 * @brief multiple contiguous memory area allocator
 *
 * @param nmemb  number of memory areas to allocate.
 * @param size   size of eachmemory area to allocate, in bytes.
 *
 * returns a pointer on the begining of the 1rst memory area in case of
 * success.  return NULL in case of error & set errno accordingly.
 * 
 * @see calloc(3)
 * @see mlock(2)
 *
 * additionally, oc_calloc return NULL is the system is unable to lock the
 * associated memory pages in physical memory.
 */
STATIC_INLINE void *
oc_calloc (size_t nmemb, size_t size)
{
	void *area = calloc (nmemb, size);
	if (area != NULL) {
#if defined(_POSIX_MEMLOCK)
		if (mlock (area, size * nmemb) < 0) {
			/*
			 * only root user is allowed to lock pages in memory
			 * (see mlock(2) for details).  in our case, if the
			 * process is not running as root user, the memory
			 * allocation succeeds but the pages are not locked in
			 * physical memory.
			 * Add ENOMEM check to ignore multiple memory lock
			 * (locking twice same address returns ENOMEM on rhel3)
			 */
			if (errno != EPERM && errno != ENOMEM) {
				free (area);
				area = NULL;
			}
		}
#endif /* _POSIX_MEMLOCK */
	}
	return area;
}

/**
 * @func oc_malloc
 * @brief single memory area allocator
 *
 * @param size   size of the memory area to allocate, in bytes.
 *
 * falls-back on a call to oc_calloc(1, size).
 * 
 * @see oc_calloc
 */
STATIC_INLINE void *
oc_malloc (size_t size)
{
	return oc_calloc (1, size);
}

/**
 * @func oc_free
 * @brief free memory area allocated by oc_malloc & oc_calloc
 *
 * @param area    pointer on the first byte of the memory area to free.
 *
 * @note oc_free does not unlock the page in memory, because single a page can
 * still contain a number of non-freed memory area (page size is 4k on i386,
 * 16k on ia64) that still need to be locked in memory.  all the memory will be
 * automatically given back to the system when every area of the current
 * physical memory page will have been freed.
 */
STATIC_INLINE void
oc_free (void *area)
{
	free (area);
}

/**
 * @func oc_mdup
 * @brief duplicate a memory area
 *
 * @param msize   size of the memory area to duplicate
 * @param source  pointer on the source memory area, to be duplicated.
 *
 * allocated area must be freed either by OC_DELETE or oc_free.  allocation
 * attempt is performed by oc_malloc.
 * 
 * @see oc_malloc
 *
 * if allocation of the copy fails, this macro return NULL.
 */

STATIC_INLINE void *
oc_mdup (size_t size, void *msource)
{
	void *mcopy = oc_malloc (size);

	if (mcopy != NULL) {
		memcpy (mcopy, msource, size);
	}
	return mcopy;
}

/**
 * @func OC_NEW
 * @brief macro to allocate a single "object".  much like C++'s new(3)
 *
 * @param type type of the variable
 *
 * allocated area must be freed either by OC_DELETE or oc_free.  allocation
 * attempt is performed by oc_malloc.
 * 
 * @see oc_malloc
 */

#define OC_NEW(type) ((type*)oc_malloc (sizeof (type)))

/**
 * @def OC_NEW_COPY
 * @brief allocate a single "object".  much like C++'s copy constructor
 *
 * @param type    type of the object to copy
 * @param source  pointer on the source memory area, to be copied in the new
 * 	          allocated area.
 *
 * this macro is a pseudo-generic allocation using oc_copy.  allocated area
 * must be freed either by OC_DELETE or oc_free.  allocation attempt is
 * performed by oc_malloc.
 * 
 * @see oc_malloc
 *
 * if allocation of the copy fails, this macro return NULL.
 */

#define OC_NEW_COPY(type, msource) ((type*)oc_mdup(sizeof(type), msource))

/**
 * @func OC_DELETE
 * @brief synonym of oc_free.
 *
 * @param area pointer on the 1st byte of the memory area to delete
 *
 * @see oc_free
 */
#define OC_DELETE(area) oc_free(area)

#else  /* __KERNEL__ || _KERNEL */

/**
 * @defgroup krn-malloc
 * @{
 * @brief kernel memory management
 */

#if defined(__linux__)

/**
 * @def OC_KMALLOC_XXX
 * @brief allocate memory from within kernel context
 *
 * @param ptr will contain the allocated area, or NULL
 * @param cast type of ptr
 * @param size memory to allocate (in bytes)
 * @param type allocation flags (HP-UX only)
 * @param allocation flags (HP-UX only)
 *
 * @li OC_KMALLOC is the default kernel memory allocator.  cannot be used from
 * interrupt-context
 *
 * @li OC_KMALLOC_DMA is the allocator to use for DMA memory area.  cannot be
 * used from interrupt-context
 *
 * @li OC_KMALLOC_IRQH is the allocator to use from interrupt-context
 *
 * @li OC_KMALLOC_LARGE is the allocator to use for large memory area.  cannot
 * be used from interrupt-context.
 */

#define OC_KMALLOC( ptr, cast, size, type, flags ) \
	(ptr) = (cast)kmalloc( (size), GFP_ATOMIC )

#define OC_KMALLOC_DMA( ptr, cast, size, type, flags ) \
	(ptr) = (cast)kmalloc( (size), GFP_ATOMIC|GFP_DMA )

#define OC_KMALLOC_IRQH( ptr, cast, size, type, flags ) \
	(ptr) = (cast)__get_free_pages( GFP_ATOMIC|GFP_DMA, get_order( size ) )

#define OC_KMALLOC_LARGE( ptr, cast, size, type, flags ) \
	(ptr) = (cast)vmalloc( size )

/**
 * @def OC_KFREE_XXX
 * @brief de-allocate memory from within kernel context
 *
 * @param ptr references the area to de-allocate
 * @flags de-allocation flags (HP-UX only)
 * @param size size of the memory to de-allocate (in bytes)
 *
 * @li OC_KFREE is the default kernel memory de-allocator, to be used for
 * memory area allocated by OC_KMALLOC.  cannot be used from interrupt-context
 *
 * @li OC_KFREE_DMA is the default DMA memory de-allocator, to be used for
 * memory area allocated by OC_KMALLOC_DMA. cannot be used from
 * interrupt-context
 *
 * @li OC_KFREE_IRQH is the de-allocator to use from interrupt-context, for
 * memory area allocated by OC_KMALLOC_IRQH.
 *
 * @li OC_KFREE_LARGE is the allocator to use for large memory area, allocated
 * by OC_KMALLOC_LARGE.  cannot be used from interrupt-context.
 */

#define OC_KFREE( ptr, flags, size ) \
	kfree( ptr )

#define OC_KFREE_DMA( ptr, flags, size ) \
	kfree( ptr )

#define OC_KFREE_IRQH( ptr, flags, size ) \
	free_pages( (unsigned long)(ptr), get_order( size ) )

#define OC_KFREE_LARGE( ptr, flags, size ) \
	vfree( ptr )

#elif defined(__hpux)

#define OC_KMALLOC( ptr, cast, size, type, flags ) \
	MALLOC( ptr, cast, size, type, (flags) )

#define OC_KMALLOC_DMA( ptr, cast, size, type, flags ) \
	MALLOC( ptr, cast, size, type, (flags) )

#define OC_KMALLOC_IRQH( ptr, cast, size, type, flags ) \
	MALLOC( ptr, cast, size, type, (flags) )

#define OC_KMALLOC_LARGE( ptr, cast, size, type, flags ) \
	MALLOC( ptr, cast, size, type, (flags) )

#define OC_KFREE( ptr, flags, size ) \
	FREE( ptr, (flags) )

#define OC_KFREE_DMA( ptr, flags, size ) \
	FREE( ptr, (flags) )

#define OC_KFREE_IRQH( ptr, flags, size ) \
	FREE( ptr, (flags) )

#define OC_KFREE_LARGE( ptr, flags, size ) \
	FREE( ptr, (flags) )

#elif defined(_KDEBUG)

#define OC_KMALLOC(a,b,c,d,e)   (a)=(b)malloc(c)
#define OC_KMALLOC_DMA		OC_KMALLOC
#define OC_KMALLOC_IRQH		OC_KMALLOC
#define OC_KMALLOC_LARGE	OC_KMALLOC

#define OC_KFREE(a,b)           free(a)
#define OC_KFREE_DMA		OC_KFREE
#define OC_KFREE_IRQH		OC_KFREE
#define OC_KFREE_LARGE		OC_KFREE

#else

#error "Unsupported OS"

#endif /* __os__ */

#endif /* !__KERNEL__ && !_KERNEL */

#endif /* _OC_MALLOC_H */
