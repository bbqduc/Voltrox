#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "png15" for configuration "RelWithDebInfo"
SET_PROPERTY(TARGET png15 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
SET_TARGET_PROPERTIES(png15 PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "/usr/lib/libz.so;/usr/lib/libm.so"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libpng15.so.15.11.0"
  IMPORTED_SONAME_RELWITHDEBINFO "libpng15.so.15"
  )

# Import target "png15_static" for configuration "RelWithDebInfo"
SET_PROPERTY(TARGET png15_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
SET_TARGET_PROPERTIES(png15_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "/usr/lib/libz.so;/usr/lib/libm.so"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libpng15.a"
  )

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
