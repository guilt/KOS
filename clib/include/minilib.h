#ifndef MINILIB_H
#define MINILIB_H

void itoa(char *buf, int base, int d);
void *memcpy(void *dest, void *src, unsigned int size); /* same as memmove */
void *memset(void *dest, int ch, unsigned int size);
void cls();
void printf(const char *format, ...);

void putchar(int c);
int getchar();

#ifdef VERBOSE
#define muted_printf printf
#else
#define muted_printf
#endif /* VERBOSE */

#endif /* MINILIB_H */
