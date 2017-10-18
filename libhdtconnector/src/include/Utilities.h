#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_GLIB_2_2X
#include <locale>
#include <codecvt>
#elif HAVE_BOOST_LOCALE
#include <boost/locale/encoding_utf.hpp>
#endif
#include <string>

using namespace std;
#ifdef HAVE_BOOST_LOCALE
using boost::locale::conv::utf_to_utf;
#endif

class Utilities
{
private:
#ifdef HAVE_GLIB_2_2X
  static wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
#endif

public:
  static string unicode_to_utf8(const wstring& unicode); 
  static wstring utf8_to_unicode(const string& utf8);
};

#endif
