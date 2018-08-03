//
// Created by null on 19.07.2018.
//

#ifndef LISTAT_SOFTWARE_RUN_XML_PARSER_H
#define LISTAT_SOFTWARE_RUN_XML_PARSER_H

#include <string>
#include <vector>

#include "xml_node.hpp"
#include "defines.h"

class xml_parser {

 public:
  xml_parser();
  xml_parser(std::string basic_string);

  void set_path_to_file(std::string basic_string);
  void read_file_and_validate();
  const std::vector<xml_node> &get_nodes() const;
  bool is_valid();

 private:
  void read_file();
  void validate();
  void add_new_node(xml_node &node);
  bool check_char_for_tag(const char &ch, bool &tag_was_open, bool &tag_was_closed, bool &tag_prepare_to_close);
  bool in_list_validate_node_data(const int &index);
  void parse_node_data(std::string &node_data, const int &index);
  bool validate_node(int index, const int &index_order);
  bool validate_node_data(const int &position);

 public:
  // Последовательность вложенних тегов
  const std::vector<std::string> nodes_order = {NODE_ROOT, NODE_INTERVALS, NODE_INTERVAL, NODE_LOW, NODE_HIGH};
  const std::vector<std::string> nodes_need_validate_data = {NODE_LOW, NODE_HIGH};

 private:
  bool input_file_is_valid;
  bool input_file_was_read;

  std::string path_to_file;
  std::vector<xml_node> nodes;
  int nodes_count;
};

#endif //LISTAT_SOFTWARE_RUN_XML_PARSER_H
