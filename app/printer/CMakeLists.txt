cmake_minimum_required(VERSION 3.20)

set(target_name launcher)
add_executable(${target_name})


file(GLOB_RECURSE SRC_FILES
    main.c
)

# add_subdirectory(../components/lvgl)
# add_subdirectory(../components/lv_drivers)
add_subdirectory(ui)

target_sources(${target_name} PRIVATE ${SRC_FILES})
target_link_libraries(
    ${target_name}
    PRIVATE
    ${SDL2_LIBRARIES} 
    -lm 
    -lpthread
    -ldl
    lv_drivers
    ui
)


