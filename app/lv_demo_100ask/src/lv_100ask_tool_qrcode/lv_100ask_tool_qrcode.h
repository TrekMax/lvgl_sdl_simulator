#ifndef LV_100ASK_TOOL_QRCODE_H
#define LV_100ASK_TOOL_QRCODE_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask.h"


/*********************
 *      DEFINES
 *********************/
#define LV_100ASK_QRCODE_SIZE           (100)
#define LV_100ASK_QRCODE_AD_SIZE        (80)
#define LV_100ASK_QRCODE_SPACE          ((LV_HOR_RES - (LV_100ASK_QRCODE_AD_SIZE * 3)) / 4)


/**********************
 *      TYPEDEFS
 **********************/
typedef struct _lv_100ask_qrcode {
	lv_obj_t * bg;      				// 背景
	lv_obj_t * qr_input;				// 二维码框(接受输入)
	lv_obj_t * qr_official_website;		// 二维码框(官网)
	lv_obj_t * qr_wechat;				// 二维码框(微信公众号)
	lv_obj_t * qr_100ask_lvgl;			// 二维码框(lvgl中文站点)
	lv_obj_t * ta_content;				// 输入框
	lv_obj_t * keyboard;				// 键盘
} T_lv_100ask_qrcode, *PT_lv_100ask_qrcode;


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_100ask_tool_qrcode(void);





/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_100ASK_TOOL_QRCODE_H */





