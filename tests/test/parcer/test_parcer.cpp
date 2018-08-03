#include <iostream>
#include <gtest/gtest.h>
#include "../../../src/include/xml_parser.hpp"
#include "../../../src/include/defines.h"

static std::string app_path;
static std::string path;

struct Parser : public testing::Test {
  xml_parser *obj;

  void SetUp() override {
    obj = new xml_parser();
    path = app_path.substr(0, app_path.find_last_of(DIR_SEP));
  }

  void TearDown() override {
    delete obj;
  }
};

TEST_F(Parser, Parser_test00) {
  std::string s = path + DIR_SEP + "test_00.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_FALSE(obj->is_valid());
}

TEST_F(Parser, Parser_test01) {
  std::string s = path + DIR_SEP + "test_01.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_FALSE(obj->is_valid());
}

TEST_F(Parser, Parser_test02) {
  std::string s = path + DIR_SEP + "test_02.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_FALSE(obj->is_valid());
}
// Корректный файл
TEST_F(Parser, Parser_test03) {
  std::string s = path + DIR_SEP + "test_03.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_TRUE(obj->is_valid());
}

TEST_F(Parser, Parser_test04) {
  std::string s = path + DIR_SEP + "test_04.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_FALSE(obj->is_valid());
}

TEST_F(Parser, Parser_test05) {
  std::string s = path + DIR_SEP + "test_05.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_FALSE(obj->is_valid());
}

TEST_F(Parser, Parser_test06) {
  std::string s = path + DIR_SEP + "test_06.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_FALSE(obj->is_valid());
}
// Корректный файл
TEST_F(Parser, Parser_test07) {
  std::string s = path + DIR_SEP + "test_07.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_TRUE(obj->is_valid());
}

TEST_F(Parser, Parser_test08) {
  std::string s = path + DIR_SEP + "test_08.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_FALSE(obj->is_valid());
}
TEST_F(Parser, Parser_test09) {
  std::string s = path + DIR_SEP + "test_09.xml";
  obj->set_path_to_file(s);
  obj->read_file_and_validate();
  ASSERT_FALSE(obj->is_valid());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  // Запоминаем путь запуска
  app_path = argv[0];

  return RUN_ALL_TESTS();
}