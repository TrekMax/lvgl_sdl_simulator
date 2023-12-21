/**
 * @file lv_demo_physics.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_physics.h"
#include "lv_physac.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void physice_create(lv_obj_t * parent);
static void physics_cb(lv_timer_t * t);
static void add_physics_click_event_cb(lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_obj_t * tv;
static lv_obj_t * body_ball;
#define floor1_len      500
#define floor2_len      500
#define floor1_ang      (13*3.14159f/180)
#define floor2_ang      (167*3.14159f/180)
#define screenWidth     800
#define screenHeight    480
#define floor_wid       8
#define     floor1_y_offset     150
#define     floor2_y_offset     50
#define     floor1_x1  (lv_coord_t)(screenWidth /2-cos(floor1_ang)*floor1_len/2-100)
#define     floor1_y1  (lv_coord_t)(screenHeight/2-sin(floor1_ang)*floor1_len/2-floor1_y_offset+floor_wid)
#define     floor1_x2  (lv_coord_t)(screenWidth /2+cos(floor1_ang)*floor1_len/2-100)
#define     floor1_y2  (lv_coord_t)(screenHeight/2+sin(floor1_ang)*floor1_len/2-floor1_y_offset+floor_wid)
#define     floor2_x1  (lv_coord_t)(screenWidth /2-cos(floor2_ang)*floor2_len/2+100)
#define     floor2_y1  (lv_coord_t)(screenHeight/2-sin(floor2_ang)*floor2_len/2+floor2_y_offset+floor_wid)
#define     floor2_x2  (lv_coord_t)(screenWidth /2+cos(floor2_ang)*floor2_len/2+100)
#define     floor2_y2  (lv_coord_t)(screenHeight/2+sin(floor2_ang)*floor2_len/2+floor2_y_offset+floor_wid)
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_physics(void)
{
    tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 45);

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tv);
    lv_obj_set_style_pad_left(tab_btns, LV_HOR_RES / 2, 0);
    lv_obj_t * logo = lv_img_create(tab_btns);
    LV_IMG_DECLARE(img_lvgl_logo);
    lv_img_set_src(logo, &img_lvgl_logo);
    lv_obj_align(logo, LV_ALIGN_LEFT_MID, -LV_HOR_RES / 2 + 25, 0);

    lv_obj_t * label = lv_label_create(tab_btns);
    lv_label_set_text(label, "LVGL v8");
    lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

    lv_obj_t * t1 = lv_tabview_add_tab(tv, "physics");
    lv_obj_t * t2 = lv_tabview_add_tab(tv, "test");
    lv_obj_t * t3 = lv_tabview_add_tab(tv, "about");
    physice_create(t1);
    InitPhysics();  //初始化物理引擎
    //添加地板
    PhysicsBody floor1 = CreatePhysicsBodyRectangle((Vector2){ screenWidth/2 - 100, screenHeight - 400 }, floor1_len, 10, 10);
    floor1->enabled = false; //固定地板
    SetPhysicsBodyRotation(floor1, floor1_ang);
    PhysicsBody floor2 = CreatePhysicsBodyRectangle((Vector2){ screenWidth/2 + 100, screenHeight - 200 }, floor2_len, 10, 10);
    floor2->enabled = false; //固定地板
    floor2->restitution = 0.35;
    SetPhysicsBodyRotation(floor2, floor2_ang);
    //添加球
    PhysicsBody circle = CreatePhysicsBodyCircle((Vector2){ screenWidth-100, screenHeight/2 }, 45, 10);
    circle->enabled = false; //固定球
    lv_timer_create(physics_cb,100,NULL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void physice_create(lv_obj_t * parent)
{
    static lv_point_t lv_point_line_floor1[2];
    lv_point_line_floor1[0].x = floor1_x1;
    lv_point_line_floor1[0].y = floor1_y1;
    lv_point_line_floor1[1].x = floor1_x2;
    lv_point_line_floor1[1].y = floor1_y2;
    static lv_point_t lv_point_line_floor2[2];
    lv_point_line_floor2[0].x = floor2_x1;
    lv_point_line_floor2[0].y = floor2_y1;
    lv_point_line_floor2[1].x = floor2_x2;
    lv_point_line_floor2[1].y = floor2_y2;
    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, floor_wid);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_line_rounded(&style_line, true);

    lv_obj_t * line_floor1 = lv_line_create(parent);
    lv_line_set_points(line_floor1,lv_point_line_floor1,2);
    lv_obj_add_style(line_floor1, &style_line, 0);

    lv_obj_t * line_floor2 = lv_line_create(parent);
    lv_line_set_points(line_floor2,lv_point_line_floor2,2);
    lv_obj_add_style(line_floor2, &style_line, 0);
    lv_obj_set_style_line_color(line_floor2,lv_palette_main(LV_PALETTE_RED),0);

    lv_obj_t * cicle_ball = lv_led_create(parent);
    lv_led_on(cicle_ball);
    lv_obj_set_size(cicle_ball,90,90);
    lv_obj_align_to(cicle_ball,parent,LV_ALIGN_RIGHT_MID,0,0);

    lv_obj_t * add_physics = lv_btn_create(parent);
    lv_obj_t * btn_label = lv_label_create(add_physics);
    lv_label_set_text(btn_label,"Add Body");
    lv_obj_align_to(add_physics,parent,LV_ALIGN_LEFT_MID,0,0);

    lv_obj_add_event_cb(add_physics, add_physics_click_event_cb, LV_EVENT_CLICKED, NULL);

    body_ball = lv_led_create(parent);
    lv_led_on(body_ball);
}

static void physics_cb(lv_timer_t * t)
{
    LV_UNUSED(t);
    RunPhysicsStep();

    int bodiesCount;
    // Draw created physics bodies
    bodiesCount = GetPhysicsBodiesCount();
    for (int i = 0; i < bodiesCount; i++)
    {
        PhysicsBody body = GetPhysicsBody(i);
        if (body != NULL)
        {
            if(body->enabled == true)
            {
                lv_obj_set_pos(body_ball,(lv_coord_t)body->position.x,(lv_coord_t)body->position.y);
            }
//            int vertexCount = GetPhysicsShapeVerticesCount(i);
//            for (int j = 0; j < vertexCount; j++)
//            {
//                Vector2 vertexA = GetPhysicsShapeVertex(body, j);
//                int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
//                Vector2 vertexB = GetPhysicsShapeVertex(body, jj);
//            }
        }
    }
    // Destroy falling physics bodies
    bodiesCount = GetPhysicsBodiesCount();
    for (int i = bodiesCount - 1; i >= 0; i--)
    {
        PhysicsBody body = GetPhysicsBody(i);

        if ((body != NULL) && (body->position.y > screenHeight))
            DestroyPhysicsBody(body);
    }
}

static void add_physics_click_event_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    Vector2 point;
    point.x = lv_rand(10,350);
    point.y = 0;
    PhysicsBody circle = CreatePhysicsBodyCircle(point,10,10);
    lv_led_set_color(body_ball,lv_palette_main(lv_rand(0,18)));
    //circle->restitution = 0.69f;
    //CreatePhysicsBodyCircle(point, lv_rand(10, 60), 10);
}
