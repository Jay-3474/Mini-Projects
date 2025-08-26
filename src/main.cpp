#include "main.hpp"

auto main() -> int
{
  std::cout << "Hello, World!" << std::endl;

  const int num = 55;

  decimal_to_hex(num);

  return 0;
}

void decimal_to_hex(int n)
{
  const int a_size = 20;
  std::array<char, a_size> m{};
  int t = 0;
  int i = 0;
  const int deviser = 16;
  const int dec = 10;

  while (n != 0 && i < static_cast<int>(m.size()))
  {
    t = n % deviser;
    if (t < dec)
    {
      m.at(i++) = t + '0';  // '0' is 48
    }
    else
    {
      m.at(i++) = t + '7';  // 'A' is 65, so +55 is '7'
    }
    n /= deviser;
  }

  for (int j = i - 1; j >= 0; j--)
  {
    std::cout << m.at(j);
  }
}
