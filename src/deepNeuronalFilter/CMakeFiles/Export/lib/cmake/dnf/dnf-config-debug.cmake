#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dnf" for configuration "Debug"
set_property(TARGET dnf APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(dnf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libdnf.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS dnf )
list(APPEND _IMPORT_CHECK_FILES_FOR_dnf "${_IMPORT_PREFIX}/lib/libdnf.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
