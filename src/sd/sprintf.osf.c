static const char ident[] = "$Id: sprintf.osf.c,v 1.2 2002/11/21 16:13:10 legoater Exp $";

/* Includes
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#if defined(__osf__)
/******************************************************************************/
extern int snprintf(char* s, size_t maxlen, const char* fmt, ...)
{
    int		len;
    va_list	args;

    va_start(args, fmt);
    len = vsnprintf(s, maxlen, fmt, args);
    va_end(args);

    return len;
}

/******************************************************************************/
extern int vsnprintf(char* s, size_t maxlen, const char* fmt, va_list args)
{
    int  len;
    FILE f;

    if (maxlen == 0)
	return 0;

    memset(&f, 0, sizeof(f));

    f._flag    = _IOWRT + _IOSTRG;

    f._bufsiz  = f._cnt = maxlen - 1;
    f._base    = f._ptr = (unsigned char*) s;
    f._bufendp = f._base + f._bufsiz;

    len = vfprintf(&f, fmt, args);
    *f._ptr = '\0';

    return len;
}
#endif
