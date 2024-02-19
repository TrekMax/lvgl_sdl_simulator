#ifndef __SCR_SWITCH_   
#define __SCR_SWITCH_
#include "stdint.h"

struct aweui_scr;

typedef void (*aweui_src_handle_t)(struct aweui_scr *from, struct aweui_scr *to);

struct aweui_scr {
	uint32_t id;
	lv_obj_t *screen;
	aweui_src_handle_t enter;
	aweui_src_handle_t exit;
	void *data;
};

enum {
	AWEUI_SCR_STANDBY = 0,
	AWEUI_SCR_CAMERA_IMAGE_PREVIEW,
	AWEUI_SCR_CAMERA_IMAGE_PROCESSING,
	AWEUI_SCR_CHAT,
	AWEUI_SCR_SETTING,
	AWEUI_SCR_MAX,
};

int aweui_scr_switch_to(uint32_t from, uint32_t to);
int aweui_scr_register(uint32_t id, struct aweui_scr *scr);
int aweui_scr_switch_to_id(uint32_t to);

#endif