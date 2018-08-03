//
// Created by null on 19.07.2018.
//

#include "include/xml_parser.hpp"

#include <iostream>
#include <fstream>
#include <forward_list>
#include <algorithm>

xml_parser::xml_parser() {
  path_to_file = "";
  nodes_count = 0;
  input_file_is_valid = false;
  input_file_was_read = false;
}

xml_parser::xml_parser(std::string basic_string)
    : xml_parser() {
  path_to_file = basic_string;
}

void xml_parser::set_path_to_file(std::string basic_string) {
  path_to_file = basic_string;
}

void xml_parser::add_new_node(xml_node &node) {
  nodes.push_back(node);
  nodes_count++;
}

void xml_parser::read_file_and_validate() {
  if (!path_to_file.empty())
    read_file();
  else {
    std::cout << "[xml_parser] File path is empty " << std::endl;
    return;
  }

  if (input_file_was_read)
    validate();
  else {
    std::cout << "[xml_parser] Input file is read ?? " << std::endl;
    input_file_is_valid = false;
    return;
  }
}

const std::vector<xml_node> &xml_parser::get_nodes() const {
  return nodes;
}

bool xml_parser::is_valid() {
  return !(!input_file_is_valid || !input_file_was_read);
}

bool xml_parser::check_char_for_tag(const char &ch, bool &tag_was_open, bool &tag_was_closed, bool &tag_prepare_to_close) {
  bool match = false;

  if (ch == '<') {
    tag_was_open = match = true;
  } else if (ch == '>') {
    tag_was_closed = match = true;
  } else if (ch == '/') {
    tag_prepare_to_close = match = true;
  }

  return match;
}

void xml_parser::read_file() {
  std::string buffer;
  std::ifstream in(path_to_file);

  if (!in) {
    // throw std::runtime_error("File not found");
    std::cout << "[parser] File not found \n Path:(" << path_to_file << ")" << std::endl;
    return;
  }
  // Храним названия открытых тегов
  std::forward_list<int> open_tags;
  std::string node_name;
  std::string node_data;
  char c;

  bool while_condition = true;
  // Был прочитан символ открытия тега "<"
  bool tag_was_open = false;
  // Был прочитан символ закрытия тега ">"
  bool tag_was_closed = false;
  // Был прочитан символ "закрытия" тега "/"
  bool tag_prepare_to_close = false;
  // Выполнено условие ... "<tag>" ... дальше по идее должны быть данные
  bool time_for_data = false;
  // Будет запоминать порядок каждоый открытой ноды <node> ... <node> и тд.
  int iteration = -1;

  while (while_condition) {
    if (!in.get(c))
      while_condition = false;
    else
      buffer += c;
    // Проверяем текущий символ. Если "<" или ">" или "/" - ставим необходимую переменную в true и идем в continue
    if (check_char_for_tag(c, tag_was_open, tag_was_closed, tag_prepare_to_close))
      if (while_condition)
        continue;
    // добавляем текущую букву ноды в "node_name"
    if ((tag_was_open && !tag_was_closed) || (tag_was_open && tag_prepare_to_close && !tag_was_closed)) {
      node_name += c;
      // Если
    } else if (tag_was_open && tag_was_closed) {
      tag_was_open = false;
      tag_was_closed = false;
      // Если был прочитан символ "закрытия" тега "/"
      if (tag_prepare_to_close) {
        // Сравниваем последнюю открытую ноду с текущей
        if (nodes[open_tags.front()].get_node_name() == node_name) {
          // Если все ОК - ставим ей valid "true"
          nodes[open_tags.front()].set_is_valid(true);
          // Удаляем ее "iteration" из списка открытых нод
          open_tags.pop_front();
        } else {
          //TODO: Можно кидать тут exception если последняя открытая нода не равна текущей ноде
          std::cout << "[parser] Error on node #" << iteration << std::endl;
        }
        tag_prepare_to_close = false;
        // Если не был прочитан символ "закрытия" тега "/" - значит это новая открытая нода
      } else {
        xml_node n(node_name);
        add_new_node(n);
        open_tags.push_front(++iteration);
      }
      node_name = "";
      /* Читаем данные внутри <%name%> в том случае если <%name%> есть в списке "nodes_need_validate_data"
       * open_tags.front() чтобы избежать повторного парсинга данных после закрытия <%name%>
       */
      if (!open_tags.empty() && in_list_validate_node_data(open_tags.front()))
        time_for_data = true;
    }
    //Дошли до открытия новой <%name%>... А значит что все было от прошлого ">" до тещуего "<" можно представить что это данные
    if (tag_was_open && time_for_data) {
      time_for_data = false;
      // Парсим информацию от прошлого прошлого ">" до тещуего "<"
      parse_node_data(node_data, iteration);

      node_data = "";
    }
    // Пока "time_for_data" = true  - сохраняем всю информацию до символа "<" в переменную
    if (time_for_data) {
      node_data += c;
    }
  }
  in.close();

  std::cout << "[parser] Read file completed." << " Found nodes: " << nodes_count << std::endl;
  input_file_was_read = true;
}

