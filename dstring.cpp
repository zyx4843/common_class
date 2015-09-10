/***********************************************************************
** Author       : zheng yi xiong 
** Date         : 2014-08-13
** Name         : dstring.h
** Description  :
** Modify Record:
***********************************************************************/

#include "dstring.h"
#include <stdarg.h>
#include <assert.h>

///////////////////////////////////////////////////////
// * ctype.h 标准库函数

#undef _UPPER
#undef _LOWER
#undef _DIGIT
#undef _SPACE
#undef _PUNCT
#undef _CONTROL
#undef _BLANK
#undef _HEX
#undef _LEADBYTE
#undef _ALPHA

#define _UPPER      0x0001
#define _LOWER      0x0002
#define _DIGIT      0x0004
#define _SPACE      0x0008 /* HT  LF  VT  FF  CR  SP */
#define _PUNCT      0x0010
#define _CONTROL    0x0020
#define _BLANK      0x0040 /* this is SP only, not SP and HT as in C99  */
#define _HEX        0x0080
#define _LEADBYTE   0x8000
#define _ALPHA      0x0103

#define upalpha ('A' - 'a')

unsigned short _dctype[] = {
	0,					/* <EOF>, 0xFFFF */
	_CONTROL,			/* CTRL+@, 0x00 */
	_CONTROL,			/* CTRL+A, 0x01 */
	_CONTROL,			/* CTRL+B, 0x02 */
	_CONTROL,			/* CTRL+C, 0x03 */
	_CONTROL,			/* CTRL+D, 0x04 */
	_CONTROL,			/* CTRL+E, 0x05 */
	_CONTROL,			/* CTRL+F, 0x06 */
	_CONTROL,			/* CTRL+G, 0x07 */
	_CONTROL,			/* CTRL+H, 0x08 */
	_CONTROL | _SPACE,	/* CTRL+I, 0x09 */
	_CONTROL | _SPACE,	/* CTRL+J, 0x0a */
	_CONTROL | _SPACE,	/* CTRL+K, 0x0b */
	_CONTROL | _SPACE,	/* CTRL+L, 0x0c */
	_CONTROL | _SPACE,	/* CTRL+M, 0x0d */
	_CONTROL,			/* CTRL+N, 0x0e */
	_CONTROL,			/* CTRL+O, 0x0f */
	_CONTROL,			/* CTRL+P, 0x10 */
	_CONTROL,			/* CTRL+Q, 0x11 */
	_CONTROL,			/* CTRL+R, 0x12 */
	_CONTROL,			/* CTRL+S, 0x13 */
	_CONTROL,			/* CTRL+T, 0x14 */
	_CONTROL,			/* CTRL+U, 0x15 */
	_CONTROL,			/* CTRL+V, 0x16 */
	_CONTROL,			/* CTRL+W, 0x17 */
	_CONTROL,			/* CTRL+X, 0x18 */
	_CONTROL,			/* CTRL+Y, 0x19 */
	_CONTROL,			/* CTRL+Z, 0x1a */
	_CONTROL,			/* CTRL+[, 0x1b */
	_CONTROL,			/* CTRL+\, 0x1c */
	_CONTROL,			/* CTRL+], 0x1d */
	_CONTROL,			/* CTRL+^, 0x1e */
	_CONTROL,			/* CTRL+_, 0x1f */
	_SPACE | _BLANK,	/* ` ', 0x20 */
	_PUNCT,				/* `!', 0x21 */
	_PUNCT,				/* 0x22 */
	_PUNCT,				/* `#', 0x23 */
	_PUNCT,				/* `$', 0x24 */
	_PUNCT,				/* `%', 0x25 */
	_PUNCT,				/* `&', 0x26 */
	_PUNCT,				/* 0x27 */
	_PUNCT,				/* `(', 0x28 */
	_PUNCT,				/* `)', 0x29 */
	_PUNCT,				/* `*', 0x2a */
	_PUNCT,				/* `+', 0x2b */
	_PUNCT,				/* `,', 0x2c */
	_PUNCT,				/* `-', 0x2d */
	_PUNCT,				/* `.', 0x2e */
	_PUNCT,				/* `/', 0x2f */
	_DIGIT | _HEX,		/* `0', 0x30 */
	_DIGIT | _HEX,		/* `1', 0x31 */
	_DIGIT | _HEX,		/* `2', 0x32 */
	_DIGIT | _HEX,		/* `3', 0x33 */
	_DIGIT | _HEX,		/* `4', 0x34 */
	_DIGIT | _HEX,		/* `5', 0x35 */
	_DIGIT | _HEX,		/* `6', 0x36 */
	_DIGIT | _HEX,		/* `7', 0x37 */
	_DIGIT | _HEX,		/* `8', 0x38 */
	_DIGIT | _HEX,		/* `9', 0x39 */
	_PUNCT,				/* `:', 0x3a */
	_PUNCT,				/* `;', 0x3b */
	_PUNCT,				/* `<', 0x3c */
	_PUNCT,				/* `=', 0x3d */
	_PUNCT,				/* `>', 0x3e */
	_PUNCT,				/* `?', 0x3f */
	_PUNCT,				/* `@', 0x40 */
	_UPPER | _HEX,		/* `A', 0x41 */
	_UPPER | _HEX,		/* `B', 0x42 */
	_UPPER | _HEX,		/* `C', 0x43 */
	_UPPER | _HEX,		/* `D', 0x44 */
	_UPPER | _HEX,		/* `E', 0x45 */
	_UPPER | _HEX,		/* `F', 0x46 */
	_UPPER,				/* `G', 0x47 */
	_UPPER,				/* `H', 0x48 */
	_UPPER,				/* `I', 0x49 */
	_UPPER,				/* `J', 0x4a */
	_UPPER,				/* `K', 0x4b */
	_UPPER,				/* `L', 0x4c */
	_UPPER,				/* `M', 0x4d */
	_UPPER,				/* `N', 0x4e */
	_UPPER,				/* `O', 0x4f */
	_UPPER,				/* `P', 0x50 */
	_UPPER,				/* `Q', 0x51 */
	_UPPER,				/* `R', 0x52 */
	_UPPER,				/* `S', 0x53 */
	_UPPER,				/* `T', 0x54 */
	_UPPER,				/* `U', 0x55 */
	_UPPER,				/* `V', 0x56 */
	_UPPER,				/* `W', 0x57 */
	_UPPER,				/* `X', 0x58 */
	_UPPER,				/* `Y', 0x59 */
	_UPPER,				/* `Z', 0x5a */
	_PUNCT,				/* `[', 0x5b */
	_PUNCT,				/* 0x5c */
	_PUNCT,				/* `]', 0x5d */
	_PUNCT,				/* `^', 0x5e */
	_PUNCT,				/* `_', 0x5f */
	_PUNCT,				/* 0x60 */
	_LOWER | _HEX,		/* `a', 0x61 */
	_LOWER | _HEX,		/* `b', 0x62 */
	_LOWER | _HEX,		/* `c', 0x63 */
	_LOWER | _HEX,		/* `d', 0x64 */
	_LOWER | _HEX,		/* `e', 0x65 */
	_LOWER | _HEX,		/* `f', 0x66 */
	_LOWER,				/* `g', 0x67 */
	_LOWER,				/* `h', 0x68 */
	_LOWER,				/* `i', 0x69 */
	_LOWER,				/* `j', 0x6a */
	_LOWER,				/* `k', 0x6b */
	_LOWER,				/* `l', 0x6c */
	_LOWER,				/* `m', 0x6d */
	_LOWER,				/* `n', 0x6e */
	_LOWER,				/* `o', 0x6f */
	_LOWER,				/* `p', 0x70 */
	_LOWER,				/* `q', 0x71 */
	_LOWER,				/* `r', 0x72 */
	_LOWER,				/* `s', 0x73 */
	_LOWER,				/* `t', 0x74 */
	_LOWER,				/* `u', 0x75 */
	_LOWER,				/* `v', 0x76 */
	_LOWER,				/* `w', 0x77 */
	_LOWER,				/* `x', 0x78 */
	_LOWER,				/* `y', 0x79 */
	_LOWER,				/* `z', 0x7a */
	_PUNCT,				/* `{', 0x7b */
	_PUNCT,				/* `|', 0x7c */
	_PUNCT,				/* `}', 0x7d */
	_PUNCT,				/* `~', 0x7e */
	_CONTROL,			/* 0x7f */
	0,					/* 0x80 */
	0,					/* 0x81 */
	0,					/* 0x82 */
	0,					/* 0x83 */
	0,					/* 0x84 */
	0,					/* 0x85 */
	0,					/* 0x86 */
	0,					/* 0x87 */
	0,					/* 0x88 */
	0,					/* 0x89 */
	0,					/* 0x8a */
	0,					/* 0x8b */
	0,					/* 0x8c */
	0,					/* 0x8d */
	0,					/* 0x8e */
	0,					/* 0x8f */
	0,					/* 0x90 */
	0,					/* 0x91 */
	0,					/* 0x92 */
	0,					/* 0x93 */
	0,					/* 0x94 */
	0,					/* 0x95 */
	0,					/* 0x96 */
	0,					/* 0x97 */
	0,					/* 0x98 */
	0,					/* 0x99 */
	0,					/* 0x9a */
	0,					/* 0x9b */
	0,					/* 0x9c */
	0,					/* 0x9d */
	0,					/* 0x9e */
	0,					/* 0x9f */
	0,					/* 0xa0 */
	0,					/* 0xa1 */
	0,					/* 0xa2 */
	0,					/* 0xa3 */
	0,					/* 0xa4 */
	0,					/* 0xa5 */
	0,					/* 0xa6 */
	0,					/* 0xa7 */
	0,					/* 0xa8 */
	0,					/* 0xa9 */
	0,					/* 0xaa */
	0,					/* 0xab */
	0,					/* 0xac */
	0,					/* 0xad */
	0,					/* 0xae */
	0,					/* 0xaf */
	0,					/* 0xb0 */
	0,					/* 0xb1 */
	0,					/* 0xb2 */
	0,					/* 0xb3 */
	0,					/* 0xb4 */
	0,					/* 0xb5 */
	0,					/* 0xb6 */
	0,					/* 0xb7 */
	0,					/* 0xb8 */
	0,					/* 0xb9 */
	0,					/* 0xba */
	0,					/* 0xbb */
	0,					/* 0xbc */
	0,					/* 0xbd */
	0,					/* 0xbe */
	0,					/* 0xbf */
	0,					/* 0xc0 */
	0,					/* 0xc1 */
	0,					/* 0xc2 */
	0,					/* 0xc3 */
	0,					/* 0xc4 */
	0,					/* 0xc5 */
	0,					/* 0xc6 */
	0,					/* 0xc7 */
	0,					/* 0xc8 */
	0,					/* 0xc9 */
	0,					/* 0xca */
	0,					/* 0xcb */
	0,					/* 0xcc */
	0,					/* 0xcd */
	0,					/* 0xce */
	0,					/* 0xcf */
	0,					/* 0xd0 */
	0,					/* 0xd1 */
	0,					/* 0xd2 */
	0,					/* 0xd3 */
	0,					/* 0xd4 */
	0,					/* 0xd5 */
	0,					/* 0xd6 */
	0,					/* 0xd7 */
	0,					/* 0xd8 */
	0,					/* 0xd9 */
	0,					/* 0xda */
	0,					/* 0xdb */
	0,					/* 0xdc */
	0,					/* 0xdd */
	0,					/* 0xde */
	0,					/* 0xdf */
	0,					/* 0xe0 */
	0,					/* 0xe1 */
	0,					/* 0xe2 */
	0,					/* 0xe3 */
	0,					/* 0xe4 */
	0,					/* 0xe5 */
	0,					/* 0xe6 */
	0,					/* 0xe7 */
	0,					/* 0xe8 */
	0,					/* 0xe9 */
	0,					/* 0xea */
	0,					/* 0xeb */
	0,					/* 0xec */
	0,					/* 0xed */
	0,					/* 0xee */
	0,					/* 0xef */
	0,					/* 0xf0 */
	0,					/* 0xf1 */
	0,					/* 0xf2 */
	0,					/* 0xf3 */
	0,					/* 0xf4 */
	0,					/* 0xf5 */
	0,					/* 0xf6 */
	0,					/* 0xf7 */
	0,					/* 0xf8 */
	0,					/* 0xf9 */
	0,					/* 0xfa */
	0,					/* 0xfb */
	0,					/* 0xfc */
	0,					/* 0xfd */
	0,					/* 0xfe */
	0					/* 0xff */
};

