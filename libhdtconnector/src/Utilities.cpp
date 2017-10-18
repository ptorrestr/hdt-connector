#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Utilities.h"

#ifdef HAVE_GLIB_2_2X
wstring_convert<codecvt_utf8_utf16<wchar_t>> Utilities::converter;
#endif

string
Utilities::unicode_to_utf8(const wstring& unicode)
{
#ifdef HAVE_GLIB_2_2X
  return converter.to_bytes(unicode);
#elif HAVE_BOOST_LOCALE
  return utf_to_utf<char>(unicode.c_str(), unicode.c_str() + unicode.size());
#endif
}

wstring
Utilities::utf8_to_unicode(const string& utf8)
{
#ifdef HAVE_GLIB_2_2X
  return converter.from_bytes(utf8);
#elif HAVE_BOOST_LOCALE
  return utf_to_utf<wchar>(unicode.c_str(), unicode.s_str() + unicode.size());
#endif
}
