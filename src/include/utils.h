//
// Created by null on 03.08.2018.
//

#ifndef LISTAT_SOFTWARE_RUN_UTILS_H
#define LISTAT_SOFTWARE_RUN_UTILS_H

#include <string>
#include <vector>
class utils {
 private:
  utils();

 public:
  static std::string vector2string(const std::vector<int> &vec);
  static void write2file(const std::string &path, const std::string &str);
};

#endif //LISTAT_SOFTWARE_RUN_UTILS_H
