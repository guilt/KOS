/* x86minilib.c - x86 specific portion of mini C library */
#include <types.h>
#include <mem.h>
#include <minilib.h>

/* The video memory address.  */
#define VIDEO 0x000b8000
#define ATTRIBUTE 7
#define LINES 25
#define COLUMNS 80

/* Video Memory */
volatile paddr video=VIDEO;

static int xpos, ypos;

static void clearline(int row) {
  char *line=(char *)video;
  int i;
  line += row * COLUMNS * 2;
  for (i = 0; i < COLUMNS * 2; i+=2) {
    *(line + i) = 0;
    *(line + i + 1) = ATTRIBUTE;
  }
}

void cls() {
  int i;
  for (i = 0; i < LINES; i++) {
      clearline(i);
  }
  xpos = 0;
  ypos = 0;
}

void putchar (int c) {
  char *cvideo=(char *)video;
  if (c == '\r') {
      xpos = 0;
      return;
  }
  if (c == '\n')
    {
    newline:
      xpos = 0;
      ypos++;
      if (ypos == LINES) { /* Scroll one line up. */
	 memcpy(cvideo,cvideo+(COLUMNS*2),((LINES-1)*COLUMNS*2));
	 ypos=LINES-1;
	 clearline(ypos);
      }
      return;
    }
  *(cvideo + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
  *(cvideo + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;
  xpos++;
  if (xpos >= COLUMNS) {
    goto newline;
  }
}
