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
  size_t bsize;
  char *buffer = (char*) malloc(bsize=sizeof(char)*0xFF), *src=buffer;

  va_list arg_list; long arg;
  va_start(arg_list, format);

  loop:

  {
    if (*(format) == 0x25 && format++)
    {
      *src = 0;

      switch (*(format))
      {
        /* % */
        case 0x25:
          format++;
          *src=0x25;
        break;

        /* d or i */
        case 0x64: case 0x69:
          format++;
          *src=0x69;
          //goto brk;
        break;

        /* None */
        default:
          *src = *format;
        break;
      }
    }

    if (*(format)) *src = *format;

    brk:
    if (!*(++format)) goto rtn;
    if (!*(++src)) goto resize;
  }

  /* Resize Buffer */
  resize: if ((size_t) (src-buffer) >= bsize)
  {
    int offset = src-buffer;
    buffer = (char*) realloc(buffer, bsize += sizeof(char) * 0xFF);
    src = buffer + offset;
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
