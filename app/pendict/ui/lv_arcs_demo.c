#include "lv_arcs_demo.h"

static lv_style_t style_text_muted;
static lv_style_t style_icon;
static lv_style_t style_title;

#include "incbin.h"
#include "utils/lv_img_utils.h"

#define LV_SYMBOL_PNG_FILE_PATH "A:/img/logo-m2.png"
#define LV_SYMBOL_GIF_FILE_PATH_1 "A:/img/8046.gif"
#define LV_SYMBOL_GIF_FILE_PATH_2 "A:/img/601D.gif"
#define LV_SYMBOL_GIF_FILE_PATH_3 "A:/img/79D1.gif"
#define LV_SYMBOL_GIF_FILE_PATH_4 "A:/img/6280.gif"
LV_FONT_DECLARE(lv_font_chinese_18);

static lv_img_dsc_t img_png1;
INCBIN(img_png1, "app/pendict/ui/assets/img/logo-m2.png");

static lv_img_dsc_t img_gif1;
INCBIN(img_gif1, "app/pendict/ui/assets/img/1.gif");
static lv_img_dsc_t img_gif2;
INCBIN(img_gif2, "app/pendict/ui/assets/img/2.gif");

static lv_img_dsc_t img_jpg1;
INCBIN(img_jpg1, "app/pendict/ui/assets/img/Meisje.jpg");

void arcs_demo_create(lv_obj_t * parent)
{
    LV_IMG_DECLARE(img_bulb_gif);
    lv_obj_t * img, *img2, *img3, *img4, *img_jpg;
    lv_obj_t * lv_img_logo;
#if 0
    img = lv_gif_create(lv_scr_act());
    lv_gif_set_src(img, &img_bulb_gif);
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 20, 0);
#endif


#if 1
    lv_style_init(&style_text_muted);
    lv_style_set_text_opa(&style_text_muted, LV_OPA_50);
    lv_style_init(&style_icon);
    lv_style_set_text_color(&style_icon, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_icon, &lv_font_montserrat_24);
    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, &lv_font_montserrat_24);
