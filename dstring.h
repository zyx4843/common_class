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
// * 双字节 字符 定义

/* 双字节字定义, double char */
typedef unsigned short	DCHAR;
typedef DCHAR			dchar;
typedef unsigned short	dctype_t;

#ifdef  __cplusplus
/* STL 双字节字符串定义 */
typedef std::basic_string< DCHAR, std::char_traits<DCHAR>, std::allocator<DCHAR> >  BASIC_DSTRING;
typedef BASIC_DSTRING basic_dstring;
class dstring;
#endif



///////////////////////////////////////////////////////
// * ctype.h 标准库函数

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
// * string.h 标准库函数

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
// * stdlib.h 标准库函数

long dstrtol(const dchar *str, dchar **endptr, int base);
unsigned long dstrtoul(const dchar *str, dchar **endptr, int base);



///////////////////////////////////////////////////////
// * stdio.h 标准库函数

int dsprintf(dchar *buf, const dchar *fmt, ...);
int dsnprintf(dchar *buf, size_t cnt, const dchar *fmt, ...);



///////////////////////////////////////////////////////
// * utf8 与 Unicode 相互转换, 非标准函数

dchar*	dutf2ucs(const char *utf8, dchar *dest = NULL, long len = 0);	//len >= strlen(utf8) + 1
char*	ducs2utf(const dchar *dstr, char *dest = NULL, long len = 0);	//len >= dstrlen(dstr) * 3 + 1



//////////////////////////////////////////////////////////////////////////
// * dstring 扩展 std::wstring

#ifdef  __cplusplus

class dstring :  public basic_dstring
{
public:
	/* 
		警告: 本类涉及和使用到的<char*>均为<utf-8>编码
	*/

	typedef basic_dstring::size_type size_type;

public:
	/* 默认构造 */
	dstring();
	~dstring();

	/* 标准参数构造 */
	dstring(const dstring& str);
	dstring(const dstring& str, size_type roff, size_type count = basic_dstring::npos);
	dstring(const dchar* str);
	dstring(const dchar* str, size_type count);
	dstring(size_type count, dchar ch);

	/* 扩展参数构造<utf-8> */
	dstring(const char *str);


	/* 标准运算符 */
	dstring& operator=(const dstring& str);
	dstring& operator=(const dchar *str);
	dstring& operator=(dchar ch);
	dstring& operator+=(const dstring& str);
	dstring& operator+=(const dchar *str);
	dstring& operator+=(dchar ch);

	/* 扩展运算符<utf-8> */
	dstring& operator=(const char *str);
	dstring& operator+=(const char *str);


	/* 标准库函数：取子串 */
	dstring substr(size_type _Off = 0, size_type _Count = npos) const;

	/* 扩展函数 : 格式化 */
	int dsnprintf(size_type cnt, const dchar *fmt, ...);
	int dsnprintf(size_type cnt, const char *fmt, ...);


	/* 扩展函数 : 去除左右空格 */
	void trim();
	void trim_l();
	void trim_r();

	
	/* 扩展函数 : 获取转换为<utf-8>编码ascii字符串 */
	/* 将本字符串拷贝到<out>的内存中去 */
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

