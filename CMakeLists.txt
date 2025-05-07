cmake_minimum_required(VERSION 4.0)

project(spacetree VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ERASED_DIR CACHE FILEPATH "Location of Erased dependency (default to submodule)")

find_package(glm CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)
find_package(Catch2 CONFIG REQUIRED)

set(AMALGAMATE_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/scripts/amalgamate.sh)
set(AMALGAMATED_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/spacetree/spacetree_amalgamated.h)
add_custom_command(
    OUTPUT ${AMALGAMATED_HEADER}
    COMMAND ${CMAKE_COMMAND} -E env ERASED_DIR=${ERASED_DIR} bash ${AMALGAMATE_SCRIPT}
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/spacetree/spacetree.h
        ${ERASED_DIR}/erased/include/erased/erased.h
        ${ERASED_DIR}/erased/include/erased/utils/utils.h
    COMMENT "Generating spacetree_amalgamated.h"
    VERBATIM
)
add_custom_target(generate_amalgamated DEPENDS ${AMALGAMATED_HEADER})

enable_testing()
add_subdirectory(tests)