#if 0
    lv_obj_t * panel1 = lv_obj_create(parent);
    lv_obj_set_height(panel1, LV_SIZE_CONTENT);

    LV_IMG_DECLARE(img_arcs_demo_widgets_avatar);
    lv_obj_t * avatar = lv_img_create(panel1);
    lv_img_set_src(avatar, &img_arcs_demo_widgets_avatar);

    lv_obj_t * name = lv_label_create(panel1);
    lv_label_set_text(name, "Elena Smith");
    lv_obj_add_style(name, &style_title, 0);

    lv_obj_t * dsc = lv_label_create(panel1);
    lv_obj_add_style(dsc, &style_text_muted, 0);
    lv_label_set_text(dsc, "This is a short description of me. Take a look at my profile!");
    lv_label_set_long_mode(dsc, LV_LABEL_LONG_WRAP);

    lv_obj_t * email_icn = lv_label_create(panel1);
    lv_obj_add_style(email_icn, &style_icon, 0);
    lv_label_set_text(email_icn, LV_SYMBOL_ENVELOPE);

    lv_obj_t * email_label = lv_label_create(panel1);
    lv_label_set_text(email_label, "elena@smith.com");

    lv_obj_t * call_icn = lv_label_create(panel1);
    lv_obj_add_style(call_icn, &style_icon, 0);
    lv_label_set_text(call_icn, LV_SYMBOL_CALL);

    lv_obj_t * call_label = lv_label_create(panel1);
    lv_label_set_text(call_label, "+79 246 123 4567");

    lv_obj_t * log_out_btn = lv_btn_create(panel1);
    lv_obj_set_height(log_out_btn, LV_SIZE_CONTENT);

    lv_obj_t * label = lv_label_create(log_out_btn);
    lv_label_set_text(label, "Log out");
    lv_obj_center(label);

    lv_obj_t * invite_btn = lv_btn_create(panel1);
    lv_obj_add_state(invite_btn, LV_STATE_DISABLED);
    lv_obj_set_height(invite_btn, LV_SIZE_CONTENT);

    label = lv_label_create(invite_btn);
    lv_label_set_text(label, "Invite");
    lv_obj_center(label);

    /*Create a keyboard*/
    lv_obj_t * kb = lv_keyboard_create(lv_scr_act());
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
#endif

    // /*Create the second panel*/
    lv_obj_t * panel2 = lv_obj_create(parent);
    lv_obj_set_style_bg_color(panel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_height(panel2, LV_SIZE_CONTENT);

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
    lv_obj_set_size(uiLabResult, 280, 130);
    // lv_obj_set_pos(uiLabResult, 20, 20);
    // lv_obj_set_align(uiLabResult, LV_ALIGN_LEFT_MID);
    lv_obj_align(uiLabResult, LV_ALIGN_LEFT_MID, 260+240, 0);
    lv_obj_set_style_text_font(uiLabResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_text(uiLabResult, "支持更大容量的高速和片外，支持用户配置数据缓存与指令缓存。带宽；其低功耗蓝牙子系统支持可通过与广播扩展实现远距离通信。它还支持 2 Mbps PHY，用于提高传输速度和数据吞吐量。ESP32-S3 的 Wi-Fi 和 Bluetooth LE 射频性能优越，在高温下也能稳定工作。.");
    // lv_textarea_set_placeholder_text(uiLabResult, "量金野支持更大容量的");
    lv_obj_set_style_text_color(uiLabResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiLabResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(uiLabResult, &ui_font_PocketDictPenRegular, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiLabResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiLabResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiLabResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiLabResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    // lv_obj_t * panel2_title = lv_label_create(panel2);
    // lv_label_set_text(panel2_title, "Your profile");
    // lv_obj_add_style(panel2_title, &style_title, 0);

    // lv_obj_t * user_name_label = lv_label_create(panel2);
    // lv_label_set_text(user_name_label, "User name");
    // lv_obj_add_style(user_name_label, &style_text_muted, 0);

    // lv_obj_t * user_name = lv_textarea_create(panel2);
    // lv_textarea_set_one_line(user_name, true);
    // lv_textarea_set_placeholder_text(user_name, "Your name");
    // lv_obj_add_event_cb(user_name, ta_event_cb, LV_EVENT_ALL, kb);

    // lv_obj_t * password_label = lv_label_create(panel2);
    // lv_label_set_text(password_label, "Password");
    // lv_obj_add_style(password_label, &style_text_muted, 0);

    // lv_obj_t * password = lv_textarea_create(panel2);
    // lv_textarea_set_one_line(password, true);
    // lv_textarea_set_password_mode(password, true);
    // lv_textarea_set_placeholder_text(password, "Min. 8 chars.");
    // lv_obj_add_event_cb(password, ta_event_cb, LV_EVENT_ALL, kb);

    // lv_obj_t * gender_label = lv_label_create(panel2);
    // lv_label_set_text(gender_label, "Gender");
    // lv_obj_add_style(gender_label, &style_text_muted, 0);

    // lv_obj_t * gender = lv_dropdown_create(panel2);
    // lv_dropdown_set_options_static(gender, "Male\nFemale\nOther");

    // lv_obj_t * birthday_label = lv_label_create(panel2);
    // lv_label_set_text(birthday_label, "Birthday");
    // lv_obj_add_style(birthday_label, &style_text_muted, 0);

    // lv_obj_t * birthdate = lv_textarea_create(panel2);
    // lv_textarea_set_one_line(birthdate, true);
    // lv_obj_add_event_cb(birthdate, birthday_event_cb, LV_EVENT_ALL, NULL);

    // /*Create the third panel*/
    // lv_obj_t * panel3 = lv_obj_create(parent);
    // lv_obj_t * panel3_title = lv_label_create(panel3);
    // lv_label_set_text(panel3_title, "Your skills");
    // lv_obj_add_style(panel3_title, &style_title, 0);

    // lv_obj_t * experience_label = lv_label_create(panel3);
    // lv_label_set_text(experience_label, "Experience");
    // lv_obj_add_style(experience_label, &style_text_muted, 0);

    // lv_obj_t * slider1 = lv_slider_create(panel3);
    // lv_obj_set_width(slider1, LV_PCT(95));
    // lv_obj_add_event_cb(slider1, slider_event_cb, LV_EVENT_ALL, NULL);
    // lv_obj_refresh_ext_draw_size(slider1);

    // lv_obj_t * team_player_label = lv_label_create(panel3);
    // lv_label_set_text(team_player_label, "Team player");
    // lv_obj_add_style(team_player_label, &style_text_muted, 0);

    // lv_obj_t * sw1 = lv_switch_create(panel3);

    // lv_obj_t * hard_working_label = lv_label_create(panel3);
    // lv_label_set_text(hard_working_label, "Hard-working");
    // lv_obj_add_style(hard_working_label, &style_text_muted, 0);

    // lv_obj_t * sw2 = lv_switch_create(panel3);

        static lv_coord_t grid_main_col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
        static lv_coord_t grid_main_row_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};

        /*Create the top panel*/
        static lv_coord_t grid_1_col_dsc[] = {LV_GRID_CONTENT, 5, LV_GRID_CONTENT, LV_GRID_FR(2), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
        static lv_coord_t grid_1_row_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, 10, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};

        static lv_coord_t grid_2_col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
        static lv_coord_t grid_2_row_dsc[] = {
            LV_GRID_CONTENT,  /*Title*/
            5,                /*Separator*/
            LV_GRID_CONTENT,  /*Box title*/
            30,               /*Boxes*/
            5,                /*Separator*/
            LV_GRID_CONTENT,  /*Box title*/
            30,               /*Boxes*/
            LV_GRID_TEMPLATE_LAST
        };


        lv_obj_set_grid_dsc_array(parent, grid_main_col_dsc, grid_main_row_dsc);

        // lv_obj_set_grid_cell(panel1, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_CENTER, 0, 1);

        // lv_obj_set_grid_dsc_array(panel1, grid_1_col_dsc, grid_1_row_dsc);
        // // lv_obj_set_grid_cell(avatar, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 0, 5);
        // lv_obj_set_grid_cell(name, LV_GRID_ALIGN_START, 2, 2, LV_GRID_ALIGN_CENTER, 0, 1);
        // lv_obj_set_grid_cell(dsc, LV_GRID_ALIGN_STRETCH, 2, 4, LV_GRID_ALIGN_START, 1, 1);
        // lv_obj_set_grid_cell(email_icn, LV_GRID_ALIGN_CENTER, 2, 1, LV_GRID_ALIGN_CENTER, 3, 1);
        // lv_obj_set_grid_cell(email_label, LV_GRID_ALIGN_START, 3, 1, LV_GRID_ALIGN_CENTER, 3, 1);
        // lv_obj_set_grid_cell(call_icn, LV_GRID_ALIGN_CENTER, 2, 1, LV_GRID_ALIGN_CENTER, 4, 1);
        // lv_obj_set_grid_cell(call_label, LV_GRID_ALIGN_START, 3, 1, LV_GRID_ALIGN_CENTER, 4, 1);
        // lv_obj_set_grid_cell(log_out_btn, LV_GRID_ALIGN_STRETCH, 4, 1, LV_GRID_ALIGN_CENTER, 3, 2);
        // lv_obj_set_grid_cell(invite_btn, LV_GRID_ALIGN_STRETCH, 5, 1, LV_GRID_ALIGN_CENTER, 3, 2);

        lv_obj_set_grid_cell(panel2, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_START, 1, 1);
        // lv_obj_set_grid_dsc_array(panel2, grid_2_col_dsc, grid_2_row_dsc);
        // lv_obj_set_grid_cell(panel2_title, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_CENTER, 0, 1);
        // lv_obj_set_grid_cell(user_name, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_CENTER, 3, 1);
        // lv_obj_set_grid_cell(user_name_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 2, 1);
        // lv_obj_set_grid_cell(password, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_CENTER, 3, 1);
        // lv_obj_set_grid_cell(password_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_START, 2, 1);
        // lv_obj_set_grid_cell(birthdate, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_CENTER, 6, 1);
        // lv_obj_set_grid_cell(birthday_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_START, 5, 1);
        // lv_obj_set_grid_cell(gender, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_CENTER, 6, 1);
        // lv_obj_set_grid_cell(gender_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 5, 1);


        // lv_obj_set_grid_cell(panel3, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
        // lv_obj_set_grid_dsc_array(panel3, grid_2_col_dsc, grid_2_row_dsc);
        // lv_obj_set_grid_cell(panel3_title, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_CENTER, 0, 1);
        // lv_obj_set_grid_cell(slider1, LV_GRID_ALIGN_CENTER, 0, 2, LV_GRID_ALIGN_CENTER, 3, 1);
        // lv_obj_set_grid_cell(experience_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 2, 1);
        // lv_obj_set_grid_cell(sw2, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 6, 1);
        // lv_obj_set_grid_cell(hard_working_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 5, 1);
        // lv_obj_set_grid_cell(sw1, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 6, 1);
        // lv_obj_set_grid_cell(team_player_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_START, 5, 1);
#endif
}
