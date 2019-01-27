#ifndef SANSKRIT_BUF_H
#define SANSKRIT_BUF_H

#include <stddef.h>


/**
 * @brief Resizable character buffer.
 * 
 */
typedef struct skt_buffer
{
    size_t size;
    char * buf;
} skt_buffer_t;


void initialize_buffer(skt_buffer_t * buf, size_t size);
size_t buffer_get_size(skt_buffer_t * buf);
char * buffer_begin(skt_buffer_t * buf);
char * buffer_end(skt_buffer_t * buf);
void buffer_resize(skt_buffer_t * buf, size_t newsize);


#endif // SANSKRIT_BUF_H
