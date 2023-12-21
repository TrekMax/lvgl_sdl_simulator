SET(SOURCES 
    src/lv_100ask_board_about/lv_100ask_board_about.c
    src/lv_100ask_boot_animation/assets/img_lv_100ask_demo_logo.c
    src/lv_100ask_demo/assets/img_lv_100ask_bg.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_2048.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_about_us.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_calc.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_camera.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_data.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_floder.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_humiture.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_music.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_QRcode.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_regbit.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_setting.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_snake.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_tetris.c
    src/lv_100ask_demo/assets/img_lv_100ask_icon_widgets.c
    src/lv_100ask_demo/lv_100ask_demo.c
    src/lv_100ask_game_2048/lv_100ask_game_2048.c
    src/lv_100ask_game_snake/lv_100ask_game_snake.c
    src/lv_100ask_tool_calc/lv_100ask_tool_calc.c
    src/lv_100ask_tool_clock/assets/img_hand.c
    src/lv_100ask_tool_clock/lv_100ask_tool_clock.c
    src/lv_100ask_tool_qrcode/lv_100ask_tool_qrcode.c
    src/lv_100ask_tool_regbit/lv_100ask_tool_regbit.c
    src/lv_100ask_tool_settings/lv_100ask_tool_settings.c
    src/lv_100ask_boot_animation/lv_100ask_boot_animation.c
    )
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    # ${CMAKE_CURRENT_SOURCE_DIR}/screens
    # ${CMAKE_CURRENT_SOURCE_DIR}/launcher

    lv_100ask_board_about/lv_100ask_board_about.h
    lv_100ask_demo/assets/lv_100ask_demo.h
    lv_100ask_game_2048/lv_100ask_game_2048.h
    lv_100ask_game_snake/lv_100ask_game_snake.h
    lv_100ask_tool_calc/lv_100ask_tool_calc.h
    lv_100ask_tool_clock/lv_100ask_tool_clock.h
    lv_100ask_tool_qrcode/lv_100ask_tool_qrcode.h
    lv_100ask_tool_regbit/lv_100ask_tool_regbit.h
    lv_100ask_tool_settings/lv_100ask_tool_settings.h
    )

# add_subdirectory(lv)
# add_subdirectory(lv_100ask_board_about)
# add_subdirectory(lv_100ask_boot_animation)
# add_subdirectory(lv_100ask_demo)
# add_subdirectory(lv_100ask_game_2048)
# add_subdirectory(lv_100ask_game_snake)
# add_subdirectory(lv_100ask_tool_calc)
# add_subdirectory(lv_100ask_tool_clock)
# add_subdirectory(lv_100ask_tool_qrcode)
# add_subdirectory(lv_100ask_tool_regbit)
# add_subdirectory(lv_100ask_tool_settings)
add_library(ui ${SOURCES})
