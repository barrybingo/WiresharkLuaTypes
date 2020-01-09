#ifndef __GLIB_TYPES_H__
#define __GLIB_TYPES_H__

#include <stdint.h>

/*
 * Basic data types
 */
typedef int            gint;
typedef unsigned int   guint;
typedef short          gshort;
typedef unsigned short gushort;
typedef long           glong;
typedef unsigned long  gulong;
typedef void *         gpointer;
typedef const void *   gconstpointer;
typedef char           gchar;
typedef unsigned char  guchar;

#if !G_TYPES_DEFINED
/* VS 2010 and later have stdint.h */
#if defined(_MSC_VER) && _MSC_VER < 1600
typedef __int8			gint8;
typedef unsigned __int8		guint8;
typedef __int16			gint16;
typedef unsigned __int16	guint16;
typedef __int32			gint32;
typedef unsigned __int32	guint32;
typedef __int64			gint64;
typedef unsigned __int64	guint64;
typedef float			gfloat;
typedef double			gdouble;
typedef int			gboolean;
#else
/* Types defined in terms of the stdint.h */
typedef int8_t         gint8;
typedef uint8_t        guint8;
typedef int16_t        gint16;
typedef uint16_t       guint16;
typedef int32_t        gint32;
typedef uint32_t       guint32;
typedef int64_t        gint64;
typedef uint64_t       guint64;
typedef float          gfloat;
typedef double         gdouble;
typedef int32_t        gboolean;
#endif
#endif

typedef guint16 gunichar2;
typedef guint32 gunichar;

/*
 * Macros
 */
#define G_N_ELEMENTS(s)      (sizeof(s) / sizeof ((s) [0]))

#define FALSE                0
#define TRUE                 1

#define G_MINSHORT           SHRT_MIN
#define G_MAXSHORT           SHRT_MAX
#define G_MAXUSHORT          USHRT_MAX
#define G_MAXINT             INT_MAX
#define G_MININT             INT_MIN
#define G_MAXINT32           INT32_MAX
#define G_MAXUINT32          UINT32_MAX
#define G_MININT32           INT32_MIN
#define G_MININT64           INT64_MIN
#define G_MAXINT64	     INT64_MAX
#define G_MAXUINT64	     UINT64_MAX

#define G_LITTLE_ENDIAN 1234
#define G_BIG_ENDIAN    4321
#define G_STMT_START    do 
#define G_STMT_END      while (0)

#define G_USEC_PER_SEC  1000000


// glibconfig.h

#ifndef _MSC_VER
G_GNUC_EXTENSION typedef signed long long gint64;
G_GNUC_EXTENSION typedef unsigned long long guint64;
#else /* _MSC_VER */
typedef signed __int64 gint64;
typedef unsigned __int64 guint64;
#endif /* _MSC_VER */

#ifndef _MSC_VER
#define G_GINT64_CONSTANT(val)	(G_GNUC_EXTENSION (val##LL))
#else /* _MSC_VER */
#define G_GINT64_CONSTANT(val)	(val##i64)
#endif /* _MSC_VER */
#ifndef _MSC_VER
#define G_GUINT64_CONSTANT(val)	(G_GNUC_EXTENSION (val##ULL))
#else /* _MSC_VER */
#define G_GUINT64_CONSTANT(val)	(val##Ui64)
#endif /* _MSC_VER */
#define G_GINT64_MODIFIER "I64"
#define G_GINT64_FORMAT "I64i"
#define G_GUINT64_FORMAT "I64u"

// other things
#define g_stpcpy(d,s) stpcpy((d),(s))
#define g_strdup(machin)	osip_strdup(machin)
#define g_strndup(s,n)  strndup((s),(n))
#define g_snprintf  snprintf
#define g_getenv	getenv
#define g_strerror(errnum) strerror(errnum)
#define g_ascii_strtoull  strtoull
#define g_ascii_strtoll  strtoll

#define g_ascii_islower islower
#define g_ascii_isalnum isalnum

#include <ctype.h>
#define g_ascii_isdigit isdigit

#endif