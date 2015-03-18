#ifndef BASE64_H
#define BASE64_H
#include <string>
#include <vector>
std::string base64_encode(unsigned char const*, unsigned int len);
std::vector<char> base64_decode(std::string const& s);

#endif