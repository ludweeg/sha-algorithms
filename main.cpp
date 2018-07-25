
#include "sha.h"
#include <iostream>

int main()
{

  std::string mess = "Send 1 BTC to Richard.";
  std::cout << "sha1:   " << sha1(mess)   << std::endl;
  std::cout << "sha224: " << sha224(mess) << std::endl;
  std::cout << "sha256: " << sha256(mess) << std::endl;
  std::cout << "sha384: " << sha384(mess) << std::endl;
  std::cout << "sha512: " << sha512(mess) << std::endl;

  return 0;
}
