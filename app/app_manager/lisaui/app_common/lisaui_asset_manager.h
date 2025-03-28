/**
 * @file lisaui_asset_manager.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-06
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_ASSET_MANAGER_H__
#define __LISAUI_ASSET_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lisaui_app_common.h"


/**
 * @brief 
 * 
 * @return lisaui_err_t 
 */
lisaui_err_t lisaui_asset_manager_init(void);
void* lisaui_asset_manager_get_asset(const char *path);
// lisaui_err_t lisaui_asset_manager_deinit(void);


#ifdef __cplusplus
}
#endif

#endif /* __LISAUI_ASSET_MANAGER_H__ */