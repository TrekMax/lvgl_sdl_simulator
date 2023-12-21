#ifndef LV_100ASK_BOARD_ABOUT_H
#define LV_100ASK_BOARD_ABOUT_H

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
#define LV_100ASK_ABOUT_US_TABLE_SPACE  (LV_HOR_RES/6)
#define LV_100ASK_ABOUT_US_TITLE_SPACE  (45)
#define LV_100ASK_QRCODE_SIZE           (100)
#define LV_100ASK_QRCODE_AD_SIZE        (80)
#define LV_100ASK_QRCODE_SPACE          ((LV_HOR_RES - (LV_100ASK_QRCODE_AD_SIZE * 3)) / 4)


/**********************
 *      TYPEDEFS
 **********************/
typedef struct _lv_100ask_about {
	lv_obj_t  * bg_about;				// 背景
	lv_obj_t  * about_table;			// 展示文字
	lv_obj_t  * qr_official_website;	// 二维码框(官网)
	lv_obj_t  * qr_wechat;				// 二维码框(微信公众号)
	lv_obj_t  * qr_100ask_lvgl;			// 二维码框(lvgl中文站点)
	lv_timer_t * task_handle; 			// 任务句柄(获取CPU使用率)
} T_lv_100ask_about, *PT_lv_100ask_about;


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_100ask_board_about(void);





/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_100ASK_BOARD_ABOUT_H */





