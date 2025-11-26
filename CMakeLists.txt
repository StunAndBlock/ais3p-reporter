cmake_minimum_required(VERSION 3.14)
project(ais3p-reporter LANGUAGES CXX)

# Установка C++ стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Рекурсивно собираем все исходники из src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Указываем include директории
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include       # свои заголовки
)



##set_target_properties(${PROJECT_NAME} PROPERTIES
##    WIN32_EXECUTABLE ON
##)
# Если ext/include содержит inline-функции, можешь использовать SYSTEM
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ext/include)

#add_custom_target(run
#    COMMAND $<TARGET_FILE:mhsp>
#    DEPENDS mhsp
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#)