unsigned short *_dpctype = _dctype + 1;
unsigned short *_dpwctype = _dctype + 1;

int diswctype(dchar wc, dctype_t wctypeFlags)
{
	return (_dpwctype[(unsigned char)(wc & 0xFF)] & wctypeFlags);
}

int disalnum(dchar c)
{
	 return (diswctype(c, _ALPHA | _DIGIT));
}

int disalpha(dchar c)
{
	return (diswctype (c, _ALPHA));
}

int disascii(dchar c)
{
	return ((dchar)c <= 0x7F);
}

int discntrl(dchar c)
{
	return(diswctype(c, _CONTROL));
}

int disdigit(dchar c)
{
	return (diswctype (c, _DIGIT));
}

int disgraph(dchar c)
{
	return (diswctype (c, _PUNCT | _ALPHA | _DIGIT));
}

int dislower(dchar c)
{
	return (diswctype (c, _LOWER));
}

int disprint(dchar c)
{
	   return (diswctype(c, _BLANK | _PUNCT | _ALPHA | _DIGIT));
}

int dispunct(dchar c)
{
	return (diswctype(c, _PUNCT));
}

int disspace(dchar c)
{
	return (diswctype(c, _SPACE));
}

int disupper(dchar c)
{
	return (diswctype(c, _UPPER));
}

