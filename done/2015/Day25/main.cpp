#include <bits/stdc++.h>
#include "../../../libs/math.h"
using namespace std;


int main()
{
    int x = 3083, y = 2978;
    int w = x + y;
    int z = w * (w - 1) / 2 - y;

    uint64_t start = 20151125;
    uint64_t res = (start * ModExp(252533, z, 33554393)) % 33554393;

	std::cout << "res: " << res << '\n';

    return(0);
}
/* 
// https://en.wikipedia.org/wiki/Pairing_function#Inverting_the_Cantor_pairing_function
 
  z = f(x,y) = (x + y) * (x + y + 1) / 2 + y
  w = x + y
  t = w(w+1) /2
  z = t+y
  int z = w*(w-1)/2 - y;

  Similiar problem: https://www.codewars.com/kata/543b9113def6343e43000875/



*/