/* fchar 0.1
 * https://github.com/ChesterOfTheSemester/fchar
 *
 * Written by : Chester Abrahams
 * Portfolio  : https://atomiccoder.com
 * LinkedIn   : https://www.linkedin.com/in/atomiccoder/ */

#ifndef FCHAR_H
#define FCHAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char *fchar(char *format, ...)
{
  va_list arg_list; long arg;
  va_start(arg_list, format);

  size_t bsize;
  char *buffer = (char*) malloc(bsize=0xFFF), *src=buffer;

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
      *src=0; format++;

      switch (*format)
      {
        /* d/i/u/o: (un)signed integer */
        case 0x64: case 0x69: case 0x75: case 0x6F:
        {
          long long num = 123456789123456789; /* Todo: Point to varying */
          /* Todo: Add specifier limitations */

          int i=0, neg=0, rem, start=0, end;
          char *rtn = malloc(sizeof(char)*0xFF), *tmp;

          /* Pre-determine if number is negative */
          if (num<0) { neg = 1; num = -num; }

          /* Generate individual base 10 digits */
          while (num)
          {
            rem = num % 10;
            rtn[i++] = (rem>9) ? (rem-10)+'a' : rem+'0';
            num /= 10;
          }

          /* Add dash at the beginning if num is negative */
          if (neg) rtn[i++] = '-';

          /* End of integer */
          rtn[i] = '\0';

          /* Reverse result before return */
          end=i-1; while (start<end)
          {
            /* Swap reverse */
            tmp = *(rtn+start);
            *(rtn+start) = *(rtn+end);
            *(rtn+end) = tmp;

            start++;
            end--;
          }

          while (*rtn) *(src++) = *(rtn++);
        }
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

      format++;
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
