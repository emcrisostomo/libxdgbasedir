cmake_minimum_required(VERSION 3.8)
project(libxdgbasedir VERSION 1.2.0)

#@formatter:off
set(PACKAGE           "libxdgbasedir")
set(PACKAGE_NAME      "${PACKAGE}")
set(PACKAGE_VERSION   "${PROJECT_VERSION}-develop")
set(PACKAGE_STRING    "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_AUTHOR    "enrico.m.crisostomo@gmail.com")
set(PACKAGE_BUGREPORT "${PACKAGE_AUTHOR}")
set(PACKAGE_TARNAME   "${PACKAGE}")
set(PACKAGE_URL       "https://github.com/emcrisostomo/${PACKAGE}")
set(LOCALEDIR         "${CMAKE_INSTALL_PREFIX}/share/locale" CACHE FILEPATH "locale dir")
#@formatter:on

set(CMAKE_CXX_STANDARD 14)

set(
        LIBXDGBASEDIR_HEADER_FILES
        src/libxdgbasedir/gettext.h
        src/libxdgbasedir/gettext_defs.h
        src/libxdgbasedir/libxdgbasedir.h
)

set(
        LIBXDGBASEDIR_SOURCE_FILES
        src/libxdgbasedir/libxdgbasedir.cpp
        ${LIBXDGBASEDIR_HEADER_FILES}
)

add_library(libxdgbasedir ${LIBXDGBASEDIR_SOURCE_FILES})
set_target_properties(libxdgbasedir PROPERTIES OUTPUT_NAME xdgbasedir)
target_include_directories(libxdgbasedir PUBLIC src)

# Add option to choose between shared and static libraries
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# include modules
include(FindGettext)
include(FindIntl)
include(CheckIncludeFileCXX)
include(CheckSymbolExists)

include_directories("${PROJECT_BINARY_DIR}")
if (Intl_LIBRARIES)
	include_directories("${Intl_INCLUDE_DIRS}")
endif ()

# check for gettext and libintl
check_include_file_cxx(getopt.h HAVE_GETOPT_H)

if (HAVE_GETOPT_H)
    check_symbol_exists(getopt_long getopt.h HAVE_GETOPT_LONG)
endif (HAVE_GETOPT_H)

# If both gettext and libintl are found, define the USE_NLS variable to
# optionally disable them
if (Intl_FOUND AND GETTEXT_FOUND)
    option(USE_NLS "Use NLS" ON)
endif ()

if (USE_NLS)
    set(ENABLE_NLS 1)

    if (Intl_LIBRARIES)
        target_link_libraries(libxdgbasedir ${Intl_LIBRARIES})
    endif ()

    # gettext configuration
    set(LINGUAS en en@quot en@boldquot it es)

    foreach (language ${LINGUAS})
        configure_file(${PROJECT_SOURCE_DIR}/po/${language}.po ${PROJECT_BINARY_DIR}/${language}.po COPYONLY)
    endforeach ()

    gettext_process_pot_file(po/${PACKAGE}.pot ALL INSTALL_DESTINATION share/locale LANGUAGES ${LINGUAS})
endif ()

# install targets
install(TARGETS libxdgbasedir DESTINATION lib)
install(FILES ${LIBXDGBASEDIR_HEADER_FILES} DESTINATION include/libxdgbasedir)

# testing
include(CTest)

add_executable(libxdgbasedir-printall test/libxdgbasedir-printall.cpp)
target_link_libraries(libxdgbasedir-printall libxdgbasedir)
add_test(libxdgbasedir-printall libxdgbasedir-printall)

add_executable(libxdgbasedir-check-values test/libxdgbasedir-check-values.cpp)
target_link_libraries(libxdgbasedir-check-values libxdgbasedir)
add_test(libxdgbasedir-check-values libxdgbasedir-check-values)

# installer
include(InstallRequiredSystemLibraries)
#@formatter:off
# Remove and default to project description when migrated to CMake 3.9
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple C++ implementation of the XDG Base Directory Specification")
set(CPACK_PACKAGE_VERSION_MAJOR       "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR       "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH       "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR              "${PACKAGE_AUTHOR}")
set(CPACK_RESOURCE_FILE_LICENSE       "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_GENERATOR                   "STGZ;TGZ")
#@formatter:on
include(CPack)
