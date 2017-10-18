#ifndef UTILITIES_H
#define UTILITIES_H

#include <locale>
#include <codecvt>
#include <string>

using namespace std;

class Utilities
{
private:
  static wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

public:
  static string unicode_to_utf8(const wstring& unicode); 
  static wstring utf8_to_unicode(const string& utf8);
};

#endif
