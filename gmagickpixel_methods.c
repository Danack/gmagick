/*
   +----------------------------------------------------------------------+
   | PHP Version 5 / Gmagick	                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 2009 Vito Chin, Mikko Koppanen                         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Mikko Kopppanen <mkoppanen@php.net>                          |
   |         Vito Chin <vito@php.net>		                          |
   +----------------------------------------------------------------------+
*/

#include "php_gmagick.h"
#include "php_gmagick_macros.h"

/* {{{ GmagickPixel Gmagick::__construct([string filename])
	Constructs a new Gmagick object
*/
PHP_METHOD(gmagickpixel, __construct)
{
	php_gmagickpixel_object *internp;
	MagickBool status; // Graphicmagick's boolean type
	char *color_name = NULL;
	int color_name_len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s!", &color_name, &color_name_len) == FAILURE) {
		return;
	}

	internp = (php_gmagickpixel_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	
	/* If color was given as parameter, set it here.*/
	if (color_name != NULL && internp->pixel_wand != NULL) {
		status = PixelSetColor(internp->pixel_wand, color_name);
		if(status == MagickFalse) {
			GMAGICK_THROW_GMAGICKPIXEL_EXCEPTION(internp->pixel_wand, "Unable to construct GmagickPixel");
		}
	}
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto GmagickPixel GmagickPixel::setColor(string color)
	Sets the color of the pixel
*/
PHP_METHOD(gmagickpixel, setcolor)
{
	php_gmagickpixel_object *internp;
	char *color_name;
	int color_name_len;
	MagickBool status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &color_name, &color_name_len) == FAILURE) {
		return;
	}

	internp = (php_gmagickpixel_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	status = PixelSetColor(internp->pixel_wand, color_name);

	if(status == MagickFalse) {
		GMAGICK_THROW_GMAGICKPIXEL_EXCEPTION(internp->pixel_wand, "Unable to set GmagickPixel color");
	}

	GMAGICK_CHAIN_METHOD; 
}
/* }}} */

/* {{{ proto array GmagickPixel::getColor([boolean as_array = false, normalise_array = false])
	Returns the color of the pixel
*/
PHP_METHOD(gmagickpixel, getcolor)
{
	php_gmagickpixel_object *internp;
	zend_bool as_array = 0, normalise_array = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|bb", &as_array, &normalise_array) == FAILURE) {
		return;
	}

	internp = (php_gmagickpixel_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	if (!as_array) {
		char *buffer, *color_string;
		int len;
		
		color_string = PixelGetColorAsString(internp->pixel_wand);
		
		len = spprintf(&buffer, 50, "rgb(%s)", color_string);
		GMAGICK_FREE_MEMORY(char *, color_string);
		RETVAL_STRINGL(buffer, len, 0);
		return;
	} else {
		array_init(return_value);
		
		if (normalise_array == 1) {
			add_assoc_double(return_value, "r", PixelGetRed(internp->pixel_wand));
			add_assoc_double(return_value, "g", PixelGetGreen(internp->pixel_wand));
			add_assoc_double(return_value, "b", PixelGetBlue(internp->pixel_wand));
		} else {
			double red, green, blue;
			
			red = PixelGetRed(internp->pixel_wand ) * 255;
			green = PixelGetGreen(internp->pixel_wand ) * 255;
			blue = PixelGetBlue(internp->pixel_wand ) * 255;

			add_assoc_long(return_value, "r", (int)(red > 0.0 ? red + 0.5 : red - 0.5));
			add_assoc_long(return_value, "g", (int)(green > 0.0 ? green + 0.5 : green - 0.5));
			add_assoc_long(return_value, "b", (int)(blue > 0.0 ? blue + 0.5 : blue - 0.5));
		}
		return;
	}
}
/* }}} */

/* {{{ proto int GmagickPixel::getColorCount()
	Returns the color count associated with this color.
*/
PHP_METHOD(gmagickpixel, getcolorcount)
{
	php_gmagickpixel_object *internp;
	long color_count;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	internp = (php_gmagickpixel_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	color_count = PixelGetColorCount(internp->pixel_wand);
	RETVAL_LONG(color_count);
}
/* }}} */

/* {{{ proto float GmagickPixel::getColorValue(int color )
	Gets the normalized color of the GmagickPixel.
*/
PHP_METHOD(gmagickpixel, getcolorvalue)
{
	php_gmagickpixel_object *internp;
	long color;
	double color_value = 0;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &color) == FAILURE) {
		return;
	}

	internp = (php_gmagickpixel_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	switch (color) {

		case GMAGICK_COLOR_BLACK:
			color_value = PixelGetBlack(internp->pixel_wand);
		break;

		case GMAGICK_COLOR_BLUE:
			color_value = PixelGetBlue(internp->pixel_wand);
		break;

		case GMAGICK_COLOR_CYAN:
			color_value = PixelGetCyan(internp->pixel_wand);
		break;

		case GMAGICK_COLOR_GREEN:
			color_value = PixelGetGreen(internp->pixel_wand);
		break;

		case GMAGICK_COLOR_RED:
			color_value = PixelGetRed(internp->pixel_wand);
		break;

		case GMAGICK_COLOR_YELLOW:
			color_value = PixelGetYellow(internp->pixel_wand);
		break;

		case GMAGICK_COLOR_MAGENTA:
			color_value = PixelGetMagenta(internp->pixel_wand);
		break;

		case GMAGICK_COLOR_OPACITY:
			color_value = PixelGetOpacity(internp->pixel_wand);
		break;

		default:
			GMAGICK_THROW_GMAGICKPIXEL_EXCEPTION(internp->pixel_wand, "Unknown color type");
		break;
	}
	RETVAL_DOUBLE(color_value);
}
/* }}} */

/* {{{ proto GmagickPixel GmagickPixel::setColorValue(int color, float value )
	Sets the normalized color of the GmagickPixel.
*/
PHP_METHOD(gmagickpixel, setcolorvalue)
{
	php_gmagickpixel_object *internp;
	long color;
	double color_value;

	/* Parse parameters given to function */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ld", &color, &color_value) == FAILURE) {
		return;
	}

	internp = (php_gmagickpixel_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	switch (color) {

		case GMAGICK_COLOR_BLACK:
			PixelSetBlack(internp->pixel_wand, color_value);
		break;

		case GMAGICK_COLOR_BLUE:
			PixelSetBlue(internp->pixel_wand, color_value);
		break;

		case GMAGICK_COLOR_CYAN:
			PixelSetCyan(internp->pixel_wand, color_value);
		break;

		case GMAGICK_COLOR_GREEN:
			PixelSetGreen(internp->pixel_wand, color_value);
		break;

		case GMAGICK_COLOR_RED:
			PixelSetRed(internp->pixel_wand, color_value);
		break;

		case GMAGICK_COLOR_YELLOW:
			PixelSetYellow(internp->pixel_wand, color_value);
		break;

		case GMAGICK_COLOR_MAGENTA:
			PixelSetMagenta(internp->pixel_wand, color_value);
		break;

		case GMAGICK_COLOR_OPACITY:
			PixelSetOpacity(internp->pixel_wand, color_value);
		break;

		default:
			GMAGICK_THROW_GMAGICKPIXEL_EXCEPTION(internp->pixel_wand, "Unknown color type");
		break;
		
	}
	GMAGICK_CHAIN_METHOD;
}
/* }}} */
