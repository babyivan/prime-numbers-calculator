//
// Created by null on 22.07.2018.
//

#include <iostream>
#include <thread>
#include "include/calc_prime_th.hpp"

calc_prime_th::calc_prime_th(int min, int max) {
  if (min <= 1)
    min = 2;

  for (int i = min; i < max; i++) {
    bool prime = true;
    for (int j = 2; j * j <= i; j++) {
      if (i % j == 0) {
        prime = false;
        break;
      }
    }
    if (prime) {
      vec.push_back(i);
    }
  }
}

std::vector<int> &calc_prime_th::get_result() {
  return vec;
}
