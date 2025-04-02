/*
 * @Author: Flying
 * @Date: 2022-05-02 17:15:11
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 17:15:32
 * @Description: 新建文件
 */
#include "app_common/lisaui_app_common.h"

/**
 * Demonstrate flex grow.
 */
int app_flex_3(lv_obj_t *parent)
{
    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_set_size(cont, 300, 220);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);

    lv_obj_t *obj;
    obj = lv_obj_create(cont);
    lv_obj_set_size(obj, 40, 40); /*Fix size*/

    obj = lv_obj_create(cont);
    lv_obj_set_height(obj, 40);
    lv_obj_set_flex_grow(obj, 1); /*1 portion from the free space*/

    obj = lv_obj_create(cont);
    lv_obj_set_height(obj, 40);
    lv_obj_set_flex_grow(obj, 2); /*2 portion from the free space*/

    obj = lv_obj_create(cont);
    lv_obj_set_size(obj, 40, 40); /*Fix size. It is flushed to the right by the "grow" items*/
    return 0;
}
