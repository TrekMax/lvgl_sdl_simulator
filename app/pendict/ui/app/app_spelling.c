#include "app_spelling.h"

#include "incbin.h"

#include "../ui.h"
#include "../utils/lv_img_utils.h"

static lv_style_t style_text_muted;
static lv_style_t style_icon;
static lv_style_t style_title;

#define LV_SYMBOL_PNG_FILE_PATH "A:/img/logo-m2.png"
#define LV_SYMBOL_GIF_FILE_PATH_1 "A:/img/8046.gif"
#define LV_SYMBOL_GIF_FILE_PATH_2 "A:/img/601D.gif"
#define LV_SYMBOL_GIF_FILE_PATH_3 "A:/img/79D1.gif"
#define LV_SYMBOL_GIF_FILE_PATH_4 "A:/img/6280.gif"

static lv_img_dsc_t img_png1;
INCBIN(img_png1, "app/pendict/ui/assets/img/logo-m2.png");

static lv_img_dsc_t img_gif1;
INCBIN(img_gif1, "app/pendict/ui/assets/img/00a3758.gif");
static lv_img_dsc_t img_gif2;
INCBIN(img_gif2, "app/pendict/ui/assets/img/00b39b6.gif");

static lv_img_dsc_t img_jpg1;
INCBIN(img_jpg1, "app/pendict/ui/assets/img/Meisje.jpg");

void app_spelling_create(lv_obj_t * parent)
{
    lv_obj_t * img, *img2, *img3, *img4, *img_jpg;
    lv_obj_t * lv_img_logo;

#if 1
    // /*Create the second panel*/
    lv_obj_t * panel2 = lv_obj_create(parent);
    lv_obj_set_style_bg_color(panel2, lv_color_hex(0x000FF0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(panel2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_height(panel2, LV_SIZE_CONTENT);
    lv_obj_set_pos(panel2, 10, 30);
    lv_obj_set_width(panel2, SCREEN_WIDTH-180);

    lv_img_logo = lv_img_create(panel2);
    // lv_img_set_src(lv_img_logo, LV_SYMBOL_PNG_FILE_PATH);
    lv_img_png_src_init(&img_png1, gimg_png1Data, gimg_png1Size);
    lv_img_set_src(lv_img_logo, &img_png1);

    img_jpg = lv_img_create(panel2);
    // lv_gif_set_src(img, LV_SYMBOL_GIF_FILE_PATH_1);
    lv_img_jpg_src_init(&img_jpg1, gimg_jpg1Data, gimg_jpg1Size);
    lv_img_set_src(img_jpg, &img_jpg1);
    lv_obj_align(img_jpg, LV_ALIGN_LEFT_MID, 100, 0);
    // lv_obj_set_size(img, 160, 160);
    // lv_img_set_zoom(img_jpg, 120);

    img = lv_gif_create(panel2);
    // lv_gif_set_src(img, LV_SYMBOL_GIF_FILE_PATH_1);
    lv_img_gif_src_init(&img_gif1, gimg_gif1Data, gimg_gif1Size);
    lv_gif_set_src(img, &img_gif1);
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 260, 0);
    // lv_obj_set_size(img, 160, 160);
    // lv_img_set_zoom(img, 120);

    img2 = lv_gif_create(panel2);
    // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    lv_img_gif_src_init(&img_gif2, gimg_gif2Data, gimg_gif2Size);
    lv_gif_set_src(img2, &img_gif2);
    lv_obj_align(img2, LV_ALIGN_LEFT_MID, 260+120, 0);
    // lv_obj_set_size(img2, 160, 160);
    // lv_img_set_zoom(img2, 120);

    // img3 = lv_gif_create(panel2);
    // lv_gif_set_src(img3, LV_SYMBOL_GIF_FILE_PATH_3);
    // lv_obj_align(img3, LV_ALIGN_LEFT_MID, 260+200, 0);
    // // lv_obj_set_size(img3, 160, 160);
    // lv_img_set_zoom(img3, 120);

    // img4 = lv_gif_create(panel2);
    // lv_gif_set_src(img4, LV_SYMBOL_GIF_FILE_PATH_4);
    // lv_obj_align(img4, LV_ALIGN_LEFT_MID, 380+200, 0);
    // // lv_obj_set_size(img4, 160, 160);
    // lv_img_set_zoom(img4, 120);

    lv_obj_t * uiLabResult;
    uiLabResult = lv_textarea_create(panel2);
    lv_obj_set_size(uiLabResult, SCREEN_WIDTH*0.8, 100);
    // lv_obj_set_pos(uiLabResult, 20, 20);
    // lv_obj_set_align(uiLabResult, LV_ALIGN_LEFT_MID);
    lv_obj_align(uiLabResult, LV_ALIGN_LEFT_MID, 260+240, 0);
    lv_obj_set_style_text_font(uiLabResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_text(uiLabResult, "支持更大容量的高速和片外，支持用户配置数据缓存与指令缓存。带宽；其低功耗蓝牙子系统支持可通过与广播扩展实现远距离通信。它还支持 2 Mbps PHY，用于提高传输速度和数据吞吐量。Listenai-ARCS 的 Wi-Fi 和 Bluetooth LE 射频性能优越，在高温下也能稳定工作。.");
    // lv_textarea_set_placeholder_text(uiLabResult, "量金野支持更大容量的");
    lv_obj_set_style_text_color(uiLabResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiLabResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(uiLabResult, &ui_font_PocketDictPenRegular, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiLabResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiLabResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiLabResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiLabResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

#endif
}