void xml_parser::parse_node_data(std::string &node_data, const int &index) {
  // Если текущий <%name%> надо проверять
  if (in_list_validate_node_data(index)) {
    //Очищаем все пробелы в строке
    node_data.erase(remove_if(node_data.begin(), node_data.end(), isspace), node_data.end());
    // std::stoi упорно не хотел у меня работать, испольузю atoi
    // По заданию мы ожидаем только цифры
    int num = atoi(node_data.c_str());

    if (num > NODE_MIN__LOW_HIGH)
      nodes[index].set_value(num);
    else
      std::cout << "[parser|info] Node [<" << nodes[index].get_node_name() << "> (index: " << (index + 1)
                << ")] Expect 'int' value > " << NODE_MIN__LOW_HIGH << std::endl;
    //TODO: Тут можно кидать exception если оказалось так что в тексте есть что-то помимо цыфр и текущая нода "low" or "high"
  }
}

// Валидатор xml-ки
void xml_parser::validate() {
  if (nodes_count < 5) {
    std::cout << "[validation|error] Nodes count < 5" << std::endl;
    input_file_is_valid = false;
    return;
  }
  // Итератор для правильной последовательности <> сначала = 0, потом будет ходить с 2
  // 2+ всегда будет "<interval>" -> "<low>" -> "<high>"
  int order_i = 0;
  input_file_is_valid = true;

  for (int i = 0; i < nodes_count; i++) {
    if (!validate_node(i, order_i)) {
      input_file_is_valid = false;
      break;
    }
    // Инкрементим и проверяем "order_i" на переполнение
    if (++order_i > (nodes_order.size() - 1))
      order_i = 2;
  }
  std::cout << (input_file_is_valid ? "[validation] Validation completed without errors.\n"
                                    : "[validation] Validation completed with errors.\n") << std::endl;
}

// Проверка <%name%> на валидность
bool xml_parser::validate_node(int index, const int &index_order) {
  // Сначала проверяем чтобы <%name%> был закрыт при парсинге xml а также находится на своем месте
  if (!nodes[index].get_is_valid() || (nodes[index].get_node_name() != nodes_order[index_order])) {
    std::cout << "[validation|error] Node [<" << nodes[index].get_node_name() << ">] not valid. Expect: <"
              << nodes_order[index_order] << ">, got: <" << nodes[index].get_node_name() << std::endl;
    return false;
  }
  // Для проверки корректности "<low>" и "<high>"
  if (!validate_node_data(index)) {
    std::cout << "[validation|error] Node [<" << nodes[index].get_node_name() << "> (index: " << (index + 1)
              << ")] value <= " << NODE_MIN__LOW_HIGH << std::endl;
    return false;
  }

  return true;
}
// Проверяем значение в нужных <%name%>
bool xml_parser::validate_node_data(const int &position) {
  // Нам нужно проверять только <low> и <high>
  if (in_list_validate_node_data(position))
    return nodes[position].get_value() > NODE_MIN__LOW_HIGH;
    // Остальные игнорируем
  else
    return true;
}

bool xml_parser::in_list_validate_node_data(const int &index) {
  bool result = false;

  for (auto const &node_name : nodes_need_validate_data)
    if (node_name == nodes[index].get_node_name()) {
      result = true;
      break;
    }

  return result;
}