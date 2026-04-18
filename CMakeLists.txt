cmake_minimum_required(VERSION 3.10)
project(hash_table_file_writer_and_reader)

set(CMAKE_C_STANDARD 11)

# Пути вывода (можно оставить как есть)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Собираем список исходников
file(GLOB SOURCE_FILES "src/*.c")

# Создаём разделяемую (динамическую) библиотеку
add_library(hash_table_file_writer_and_readerSHARED ${SOURCE_FILES})
target_include_directories(hash_table_file_writer_and_reader PRIVATE include)

include(GNUInstallDirs)

# Устанавливаем библиотеку и заголовки
install(TARGETS hash_table_file_writer_and_reader
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hash_table_file_writer_and_reader)
