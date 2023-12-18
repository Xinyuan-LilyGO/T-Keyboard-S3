/**
 * @file lv_animimg.h
 *
 */

#ifndef LV_ANIM_IMG_H
#define LV_ANIM_IMG_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../lvgl.h"

#if LV_USE_ANIMIMG != 0

/*Testing of dependencies*/
#if LV_USE_IMG == 0
#error "lv_animimg: lv_img is required. Enable it in lv_conf.h (LV_USE_IMG 1)"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

extern const lv_obj_class_t lv_animimg_class;

/*Data of image*/
typedef struct {
    lv_img_t img;
    lv_anim_t anim;
    /*picture sequence */
    const void ** dsc;
    int8_t  pic_count;
} lv_animimg_t;


/*Image parts*/
enum {
    LV_ANIM_IMG_PART_MAIN,
};
typedef uint8_t lv_animimg_part_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create an animation image objects
 * @param parent pointer to an object, it will be the parent of the new button
 * @return pointer to the created animation image object
 */
lv_obj_t * lv_animimg_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the image animation images source.
 * @param img pointer to an animation image object
 * @param dsc pointer to a series images
 * @param num images' number
 * @param reverse play in reverse.
 */
void lv_animimg_set_src(lv_obj_t * img, const void * dsc[], uint8_t num, bool reverse);

/**
 * Startup the image animation.
 * @param obj pointer to an animation image object
 */
void lv_animimg_start(lv_obj_t * obj);

/**
 * Delete the image animation.
 * @param obj pointer to an animation image object
 */
bool lv_animimg_del(lv_obj_t * obj);

/**
 * Set the image animation duration time. unit:ms
 * @param img pointer to an animation image object
 */
void lv_animimg_set_duration(lv_obj_t * img, uint32_t duration);

/**
 * Set the image animation reapeatly play times.
 * @param img pointer to an animation image object
 * @param count the number of times to repeat the animation
 */
void lv_animimg_set_repeat_count(lv_obj_t * img, uint16_t count);

/**
 * Make the image animation to play back to when the forward direction is ready.
 * @param img pointer to an animation image object
 * @param duration the duration of the playback image animation in milliseconds. 0: disable playback
 */
void lv_animimg_set_playback_time(lv_obj_t * img, uint16_t duration);

/**
 * Make the image animation to play back to when the forward direction is ready.
 * @param img pointer to an animation image object
 * @param duration delay in milliseconds before starting the playback image animation.
 */
void lv_animimg_set_playback_delay(lv_obj_t * img, uint16_t duration);

/**
 * Set a function call when the animation image really starts (considering `delay`)
 * @param img pointer to an animation image object
 * @param start_cb  a function call when the animation is start
 */
void lv_animimg_set_start_cb(lv_obj_t * img, lv_anim_ready_cb_t start_cb);

/**
 * Set a function call when the animation is ready
 * @param img pointer to an animation image object
 * @param ready_cb  a function call when the animation is ready
 */
void lv_animimg_set_ready_cb(lv_obj_t * img, lv_anim_ready_cb_t ready_cb);

/*=====================
 * Getter functions
 *====================*/

#endif /*LV_USE_ANIMIMG*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_ANIM_IMG_H*/
