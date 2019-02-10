#ifndef SANSKRIT_BUF_H
#define SANSKRIT_BUF_H

#include <stddef.h>

#if defined (__GNUC__) && __GNUC__ >= 3
#  define SANSKRIT_BUF_ATTRIBUTE_NORETURN __attribute__ ((__noreturn__))
#  define SANSKRIT_BUF_ATTRIBUTE_PURE __attribute__ ((__pure__))
#  define SANSKRIT_BUF_ATTRIBUTE_DEPRECATED __attribute__ ((__deprecated__))
#  define SANSKRIT_BUF_BUILTIN_EXPECT(exp, c) __builtin_expect ((exp), (c))
#else
#  if ! defined (SANSKRIT_BUF_ATTRIBUTE_NORETURN)
#    define SANSKRIT_BUF_ATTRIBUTE_NORETURN /* empty */
#  endif
#  define SANSKRIT_BUF_ATTRIBUTE_PURE /* empty */
#  define SANSKRIT_BUF_ATTRIBUTE_DEPRECATED /* empty */
#  define SANSKRIT_BUF_BUILTIN_EXPECT(exp, c) (exp)
#endif

/**
 * @brief Resizable character buffer.
 *
 */
typedef struct skt_buffer
{
    /*! Allocated size of buffer. */
    size_t size;
    /*! Position for reading and writing. */
    size_t pos;
    /*! Pointer to buffer. */
    char * buf;
} skt_buffer_t;


/**
 * @brief Constructor.
 *
 * @param buf  buffer variable
 * @param size  initial size
 */
void initialize_buffer(skt_buffer_t * buf, size_t size);

/**
 * @brief Return size of buffer.
 *
 * @param buf  buffer
 * @return size
 */
size_t buffer_get_size(skt_buffer_t const * buf) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Pointer to start of buffer.
 *
 * @param buf  buffer
 * @return char*  pointer to start of buffer
 */
char * buffer_begin(skt_buffer_t const * buf) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Pointer to one after last character of buffer. Think C++'s `std::end(buf)`.
 * Basically `buffer_begin(buf) + buffer_get_size(buf)`.
 *
 * @param buf buffer
 * @return char*  pointer to one after last character of buffer
 */
char * buffer_end(skt_buffer_t const * buf) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Pointer to buffer at position.
 *
 * @param buf  buffer
 * @return char*  pointer to buffer at position
 */
char * buffer_at_pos(skt_buffer_t const * buf) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Resize buffer.
 *
 * @param buf buffer
 * @param newsize new size
 */
void buffer_resize(skt_buffer_t * buf, size_t newsize);

/**
 * @brief Lenght of string in buffer.
 *
 * @param buf  buffer
 * @return lenght
 */
size_t buffer_strlen(skt_buffer_t const * buf) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Concatenate a string with the content of the buffer.
 * Does not change position. Reallocates/extends buffer to accommodate `src`.
 *
 * @param buf  buffer
 * @param src   string to contatenate
 */
void buffer_strcat(skt_buffer_t * buf, char const * src);

/**
 * @brief Concatenate at most `n` characters from `src` with the content of the buffer.
 * Does not change position. Reallocates/extends buffer to accommodate `src`.
 *
 * @param buf  buffer
 * @param src  source string
 * @param n  limit
 */
void buffer_strncat(skt_buffer_t * buf, char const * src, size_t n);

/**
 * @brief Concatenate one character. Does not change position.
 * Reallocates/extends buffer to accomodate `ch`.
 *
 * @param buf  buffer
 * @param ch  character
 */
void buffer_chrcat(skt_buffer_t * buf, char ch);

/**
 * @brief Copies `src` into `buf`.
 *
 * @param buf  buffer
 * @param src  source string
 */
void buffer_strcpy(skt_buffer_t * buf, char const * src);

/**
 * @brief Test whehther position is at EOF.
 *
 * @param buf  buffer
 * @return TRUE if position is at EOF, FALSE otherwise
 */
int buffer_at_eof(skt_buffer_t const * buf) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief This function returns position in buffer.
 *
 * @param buf  buffer
 * @return position
 */
size_t buffer_pos(skt_buffer_t const * buf) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Sets position for reading and writing.
 *
 * @param buf  buffer
 * @param p  position
 * @return previous position
 */
size_t buffer_set_pos(skt_buffer_t * buf, size_t p);

/**
 * @brief Advances position in buffer by one character.
 * Equivalent of `buffer_pos_move(buf, 1)`.
 *
 * @param buf  buffer
 * @return size_t  previous position
 */
size_t buffer_pos_advance(skt_buffer_t * buf);

/**
 * @brief Moves position in buffer one step backwards.
 * Equivalent of `buffer_pos_move(buf, -1)`.
 *
 * @param buf  buffer
 * @return size_t  previous position
 */
size_t buffer_pos_retreat(skt_buffer_t * buf);

/**
 * @brief Moves poistion in buffer by `dist` characters in either direction.
 * Positive value of `dist` moves position forward,
 * negative value moves position backwards.
 *
 * @param buf  buffer
 * @param dist  distance
 * @return size_t  previous position
 */
size_t buffer_pos_move(skt_buffer_t * buf, ptrdiff_t dist);

/**
 * @brief Write x into buffer and advance position.
 *
 * @param buf buffer
 * @param x   character to be writtern
 */
void buffer_write(skt_buffer_t * buf, char x);

/**
 * @brief Read character from position and advance.
 *
 * @param buf  buffer
 * @return read character
 */
char buffer_read(skt_buffer_t * buf);

/**
 * @brief Set character at position but do not advance.
 *
 * @param buf  buffer
 * @param x    character to be set
 */
void buffer_poke(skt_buffer_t * buf, char x);

/**
 * @brief Like `buffer_poke()` but at specific position.
 *
 * @param buf  buffer
 * @param pos  possition in buffer
 * @param x  character to be written
 */
void buffer_poke_at(skt_buffer_t * buf, size_t pos, char x);

/**
 * @brief Read character at position but do not advance.
 *
 * @param buf  buffer
 * @return character read at position
 */
char buffer_peek(skt_buffer_t const * buf) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Like `buffer_peek()` but at distance `dist` from position in buffer.
 *
 * @param buf  buffer
 * @param dist  distance
 * @return character at position in distance `dist` from buffer position
 */
char buffer_peek_rel(skt_buffer_t const * buf, ptrdiff_t dist) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Peek at character at position `pos`.
 *
 * @param buf  buffer
 * @param pos  position to peek at
 * @return chararacter at position `pos`
 */
char buffer_peek_at(skt_buffer_t const * buf, size_t pos) SANSKRIT_BUF_ATTRIBUTE_PURE;

/**
 * @brief Advance first and then peek at position.
 *
 * @param buf  buffer
 * @return character
 */
char buffer_advance_and_peek(skt_buffer_t * buf);


#endif // SANSKRIT_BUF_H
