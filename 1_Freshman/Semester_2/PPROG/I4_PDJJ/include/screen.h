/** 
 * @brief It defines a screen
 * 
 * @file screen.h
 * @version 1.0 
 * @date 04-02-2019
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__
/**
 * @brief defines the max number of screen
 *
 */
#define SCREEN_MAX_STR 80
/**
 * @brief defines the Object structure
 *
 */
typedef struct _Area Area;
/**
 * @brief screen inicialiciation
 *
 * @return void
 */
void  screen_init();

/**
 * @brief destroy area
 *
 * @return 
 */
void  screen_destroy();
/**
 * @brief screen paints
 *
 * @return void
 */
void  screen_paint();
/**
 * @brief screen gets
 *
 * @param str
 * @return void
 */
void  screen_gets(char *str);
/**
 * @brief inicial area
 *
 * @param x
 * @param y
 * @param width
 * @param height
 * @return area
 */
Area* screen_area_init(int x, int y, int width, int height);
/**
 * @brief destroy area
 *
 * @param area
 * @return area, in case of error NULL
 */
void  screen_area_destroy(Area* area);
/**
 * @brief clear area
 *
 * @param area
 * @return void
 */
void  screen_area_clear(Area* area);
/**
 * @brief reset cursor
 *
 * @param area
 * @return void
 */
void  screen_area_reset_cursor(Area* area);
/**
 * @brief puts area
 *
 * @param area
 * @param str
 * @return void
 */
void  screen_area_puts(Area* area, char *str);

#endif

