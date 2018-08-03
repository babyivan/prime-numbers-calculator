//
// Created by null on 19.07.2018.
//

#ifndef LISTAT_SOFTWARE_RUN_XML_NODE_H
#define LISTAT_SOFTWARE_RUN_XML_NODE_H

#include <string>

class xml_node {

 public:
  xml_node();
  xml_node(std::string name);

  const std::string &get_node_name() const;

  void set_value(int new_value);
  const int &get_value() const;

  void set_is_valid(bool new_value);
  const bool &get_is_valid() const;

  //bool operator ==(xml_node &a, xml_node &b);

 private:
  std::string name;
  int value;
  bool is_valid;
};

#endif //LISTAT_SOFTWARE_RUN_XML_NODE_H
