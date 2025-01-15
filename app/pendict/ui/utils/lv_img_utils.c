/**
 * @file lv_img_utils.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-23
 *
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lv_img_utils.h"
#ifdef __ZEPHYR__
	#include <zephyr/kernel.h>
	#include "lvgl.h"
#else
	#include "lvgl/lvgl.h"
#endif
// #include "log_print.h"
// #define LOG_INF CLOG
#define LOG_INF LV_LOG_USER

int lv_img_png_src_init(lv_img_dsc_t *dsc, const void *data, uint32_t size)
{
	img_header_t header;
	LOG_INF("lv_img_png_src_init: data=%p, size=%d", data, size);

	if (img_png_get_info(data, size, &header))
	{
		LOG_INF("lv_img_png_src_init: get png info failed");
		return -1;
	}

	dsc->data = data;
	dsc->data_size = size;
	dsc->header.w = header.width;
	dsc->header.h = header.height;
	dsc->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;

	LOG_INF("lv_img_png_src_init: w=%d, h=%d", dsc->header.w, dsc->header.h);
	return 0;
}

int lv_img_gif_src_init(lv_img_dsc_t *dsc, const void *data, uint32_t size)
{
	img_header_t header;
	LOG_INF("lv_img_gif_src_init: data=%p, size=%d", data, size);

	if (img_gif_get_info(data, size, &header))
	{
		LOG_INF("lv_img_gif_src_init: get gif info failed");
		return -1;
	}

	dsc->data = data;
	dsc->data_size = size;
	dsc->header.w = header.width;
	dsc->header.h = header.height;
	dsc->header.cf = LV_IMG_CF_RAW;

	LOG_INF("lv_img_gif_src_init: w=%d, h=%d", dsc->header.w, dsc->header.h);
	return 0;
}

int lv_img_jpg_src_init(lv_img_dsc_t *dsc, const void *data, uint32_t size)
{
	img_header_t header;
	LOG_INF("lv_img_jpg_src_init: data=%p, size=%d", data, size);

	if (img_jpg_get_info(data, size, &header))
	{
		LOG_INF("lv_img_jpg_src_init: get jpg info failed");
		return -1;
	}

	dsc->data = data;
	dsc->data_size = size;
	dsc->header.w = header.width;
	dsc->header.h = header.height;
	dsc->header.cf = LV_IMG_CF_RAW;

	LOG_INF("lv_img_jpg_src_init: w=%d, h=%d", dsc->header.w, dsc->header.h);
	return 0;
}