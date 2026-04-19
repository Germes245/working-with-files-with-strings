cmake_minimum_required(VERSION 3.10)
project(working-with-files-with-strings)

set(CMAKE_C_STANDARD 11)

# Пути вывода (можно оставить как есть)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Собираем список исходников
file(GLOB SOURCE_FILES "src/*.c")

# Создаём разделяемую (динамическую) библиотеку
add_library(working-with-files-with-strings SHARED ${SOURCE_FILES})
target_include_directories(working-with-files-with-strings PRIVATE include)

include(GNUInstallDirs)

# Устанавливаем библиотеку и заголовки
install(TARGETS working-with-files-with-strings
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/working-with-files-with-strings)
