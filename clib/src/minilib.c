/* minilib.c - mini C library until the new small C library kicks in */
#include <types.h>
#include <mem.h>
#include <minilib.h>

void itoa (char *buf, int base, int d) {
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;
  
  /* If %d is specified and D is minus, put `-' in the head.  */
  if (base == 'd' && d < 0)
    {
      *p++ = '-';
      buf++;
      ud = -d;
    }
  else if (base == 'x')
    divisor = 16;

  /* Divide UD by DIVISOR until UD == 0.  */
  do
    {
      int remainder = ud % divisor;
      
      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
  while (ud /= divisor);

  /* Terminate BUF.  */
  *p = 0;
  
  /* Reverse BUF.  */
  p1 = buf;
  p2 = p - 1;
  while (p1 < p2)
    {
      char tmp = *p1;
      *p1 = *p2;
      *p2 = tmp;
      p1++;
      p2--;
    }
}

void *memset(void *dest, int ch, unsigned int size) {
    char *cdest=(char *)dest;
    char cch=(char)ch;
    while(size--) {
	*cdest=cch;
	cdest++;
    }
}

void *memcpy(void *dest, void *src, unsigned int size) {
    char *cdest=(char *)dest;
    char *csrc=(char *)src;
    if(csrc==cdest||!size) ;
    else {
      if(cdest > csrc && cdest < (csrc+size)) { /* L to R */
	cdest+=size-1;
	csrc+=size-1;
	while(size--) {
	  *cdest=*csrc;
	  cdest--;
	  csrc--;
	}
      } else { /* R to L */
	while(size--) {
         *cdest=*csrc;
          cdest++;
          csrc++;
	}
      }
    }
    return dest;
}

void printf (const char *format, ...) {
  char **arg = (char **) &format;
  int c;
  char buf[20];

  arg++;
  
  while ((c = *format++) != 0)
    {
      if (c != '%')
	putchar (c);
      else
	{
	  char *p;
	  
	  c = *format++;
	  switch (c)
	    {
	    case 'd':
	    case 'u':
	    case 'x':
	      itoa (buf, c, *((int *) arg++));
	      p = buf;
	      goto string;
	      break;

	    case 's':
	      p = *arg++;
	      if (! p)
		p = "(null)";

	    string:
	      while (*p)
		putchar (*p++);
	      break;

	    default:
	      putchar (*((int *) arg++));
	      break;
	    }
	}
    }
}