int disxdigit(dchar c)
{
	return (diswctype(c, _HEX));
}

dchar dtoupper(dchar c)
{
	if(diswctype (c, _LOWER))
		return (c + upalpha);
	return(c);
}

dchar dtolower(dchar c)
{
	if(diswctype (c, _UPPER))
		return (c - upalpha);
	return(c);
}


///////////////////////////////////////////////////////
// * string.h 标准库函数

dchar* dstrcat(dchar* destination, const dchar* source)
{
	dchar* ptr = destination;

	for(; *ptr; ++ptr);

	while((*ptr++ = *source++));

	return destination;
}

dchar* dstrncat(dchar* destination, const dchar* source, size_t num)
{
	size_t count = (size_t)num;

	if(count > 0)
	{
		dchar* d = destination;
		const dchar* s = source;

		while(*d != 0)
		{
			d++;
		}

		do
		{
			if ((*d = *s++) == 0)
			{
				break;
			}
			d++;
		}while(--count > 0);

		*d = 0;
	}

	return destination;
}

dchar* dstrcpy(dchar * destination, const dchar* source)
{
	dchar* d = destination;

	for(; (*d = *source); ++source, ++d);

	return destination;
}

dchar* dstrncpy(dchar* destination, const dchar* source, size_t num)
{
	size_t count = (size_t)num;

	if(count != 0)
	{
		dchar* d = destination;
		const dchar* s = source;

		do
		{
			if((*d++ = *s++) == 0)
			{
				while(--count != 0)
				{
					*d++ = 0;
				}
				break;
			}
		}while(--count != 0);

		/* 标准库, 不处理结尾 */
		d--;
		*d = 0;
	}
	else
	{
		destination[0] = 0;
	}

	return destination;
}

