cmake_minimum_required(VERSION 3.16)
project(metroidvania C)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(
  ${CMAKE_SOURCE_DIR}/include 
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/lib/libglfw.3.dylib
)

target_link_options(${PROJECT_NAME} PRIVATE
  "LINKER:-rpath,${CMAKE_SOURCE_DIR}/lib"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets

  COMMAND codesign --force --sign - --timestamp=none
  ${CMAKE_SOURCE_DIR}/lib/libglfw.3.dylib

  COMMAND codesign --force --sign - --timestamp=none
  $<TARGET_FILE:${PROJECT_NAME}>
)

