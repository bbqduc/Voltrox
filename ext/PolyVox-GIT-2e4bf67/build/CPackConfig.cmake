# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. Example variables are:
#   CPACK_GENERATOR                     - Generator used to create package
#   CPACK_INSTALL_CMAKE_PROJECTS        - For each project (path, name, component)
#   CPACK_CMAKE_GENERATOR               - CMake Generator used for the projects
#   CPACK_INSTALL_COMMANDS              - Extra commands to install components
#   CPACK_INSTALLED_DIRECTORIES           - Extra directories to install
#   CPACK_PACKAGE_DESCRIPTION_FILE      - Description file for the package
#   CPACK_PACKAGE_DESCRIPTION_SUMMARY   - Summary of the package
#   CPACK_PACKAGE_EXECUTABLES           - List of pairs of executables and labels
#   CPACK_PACKAGE_FILE_NAME             - Name of the package generated
#   CPACK_PACKAGE_ICON                  - Icon used for the package
#   CPACK_PACKAGE_INSTALL_DIRECTORY     - Name of directory for the installer
#   CPACK_PACKAGE_NAME                  - Package project name
#   CPACK_PACKAGE_VENDOR                - Package project vendor
#   CPACK_PACKAGE_VERSION               - Package project version
#   CPACK_PACKAGE_VERSION_MAJOR         - Package project version (major)
#   CPACK_PACKAGE_VERSION_MINOR         - Package project version (minor)
#   CPACK_PACKAGE_VERSION_PATCH         - Package project version (patch)

# There are certain generator specific ones

# NSIS Generator:
#   CPACK_PACKAGE_INSTALL_REGISTRY_KEY  - Name of the registry key for the installer
#   CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS - Extra commands used during uninstall
#   CPACK_NSIS_EXTRA_INSTALL_COMMANDS   - Extra commands used during install


SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_NSIS "ON")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_ZIP "OFF")
SET(CPACK_CMAKE_GENERATOR "Visual Studio 10")
SET(CPACK_COMPONENTS_ALL "Unspecified;development;library")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "NSIS")
SET(CPACK_INSTALL_CMAKE_PROJECTS "F:/trol2/trol2/ext/PolyVox-GIT-2e4bf67/build;PolyVox;ALL;/")
SET(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/PolyVox")
SET(CPACK_MODULE_PATH "")
SET(CPACK_NSIS_CONTACT "matt@milliams.com")
SET(CPACK_NSIS_DISPLAY_NAME "PolyVox SDK 0.1.0")
SET(CPACK_NSIS_DISPLAY_NAME_SET "TRUE")
SET(CPACK_NSIS_HELP_LINK "http:\\\\thermite3d.org/phpBB/")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_MODIFY_PATH "ON")
SET(CPACK_NSIS_PACKAGE_NAME "PolyVox SDK 0.1.0")
SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\thermite3d.org")
SET(CPACK_OUTPUT_CONFIG_FILE "F:/trol2/trol2/ext/PolyVox-GIT-2e4bf67/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files (x86)/CMake 2.8/share/cmake-2.8/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "PolyVox SDK")
SET(CPACK_PACKAGE_FILE_NAME "PolyVox SDK-0.1.0-win32")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "PolyVox SDK 0.1.0")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "PolyVox SDK 0.1.0")
SET(CPACK_PACKAGE_NAME "PolyVox SDK")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Thermite 3D Team")
SET(CPACK_PACKAGE_VERSION "0.1.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_RESOURCE_FILE_LICENSE "C:/Program Files (x86)/CMake 2.8/share/cmake-2.8/Templates/CPack.GenericLicense.txt")
SET(CPACK_RESOURCE_FILE_README "C:/Program Files (x86)/CMake 2.8/share/cmake-2.8/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files (x86)/CMake 2.8/share/cmake-2.8/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "ZIP")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "F:/trol2/trol2/ext/PolyVox-GIT-2e4bf67/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "ON")
SET(CPACK_SYSTEM_NAME "win32")
SET(CPACK_TOPLEVEL_TAG "win32")

# Configuration for component "library"

SET(CPACK_COMPONENTS_ALL Unspecified development library)
SET(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "Library")
SET(CPACK_COMPONENT_LIBRARY_DESCRIPTION "The runtime libraries")
SET(CPACK_COMPONENT_LIBRARY_REQUIRED TRUE)

# Configuration for component "development"

SET(CPACK_COMPONENTS_ALL Unspecified development library)
SET(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "Development")
SET(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION "Files required for developing with PolyVox")
SET(CPACK_COMPONENT_DEVELOPMENT_DEPENDS library)

# Configuration for component "example"

SET(CPACK_COMPONENTS_ALL Unspecified development library)
SET(CPACK_COMPONENT_EXAMPLE_DISPLAY_NAME "OpenGL Example")
SET(CPACK_COMPONENT_EXAMPLE_DESCRIPTION "A PolyVox example application using OpenGL")
SET(CPACK_COMPONENT_EXAMPLE_DEPENDS library)

# Configuration for component group "bindings"
SET(CPACK_COMPONENT_GROUP_BINDINGS_DISPLAY_NAME "Bindings")
SET(CPACK_COMPONENT_GROUP_BINDINGS_DESCRIPTION "Language bindings")

# Configuration for component "python"

SET(CPACK_COMPONENTS_ALL Unspecified development library)
SET(CPACK_COMPONENT_PYTHON_DISPLAY_NAME "Python Bindings")
SET(CPACK_COMPONENT_PYTHON_DESCRIPTION "PolyVox bindings for the Python language")
SET(CPACK_COMPONENT_PYTHON_GROUP bindings)
SET(CPACK_COMPONENT_PYTHON_DEPENDS library)
SET(CPACK_COMPONENT_PYTHON_DISABLED TRUE)