int dstrcmp(const dchar* str1, const dchar* str2)
{
	const dchar* s1 = str1;
	const dchar* s2 = str2;

	while(*s1 == *s2)
	{
		if (*s1 == 0)
		{
			return 0;
		}
		s1++;
		s2++;
	}

	return (*(const dchar*)(s1) - *(const dchar*)(s2));
}

int dstrncmp(const dchar* str1, const dchar* str2, size_t num)
{
	const dchar* s1 = str1;
	const dchar* s2 = str2;
	size_t n = (size_t)num;

	if(n == 0)
	{
		return 0;
	}

	do
	{
		if(*s1 != *s2++)
		{
			return (*(const dchar*)s1 - *(const dchar*)(--s2));
		}

		if(*s1++ == 0)
		{
			break;
		}
	}while(--n != 0);

	return 0;
}

size_t dstrlen(const dchar* str)
{
	const dchar* s;

	if(str == 0)
	{
		return 0;
	}

	for(s = str; *s; ++s);

	return (size_t)(s - str);
}

dchar* dstrchr(const dchar* str, int character)
{
	const dchar* s = str;
	dchar cc = (dchar)character;

	while(*s)
	{
		if(*s == cc)
		{
			return (dchar*)s;
		}
		s++;
	}

	if(cc == 0)
	{
		return (dchar*)s;
	}

	return 0;
}

dchar* dstrrchr(const dchar* str, int character)
{
	dchar* s = (dchar*)str;
	dchar cc = (dchar)character;
	const dchar* sp=(dchar*)0;

	while(*s)
	{
		if(*s == cc)
		{
			sp = s;
		}
		s++;
	}

	if(cc == 0)
	{
		sp = s;
	}

	return (dchar*)sp;
}

dchar* dstrstr(const dchar* str1, const dchar* str2)
{
	dchar* s = (dchar*)str1;
	dchar* find = (dchar*)str2;

	dchar c, sc;
	size_t len;

	if((c = *find++) != 0)
	{
		len = dstrlen(find);
		do
		{
			do
			{
				if((sc = *s++) == 0)
				{
					return 0;
				}
			}while(sc != c);
		}while(dstrncmp(s, find, len) != 0);
		s--;
	}

	return (dchar*)s;
}

