//
// Created by null on 22.07.2018.
//

#ifndef LISTAT_SOFTWARE_RUN_CALC_PRIME_TH_H
#define LISTAT_SOFTWARE_RUN_CALC_PRIME_TH_H

#include <vector>

class calc_prime_th {
 public:
  calc_prime_th(int min, int max);
  std::vector<int> &get_result();
  
 private:
  std::vector<int> vec;
};

#endif //LISTAT_SOFTWARE_RUN_CALC_PRIME_TH_H
