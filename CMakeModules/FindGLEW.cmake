# This module defines GLEW_LIBRARY GLEW_FOUND, if false, do not try to link
# GLEW_INCLUDE_DIR, where to find the headers
#
# $GLEW_DIR is an environment variable that would correspond to the ./configure
# --prefix=$GLEW_DIR
#

find_path(
  GLEW_INCLUDE_DIR GL/glew.h
  PATHS $ENV{GLEW_DIR}
  NO_DEFAULT_PATH
  PATH_SUFFIXES include)

find_path(
  GLEW_INCLUDE_DIR GL/glew.h
  PATHS ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/include
        /usr/include
        /sw/include # Fink
        /opt/local/include # DarwinPorts
        /opt/csw/include # Blastwave
        /opt/include
        /usr/freeware/include)

find_library(
  GLEW_LIBRARY
  NAMES glew libglew libGLEW libglew32 libGLEW32
  PATHS $ENV{GLEW_DIR}
  NO_DEFAULT_PATH
  PATH_SUFFIXES lib64 lib)

find_library(
  GLEW_LIBRARY
  NAMES glew libglew libGLEW libglew32 libGLEW32
  PATHS ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        /usr/freeware
  PATH_SUFFIXES lib64 lib)

set(GLEW_FOUND "NO")
if(GLEW_LIBRARY AND GLEW_INCLUDE_DIR)
  set(GLEW_FOUND "YES")
  add_compile_definitions(GLEW_FOUND=1)
endif(GLEW_LIBRARY AND GLEW_INCLUDE_DIR)
