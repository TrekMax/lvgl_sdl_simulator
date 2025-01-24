/***********
 * @file lv_long_txt_label.c
 * 描述： 长文本变成单行多个label创建
 * @author 徐华振-hzxu2@iflytek.com
 * @date 2023-06-29 21:32 
 * @note 
***********/

#include "lv_long_txt_label.h"
#include "plat_os.h"


#define LV_OBJX_NAME "lv_long_txt_label"

//定义lv_signal_cb_t 变量，用于保存继承组件的ancestor_signal回调
static lv_signal_cb_t ancestor_signal;
/**
 * 实现lv_obj_t的single回调，实现lv_obj_get_type可以获取到自己定义的LV_OBJX_NAME
 * 和 调用lv_obj_del 的时候实现内存释放 
*/
static lv_res_t lv_long_txt_label_signal(lv_obj_t * this, lv_signal_t sign, void * param)
{
    lv_res_t res = ancestor_signal(this, sign, param);
    if(res != LV_RES_OK) return res;

    if(sign == LV_SIGNAL_GET_TYPE) return lv_obj_handle_get_type_signal(param, LV_OBJX_NAME);
    
    if(sign == LV_SIGNAL_CLEANUP) 
    {
    /*此处需要增加lv_obj_del时释放ext中内存的代码*/
    }

    return res;
}

/**********
 * 判断obj是否是当前类型
*********/
bool lv_obj_is_long_txt_label(lv_obj_t * obj)
{    
    lv_obj_type_t type;

    lv_obj_get_type(obj, &type);
    uint8_t cnt;
    for(cnt = 0; cnt < LV_MAX_ANCESTOR_NUM; cnt++) {
        if(type.type[cnt] == NULL) break;
        return strcmp((char *)(type.type[cnt]), LV_OBJX_NAME) == 0;
    }
    return false;
}

/**
 * @brief 长文本变成单行多个label创建
 * 
 * @param par 
 * @param label 单个label的样式label,需提前创建一个创建完可销毁
 * @param src 
 * @param w 
 * @return lv_obj_t* 
 */
lv_obj_t * lv_long_txt_label_create(lv_obj_t * par, lv_obj_t *label, char *src, int w)
{
    lv_obj_t * this = ui_base_create_tranparent_obj(par);
    LV_ASSERT_MEM(this);
    if(this == NULL) return NULL;

    //必需实现
    if (ancestor_signal == NULL) ancestor_signal = lv_obj_get_signal_cb(this);

    lv_long_txt_label_ext_t * ext = lv_obj_allocate_ext_attr(this, sizeof(lv_long_txt_label_ext_t));
    LV_ASSERT_MEM(ext);
    if(ext == NULL) 
    {
        lv_obj_del(this);
        return NULL;
    }

    //此处增加ext初始化代码

    //必需实现
    lv_obj_set_signal_cb(this, lv_long_txt_label_signal);
    lv_page_glue_obj(this, true);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_t *label_content = NULL;
    lv_obj_t *tmp_obj = NULL;
    int line_start = 0;
    while(src[line_start] != '\0')
    {
        int ret = lv_label_get_next_line(label, src, line_start, w);
        if (ret > 0)
        {
            char *txt = os_mem_alloc(ret + 1);
            sprintf(txt, "%.*s", ret, src + line_start);
            line_start += ret;
            label_content = lv_label_create(this, label);
            lv_label_set_long_mode(label_content, LV_LABEL_LONG_EXPAND);
            lv_page_glue_obj(label_content, true);
            lv_label_set_text(label_content, txt);
            if (tmp_obj)
                lv_obj_align(label_content, tmp_obj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, lv_obj_get_height(label_content) / 4);
            else
                lv_obj_align(label_content, this, LV_ALIGN_IN_TOP_LEFT, 0, 0);
            os_mem_free(txt);
        }
    }
    lv_obj_set_height(this, lv_obj_get_y(label_content) + lv_obj_get_height(label_content));
    //控件创建代码：
    return this;
}