/*
 *  memutils.h
 */
#ifndef MEMUTILS_H
  #define MEMUTILS_H

#define memalloc(pointer, size) memoryalloc( (void **)pointer, size, __func__)

void memoryalloc( void ** p_ptr, size_t p_size, const char * const p_func );

#endif
