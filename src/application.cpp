//
// Created by null on 19.07.2018.
//

#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include <functional>
#include <mutex>

#include "include/application.hpp"

#include "include/xml_parser.hpp"
#include "include/calc_prime_th.hpp"
#include "include/defines.h"
#include "include/utils.h"

application::application(int &argc, char *argv[]) {
  std::string start_path(argv[0]);
  // Определяем путь запуска
  program_start_path = start_path.substr(0, start_path.find_last_of(DIR_SEP));
  // Даем парсеру знать где лежит входящий файл
  parser.set_path_to_file(program_start_path + DIR_SEP + FILE_IN_NAME);
  // Устанавливаем путь для исходящего файла
  out_file_path = program_start_path + DIR_SEP + FILE_OUT_NAME;
}

void application::start_threads(std::vector<int> &result) {
  std::mutex mutex_lock;

  for (int i = 3; i < parser.get_nodes().size(); i += 3) {
    int node_min = parser.get_nodes()[i].get_value();
    int node_max = parser.get_nodes()[i + 1].get_value();
    //std::cout << std::thread::hardware_concurrency();
    threads.push_back(
        std::thread([&result, node_min, node_max, &mutex_lock]() {
          // Для красивого вывода в консоль, (отладка) лок... в продакшене нужно не лочить
          mutex_lock.lock();
          std::cout << "[thread|info] Thread: [" << std::this_thread::get_id() << "] start with params: [min:" << node_min << ", max:" << node_max
                    << "]" << std::endl;
          auto t_start = std::chrono::high_resolution_clock::now();
          mutex_lock.unlock();

          calc_prime_th t(node_min, node_max);
          auto res = t.get_result();

          // Для красивого вывода в консоль, (отладка) лок... в продакшене нужно не лочить
          mutex_lock.lock();
          auto t_stop = std::chrono::high_resolution_clock::now();
          auto diff = std::chrono::duration_cast<std::chrono::duration<double>>(t_stop - t_start).count();

          std::cout << "[thread|info] Thread: [" << std::this_thread::get_id() << "] finish. (exec time: " << diff
                    << " sec.)" << std::endl;
          // Нужно лочить только эту строку в продакшене...
          // Корректное добавление результата в вектор, нужен обязательно лок
          // mtx.lock();
          result.insert(result.end(), res.begin(), res.end());
          mutex_lock.unlock();
          //std::this_thread::sleep_for(std::chrono::milliseconds(1200));
        })
    );
  }
  // std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));
  for (auto &thread : threads) {
    if (thread.joinable())
      thread.join();
  }
  std::cout << "All threads was finished." << std::endl;
}

void application::run() {
  std::vector<int> result;

  // Парсим и валидируем xml
  parser.read_file_and_validate();

  // Если наша xml валидна - запускам решение задач...
  if (parser.is_valid()) {
    // Запускаем процесс
    start_threads(result);

    // Сортируем и избавляемся от повторяющихся цифр
    // https://stackoverflow.com/a/1041939
    std::sort(result.begin(), result.end());
    result.erase(
        std::unique(result.begin(), result.end()),
        result.end()
    );
    // Превращаем вектор в строку
    std::string result_string = utils::vector2string(result);
    // Записываем в xml файл
    utils::write2file(out_file_path, result_string);
  } else
    std::cout << "The program will be completed." << std::endl;

//  std::cout << "\nPress any key for exit ...\n" << std::endl;
//  std::cin.get();
}