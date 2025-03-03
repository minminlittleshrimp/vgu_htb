cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "-no-pie -fno-pie -fno-stack-protector -z execstack -Wl,-z,norelro -g -O0")        ## Don't Optimize
project(AttackDLT)

find_package(PkgConfig)
pkg_check_modules(DLT REQUIRED automotive-dlt)

include_directories("${DLT_INCLUDE_DIRS}")

add_executable(dlt_vuln dlt_vuln.c)

target_link_libraries(dlt_vuln ${DLT_LIBRARIES})
