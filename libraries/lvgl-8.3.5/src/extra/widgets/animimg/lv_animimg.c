/**
 * @file lv_animimg.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_animimg.h"
#if LV_USE_ANIMIMG != 0

/*Testing of dependencies*/
#if LV_USE_IMG == 0
    #error "lv_animimg: lv_img is required. Enable it in lv_conf.h (LV_USE_IMG  1) "
#endif

#include "../../../misc/lv_assert.h"
#include "../../../draw/lv_img_decoder.h"
#include "../../../misc/lv_fs.h"
#include "../../../misc/lv_txt.h"
#include "../../../misc/lv_math.h"
#include "../../../misc/lv_log.h"
#include "../../../misc/lv_anim.h"

/*********************
 *      DEFINES
 *********************/
#define LV_OBJX_NAME "lv_animimg"

#define MY_CLASS &lv_animimg_class

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void index_change(lv_obj_t * obj, int32_t index);
static void lv_animimg_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t lv_animimg_class = {
    .constructor_cb = lv_animimg_constructor,
    .instance_size = sizeof(lv_animimg_t),
    .base_class = &lv_img_class
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_animimg_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&lv_animimg_class, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

void lv_animimg_set_src(lv_obj_t * obj, const void * dsc[], uint8_t num, bool reverse)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    animimg->dsc = dsc;
    animimg->pic_count = num;
    if(reverse) {
        lv_anim_set_values(&animimg->anim, num, 0);
    }
    else {
        lv_anim_set_values(&animimg->anim, 0, num);
    }
}

void lv_animimg_start(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    lv_anim_start(&animimg->anim);
}

bool lv_animimg_del(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    return lv_anim_del(&animimg->anim, NULL);
}


/*=====================
 * Setter functions
 *====================*/

void lv_animimg_set_duration(lv_obj_t * obj, uint32_t duration)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    lv_anim_set_time(&animimg->anim, duration);
}

void lv_animimg_set_repeat_count(lv_obj_t * obj, uint16_t count)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    lv_anim_set_repeat_count(&animimg->anim, count);
}

void lv_animimg_set_playback_time(lv_obj_t * obj, uint16_t duration)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    lv_anim_set_playback_time(&animimg->anim, duration);
}

void lv_animimg_set_playback_delay(lv_obj_t * obj, uint16_t duration)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    lv_anim_set_playback_delay(&animimg->anim, duration);
}

void lv_animimg_set_start_cb(lv_obj_t * obj, lv_anim_start_cb_t start_cb)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    lv_anim_set_start_cb(&animimg->anim, start_cb);
}

void lv_animimg_set_ready_cb(lv_obj_t * obj, lv_anim_start_cb_t ready_cb)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    lv_anim_set_ready_cb(&animimg->anim, ready_cb);
}

/*=====================
 * Getter functions
 *====================*/

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_animimg_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_TRACE_OBJ_CREATE("begin");

    LV_UNUSED(class_p);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;

    animimg->dsc = NULL;
    animimg->pic_count = -1;
    //initial animation
    lv_anim_init(&animimg->anim);
    lv_anim_set_var(&animimg->anim, obj);
    lv_anim_set_time(&animimg->anim, 30);
    lv_anim_set_exec_cb(&animimg->anim, (lv_anim_exec_xcb_t)index_change);
    lv_anim_set_values(&animimg->anim, 0, 1);
    lv_anim_set_repeat_count(&animimg->anim, LV_ANIM_REPEAT_INFINITE);
}

static void index_change(lv_obj_t * obj, int32_t index)
{
    lv_animimg_t * animimg = (lv_animimg_t *)obj;
    index = animimg->pic_count == index ? index - 1 : index;
    lv_img_set_src(obj, animimg->dsc[index]);
}

#endif
