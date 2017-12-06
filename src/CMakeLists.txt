
add_subdirectory(resources)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wextra")
  # -fno-rtti, Disable real-time type information
  # -fno-exceptions Disable exceptions
  # -fsanitize=address Enable memory sanitize plugin
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -Wextra -fno-exceptions")
  # -fsanitize=address, Enable memory address sanitizer.
  #  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  # -fsanitize=leak, Enable memory leak sanitizer.
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
  # -fsanitize=memory, Enable detecting uninitited memory sanitizer.
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory "
  #    "-fsanitize-memory-track-origins -fPIC -pie -fno-omit-frame-pointer")

  #  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wimplicit-fallthrough=1")

  # Enable Qt builtin debug mode
  add_definitions("-DQT_MESSAGELOGCONTEXT")
else()
  # -Wl, -O2 Enable linker optimizations
  #-Wl, --gc-sections Remove unused code resulting from -fdsta-sections and -ffunction-sections
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -Wl,-O1 -Wl,--gc-sections")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wl,-O1 -Wl,--gc-sections -Wno-unused-result")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(INSTALLER_SHARE_DIR ${CMAKE_INSTALL_PREFIX}/share/deepin-lang-selector)

# Defines path to resource directories
if (CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions("-DBUILTIN_HOOKS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/hooks\"")
  add_definitions("-DI18N_DIR=\"${CMAKE_CURRENT_BINARY_DIR}/i18n\"")
  add_definitions("-DRESOURCES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/resources\"")
  add_definitions("-DTOOLS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/tools\"")
else()
  add_definitions("-DN_DEBUG")
  add_definitions("-DBUILTIN_HOOKS_DIR=\"${INSTALLER_SHARE_DIR}/hooks\"")
  add_definitions("-DI18N_DIR=\"${INSTALLER_SHARE_DIR}/i18n\"")
  add_definitions("-DRESOURCES_DIR=\"${INSTALLER_SHARE_DIR}/resources\"")
  add_definitions("-DTOOLS_DIR=\"${INSTALLER_SHARE_DIR}/tools\"")
endif()

find_package(PkgConfig REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5X11Extras REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5LinguistTools)

set(Qt_LIBS
    Qt5::Gui
    Qt5::Network
    Qt5::Widgets
    Qt5::X11Extras
    Qt5::Xml
    )

set(SRC_FILES
    main.cpp

    base/consts.h
    base/command.cpp
    base/command.h
    base/file_util.cpp
    base/file_util.h

    service/settings_manager.cpp
    service/settings_manager.h
    service/settings_name.h
    service/system_language.cpp
    service/system_language.h

    ui/main_window.cpp
    ui/main_window.h
    ui/delegates/frameless_list_delegate.cpp
    ui/delegates/frameless_list_delegate.h
    ui/delegates/language_delegate.cpp
    ui/delegates/language_delegate.h
    ui/frames/select_language_frame.cpp
    ui/frames/select_language_frame.h
    ui/models/language_list_model.cpp
    ui/models/language_list_model.h
    ui/utils/widget_util.cpp
    ui/utils/widget_util.h
    ui/views/frameless_list_view.cpp
    ui/views/frameless_list_view.h
    ui/widgets/flat_button.cpp
    ui/widgets/flat_button.h
    ui/widgets/nav_button.cpp
    ui/widgets/nav_button.h
    ui/widgets/pointer_button.cpp
    ui/widgets/pointer_button.h

    ui/images/images.qrc
    ui/styles/styles.qrc
    )

# Generate .qm files from .ts files.
file(GLOB INSTALLER_TRANSLATION_TS
     ${CMAKE_CURRENT_SOURCE_DIR}/i18n/installer-*.ts)
set_source_files_properties(${INSTALLER_TRANSLATION_TS}
                            PROPERTIES OUTPUT_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/i18n)
qt5_add_translation(INSTALLER_TRANSLATION_QM ${INSTALLER_TRANSLATION_TS})
add_custom_target(installer-qm-update DEPENDS ${INSTALLER_TRANSLATION_QM})

add_executable(deepin-lang-selector ${SRC_FILES})
target_link_libraries(deepin-lang-selector ${Qt_LIBS})
add_dependencies(deepin-lang-selector installer-qm-update)

install(TARGETS deepin-lang-selector
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)