#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Utilities.h"

#ifdef HAVE_CODECVT
wstring_convert<codecvt_utf8_utf16<wchar_t>> Utilities::converter;
#endif

string
Utilities::unicode_to_utf8(const wstring& unicode)
{
#ifdef HAVE_CODECVT
  return converter.to_bytes(unicode);
#endif
#ifdef HAVE_BOOST_LOCALE
  return utf_to_utf<char>(unicode.c_str(), unicode.c_str() + unicode.size());
#endif
}

wstring
Utilities::utf8_to_unicode(const string& utf8)
{
#ifdef HAVE_CODECVT
  return converter.from_bytes(utf8);
#endif
#ifdef HAVE_BOOST_LOCALE
  return utf_to_utf<wchar_t>(utf8.c_str(), utf8.c_str() + utf8.size());
#endif
}
