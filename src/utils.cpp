//
// Created by null on 04.08.2018.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include "include/utils.h"

utils::utils() {}

// https://stackoverflow.com/questions/8581832/converting-a-vectorint-to-string
std::string utils::vector2string(const std::vector<int> &vec) {
  std::stringstream ss;
  int first = true;

  for (const int &it : vec) {
    if (!first)
      ss << " ";
    first = false;
    ss << it;
  }
  return ss.str();
}

// Простенькая запись в файл
void utils::write2file(const std::string &path, const std::string &str) {
  std::ofstream out_file;
  // Перезаписываем если файл уже существует
  out_file.open(path, std::ios_base::trunc);

  out_file
      << "<root>\n"
      << "  <primes> "
      << str
      << " </primes>\n"
      << "</root>";
  out_file.close();

  std::cout << "\n[writer] File write successful !!!\n Path: \"" << path << "\"" << std::endl;
}