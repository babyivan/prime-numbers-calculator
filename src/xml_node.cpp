//
// Created by null on 19.07.2018.
//

#include "include/xml_node.hpp"

xml_node::xml_node() {
  name = "";
  value = -1;
  is_valid = false;
}

xml_node::xml_node(std::string name)
    : xml_node() {
  this->name = name;
}

const std::string &xml_node::get_node_name() const {
  return name;
}

void xml_node::set_value(int new_value) {
  value = new_value;
}

const int &xml_node::get_value() const {
  return value;
}
void xml_node::set_is_valid(bool new_value) {
  is_valid = new_value;
}
const bool &xml_node::get_is_valid() const {
  return is_valid;
}
