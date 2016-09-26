/* X3F_PRINTF.C
 *
 * Library for printout, depending on seriousity level.
 *
 * Copyright 2015 - Roland and Erik Karlsson
 * BSD-style - see doc/copyright.txt
 *
 */

#include "x3f_printf.h"

#include <stdio.h>
#include <stdarg.h>

//x3f_verbosity_t x3f_printf_level = INFO;
x3f_verbosity_t x3f_printf_level = DEBUG; //crw

extern void x3f_printf(x3f_verbosity_t level, const char *fmt, ...)
{
  va_list ap;

  if (level > x3f_printf_level) return;

  va_start(ap, fmt);
  vfprintf(level > WARN ? stdout : stderr, fmt, ap);
  va_end(ap);
}
