/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#ifdef __ZEPHYR__
#include "lvgl.h"
#include "core/lv_disp.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(aweui_screen_char, LOG_LEVEL_INF);

#include <csk_malloc.h>
#else
#include <stdlib.h>
#include "lvgl/lvgl.h"
#define LOG_INF LV_LOG_USER
#define printf LV_LOG_USER
#define printk LV_LOG_USER
#endif

#include "aweui_resources.h"
#include "aweui_screen.h"
#include "aweui_types.h"
#include "aweui_event.h"
#include "aweui_screen_llm_chat.h"
#include "aweui_chat_btn_group.h"
#include "screen_switch.h"

lv_obj_t *chat_home = NULL;
lv_obj_t *llm_chat_result_panel = NULL;
lv_obj_t *llm_chat_result_panel_parent = NULL;
static lv_obj_t *wait_img = NULL;
static lv_obj_t *recognition_result = NULL;
static lv_obj_t *recognition_ing = NULL;
static lv_obj_t *err_img = NULL;
lv_img_dsc_t img_dsc;
lv_obj_t *ui_demo_listenai_img = NULL;
bool chat_flag = false;
bool test_flag = false;
typedef enum
{
	txt_e,
	photo_e,
	err_e
} rlt_type;

void ui_set_img(uint8_t *buf, uint32_t size)
{

#ifdef __ZEPHYR__
	char *req_buf = csk_malloc(size);
#else
	char *req_buf = malloc(size);
#endif
	memcpy(req_buf, buf, size);
	img_dsc.header.always_zero = 0;

	img_dsc.data_size = size;
	img_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
	img_dsc.header.h = 240;
	img_dsc.header.w = 240;
	img_dsc.header.always_zero = 0;
	img_dsc.data = buf;

	lv_img_set_src(ui_demo_listenai_img, &img_dsc);
	lv_obj_clear_flag(ui_demo_listenai_img, LV_OBJ_FLAG_HIDDEN); // 显示对象

#ifdef __ZEPHYR__
	csk_free(req_buf);
#else
	free(req_buf);
#endif
}
// 开始录音
void start_voice_recognition(void)
{
	lv_obj_clear_flag(wait_img, LV_OBJ_FLAG_HIDDEN);	  // 显示对象
	lv_obj_add_flag(recognition_ing, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
}
void set_chat_status(uint8_t status, rlt_type type_rlt, uint8_t *buf, uint32_t size)
{
	chat_flag = status;
	if (chat_flag)
	{
		// lv_obj_add_flag(wait_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
		if (type_rlt == txt_e)
		{
			// lv_obj_clear_flag(recognition_result, LV_OBJ_FLAG_HIDDEN); // 显示对象
			lv_textarea_set_text(recognition_result, "既然如此， 就我个人来说，好好学习对我的意义，不能不说非常重大。 美华纳曾经说过，勿问成功的秘诀为何，且尽全力做你应该做的事吧。这启发了我， 一般来说， 总结的来说， 本人也是经过了深思熟虑，在每个日日夜夜思考这个问题。 王阳明曾经提到过，故立志者，为学之心也；为学者，立志之事也。这启发了我， 总结的来说， 我们都知道，只要有意义，那么就必须慎重考虑。现在，解决好好学习的问题，是非常非常重要的。 所以， 好好学习的发生，到底需要如何做到，又会如何产生。 而这些并不是完全重要，更加重要的问题是， 冯学峰曾经提到过，当一个人用工作去迎接光明，光明很快就会来照耀着他。我希望诸位也能好好地体会这句话。");
		}
		else if (type_rlt == photo_e)
		{
			ui_set_img(buf, size);
		}
	}
	else
	{
		// lv_obj_add_flag(wait_img, LV_OBJ_FLAG_HIDDEN);	// 隐藏对象
		lv_obj_clear_flag(err_img, LV_OBJ_FLAG_HIDDEN); // 显示对象
	}
}

void ui_event_chat(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	printf("[%d:%s] event: %X\n", __LINE__, __func__, event_code);
	// lv_obj_t *obj = lv_event_get_target(e);
	if (event_code == LV_EVENT_PRESSED)
	{
	}
}

lv_obj_t *aweui_chat_result_create(lv_obj_t *parent, aweui_llm_mode_e mode)
{
	aweui_status_bar_home_btn_hide(true);
	// ui_camera_creat(NULL);
	llm_chat_result_panel_parent = parent;
	llm_chat_result_panel = lv_obj_create(parent);
	lv_obj_remove_style_all(llm_chat_result_panel);
	lv_obj_clear_flag(llm_chat_result_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_bg_color(llm_chat_result_panel, lv_color_hex(0x000ff0), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(llm_chat_result_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_size(llm_chat_result_panel, LV_PCT(100), 200);
	lv_obj_set_y(llm_chat_result_panel, 40);
	lv_obj_set_style_pad_all(parent, 0, 0);
	lv_obj_set_style_pad_all(llm_chat_result_panel, 0, 0);

	// 错误图标
	err_img = lv_img_create(llm_chat_result_panel);
	lv_img_set_src(err_img, &ic_warning);
	// lv_obj_set_pos(err_img, -30, -20);
	lv_obj_set_align(err_img, LV_ALIGN_BOTTOM_MID);
	lv_obj_add_flag(err_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
	lv_obj_clear_flag(err_img, LV_OBJ_FLAG_SCROLLABLE);						   /// Flags
	lv_obj_add_event_cb(err_img, ui_event_chat, LV_EVENT_PRESSED, NULL);
	lv_obj_add_flag(err_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
	// recognition_result文本结果
	recognition_result = lv_textarea_create(llm_chat_result_panel);
	lv_obj_set_size(recognition_result, LV_PCT(75), LV_PCT(90));
	// lv_obj_set_x(recognition_result, 0);
	// lv_obj_set_y(recognition_result, 50);
	// lv_obj_set_pos(recognition_result, LV_PCT(5), LV_PCT(5));
	lv_obj_set_style_text_font(recognition_result, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
	// lv_textarea_set_text(recognition_result, "11111");
	lv_obj_set_style_text_color(recognition_result, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_bg_color(recognition_result, lv_color_black(), 0);

	static lv_style_t style_rlt;
	lv_style_init(&style_rlt);
	lv_style_set_bg_color(&style_rlt, lv_color_hex(0x000000));
	// lv_style_set_bg_opa(&style_home, LV_OPA_30); /* 50%透明 */
	lv_style_set_border_width(&style_rlt, 0);
	lv_obj_add_style(recognition_result, &style_rlt, 0);
	lv_style_set_border_color(&style_rlt, lv_color_hex(0x000000));

	// lv_obj_add_flag(recognition_result, LV_OBJ_FLAG_HIDDEN); // 隐藏对象

	// 图像结果
	ui_demo_listenai_img = lv_img_create(llm_chat_result_panel);
	lv_obj_set_size(ui_demo_listenai_img, LV_PCT(75), LV_PCT(75));

	if(mode == AWEUI_LLM_MODE_ONESHOT){
		aweui_add_chat_camera_ui(llm_chat_result_panel, UI_CAMERA);
	}else{
		aweui_add_chat_camera_ui(llm_chat_result_panel, UI_CAMERA_LONG);
	}
	return llm_chat_result_panel;
}

int aweui_screen_chat_result_text(const awe_llm_status_t llm_ret_status, const char *text, aweui_text_mode_t text_mode)
{
	aweui_scr_switch_to_id(AWEUI_SCR_CHAT);

	switch (llm_ret_status)
	{
	case AWEUI_LLM_STATUS_WAITING:
		// 等待
		break;
	case AWEUI_LLM_STATUS_PROCESSING:
		// 处理中
		break;
	case AWEUI_LLM_STATUS_SUCCESS:
		// 成功
		break;
	case AWEUI_LLM_STATUS_FAIL:
		// 失败
		break;
	default:
		break;
	}
	// LOG_INF("LLM Result: %s", text);
	if (strlen(text) == 0)
	{
		return AWEUI_ERR_OK;
	}
	if (text_mode == AWEUI_TEXT_MODE_APPEND)
	{
		lv_textarea_add_text(recognition_result, text);
	}
	else
	{
		lv_textarea_set_text(recognition_result, text);
	}

	lv_obj_clear_flag(recognition_result, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_demo_listenai_img, LV_OBJ_FLAG_HIDDEN);

	return AWEUI_ERR_OK;
}

static lv_img_dsc_t desc = {0};
int aweui_screen_chat_result_picture(const awe_llm_status_t llm_ret_status, const aweui_img_t img)
{
	aweui_scr_switch_to_id(AWEUI_SCR_CHAT);

	switch (llm_ret_status)
	{
	case AWEUI_LLM_STATUS_WAITING:
		// 等待
		break;
	case AWEUI_LLM_STATUS_PROCESSING:
		// 处理中
		break;
	case AWEUI_LLM_STATUS_SUCCESS:
		// 成功
		break;
	case AWEUI_LLM_STATUS_FAIL:
		// 失败
		break;
	default:
		break;
	}
	desc.header.always_zero = 0;
	desc.header.w = img.width;
	desc.header.h = img.height;
	desc.header.cf = LV_IMG_CF_TRUE_COLOR;

	desc.data_size = img.len;
	desc.data = img.data;
	lv_img_set_src(ui_demo_listenai_img, &desc);
	lv_obj_clear_flag(ui_demo_listenai_img, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(recognition_result, LV_OBJ_FLAG_HIDDEN);

	return AWEUI_ERR_OK;
}

static struct aweui_scr aweui_screen_camera = {0};

static void aweui_src_chat_enter_handle(struct aweui_scr *from, struct aweui_scr *to)
{
	if (to == NULL) {
		return;
	}

	if (to->screen == NULL) {
		to->screen = aweui_chat_result_create(lv_scr_act(), aweui_get_llm_mode());
	}

	if (to->screen == NULL) {
		return;
	}

	lv_obj_clear_flag(to->screen, LV_OBJ_FLAG_HIDDEN);

	/* clear text area */
	lv_textarea_set_text(recognition_result, "");
}

static void aweui_src_chat_exit_handle(struct aweui_scr *from, struct aweui_scr *to)
{
	if (from == NULL) {
		return;
	}

	if (from->screen == NULL) {
		return;
	}

	lv_obj_add_flag(from->screen, LV_OBJ_FLAG_HIDDEN);
}

int aweui_screen_chat_init(void)
{
	aweui_screen_camera.id = AWEUI_SCR_CHAT;
	aweui_screen_camera.enter = aweui_src_chat_enter_handle;
	aweui_screen_camera.exit = aweui_src_chat_exit_handle;
	aweui_screen_camera.screen = NULL;

	aweui_scr_register(AWEUI_SCR_CHAT, &aweui_screen_camera);

	return 0;
}
