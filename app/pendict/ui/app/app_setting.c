#include "app_setting.h"

#include "incbin.h"

#include "../ui.h"
#include "../utils/lv_img_utils.h"


// Setting App
lv_obj_t * uiAppSetting;
lv_obj_t * uiAppSetting_LabelBacklight;
lv_obj_t * uiAppSetting_LabelVolume;
lv_obj_t * uiAppSetting_SliderBacklight;
lv_obj_t * uiAppSetting_SliderVolume;


static const lv_font_t * font_normal;
static ui_set_backlight_cb_t backlight_update_cb = NULL;
static ui_set_volume_cb_t volume_update_cb = NULL;

void ui_register_set_backlight_cb(ui_set_backlight_cb_t update_handler)
{
    backlight_update_cb = update_handler;
}
void ui_register_set_volume_cb(ui_set_volume_cb_t update_handler)
{
    volume_update_cb = update_handler;
}


static void ui_event_SliderHandler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_coord_t *s = lv_event_get_param(e);
        *s = LV_MAX(*s, 60);
    } else if(code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
        if(dsc->part == LV_PART_KNOB && lv_obj_has_state(obj, LV_STATE_PRESSED)) {
            char buf[8];
            lv_snprintf(buf, sizeof(buf), "%"LV_PRId32, lv_slider_get_value(obj));

            lv_point_t text_size;
            lv_txt_get_size(&text_size, buf, font_normal, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

            lv_area_t txt_area;
            txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - text_size.x / 2;
            txt_area.x2 = txt_area.x1 + text_size.x;
            txt_area.y2 = dsc->draw_area->y1 - 10;
            txt_area.y1 = txt_area.y2 - text_size.y;

            lv_area_t bg_area;
            bg_area.x1 = txt_area.x1 - LV_DPX(8);
            bg_area.x2 = txt_area.x2 + LV_DPX(8);
            bg_area.y1 = txt_area.y1 - LV_DPX(8);
            bg_area.y2 = txt_area.y2 + LV_DPX(8);

            lv_draw_rect_dsc_t rect_dsc;
            lv_draw_rect_dsc_init(&rect_dsc);
            rect_dsc.bg_color = lv_palette_darken(LV_PALETTE_GREY, 3);
            rect_dsc.radius = LV_DPX(5);
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &bg_area);

            lv_draw_label_dsc_t label_dsc;
            lv_draw_label_dsc_init(&label_dsc);
            label_dsc.color = lv_color_white();
            label_dsc.font = font_normal;
            lv_draw_label(dsc->draw_ctx, &label_dsc, &txt_area, buf, NULL);
        }
    } else if(code == LV_EVENT_VALUE_CHANGED) {
        if (obj == uiAppSetting_SliderBacklight) {
            if (backlight_update_cb) {
                backlight_update_cb(lv_slider_get_value(obj));
            }
        } else if (obj == uiAppSetting_SliderVolume) {
            if (volume_update_cb) {
                volume_update_cb(lv_slider_get_value(obj));
            }
        }
    }
}


void app_setting_create(lv_obj_t * parent)
{
    uiAppSetting = lv_obj_create(NULL);
    lv_obj_clear_flag(uiAppSetting, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiAppSetting, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiAppSetting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(uiAppSetting, SCREEN_WIDTH, 180);

    uiAppSetting_LabelBacklight = lv_label_create(uiAppSetting);
    lv_obj_set_size(uiAppSetting_LabelBacklight, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_align(uiAppSetting_LabelBacklight, LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(uiAppSetting_LabelBacklight, 30, 0);
    lv_label_set_text(uiAppSetting_LabelBacklight, "亮度");
    lv_obj_set_style_text_color(uiAppSetting_LabelBacklight, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiAppSetting_LabelBacklight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(uiAppSetting_LabelBacklight, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiAppSetting_SliderBacklight = lv_slider_create(uiAppSetting);
    lv_obj_set_size(uiAppSetting_SliderBacklight, SCREEN_WIDTH*0.7, 16);
    lv_obj_set_pos(uiAppSetting_SliderBacklight, 22, 0);
    lv_obj_set_align(uiAppSetting_SliderBacklight, LV_ALIGN_CENTER);
    lv_slider_set_value(uiAppSetting_SliderBacklight, 100, LV_ANIM_OFF);
    lv_slider_set_range(uiAppSetting_SliderBacklight, UI_SILDER_BACKLIGHT_BRIGHTNESS_MIN_VALUE, UI_SILDER_BACKLIGHT_BRIGHTNESS_MAX_VALUE);
    lv_obj_set_style_bg_color(uiAppSetting_SliderBacklight, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiAppSetting_SliderBacklight, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    uiAppSetting_LabelVolume = lv_label_create(uiAppSetting);
    lv_obj_set_size(uiAppSetting_LabelVolume, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_align(uiAppSetting_LabelVolume, LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(uiAppSetting_LabelVolume, 30, 40);
    lv_label_set_text(uiAppSetting_LabelVolume, "音量");
    lv_obj_set_style_text_color(uiAppSetting_LabelVolume, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiAppSetting_LabelVolume, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(uiAppSetting_LabelVolume, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiAppSetting_SliderVolume = lv_slider_create(uiAppSetting);
    lv_obj_set_size(uiAppSetting_SliderVolume,  SCREEN_WIDTH*0.7, 16);
    lv_obj_set_pos(uiAppSetting_SliderVolume, 22, 40);
    lv_obj_set_align(uiAppSetting_SliderVolume, LV_ALIGN_CENTER);
    lv_slider_set_value(uiAppSetting_SliderVolume, 8, LV_ANIM_OFF);
    lv_slider_set_range(uiAppSetting_SliderVolume, UI_SILDER_VOLUME_MIN_VALUE, UI_SILDER_VOLUME_MAX_VALUE);
    lv_obj_set_style_bg_color(uiAppSetting_SliderVolume, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiAppSetting_SliderVolume, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    font_normal = LV_FONT_DEFAULT;
    lv_obj_add_event_cb(uiAppSetting_SliderBacklight, ui_event_SliderHandler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(uiAppSetting_SliderVolume, ui_event_SliderHandler, LV_EVENT_ALL, NULL);
}


lv_obj_t * app_setting_get_page(void)
{
    return uiAppSetting;
}