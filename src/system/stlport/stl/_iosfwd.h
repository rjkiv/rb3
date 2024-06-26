#ifndef _STLP_INTERNAL_IOSFWD
#define _STLP_INTERNAL_IOSFWD

// This file provides forward declarations of the most important I/O
// classes.  Note that almost all of those classes are class templates,
// with default template arguments.  According to the C++ standard,
// if a class template is declared more than once in the same scope
// then only one of those declarations may have default arguments.

// <iosfwd> contains the same declarations as other headers, and including
// both <iosfwd> and (say) <iostream> is permitted.  This means that only
// one header may contain those default template arguments.

// In this implementation, the declarations in <iosfwd> contain default
// template arguments.  All of the other I/O headers include <iosfwd>.

#ifndef _STLP_CHAR_TRAITS_H
#  include <stl/char_traits.h>
#endif

namespace _STLP_STD {

class ios_base;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_ios;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_streambuf;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_istream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_ostream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_iostream;

template <class _CharT, class  _Traits = char_traits<_CharT>,
          class _Allocator = allocator<_CharT> >
class basic_stringbuf;

template <class _CharT, class _Traits = char_traits<_CharT>,
          class _Allocator = allocator<_CharT> >
class basic_istringstream;

template <class _CharT, class _Traits = char_traits<_CharT>,
          class _Allocator = allocator<_CharT> >
class basic_ostringstream;

template <class _CharT, class _Traits = char_traits<_CharT>,
          class _Allocator = allocator<_CharT> >
class basic_stringstream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_filebuf;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_ifstream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_ofstream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class basic_fstream;

template <class _CharT, class _Traits = char_traits<_CharT> >
class istreambuf_iterator;

template <class _CharT, class _Traits = char_traits<_CharT> >
class ostreambuf_iterator;

typedef basic_ios<char, char_traits<char> >    ios;
typedef basic_ios<wchar_t, char_traits<wchar_t> > wios;

// Forward declaration of class locale, and of the most important facets.
class locale;
template <class _Facet> inline const _Facet& use_facet(const locale&);

template <class _CharT> class ctype;
template <class _CharT> class ctype_byname;
template <class _CharT> class collate;
template <class _CharT> class collate_byname;

template<> class ctype<char>;
template<> class ctype_byname<char>;
template<> class collate<char>;
template<> class collate_byname<char>;

template<> class ctype<wchar_t>;
template<> class ctype_byname<wchar_t>;
template<> class collate<wchar_t>;
template<> class collate_byname<wchar_t>;

// Typedefs for ordinary (narrow-character) streams.
//template<> class basic_streambuf<char, char_traits<char> >;

typedef basic_istream<char, char_traits<char> >  istream;
typedef basic_ostream<char, char_traits<char> >  ostream;
typedef basic_iostream<char, char_traits<char> > iostream;
typedef basic_streambuf<char,char_traits<char> > streambuf;

typedef basic_stringbuf<char, char_traits<char>, allocator<char> >     stringbuf;
typedef basic_istringstream<char, char_traits<char>, allocator<char> > istringstream;
typedef basic_ostringstream<char, char_traits<char>, allocator<char> > ostringstream;
typedef basic_stringstream<char, char_traits<char>, allocator<char> >  stringstream;

typedef basic_filebuf<char, char_traits<char> >  filebuf;
typedef basic_ifstream<char, char_traits<char> > ifstream;
typedef basic_ofstream<char, char_traits<char> > ofstream;
typedef basic_fstream<char, char_traits<char> >  fstream;

// Typedefs for wide-character streams.
typedef basic_streambuf<wchar_t, char_traits<wchar_t> > wstreambuf;
typedef basic_istream<wchar_t, char_traits<wchar_t> >   wistream;
typedef basic_ostream<wchar_t, char_traits<wchar_t> >   wostream;
typedef basic_iostream<wchar_t, char_traits<wchar_t> >  wiostream;

typedef basic_stringbuf<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >     wstringbuf;
typedef basic_istringstream<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wistringstream;
typedef basic_ostringstream<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wostringstream;
typedef basic_stringstream<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >  wstringstream;

typedef basic_filebuf<wchar_t, char_traits<wchar_t> >  wfilebuf;
typedef basic_ifstream<wchar_t, char_traits<wchar_t> > wifstream;
typedef basic_ofstream<wchar_t, char_traits<wchar_t> > wofstream;
typedef basic_fstream<wchar_t, char_traits<wchar_t> >  wfstream;

}

#endif

// Local Variables:
// mode:C++
// End:
