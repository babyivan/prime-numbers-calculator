//
// Created by null on 26.07.2018.
//

#ifndef LISTAT_SOFTWARE_RUN_DEFINES_H
#define LISTAT_SOFTWARE_RUN_DEFINES_H

#ifdef __unix__
#define DIR_SEP "/"
#elif defined(_WIN32) || defined(WIN32)
#define DIR_SEP "\\"
#endif
// Имя входящего файла (должен лежать рядом с программой)
#define FILE_IN_NAME "file.xml"
// Имя исходящего файла
#define FILE_OUT_NAME "file_output.xml"

// Определяем ноды
#define NODE_ROOT "root"
#define NODE_INTERVALS "intervals"
#define NODE_INTERVAL "interval"
#define NODE_LOW "low"
#define NODE_HIGH "high"
// Минимальное значение в <low> и <high>
#define NODE_MIN__LOW_HIGH 0

#endif //LISTAT_SOFTWARE_RUN_DEFINES_H
