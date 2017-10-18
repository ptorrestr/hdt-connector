#include "Utilities.h"

wstring_convert<codecvt_utf8_utf16<wchar_t>> Utilities::converter;

string
Utilities::unicode_to_utf8(const wstring& unicode)
{
  return converter.to_bytes(unicode);
}

wstring
Utilities::utf8_to_unicode(const string& utf8)
{
  return converter.from_bytes(utf8);
}
