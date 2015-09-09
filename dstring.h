#ifndef __D_STRING_H__
#define __D_STRING_H__

#include <string.h>
#include <string>

#ifdef  __cplusplus
extern "C" {
#endif


#ifndef WIN32
#ifndef INT_MIN
#define INT_MIN (-2147483647 - 1)
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef LONG_MIN
#define LONG_MIN (-2147483647L - 1)
#endif

#ifndef LONG_MAX
#define LONG_MAX 2147483647L
#endif

#ifndef ULONG_MAX
#define ULONG_MAX 0xffffffffUL
#endif
#endif

///////////////////////////////////////////////////////
// * ˫�ֽ� �ַ� ����

/* ˫�ֽ��ֶ���, double char */
typedef unsigned short	DCHAR;
typedef DCHAR			dchar;
typedef unsigned short	dctype_t;

#ifdef  __cplusplus
/* STL ˫�ֽ��ַ������� */
typedef std::basic_string< DCHAR, std::char_traits<DCHAR>, std::allocator<DCHAR> >  BASIC_DSTRING;
typedef BASIC_DSTRING basic_dstring;
class dstring;
#endif



///////////////////////////////////////////////////////
// * ctype.h ��׼�⺯��

int disalnum(dchar c);
int disalpha(dchar c);
int disascii(dchar c);
int discntrl(dchar c);
int disdigit(dchar c);
int disgraph(dchar c);
int dislower(dchar c);
int disprint(dchar c);
int dispunct(dchar c);
int disspace(dchar c);
int disupper(dchar c);
int disxdigit(dchar c);

dchar dtoupper(dchar c);
dchar dtolower(dchar c);



///////////////////////////////////////////////////////
// * string.h ��׼�⺯��

dchar*	dstrcat(dchar *destination, const dchar *source);
dchar*	dstrncat(dchar *destination, const dchar *source, size_t num);
dchar*	dstrcpy(dchar *destination, const dchar *source);
dchar*	dstrncpy(dchar *destination, const dchar *source, size_t num);
int		dstrcmp(const dchar *str1, const dchar *str2);
int		dstrncmp(const dchar *str1, const dchar *str2, size_t num);

size_t	dstrlen (const dchar *str);
dchar*	dstrchr(const dchar *str, int character);
dchar*	dstrrchr(const dchar *str, int character);
dchar*	dstrstr(const dchar *str1, const dchar *str2);
dchar*	dstrtok(dchar *str, const dchar *delimiters);



///////////////////////////////////////////////////////
// * stdlib.h ��׼�⺯��

long dstrtol(const dchar *str, dchar **endptr, int base);
unsigned long dstrtoul(const dchar *str, dchar **endptr, int base);



///////////////////////////////////////////////////////
// * stdio.h ��׼�⺯��

int dsprintf(dchar *buf, const dchar *fmt, ...);
int dsnprintf(dchar *buf, size_t cnt, const dchar *fmt, ...);



///////////////////////////////////////////////////////
// * utf8 �� Unicode �໥ת��, �Ǳ�׼����

dchar*	dutf2ucs(const char *utf8, dchar *dest = NULL, long len = 0);	//len >= strlen(utf8) + 1
char*	ducs2utf(const dchar *dstr, char *dest = NULL, long len = 0);	//len >= dstrlen(dstr) * 3 + 1



//////////////////////////////////////////////////////////////////////////
// * dstring ��չ std::wstring

#ifdef  __cplusplus

class dstring :  public basic_dstring
{
public:
	/* 
		����: �����漰��ʹ�õ���<char*>��Ϊ<utf-8>����
	*/

	typedef basic_dstring::size_type size_type;

public:
	/* Ĭ�Ϲ��� */
	dstring();
	~dstring();

	/* ��׼�������� */
	dstring(const dstring& str);
	dstring(const dstring& str, size_type roff, size_type count = basic_dstring::npos);
	dstring(const dchar* str);
	dstring(const dchar* str, size_type count);
	dstring(size_type count, dchar ch);

	/* ��չ��������<utf-8> */
	dstring(const char *str);


	/* ��׼����� */
	dstring& operator=(const dstring& str);
	dstring& operator=(const dchar *str);
	dstring& operator=(dchar ch);
	dstring& operator+=(const dstring& str);
	dstring& operator+=(const dchar *str);
	dstring& operator+=(dchar ch);

	/* ��չ�����<utf-8> */
	dstring& operator=(const char *str);
	dstring& operator+=(const char *str);


	/* ��׼�⺯����ȡ�Ӵ� */
	dstring substr(size_type _Off = 0, size_type _Count = npos) const;

	/* ��չ���� : ��ʽ�� */
	int dsnprintf(size_type cnt, const dchar *fmt, ...);
	int dsnprintf(size_type cnt, const char *fmt, ...);


	/* ��չ���� : ȥ�����ҿո� */
	void trim();
	void trim_l();
	void trim_r();

	
	/* ��չ���� : ��ȡת��Ϊ<utf-8>����ascii�ַ��� */
	/* �����ַ���������<out>���ڴ���ȥ */
	std::string a_str();
	int			a_str(char *out);
	int			a_str(char *out, size_type cnt);
};

#endif


#ifdef  __cplusplus
}
#endif

#endif
//end

