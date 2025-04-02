/*
 * @Author: Flying
 * @Date: 2022-05-02 17:15:11
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 17:15:22
 * @Description: 新建文件
 */
#include "app_common/lisaui_app_common.h"

/**
 * A simple row and a column layout with flexbox
 */
int app_flex_1(lv_obj_t *parent)
{
    /*Create a container with ROW flex direction*/
    lv_obj_t *cont_row = lv_obj_create(parent);
    lv_obj_set_size(cont_row, 300, 75);
    lv_obj_align(cont_row, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

    /*Create a container with COLUMN flex direction*/
    lv_obj_t *cont_col = lv_obj_create(parent);
    lv_obj_set_size(cont_col, 200, 150);
    lv_obj_align_to(cont_col, cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);

    uint32_t i;
    for (i = 0; i < 10; i++)
    {
        lv_obj_t *obj;
        lv_obj_t *label;

        /*Add items to the row*/
        obj = lv_btn_create(cont_row);
        lv_obj_set_size(obj, 100, LV_PCT(100));

        label = lv_label_create(obj);
        lv_label_set_text_fmt(label, "Item: %u", i);
        lv_obj_center(label);

        /*Add items to the column*/
        obj = lv_btn_create(cont_col);
        lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);

        label = lv_label_create(obj);
        lv_label_set_text_fmt(label, "Item: %" LV_PRIu32, i);
        lv_obj_center(label);
    }
    return 0;
}
