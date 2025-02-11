cmake_minimum_required(VERSION 3.20)

set(target_name pendict)
add_executable(${target_name})


file(GLOB_RECURSE SRC_FILES
    main.c
)
add_subdirectory(ui)

target_sources(${target_name} PRIVATE ${SRC_FILES})
set(LINK_SCRIPTS "-T/home/listenai/Develop/GUI/LVGL/lvgl_sdl_simulator/app/pendict/ui/lisaui_apps.ld")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z separate-code")

target_link_libraries(
    ${target_name}
    PRIVATE
    ${SDL2_LIBRARIES} 
    -lm 
    -lpthread
    -ldl
    # -L/usr/local/lib -lfreetype
    lv_drivers
    ui
    ${LINK_SCRIPTS}
)

# set(CMAKE_VERBOSE_MAKEFILE ON)