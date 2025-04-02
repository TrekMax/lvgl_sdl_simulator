// #include "../../lv_examples.h"
#include "lisaui_app_common.h"

#if LV_BUILD_EXAMPLES
#if LV_USE_FREETYPE

static const char *TAG = "lv_example_freetype_1";

/**
 * Load a font with FreeType
 */
void lv_example_freetype_1(lv_obj_t *parent)
{
    LISAUI_LOGI(TAG, "lv_example_freetype_1");
    /*Create a font*/
    static lv_ft_info_t info;
    /*FreeType uses C standard file system, so no driver letter is required.*/
    // info.name = "./lvgl/examples/libs/freetype/Lato-Regular.ttf";
    // info.name = "app/app_manager/lisaui/app/app_lvgl_demo/freetype/fonts/Lato-Regular.ttf";
    info.name = "app/app_manager/lisaui/app/app_lvgl_demo/freetype/fonts/SourceHanSerifSC-Regular.otf";
    info.weight = 48;
    info.style = FT_FONT_STYLE_NORMAL;
    info.mem = NULL;
    if(!lv_ft_font_init(&info)) {
        LV_LOG_ERROR("create failed.");
        LISAUI_LOGE(TAG, "create failed.");
        return;
    }

    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, info.font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_text_color(&style, lv_color_hex(0xFFFFFF));

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(parent);
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Hello world\nI'm a font created with FreeType");
    lv_obj_center(label);

    lv_obj_t *label2 = lv_label_create(parent);
    lv_label_set_text(label2, "SourceHanSerifSC-Regular.otf");
    lv_obj_add_style(label2, &style, 0);
    lv_obj_set_style_text_font(label2, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 100);
}
#else

void lv_example_freetype_1(void)
{
    /*TODO
     *fallback for online examples*/

    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "FreeType is not installed");
    lv_obj_center(label);
}

#endif
#endif
