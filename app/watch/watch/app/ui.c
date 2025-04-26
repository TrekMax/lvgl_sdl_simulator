// LVGL VERSION: 8.2.0

#include "ui.h"
#include "ui_helpers.h"
#include "ui_HomePage.h"
#include "pubsub.h"
#include "utils_log.h"

static const char *TAG = "WatchUI";

void SDL_KeyBoard_Subscriber(PubSub_Message_t message)
{
    LOGI(TAG, "Switching to page, msg id: %d", message.id);
    Page_Back();
}

static void main_timer(lv_timer_t *timer)
{
    // do something in main timer
}

void ui_init(void)
{
    LOGI(TAG, "ui_init");
    Publisher_init(&SDL_KeyBoard_Publisher);
    Publisher_subscribe(&SDL_KeyBoard_Publisher, SDL_KeyBoard_Subscriber);

    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    // timer
    lv_timer_t *ui_MainTimer = lv_timer_create(main_timer, 1000, NULL);

    Pages_init();
}
