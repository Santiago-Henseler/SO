#ifndef STDARG_H
#define STDARG_H

// Definicion para poder aceptar parametros variables
// Son directivas al ensamblador

typedef __builtin_va_list va_list;

#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)

#endif