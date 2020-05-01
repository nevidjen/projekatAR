cmake_minimum_required (VERSION 3.10)
project (projekatAR)

set(TARGET_NAME "projectExe")
set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
   )

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

add_subdirectory("${PROJECT_SOURCE_DIR}/include")
add_subdirectory("${PROJECT_SOURCE_DIR}/src")

message(STATUS "HEADERS  ${HEADERS}")
message(STATUS "SOURCES  ${SOURCES}")

add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS})
