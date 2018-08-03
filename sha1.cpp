#include "sha.h"

std::function<int32(int32,int32,int32)> getFunc(size_t t)
{
  if(t < 20)
    return [](int32 x, int32 y, int32 z) -> int32 { return CH(x,y,z); };
  else if(t < 40)
    return [](int32 x, int32 y, int32 z) -> int32 { return PARITY(x,y,z); };
  else if(t < 60)
    return [](int32 x, int32 y, int32 z) -> int32 { return MAJ(x,y,z); };
  else
    return [](int32 x, int32 y, int32 z) -> int32 { return PARITY(x,y,z); };

}

std::string preprocessing1(std::string mess)
{
  std::stringstream ss;

  // l + 1 + k ≡ 448 mod 512 (1 -> 1000 0000(bin) = 80(hex) -> 8 bit)
  int32 l = {(int32)(8 * mess.length())};
  int32 k = {(448 - (8 + l)) % 512};

  for(size_t i {}; i < mess.length(); ++i)
    ss << std::setw(2) << std::setfill('0') << std::hex << (int32)mess[i];
  ss << "80" << std::setw(16 + k / 4) << std::setfill('0') << std::hex << l;

  return ss.str();
}

std::string hashComputation1(std::string pmess)
{
  int32 a,b,c,d,e,t0;
  int32 w[80],H[5] {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0};

  for(size_t i {}, j {}; i < pmess.length(); i += 8, ++j)
  {
    w[j] = std::stoll(pmess.substr(i,8), 0, 16);

    if(j == 15)
    {
      for(j = 16; j < 80; ++j)
        w[j] = ROTL_32((w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16]),1);
      j = -1;

      a = H[0];
      b = H[1];
      c = H[2];
      d = H[3];
      e = H[4];

      for(size_t t {}; t < 80; ++t)
      {
        auto f = getFunc(t);
        t0 = ROTL_32(a,5) + f(b,c,d) + e + K[t] + w[t];
        e = d;
        d = c;
        c = ROTL_32(b,30);
        b = a;
        a = t0;
      }

      H[0] += a;
      H[1] += b;
      H[2] += c;
      H[3] += d;
      H[4] += e;
    }
  }

  std::stringstream ss;
  for(size_t i {}; i < 5; ++i)
    ss << std::setw(8) << std::setfill('0') << std::hex << H[i];

  return ss.str();
}

std::string sha1(std::string mess)
{
  std::string pmess {preprocessing1(mess)};
  return hashComputation1(pmess);
}
