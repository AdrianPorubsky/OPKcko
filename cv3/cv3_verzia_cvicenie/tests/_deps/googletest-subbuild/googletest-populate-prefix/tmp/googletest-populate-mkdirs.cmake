# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-src"
  "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-build"
  "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/adrian/CLionProjects/untitled/OPKcko/cv3/cv3_verzia_cvicenie/tests/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
