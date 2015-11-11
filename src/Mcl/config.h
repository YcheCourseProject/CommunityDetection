/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Predefined possible va_copy() implementation (id: ASP) */
#define __VA_COPY_USE_ASP(d, s) do { *(d) = *(s); } while (0)

/* Predefined possible va_copy() implementation (id: ASS) */
#define __VA_COPY_USE_ASS(d, s) do { (d) = (s); } while (0)

/* Predefined possible va_copy() implementation (id: C99) */
#define __VA_COPY_USE_C99(d, s) va_copy((d), (s))

/* Predefined possible va_copy() implementation (id: CPP) */
#define __VA_COPY_USE_CPP(d, s) memcpy((void *)(d), (void *)(s)), sizeof(*(s))

/* Predefined possible va_copy() implementation (id: CPS) */
#define __VA_COPY_USE_CPS(d, s) memcpy((void *)&(d), (void *)&(s)), sizeof((s))

/* Predefined possible va_copy() implementation (id: GCB) */
#define __VA_COPY_USE_GCB(d, s) __builtin_va_copy((d), (s))

/* Predefined possible va_copy() implementation (id: GCH) */
#define __VA_COPY_USE_GCH(d, s) __va_copy((d), (s))

/* Predefined possible va_copy() implementation (id: GCM) */
#define __VA_COPY_USE_GCM(d, s) VA_COPY((d), (s))

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the `floor' function. */
#define HAVE_FLOOR 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define HAVE_MALLOC 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `pow' function. */
#define HAVE_POW 1

/* Define if you have POSIX threads libraries and header files. */
/* #undef HAVE_PTHREAD */

/* Define to 1 if you have the `rint' function. */
#define HAVE_RINT 1

/* Define to 1 if you have the `sqrt' function. */
#define HAVE_SQRT 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if va_copy() macro exists (and no fallback implementation is
   required) */
/* #undef HAVE_VA_COPY */

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* output citation reference (default yes) */
#define MCL_HELPFUL_REMINDER /**/

/* Name of package */
#define PACKAGE "mcl"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "mcl-devel@lists.micans.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "mcl"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "mcl 14-137"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "mcl"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "14-137"

/* Define to the necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "14-137"

/* Optional va_copy() implementation activation */
#ifndef HAVE_VA_COPY
#define va_copy(d, s) __VA_COPY_USE(d, s)
#define HAVE_VA_COPY 1
#endif


/* Define to id of used va_copy() implementation */
#define __VA_COPY_USE __VA_COPY_USE_GCH

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
