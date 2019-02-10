#include "buf.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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
    buf->pos = 0;
}

static inline
void assert_buffer_initialized(skt_buffer_t const * buf)
{
    assert(buf != NULL);
    assert(buf->buf != NULL);
}

size_t
buffer_get_size(skt_buffer_t const * buf)
{
    assert_buffer_initialized(buf);

    return buf->size;
}


char *
buffer_begin(skt_buffer_t const * buf)
{
    assert_buffer_initialized(buf);

    return buf->buf;
}


char *
buffer_end(skt_buffer_t const * buf)
{
    assert_buffer_initialized(buf);

    return buf->buf + buf->size;
}


char *
buffer_at_pos(skt_buffer_t const * buf)
{
    assert_buffer_initialized(buf);
    assert(buf->pos <= buf->size);

    return &buf->buf[buf->pos];
}


void
buffer_resize(skt_buffer_t * buf, size_t newsize)
{
    assert_buffer_initialized(buf);

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


size_t
buffer_strlen(skt_buffer_t const * buf)
{
    assert_buffer_initialized(buf);

    return strlen(buf->buf);
}


void
buffer_strcat(skt_buffer_t * buf, char const * src)
{
    assert_buffer_initialized(buf);

    size_t src_len = strlen(src);
    size_t buf_len = strlen(buf->buf);
    size_t total_size = src_len + buf_len + 1;
    if (buf->size < total_size)
    {
        buffer_resize(buf, total_size + total_size / 2);
    }

    strcat(buf->buf + buf_len, src);
}


void
buffer_strncat(skt_buffer_t * buf, char const * src, size_t n)
{
    assert_buffer_initialized(buf);

    size_t buf_len = strlen(buf->buf);
    size_t total_size = n + buf_len + 1;
    if (buf->size < total_size)
    {
        buffer_resize(buf, total_size + total_size / 2);
    }

    strncat(buf->buf + buf_len, src, n);
}


void
buffer_chrcat(skt_buffer_t * buf, char ch)
{
    assert_buffer_initialized(buf);

    size_t buf_len = strlen(buf->buf);
    size_t total_size = buf_len + 1 + 1;
    if (buf->size < buf_len + 1)
    {
        buffer_resize(buf, total_size);
    }

    buf->buf[buf_len] = ch;
    buf->buf[buf_len + 1] = 0;
}


void
buffer_strcpy(skt_buffer_t * buf, char const * src)
{
    assert_buffer_initialized(buf);

    size_t const len = strlen(src);
    if (len + 1 >= buf->size)
    {
        buffer_resize(buf, len + 1);
    }

    strcpy(buf->buf, src);
}


int
buffer_at_eof(skt_buffer_t const * buf)
{
    assert_buffer_initialized(buf);
    assert(buf->pos <= buf->size);

    return buf->pos == buf->size;
}

size_t
buffer_pos(skt_buffer_t const * buf)
{
    assert_buffer_initialized(buf);

    return buf->pos;
}

size_t
buffer_set_pos(skt_buffer_t * buf, size_t p)
{
    assert_buffer_initialized(buf);
    assert(p <= buf->size);

    size_t const old_pos = buf->pos;
    buf->pos = p;
    return old_pos;
}

size_t
buffer_pos_advance(skt_buffer_t * buf)
{
    return buffer_pos_move(buf, 1);
}

size_t
buffer_pos_retreat(skt_buffer_t * buf)
{
    return buffer_pos_move(buf, -1);
}

size_t
buffer_pos_move(skt_buffer_t * buf, ptrdiff_t dist)
{
    return buffer_set_pos(buf, (size_t)((ptrdiff_t)buffer_pos(buf) + dist));
}

void
buffer_write(skt_buffer_t * buf, char x)
{
    assert_buffer_initialized(buf);
    assert(buf->pos <= buf->size);

    if (buf->pos == buf->size)
    {
        buffer_resize(buf, buf->size + buf->size / 2 + 1);
    }

    buf->buf[buf->pos++] = x;
}

char
buffer_read(skt_buffer_t * buf)
{
    assert_buffer_initialized(buf);
    assert(buf->pos < buf->size);

    return buf->buf[buf->pos++];
}

void
buffer_poke(skt_buffer_t * buf, char ch)
{
    assert_buffer_initialized(buf);
    assert(buf->pos < buf->size);

    buf->buf[buf->pos] = ch;
}

void
buffer_poke_at(skt_buffer_t * buf, size_t pos, char ch)
{
    assert_buffer_initialized(buf);
    assert(pos < buf->size);

    buf->buf[pos] = ch;
}

char
buffer_peek(skt_buffer_t const * buf)
{
    assert_buffer_initialized(buf);
    assert(buf->pos < buf->size);

    return buf->buf[buf->pos];
}

char
buffer_peek_rel(skt_buffer_t const * buf, ptrdiff_t dist)
{
    assert_buffer_initialized(buf);
    assert(buf->pos <= buf->size);
    size_t const peek_pos = (size_t)((ptrdiff_t)buf->pos + dist);
    assert(peek_pos < buf->size);

    return buf->buf[peek_pos];
}


char
buffer_peek_at(skt_buffer_t const * buf, size_t pos)
{
    assert_buffer_initialized(buf);
    assert(pos < buf->size);

    return buf->buf[pos];
}


char
buffer_advance_and_peek(skt_buffer_t * buf)
{
    buffer_pos_advance(buf);
    return buffer_peek(buf);
}
