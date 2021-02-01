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
  va_list arg_list;
  va_start(arg_list, format);

  size_t bsize;
  char *buffer = (char*) malloc(bsize=0xFFF), *src=buffer,
       hx[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'},
       hX[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

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
          int num = va_arg(arg_list, int); /* Todo: support long long (lld) */
          int i=0, neg=0, rem, start=0, end, base=*format==0x6F?8:10;
          char *rtn = malloc(sizeof(char)*0xFF), *tmp;

          /* Pre-determine if number is negative */
          if (num<0) { neg = *format<0x6A?1:0; num = -num; }

          /* Generate individual base 10/8 digits */
          while (num)
          {
            rem = num % base;
            rtn[i++] = rem>9 ? (rem-base)+'a' : rem+'0';
            num /= base;
          }

          /* Add dash at the beginning if num is negative */
          if (neg) rtn[i++] = '-'; rtn[i] = '\0'; /* End of number */

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
        case 0x78: case 0x58:
        {
          char *rtn = malloc(sizeof(char)*0xFF);
          unsigned int i, start=0, end, rem, tmp,
                       num = va_arg(arg_list, unsigned int);

          /* Generate individual base 16 hexadecimal digits */
          while(num)
          {
            rtn[i++] = *format==0x78 ? hx[num % 16] : hX[num % 16];
            num /= 16;
          }

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

        /* f/F: Float */
        /* e/E: Scientific notation */
        /* g/G: e or f depending on unit size */
        /* a/A: Hexadecimal float */

        /* s/c: Character(s) */
        case 0x63: case 0x73:
        {
          char *chr = va_arg(arg_list, char*);

          while(*chr)
          {
            *(src++) = *(chr++);
            if (*format==0x63) break;
          }
        }
        break;

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

#endif

/**
  va_list arg_list; long arg;
  va_start(args, format);

  arg = va_arg(arg_list, long);
  arg = va_arg(arg_list, long);

  printf("test: %d\n", arg);
*/
