# Install script for directory: C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/thirdParty/spade-engine/thirdParty/ldtk

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/install/GCC 14.2.0 x86_64-w64-mingw32")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/LDtkLoader" TYPE FILE FILES
    "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/thirdParty/spade-engine/thirdParty/ldtk/LICENSE.md"
    "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/thirdParty/spade-engine/thirdParty/ldtk/README.md"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/thirdParty/spade-engine/thirdParty/ldtk/include/LDtkLoader")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/include/LDtkLoader")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/lib/Debug/LDtkLoader-d.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/lib/Release/LDtkLoader.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/lib/MinSizeRel/LDtkLoader.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/lib/RelWithDebInfo/LDtkLoader.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader/LDtkLoaderTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader/LDtkLoaderTargets.cmake"
         "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/CMakeFiles/Export/f9647eb62aabc71d50658ff864394ae9/LDtkLoaderTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader/LDtkLoaderTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader/LDtkLoaderTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader" TYPE FILE FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/CMakeFiles/Export/f9647eb62aabc71d50658ff864394ae9/LDtkLoaderTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader" TYPE FILE FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/CMakeFiles/Export/f9647eb62aabc71d50658ff864394ae9/LDtkLoaderTargets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader" TYPE FILE FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/CMakeFiles/Export/f9647eb62aabc71d50658ff864394ae9/LDtkLoaderTargets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader" TYPE FILE FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/CMakeFiles/Export/f9647eb62aabc71d50658ff864394ae9/LDtkLoaderTargets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader" TYPE FILE FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/CMakeFiles/Export/f9647eb62aabc71d50658ff864394ae9/LDtkLoaderTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader" TYPE FILE FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/LDtkLoaderConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/LDtkLoader" TYPE FILE FILES "C:/Users/Iustin/Documents/PROJECTS/_C++/SPADE-ENGINE/out/build/GCC 14.2.0 x86_64-w64-mingw32/thirdParty/spade-engine/thirdParty/ldtk/LDtkLoaderConfigVersion.cmake")
endif()

