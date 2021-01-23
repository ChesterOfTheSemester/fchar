/* fchar 0.1
 * https://github.com/ChesterOfTheSemester/fchar
 *
 * Written by : Chester Abrahams
 * Portfolio  : https://atomiccoder.com
 * LinkedIn   : https://www.linkedin.com/in/atomiccoder/ */

#ifndef FCHAR_H
#define FCHAR_H

#include <stdio.h>
#include <stdarg.h>

#define totalDigits(n) (int) floor(log10(abs(n)))+1

char *fchar(char *format, ...)
{
  va_list arg_list; long arg;
  va_start(arg_list, format);

  size_t bsize;
  char *buffer = (char*) malloc(bsize=(sizeof(char)*0xFFF)), *src=buffer;

  loop:
  {
    /* Resize Buffer */
    resize: if ((size_t) (src-buffer) >= bsize)
    {
      int offset = src-buffer;
      buffer = (char*) realloc(buffer, bsize+=(sizeof(char)*0xFF));
      src = buffer + offset;
    }

    if (*(format) == 0x25)
    {
      *src = 0;
      format++;

      switch (*format)
      {
        /* d/i/u/o: (un)signed integer */
        case 0x64: case 0x69:
          *src=0x69;
        break;

        /* x/X: Hexadecimal integer */
        /* f/F: Float */
        /* e/E: Scientific notation */
        /* g/G: e or f depending on unit size */
        /* a/A: Hexadecimal float */
        /* s/c: Character(s) */
        /* p: Pointer address */

        /* % */
        case 0x25:
          *src=0x25;
        break;

        /* n: None */
        default:
          *src = *format;
        break;
      }
    }

    if (!*src) *src = *format;

    brk:
    if (!*(++format)) goto rtn;
    if (!*(++src)) goto resize;
  }

  if (*format) goto loop;

  rtn: return (char*) buffer;
}

#undef dig
#endif

/**
  va_list arg_list; long arg;
  va_start(args, format);

  arg = va_arg(arg_list, long);
  arg = va_arg(arg_list, long);

  printf("test: %d\n", arg);
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv)
{
    printf("result: %s", fchar("Names %i", "chester"));
    return 0;
}
