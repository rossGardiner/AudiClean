#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dnf" for configuration ""
set_property(TARGET dnf APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(dnf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libdnf.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS dnf )
list(APPEND _IMPORT_CHECK_FILES_FOR_dnf "${_IMPORT_PREFIX}/lib/libdnf.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
