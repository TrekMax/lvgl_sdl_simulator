
SET(SOURCES 
    ui.c
    screen/aweui_status_bar.c
    screen/aweui_chat_btn_group.c
    screen/aweui_screen_standby.c
    screen/aweui_screen_bar_setting.c
    screen/aweui_screen_camera.c
    screen/aweui_screen_network.c
    screen/aweui_screen_llm_chat.c
    screen/screen_switch.c

    # theme/lv_theme_ultra_marine.c

    widgets/radio_button.c
    widgets/floating_button.c
    widgets/radio_group.c
    widgets/llm_dialog.c
    
    utils/img_utils.c
    utils/lv_img_utils.c

    aweui_event.c
)

SET(ASSETS_FONT
    assets/fonts/lv_font_chinese_14.c
    assets/fonts/lv_font_notosans_cs_medium_18.c
    # assets/fonts/lv_font_chinese_26.c

    assets/fonts/lv_font_clock_word.c
    assets/fonts/lv_font_screen_word.c
)

SET(ASSETS_IMG
    assets/xiaoling_listening_s.c
    assets/xiaoling_standby_s.c
    assets/xiaoling_thinking_s.c
    assets/wifi_tool_qrcode.c
    assets/icon_music.c
    assets/btn_camera_active.c
    assets/btn_voice_active.c
    assets/btn_camera_l_active.c


    assets/btn_flipcamera.c
    assets/btn_takephoto_48.c
    assets/btn_takephoto_56.c
    assets/btn_tick_48.c
    assets/btn_tick_56.c


    assets/btn_cross.c
    assets/btn_flipcamera.c
    assets/btn_takephoto_48.c
    assets/btn_takephoto_56.c
    assets/btn_tick_48.c
    assets/btn_tick_56.c
    assets/btn_withdraw.c
    assets/ic_brightness_high.c
    assets/ic_brightness_low.c
    assets/ic_cross.c
    assets/ic_filpcamera.c
    assets/ic_launch_camera.c
    assets/ic_launch_setting.c
    assets/ic_launch_voice.c
    assets/ic_nav_home.c
    assets/ic_radio_off.c
    assets/ic_radio_on.c
    assets/ic_status_wifi0.c
    assets/ic_status_wifi1.c
    assets/ic_tick.c
    assets/ic_volumn_high.c
    assets/ic_volumn_low.c
    assets/ic_warning.c
    assets/anim_loading.c
    assets/anim_speak.c
    assets/btn_camera_active.c
    assets/btn_voice_active.c
    assets/btn_camera_l_active.c
    assets/anim_circle.c
)

if(DEFINED ENV{ZEPHYR_BASE})
  message(STATUS "Building with Zephyr")
  zephyr_include_directories(./)
  zephyr_library_sources(${SOURCES} ${ASSETS_FONT} ${ASSETS_IMG})
else()
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/screen
        # ${CMAKE_CURRENT_SOURCE_DIR}/theme
        ${CMAKE_CURRENT_SOURCE_DIR}/widgets
        )

    add_library(aweui ${SOURCES} ${ASSETS_FONT} ${ASSETS_IMG})
endif()
