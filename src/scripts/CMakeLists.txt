# Install resources/ folder, excluding desktop file and icons.

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/session.wrapper
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/deepin-lang-selector/
        PERMISSIONS
        OWNER_READ OWNER_EXECUTE OWNER_WRITE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
        )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/1050-deepin-lang-selector
        DESTINATION /lib/live/config
        PERMISSIONS
        OWNER_READ OWNER_EXECUTE OWNER_WRITE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
        )
