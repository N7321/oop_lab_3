# CMakeLists.txt для лабораторной работы 2
# Демонстрирует современную организацию проекта с разделением на библиотеку и исполняемый файл

cmake_minimum_required(VERSION 3.10)

# Настройка проекта
project(lab_03 
    VERSION 1.0.0
    LANGUAGES CXX
)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)  # Изменено с 20 на 11 для совместимости
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# Настройка директорий
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Добавление директории с заголовочными файлами
include_directories(${INCLUDE_DIR})

# Поиск исходных файлов библиотеки
file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

# Создание библиотеки
add_library(lab_03_lib ${LIBRARY_SOURCES})

# Создание исполняемого файла
add_executable(lab_03_exe main.cpp)

# Связывание библиотеки с исполняемым файлом
target_link_libraries(lab_03_exe PRIVATE lab_03_lib)

enable_testing()

add_executable(tests test/Gtests.cpp)

target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)


# Настройка компилятора (опционально)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab_03_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab_03_exe PRIVATE -Wall -Wextra -Wpedantic)
endif()
add_test(NAME MyProjectTests COMMAND tests)