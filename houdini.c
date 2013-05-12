/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Jeff Welch <whatthejeff@gmail.com>                           |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_houdini.h"

static zend_class_entry *houdini_ce_HoudiniException;

#define PHP_HOUDINI_CHECK_UTF8(string, length) do { \
	size_t position = 0; \
	int status; \
\
	while (position < length) { \
		php_houdini_next_utf8_char((const unsigned char *)string, length, &position, &status); \
		if (status != SUCCESS) { \
			zend_throw_exception(houdini_ce_HoudiniException, "Input string must be valid UTF-8", 0 TSRMLS_CC); \
			return; \
		} \
	} \
} while(0)

#define PHP_HOUDINI_FUNCTION(function_name) do{ \
	char *string = NULL; \
	int length; \
\
	gh_buf buffer = GH_BUF_INIT; \
\
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &string, &length) == FAILURE) { \
		return; \
	} \
\
	if (length == 0) { \
		RETURN_EMPTY_STRING(); \
	} \
\
	PHP_HOUDINI_CHECK_UTF8(string, length); \
\
	if (function_name(&buffer, (const uint8_t *)string, length)) { \
		RETVAL_STRINGL(buffer.ptr, buffer.size, 1); \
		gh_buf_free(&buffer); \
	} else { \
		RETVAL_STRINGL(string, length, 1); \
	} \
} while (0)


/* {{{ Note: The following section of utf8-related functions/macros was imported
   from ext/standard/html.c to provide `php_next_utf8_char()` for versions of PHP
   that are missing it. */
#define MB_FAILURE(pos, advance) do { \
	*cursor = pos + (advance); \
	*status = FAILURE; \
	return 0; \
} while (0)

#define CHECK_LEN(pos, chars_need) ((str_len - (pos)) >= (chars_need))

/* valid as single byte character or leading byte */
#define utf8_lead(c)  ((c) < 0x80 || ((c) >= 0xC2 && (c) <= 0xF4))
/* whether it's actually valid depends on other stuff;
 * this macro cannot check for non-shortest forms, surrogates or
 * code points above 0x10FFFF */
#define utf8_trail(c) ((c) >= 0x80 && (c) <= 0xBF)

static inline unsigned int php_houdini_next_utf8_char(
		const unsigned char *str,
		size_t str_len,
		size_t *cursor,
		int *status)
{
	size_t pos = *cursor;
	unsigned int this_char = 0;
	unsigned char c;

	*status = SUCCESS;
	assert(pos <= str_len);

	if (!CHECK_LEN(pos, 1))
		MB_FAILURE(pos, 1);

	/* We'll follow strategy 2. from section 3.6.1 of UTR #36:
	 * "In a reported illegal byte sequence, do not include any
	 *  non-initial byte that encodes a valid character or is a leading
	 *  byte for a valid sequence." */
	c = str[pos];
	if (c < 0x80) {
		this_char = c;
		pos++;
	} else if (c < 0xc2) {
		MB_FAILURE(pos, 1);
	} else if (c < 0xe0) {
		if (!CHECK_LEN(pos, 2))
			MB_FAILURE(pos, 1);

		if (!utf8_trail(str[pos + 1])) {
			MB_FAILURE(pos, utf8_lead(str[pos + 1]) ? 1 : 2);
		}
		this_char = ((c & 0x1f) << 6) | (str[pos + 1] & 0x3f);
		if (this_char < 0x80) { /* non-shortest form */
			MB_FAILURE(pos, 2);
		}
		pos += 2;
	} else if (c < 0xf0) {
		size_t avail = str_len - pos;

		if (avail < 3 ||
				!utf8_trail(str[pos + 1]) || !utf8_trail(str[pos + 2])) {
			if (avail < 2 || utf8_lead(str[pos + 1]))
				MB_FAILURE(pos, 1);
			else if (avail < 3 || utf8_lead(str[pos + 2]))
				MB_FAILURE(pos, 2);
			else
				MB_FAILURE(pos, 3);
		}

		this_char = ((c & 0x0f) << 12) | ((str[pos + 1] & 0x3f) << 6) | (str[pos + 2] & 0x3f);
		if (this_char < 0x800) { /* non-shortest form */
			MB_FAILURE(pos, 3);
		} else if (this_char >= 0xd800 && this_char <= 0xdfff) { /* surrogate */
			MB_FAILURE(pos, 3);
		}
		pos += 3;
	} else if (c < 0xf5) {
		size_t avail = str_len - pos;

		if (avail < 4 ||
				!utf8_trail(str[pos + 1]) || !utf8_trail(str[pos + 2]) ||
				!utf8_trail(str[pos + 3])) {
			if (avail < 2 || utf8_lead(str[pos + 1]))
				MB_FAILURE(pos, 1);
			else if (avail < 3 || utf8_lead(str[pos + 2]))
				MB_FAILURE(pos, 2);
			else if (avail < 4 || utf8_lead(str[pos + 3]))
				MB_FAILURE(pos, 3);
			else
				MB_FAILURE(pos, 4);
		}

		this_char = ((c & 0x07) << 18) | ((str[pos + 1] & 0x3f) << 12) | ((str[pos + 2] & 0x3f) << 6) | (str[pos + 3] & 0x3f);
		if (this_char < 0x10000 || this_char > 0x10FFFF) { /* non-shortest form or outside range */
			MB_FAILURE(pos, 4);
		}
		pos += 4;
	} else {
		MB_FAILURE(pos, 1);
	}

	*cursor = pos;
	return this_char;
}
/* }}} */


