#include "buf.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

void
initialize_buffer(skt_buffer_t * buf, size_t size)
{
    buf->buf = (char *)malloc(size);
    if (buf->buf == NULL)
    {
        perror("Failed to allocate buffer");
        exit(EXIT_FAILURE);
    }
    buf->size = size;
    memset(buf->buf, 0, buf->size);
}


size_t
buffer_get_size(skt_buffer_t * buf)
{
    return buf->size;
}


char *
buffer_begin(skt_buffer_t * buf)
{
    return buf->buf;
}


char *
buffer_end(skt_buffer_t * buf)
{
    return buf->buf + buf->size;
}


void
buffer_resize(skt_buffer_t * buf, size_t newsize)
{
    if (buf->buf == NULL)
        return;

    char * newbuf = (char *)realloc(buf->buf, newsize);
    if (newbuf == NULL)
    {
        perror("Failed to re-allocate buffer");
        exit(EXIT_FAILURE);
    }
    buf->buf = newbuf;
    
    if (newsize > buf->size)
        memset(buf->buf + buf->size, 0, newsize - buf->size);
    
    buf->size = newsize;
}
