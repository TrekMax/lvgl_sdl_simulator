#ifndef LV_100ASK_TOOL_CLOCK_H
#define LV_100ASK_TOOL_CLOCK_H

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

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _lv_100ask_clock {
	lv_obj_t * bg_tool_clock;     			// 背景
	lv_obj_t * g_gauge_clock;	 			// 表盘
	lv_meter_indicator_t * indic_sec;
	lv_meter_indicator_t * indic_min;
	lv_meter_indicator_t * indic_hour;
	lv_obj_t * g_label_clock_time;    	 	// 展示时间信息
	lv_timer_t * timer_handle;
} T_lv_100ask_clock, *PT_lv_100ask_clock;


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_100ask_tool_clock(void);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_100ASK_TOOL_CLOCK_H */