/* {{{ string houdini_escape_html(string str [, bool $secure = true ])
   Escapes an HTML string */
PHP_FUNCTION(houdini_escape_html)
{
	char *string = NULL;
	int length;
	zend_bool secure = 1;

	gh_buf buffer = GH_BUF_INIT;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &string, &length, &secure) == FAILURE) {
		return;
	}

	if (length == 0) {
		RETURN_EMPTY_STRING();
	}

	PHP_HOUDINI_CHECK_UTF8(string, length);

	if (houdini_escape_html0(&buffer, (const uint8_t *)string, length, secure)) {
		RETVAL_STRINGL(buffer.ptr, buffer.size, 1);
		gh_buf_free(&buffer);
	} else {
		RETVAL_STRINGL(string, length, 1);
	}
}
/* }}} */

/* {{{ proto string houdini_unescape_html(string str)
   Unescapes an HTML string */
PHP_FUNCTION(houdini_unescape_html)
{
	PHP_HOUDINI_FUNCTION(houdini_unescape_html);
}
/* }}} */

/* {{{ proto string houdini_escape_js(string str)
   Escapes a JavaScript string */
PHP_FUNCTION(houdini_escape_js)
{
	PHP_HOUDINI_FUNCTION(houdini_escape_js);
}
/* }}} */

/* {{{ proto string houdini_unescape_js(string str)
   Unescapes a JavaScript string */
PHP_FUNCTION(houdini_unescape_js)
{
	PHP_HOUDINI_FUNCTION(houdini_unescape_js);
}
/* }}} */

/* {{{ proto string houdini_escape_uri(string str)
   Escapes a URI string */
PHP_FUNCTION(houdini_escape_uri)
{
	PHP_HOUDINI_FUNCTION(houdini_escape_uri);
}
/* }}} */

/* {{{ proto string houdini_unescape_uri(string str)
   Unescapes a URI string */
PHP_FUNCTION(houdini_unescape_uri)
{
	PHP_HOUDINI_FUNCTION(houdini_unescape_uri);
}
/* }}} */

/* {{{ proto string houdini_escape_url(string str)
   Escapes a URL string */
PHP_FUNCTION(houdini_escape_url)
{
	PHP_HOUDINI_FUNCTION(houdini_escape_url);
}
/* }}} */

/* {{{ proto string houdini_unescape_url(string str)
   Unescapes a URL string */
PHP_FUNCTION(houdini_unescape_url)
{
	PHP_HOUDINI_FUNCTION(houdini_unescape_url);
}
/* }}} */

/* {{{ proto string houdini_escape_xml(string str)
   Escapes an XML string */
PHP_FUNCTION(houdini_escape_xml)
{
	PHP_HOUDINI_FUNCTION(houdini_escape_xml);
}
/* }}} */

/* {{{ proto string houdini_escape_href(string str)
   Escapes an HREF string */
PHP_FUNCTION(houdini_escape_href)
{
	PHP_HOUDINI_FUNCTION(houdini_escape_href);
}
/* }}} */

const zend_function_entry houdini_functions[] = {
	PHP_FE(houdini_escape_html,      NULL)
	PHP_FE(houdini_unescape_html,    NULL)
	PHP_FE(houdini_escape_js,        NULL)
	PHP_FE(houdini_unescape_js,      NULL)
	PHP_FE(houdini_escape_uri,       NULL)
	PHP_FE(houdini_unescape_uri,     NULL)
	PHP_FE(houdini_escape_url,       NULL)
	PHP_FE(houdini_unescape_url,     NULL)
	PHP_FE(houdini_escape_xml,       NULL)
	PHP_FE(houdini_escape_href,      NULL)
	{ NULL, NULL, NULL }
};

PHP_MINIT_FUNCTION(houdini)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "HoudiniException", NULL);
	houdini_ce_HoudiniException = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL  TSRMLS_CC);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(houdini)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(houdini)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Houdini Support", "enabled");
	php_info_print_table_row(2, "Version", PHP_HOUDINI_EXT_VERSION);
	php_info_print_table_end();
}

zend_module_entry houdini_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_HOUDINI_EXT_NAME,
	houdini_functions,
	PHP_MINIT(houdini),
	PHP_MSHUTDOWN(houdini),
	NULL,
	NULL,
	PHP_MINFO(houdini),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_HOUDINI_EXT_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HOUDINI
ZEND_GET_MODULE(houdini)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