dchar* dstrtok(dchar* str, const dchar* delimiters)
{
	dchar* s = str;
	const dchar* delim = delimiters;

	const dchar *spanp;
	int c, sc;
	dchar *tok;
	static dchar *last;

	if((s == NULL) && ((s = last) == NULL))
	{
		return (NULL);
	}

cont:
	c = *s++;
	for(spanp = delim; (sc = *spanp++) != 0;)
	{
		if(c == sc)
		{
			goto cont;
		}
	}

	if(c == 0)
	{	
		last = NULL;
		return (NULL);
	}
	tok = s - 1;

	for(;;)
	{
		c = *s++;
		spanp = delim;
		do
		{
			if((sc = *spanp++) == c)
			{
				if (c == 0)
				{
					s = NULL;
				}
				else
				{
					s[-1] = 0;
				}
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
}


///////////////////////////////////////////////////////
// * stdlib.h 标准库函数

long dstrtol(const dchar* str, dchar** endptr, int base)
{
	const dchar *s = str;
	unsigned long acc;
	int c;
	unsigned long cutoff;
	int neg = 0, any, cutlim;

	do
	{
		c = *s++;
	}while(disspace(c));

	if(c == '-')
	{
		neg = 1;
		c = *s++;
	}
	else if(c == '+')
	{
		c = *s++;
	}

	if((base == 0 || base == 16) &&
		(c == '0') && (*s == 'x' || *s == 'X'))
	{
		c = s[1];
		s += 2;
		base = 16;
	}

	if (base == 0)
	{
		base = c == '0' ? 8 : 10;
	}

	cutoff = neg ? (-(unsigned long)LONG_MIN) : LONG_MAX;
	cutlim = cutoff % (unsigned long)(base);
	cutoff /= (unsigned long)(base);
	for(acc = 0, any = 0;; c = *s++)
	{
		if(disdigit(c))
		{
			c -= '0';
		}
		else if(disalpha(c))
		{
			c -= disupper(c) ? ('A' - 10) : ('a' - 10);
		}
		else
		{
			break;
		}

		if(c >= base)
		{
			break;
		}

		if(any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
		{
			any = -1;
		}
		else
		{
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if(any < 0)
	{
		acc = neg ? LONG_MIN : LONG_MAX;
	}
	else if(neg)
	{
		acc = -acc;
	}

	if(endptr != 0)
	{
		*endptr = any ? ((dchar *)s - 1) : (dchar *)str;
	}

	return acc;
}

unsigned long dstrtoul(const dchar* str, dchar** endptr, int base)
{
	const dchar *s = str;
	unsigned long acc;
	int c;
	unsigned long cutoff;
	int neg = 0, any, cutlim;

	do
	{
		c = *s++;
	} while(disspace(c));

	if(c == '-')
	{
		neg = 1;
		c = *s++;
	}
	else if(c == '+')
	{
		c = *s++;
	}

	if((base == 0 || base == 16) &&
		(c == '0') && (*s == 'x' || *s == 'X'))
	{
		c = s[1];
		s += 2;
		base = 16;
	}
	if(base == 0)
	{
		base = c == '0' ? 8 : 10;
	}
	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
	for(acc = 0, any = 0;; c = *s++)
	{
		if(disdigit(c))
		{
			c -= '0';
		}
		else if(disalpha(c))
		{
			c -= disupper(c) ? ('A' - 10) : ('a' - 10);
		}
		else
		{
			break;
		}

		if(c >= base)
		{
			break;
		}
		if(any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
		{
			any = -1;
		}
		else
		{
			any = 1;
			acc *= base;
			acc += c;
		}
	}

	if(any < 0)
	{
		acc = ULONG_MAX;
	}
	else if(neg)
	{
		acc = -acc;
	}

	if(endptr != 0)
	{
		*endptr = any ? ((dchar*)s - 1) : (dchar*)str;
	}

	return acc;
}



///////////////////////////////////////////////////////
// * stdio.h 标准库函数

#define ZEROPAD 1               /* pad with zero */
#define SIGN    2               /* unsigned/signed long */
#define PLUS    4               /* show plus */
#define SPACE   8               /* space if plus */
#define LEFT    16              /* left justified */
#define SPECIAL 32              /* 0x */
#define LARGE   64              /* use 'ABCDEF' instead of 'abcdef' */

static int
skip_atoi(const dchar **s)
{
	int i = 0;

	while (disdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	return i;
}

static dchar *
number(dchar * buf, dchar * end, long long num, int base, int size, int precision, int type)
{
	dchar c,sign, tmp[66];
	const dchar *digits;
	const dchar small_digits[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
	const dchar large_digits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
	int i;

	digits = (type & LARGE) ? large_digits : small_digits;
	if (type & LEFT)
		type &= ~ZEROPAD;
	if (base < 2 || base > 36)
		return 0;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	if (type & SIGN) {
		if (num < 0) {
			sign = '-';
			num = -num;
			size--;
		} else if (type & PLUS) {
			sign = '+';
			size--;
		} else if (type & SPACE) {
			sign = ' ';
			size--;
		}
	}
	if (type & SPECIAL) {
		if (base == 16)
			size -= 2;
		else if (base == 8)
			size--;
	}
	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	else
	{
		while (num != 0)
		{
			int res = (int)(((unsigned long long) num) % (unsigned long) base);
			num = ((unsigned long long) num) / (unsigned) base;
			tmp[i++] = digits[res];
		}
	}
	if (i > precision)
		precision = i;
	size -= precision;
	if (!(type&(ZEROPAD+LEFT))) {
		while(size-->0) {
			if (buf <= end)
				*buf = ' ';
			++buf;
		}
	}
	if (sign) {
		if (buf <= end)
			*buf = sign;
		++buf;
	}
	if (type & SPECIAL) {
		if (base==8) {
			if (buf <= end)
				*buf = '0';
			++buf;
		} else if (base==16) {
			if (buf <= end)
				*buf = '0';
			++buf;
			if (buf <= end)
				*buf = digits[33];
			++buf;
		}
	}
	if (!(type & LEFT)) {
		while (size-- > 0) {
			if (buf <= end)
				*buf = c;
			++buf;
		}
	}
	while (i < precision--) {
		if (buf <= end)
			*buf = '0';
		++buf;
	}
	while (i-- > 0) {
		if (buf <= end)
			*buf = tmp[i];
		++buf;
	}
	while (size-- > 0) {
		if (buf <= end)
			*buf = ' ';
		++buf;
	}
	return buf;
}

static dchar*
string_s(dchar* buf, dchar* end, const char* s, int len, int field_width, int precision, int flags)
{
	int i;
	if (s == NULL)
	{
		s = "<NULL>";
		len = 6;
	}
	else
	{
		if (len == -1)
		{
			len = 0;
			while (s[len] && (unsigned int)len < (unsigned int)precision)
				len++;
		}
		else
		{
			if ((unsigned int)len > (unsigned int)precision)
				len = precision;
		}
	}
	if (!(flags & LEFT))
		while (len < field_width--)
		{
			if (buf <= end)
				*buf = ' ';
			++buf;
		}
		for (i = 0; i < len; ++i)
		{
			if (buf <= end)
				*buf = *s++;
			++buf;
		}
		while (len < field_width--)
		{
			if (buf <= end)
				*buf = ' ';
			++buf;
		}
		return buf;
}

static dchar* 
string_w(dchar* buf, dchar* end, const dchar* sw, int len, int field_width, int precision, int flags)
{
	dchar dnull[] = {'<','N','U','L','L','>','\0'};

	int i;
	if (sw == NULL)
	{
		sw = dnull;
		len = 6;
	}
	else
	{
		if (len == -1)
		{
			len = 0;
			while (sw[len] && (unsigned int)len < (unsigned int)precision)
				len++;
		}
		else
		{
			if ((unsigned int)len > (unsigned int)precision)
				len = precision;
		}
	}
	if (!(flags & LEFT))
		while (len < field_width--)
		{
			if (buf <= end)
				*buf = ' ';
			buf++;
		}
		for (i = 0; i < len; ++i)
		{
			if (buf <= end)
				*buf = *sw++;
			buf++;
		}
		while (len < field_width--)
		{
			if (buf <= end)
				*buf = ' ';
			buf++;
		}
		return buf;
}

static int
_dvsnwprintf(dchar *buf, size_t cnt, const dchar *fmt, va_list args)
{
	//int len;
	unsigned long long num;
	int base;
	dchar * str, * end;
	const char *s;
	const dchar *sw;

	int flags;		/* flags to number() */

	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
						number of chars for from string */
	int qualifier;		/* 'h', 'l', 'L', 'w' or 'I' for integer fields */

	str = buf;
	end = buf + cnt - 1;
	if (end < buf - 1) {
		end = ((dchar*)(-1));
		cnt = end - buf + 1;
	}

	for ( ; *fmt ; ++fmt) {
		if (*fmt != '%') {
			if (str <= end)
				*str = *fmt;
			++str;
			continue;
		}

		/* process flags */
		flags = 0;
repeat:
		++fmt;		/* this also skips first '%' */
		switch (*fmt) {
				case '-': flags |= LEFT; goto repeat;
				case '+': flags |= PLUS; goto repeat;
				case ' ': flags |= SPACE; goto repeat;
				case '#': flags |= SPECIAL; goto repeat;
				case '0': flags |= ZEROPAD; goto repeat;
		}

		/* get field width */
		field_width = -1;
		if (disdigit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {
			++fmt;
			/* it's the next argument */
			field_width = va_arg(args, int);
			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		/* get the precision */
		precision = -1;
		if (*fmt == '.') {
			++fmt;
			if (disdigit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {
				++fmt;
				/* it's the next argument */
				precision = va_arg(args, int);
			}
			if (precision < 0)
				precision = 0;
		}

		/* get the conversion qualifier */
		qualifier = -1;
		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L' || *fmt == 'w') {
			qualifier = *fmt;
			++fmt;
		} else if (*fmt == 'I' && *(fmt+1) == '6' && *(fmt+2) == '4') {
			qualifier = *fmt;
			fmt += 3;
		}

		/* default base */
		base = 10;

		switch (*fmt) {
		case 'c':
			if (!(flags & LEFT))
				while (--field_width > 0) {
					if (str <= end)
						*str = ' ';
					++str;
				}
				if (qualifier == 'h') {
					if (str <= end)
						*str = (dchar) va_arg(args, int);
					++str;
				} else {
					if (str <= end)
						*str = (dchar) va_arg(args, int);
					++str;
				}
				while (--field_width > 0) {
					if (str <= end)
						*str = ' ';
					++str;
				}
				continue;

		case 'C':
			if (!(flags & LEFT))
				while (--field_width > 0) {
					if (str <= end)
						*str = ' ';
					++str;
				}
				if (qualifier == 'l' || qualifier == 'w') {
					if (str <= end)
						*str = (dchar) va_arg(args, int);
					++str;
				} else {
					if (str <= end)
						*str = (dchar) va_arg(args, int);
					++str;
				}
				while (--field_width > 0) {
					if (str <= end)
						*str = ' ';
					++str;
				}
				continue;

		case 's':
			if (qualifier == 'h') {
				/* print ascii string */
				s = va_arg(args, char *);
				str = string_s(str, end, s, -1,  field_width, precision, flags);
			} else {
				/* print unicode string */
				sw = va_arg(args, dchar *);
				str = string_w(str, end, sw, -1, field_width, precision, flags);
			}
			continue;

		case 'S':
			if (qualifier == 'l' || qualifier == 'w') {
				/* print unicode string */
				sw = va_arg(args, dchar *);
				str = string_w(str, end, sw, -1, field_width, precision, flags);
			} else {
				/* print ascii string */
				s = va_arg(args, char *);
				str = string_s(str, end, s, -1,  field_width, precision, flags);
			}
			continue;

		//case 'Z':
		//	if (qualifier == 'h') {
		//		/* print counted ascii string */
		//		PANSI_STRING pus = va_arg(args, PANSI_STRING);
		//		if ((pus == NULL) || (pus->Buffer == NULL)) {
		//			s = NULL;
		//			len = -1;
		//		} else {
		//			s = pus->Buffer;
		//			len = pus->Length;
		//		}
		//		str = string(str, end, s, len,  field_width, precision, flags);
		//	} else {
		//		/* print counted unicode string */
		//		PUNICODE_STRING pus = va_arg(args, PUNICODE_STRING);
		//		if ((pus == NULL) || (pus->Buffer == NULL)) {
		//			sw = NULL;
		//			len = -1;
		//		} else {
		//			sw = pus->Buffer;
		//			len = pus->Length / sizeof(WCHAR);
		//		}
		//		str = stringw(str, end, sw, len,  field_width, precision, flags);
		//	}
		//	continue;

		case 'p':
			if (field_width == -1) {
				field_width = 2*sizeof(void *);
				flags |= ZEROPAD;
			}
			str = number(str, end,
				(unsigned long) va_arg(args, void *), 16,
				field_width, precision, flags);
			continue;

		case 'n':
			/* FIXME: What does C99 say about the overflow case here? */
			if (qualifier == 'l') {
				long * ip = va_arg(args, long *);
				*ip = (str - buf);
			} else {
				int * ip = va_arg(args, int *);
				*ip = (str - buf);
			}
			continue;

			/* integer number formats - set up the flags and "break" */
		case 'o':
			base = 8;
			break;

		case 'b':
			base = 2;
			break;

		case 'X':
			flags |= LARGE;
		case 'x':
			base = 16;
			break;

		case 'd':
		case 'i':
			flags |= SIGN;
		case 'u':
			break;

		default:
			if (*fmt != '%') {
				if (str <= end)
					*str = '%';
				++str;
			}
			if (*fmt) {
				if (str <= end)
					*str = *fmt;
				++str;
			} else
				--fmt;
			continue;
		}

		if (qualifier == 'I')
			num = va_arg(args, unsigned long long);
		else if (qualifier == 'l')
			num = va_arg(args, unsigned long);
		else if (qualifier == 'h') {
			if (flags & SIGN)
				num = va_arg(args, int);
			else
				num = va_arg(args, unsigned int);
		}
		else {
			if (flags & SIGN)
				num = va_arg(args, int);
			else
				num = va_arg(args, unsigned int);
		}
		str = number(str, end, num, base, field_width, precision, flags);
	}
	if (str <= end)
		*str = '\0';
	else if (cnt > 0)
		/* don't write out a null byte if the buf size is zero */
		*end = '\0';
	return str-buf;
}

int dsprintf(dchar* buf, const dchar* fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = _dvsnwprintf(buf,INT_MAX,fmt,args);
	va_end(args);
	return i;
}


int dsnprintf(dchar* buf, size_t cnt, const dchar* fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i=_dvsnwprintf(buf,cnt,fmt,args);
	va_end(args);
	return i;
}



///////////////////////////////////////////////////////
// * utf8 与 Unicode 相互转换, 非标准函数

dchar* dutf2ucs(const char* utf8, dchar* dest, long len)
{
	long size = 0, index = 0, out_index = 0;
	dchar *out;
	unsigned char c;
	char* utf = (char*)(utf8);

	if(NULL == utf)
	{
		assert(false);
		return NULL;
	}

	if(strlen(utf) <= 0)
	{
		if(NULL != dest)
		{
			dest[0] = '\0';
			return dest;
		}
		else
		{
			out = new dchar[1];
			assert(NULL != out);
			out[0] = '\0';
			return (dchar*)(out);
		}
	}

	c = utf[index++];
	while(c)
	{
		if((c & 0x80) == 0)
		{
			index += 0;
		}
		else if((c & 0xe0) == 0xe0)
		{
			index += 2;
		}
		else
		{
			index += 1;
		}
		size += 1;
		c = utf[index++];
	}

	if(size <= 0)
	{
		return NULL;
	}

	if(NULL != dest)
	{
		out = dest;
	}
	else
	{
		len = size + 1;
		out = new dchar[len];

		assert(NULL != out);
		if(out == NULL)
		{
			return NULL;
		}
	}

	index = 0;
	c = utf[index++];
	while(('\0' != c) && (out_index + 1 < len))
	{
		if((c & 0x80) == 0)
		{
			//0xxxxxx
			out[out_index++] = c;
		}
		else if((c & 0xe0) == 0xe0)
		{
			//1110xxxx 10xxxxxx 10xxxxxx
			out[out_index] = (c & 0x1F) << 12;
			c = utf[index++];
			out[out_index] |= (c & 0x3F) << 6;
			c = utf[index++];
			out[out_index++] |= (c & 0x3F);
		}
		else
		{
			//110xxxxx 10xxxxxx
			out[out_index] = (c & 0x3F) << 6;
			c = utf[index++];
			out[out_index++] |= (c & 0x3F);
		}
		c = utf[index++];
	}
	out[out_index] = 0;

	return out;
}

char* ducs2utf(const dchar* dstr, char* dest, long len)
{
	long size = 0, index = 0, out_index = 0;
	unsigned char* out;
	unsigned short c;
	dchar* ucs2 = (dchar*)(dstr);

	if(NULL == ucs2)
	{
		assert(false);
		return NULL;
	}

	if(dstrlen(ucs2) <= 0)
	{
		if(NULL != dest)
		{
			dest[0] = '\0';
			return dest;
		}
		else
		{
			out = new unsigned char[1];
			assert(NULL != out);
			out[0] = '\0';
			return (char*)(out);
		}
	}

	c = ucs2[index++];
	while(c)
	{
		if(c < 0x0080)
		{
			size += 1;
		}
		else if(c < 0x0800)
		{
			size += 2;
		}
		else
		{
			size += 3;
		}
		c = ucs2[index++];
	}

	if(size <= 0)
	{
		return NULL;
	}

	if(NULL != dest)
	{
		out = (unsigned char*)(dest);
	}
	else
	{
		len = size + 1;
		out = new unsigned char[len];

		assert(NULL != out);
		if(NULL == out)
		{
			return NULL;
		}
	}

	index = 0;
	c = ucs2[index++];
	while('\0' != c)
	{
		if(c < 0x080)
		{
			if(out_index + 1 >= len) break;

			out[out_index++] = static_cast<unsigned char>(c);
		}
		else if(c < 0x800)
		{
			if(out_index + 2 >= len) break;

			out[out_index++] = 0xc0 | (c >> 6);
			out[out_index++] = 0x80 | (c & 0x3f);
		}
		else
		{
			if(out_index + 3 >= len) break;

			out[out_index++] = 0xe0 | (c >> 12);
			out[out_index++] = 0x80 | ((c >> 6) & 0x3f);
			out[out_index++] = 0x80 | (c & 0x3f);
		}
		c = ucs2[index++];
	}
	out[out_index] = 0x00;

	return (char*)(out);
}


//////////////////////////////////////////////////////////////////////////
// * dstring 扩展 std::wstring

#ifdef  __cplusplus

/* 默认构造 */

dstring::dstring()
: basic_dstring()
{

}

dstring::~dstring()
{

}


/* 标准参数构造 */

dstring::dstring(const dstring& str)
: basic_dstring(str)
{

}

dstring::dstring(const dstring& str, size_type roff, size_type count)
: basic_dstring(str, roff, count)
{

}

dstring::dstring(const dchar* str)
: basic_dstring(str)
{

}

dstring::dstring(const dchar* str, size_type count)
: basic_dstring(str, count)
{

}

dstring::dstring(size_type count, dchar ch)
: basic_dstring(count, ch)
{

}


/* 扩展参数构造 utf-8编码 */

dstring::dstring(const char *str)
: basic_dstring()
{
	dchar *ptr = dutf2ucs(str);

	if(NULL != ptr)
	{
		assign(ptr);

		delete [] ptr;
		ptr = NULL;
	}
}


/* 标准运算符 */

dstring& dstring::operator=(const dstring& str)
{
	assign(str);
	return (*this);
}

dstring& dstring::operator=(const dchar *str)
{
	assign(str);
	return (*this);
}

dstring& dstring::operator=(dchar ch)
{
	assign((size_type)(1), ch);
	return (*this);
}

dstring& dstring::operator+=(const dstring& str)
{
	append(str);
	return (*this);
}

dstring& dstring::operator+=(const dchar *str)
{
	append(str);
	return (*this);
}

dstring& dstring::operator+=(dchar ch)
{
	append((size_type)(1), ch);
	return (*this);
}

/* 扩展运算符 */
dstring& dstring::operator=(const char *str)
{
	dchar *ptr = dutf2ucs(str);
	
	if(NULL != ptr)
	{
		assign(ptr);

		delete [] ptr;
		ptr = NULL;
	}
	else
	{
		assign('\0');
	}

	return (*this);
}

dstring& dstring::operator+=(const char *str)
{
	dchar *ptr = dutf2ucs(str);

	if(NULL != ptr)
	{
		append(ptr);

		delete [] ptr;
		ptr = NULL;
	}

	return (*this);
}

dstring dstring::substr(size_type _Off, size_type _Count) const
{	// return [_Off, _Off + _Count) as new string
	return (dstring(*this, _Off, _Count));
}

/* 扩展函数 : 格式化 */
int dstring::dsnprintf(size_type cnt, const dchar *fmt, ...)
{
	dchar *ptr = new dchar[cnt + 1];
	assert(NULL != ptr);
	memset(ptr, 0, sizeof(dchar) * (cnt + 1));

	va_list args;
	int i;

	va_start(args, fmt);
	i=_dvsnwprintf(ptr, cnt, fmt, args);
	va_end(args);

	assign(ptr);

	delete [] ptr;
	ptr = NULL;
	return i;
}

int dstring::dsnprintf(size_type cnt, const char *fmt, ...)
{
	dchar *str = dutf2ucs(fmt);

	if(NULL != str)
	{
		dchar *ptr = new dchar[cnt + 1];
		assert(NULL != ptr);
		memset(ptr, 0, sizeof(dchar) * (cnt + 1));

		va_list args;
		int i;

		va_start(args, fmt);
		i=_dvsnwprintf(ptr, cnt, str, args);
		va_end(args);
		
		assign(ptr);

		delete [] str;
		str = NULL;
		delete [] ptr;
		ptr = NULL;

		return i;
	}

	return 0;
}


/* 扩展函数 : 去除左右空格 */
void dstring::trim()
{
	dchar str[8] = {' ', '\t', '\0'};

	erase(find_last_not_of(str) + 1);
	erase(0, find_first_not_of(str));
}

void dstring::trim_l()
{
	dchar str[8] = {' ', '\t', '\0'};

	erase(0, find_first_not_of(str));
}

void dstring::trim_r()
{
	dchar str[8] = {' ', '\t', '\0'};

	erase(find_last_not_of(str) + 1);
}

/* 扩展函数 : 获取转换为<utf-8>编码ascii字符串 */
std::string dstring::a_str()
{
	char *str = ducs2utf(c_str());

	if(NULL != str)
	{
		std::string ss = str;
		delete [] str;
		str = NULL;

		return ss;
	}

	return "";
}

int dstring::a_str(char *out)
{
	char *str = ducs2utf(c_str());

	out[0] = '\0';

	if(NULL != str)
	{
		int len = strlen(str);
		
		strncpy(out, str, len);

		out[len] = '\0';

		delete [] str;
		str = NULL;

		return len;
	}

	return 0;
}

int dstring::a_str(char *out, size_type cnt)
{
	char *str = ducs2utf(c_str());

	out[0] = '\0';

	if(NULL != str)
	{
		int len = strlen(str);

		if(len + 1 > cnt)
		{
			len = cnt - 1;
		}

		strncpy(out, str, len);

		out[len] = '\0';

		delete [] str;
		str = NULL;

		return len;
	}

	return 0;
}


#endif

//end
