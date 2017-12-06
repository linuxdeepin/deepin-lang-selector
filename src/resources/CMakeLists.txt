# Install resources/ folder, excluding desktop file and icons.

install(
    FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/default_wallpaper.jpg
    ${CMAKE_CURRENT_SOURCE_DIR}/languages.json
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-lang-selector/resources
)
