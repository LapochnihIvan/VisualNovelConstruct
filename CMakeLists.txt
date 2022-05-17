cmake_minimum_required(VERSION 3.16.3)
project(VisualNovelConstruct)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread -lX11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(lib/rapidxml-1.13)

set(SFML_DIR lib/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

set(GUI_CLASSES GameGUI BaseAnimObject AnimRectWithText Background Person PhraseTextArea Button)
set(LOGIC_CLASSES GameLogic Reader)

set(GUI_INCLUDES ${GUI_CLASSES})
set(GUI_SOURCES ${GUI_CLASSES})
set(LOGIC_INCLUDES ${LOGIC_CLASSES})
set(LOGIC_SOURCES ${LOGIC_CLASSES})

list(TRANSFORM GUI_INCLUDES PREPEND include/gui/)
list(TRANSFORM GUI_INCLUDES APPEND .hpp)
list(TRANSFORM GUI_SOURCES PREPEND src/gui/)
list(TRANSFORM GUI_SOURCES APPEND .cpp)

list(TRANSFORM LOGIC_INCLUDES PREPEND include/logic/)
list(TRANSFORM LOGIC_INCLUDES APPEND .hpp)
list(TRANSFORM LOGIC_SOURCES PREPEND src/logic/)
list(TRANSFORM LOGIC_SOURCES APPEND .cpp)

add_executable(VisualNovelConstruct src/main.cpp ${GUI_INCLUDES} ${GUI_SOURCES} ${LOGIC_INCLUDES} ${LOGIC_SOURCES})

target_link_libraries(VisualNovelConstruct PRIVATE sfml-graphics sfml-audio -lX11)
target_include_directories(VisualNovelConstruct PRIVATE include/gui include/logic lib)
