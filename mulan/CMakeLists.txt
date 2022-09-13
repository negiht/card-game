cmake_minimum_required(VERSION 3.18)

project(mulan)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(mulan
    src/main.cpp
    src/resource_registry.cpp
    src/game.cpp
    src/sgg_draw_utils.cpp
    src/sgg_selection_helper.cpp
    src/sgg_multi_selection_helper.cpp
    src/phases/loading_phase.cpp
    src/phases/selection_phase.cpp
    src/phases/target_selection_phase.cpp
    src/phases/card_effect_phase.cpp
    src/phases/end_phase.cpp
    src/views/sgg_loading_phase_view.cpp
    src/views/sgg_selection_phase_view.cpp
    src/views/sgg_card_effect_phase_view.cpp
    src/views/sgg_end_phase_view.cpp
    "include/mulan/exitor.hpp"
 )

target_include_directories(mulan
PRIVATE
include
include/mulan
3rdparty/include
3rdparty 
)

target_link_libraries(mulan
PRIVATE
${CMAKE_SOURCE_DIR}/3rdparty/lib/sggd.lib
)

set_target_properties(mulan PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
