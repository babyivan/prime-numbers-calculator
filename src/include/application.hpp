//
// Created by null on 19.07.2018.
//

#ifndef LISTAT_SOFTWARE_RUN_APPLICATION_H
#define LISTAT_SOFTWARE_RUN_APPLICATION_H

#include <vector>
#include <thread>
#include "xml_parser.hpp"

class application {

 public:
  application(int &argc, char *argv[]);
  void run();

 private:
  void start_threads(std::vector<int> &result);

 private:
  xml_parser parser;
  std::vector<std::thread> threads;

  std::string program_start_path;
  std::string out_file_path;
};

#endif //LISTAT_SOFTWARE_RUN_APPLICATION_H
