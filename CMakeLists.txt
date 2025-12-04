cmake_minimum_required(VERSION 3.14)
project(ais3p-reporter LANGUAGES CXX)

# Установка C++ стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(X11 REQUIRED)
find_package(Freetype REQUIRED)

find_path(XFT_INCLUDE_DIR X11/Xft/Xft.h
    PATHS /usr/include /usr/local/include)
find_library(XFT_LIBRARY Xft)

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
        ${FREETYPE_INCLUDE_DIRS} 
)


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${X11_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${XFT_LIBRARY} 
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