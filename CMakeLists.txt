cmake_minimum_required(VERSION 2.8)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

project(ContourToSurfaceRegistration)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/src)

include(CTest)

if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
endif(NOT LIBRARY_OUTPUT_PATH)

if(NOT EXECUTABLE_OUTPUT_PATH)
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")
endif(NOT EXECUTABLE_OUTPUT_PATH)

mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH} ${EXECUTABLE_OUTPUT_PATH})

include(${PROJECT_SOURCE_DIR}/CMake/ExternalData.cmake)
list(APPEND ExternalData_URL_TEMPLATES
  "file://local/home/ibanez/data/INCF/WHS/%(algo)/%(hash)"
  "http://midas.kitware.com/api/rest/midas.bitstream.by.hash?hash=%(hash)&algorithm=%(algo)"
  )

add_subdirectory(src)
add_subdirectory(test)

ExternalData_Add_Target(WHSData)
