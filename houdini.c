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

#include "php.h"
#include "ext/standard/info.h"
#include "ext/standard/html.h"
#include "houdini.h"
#include "php_houdini.h"

#include <zend_exceptions.h>

static int le_houdini;

static zend_class_entry *houdini_ce_HoudiniException;

#define PHP_HOUDINI_CHECK_UTF8(string, length) \
	if (!php_houdini_check_utf8_encoding(string, length)) { \
		zend_throw_exception(houdini_ce_HoudiniException, "Input string must be valid UTF-8", 0 TSRMLS_CC); \
		return; \
	}

#define PHP_HOUDINI_FUNCTION(function_name) \
	PHP_FUNCTION(function_name) \
	{ \
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
		PHP_HOUDINI_CHECK_UTF8(string, length) \
\
		if (function_name(&buffer, (const uint8_t *)string, length)) { \
			RETVAL_STRINGL(buffer.ptr, buffer.size, 1); \
			gh_buf_free(&buffer); \
		} else { \
			RETVAL_STRINGL(string, length, 1); \
		} \
	}

static int php_houdini_check_utf8_encoding(char utf8[], int len)
{
	size_t pos = 0;
	int status;

	while (pos < len) {
		php_next_utf8_char((const unsigned char *)utf8, len, &pos, &status);
		if (status != SUCCESS) {
			return 0;
		}
	}
	return 1;
}

const zend_function_entry houdini_functions[] = {
	PHP_FE(houdini_escape_html,		NULL)
	PHP_FE(houdini_unescape_html,	NULL)
	PHP_FE(houdini_escape_js,		NULL)
	PHP_FE(houdini_unescape_js,		NULL)
	PHP_FE(houdini_escape_uri,		NULL)
	PHP_FE(houdini_unescape_uri,	NULL)
	PHP_FE(houdini_escape_url,		NULL)
	PHP_FE(houdini_unescape_url,	NULL)
	PHP_FE(houdini_escape_xml,		NULL)
	PHP_FE(houdini_escape_href,		NULL)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(houdini)
{
	php_houdini_init(TSRMLS_C);
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

/* proto string houdini_escape_html(string str [, bool $secure = true ])
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

	PHP_HOUDINI_CHECK_UTF8(string, length)

	if (houdini_escape_html0(&buffer, (const uint8_t *)string, length, secure)) {
		RETVAL_STRINGL(buffer.ptr, buffer.size, 1);
		gh_buf_free(&buffer);
	} else {
		RETVAL_STRINGL(string, length, 1);
	}
}

/* proto string houdini_unescape_html(string str)
   Unescapes an HTML string */
PHP_HOUDINI_FUNCTION(houdini_unescape_html)

/* proto string houdini_escape_js(string str)
   Escapes a JavaScript string */
PHP_HOUDINI_FUNCTION(houdini_escape_js)

/* proto string houdini_unescape_js(string str)
   Unescapes a JavaScript string */
PHP_HOUDINI_FUNCTION(houdini_unescape_js)

/* proto string houdini_escape_uri(string str)
   Escapes a URI string */
PHP_HOUDINI_FUNCTION(houdini_escape_uri)

/* proto string houdini_unescape_uri(string str)
   Unescapes a URI string */
PHP_HOUDINI_FUNCTION(houdini_unescape_uri)

/* proto string houdini_escape_url(string str)
   Escapes a URL string */
PHP_HOUDINI_FUNCTION(houdini_escape_url)

/* proto string houdini_unescape_url(string str)
   Unescapes a URL string */
PHP_HOUDINI_FUNCTION(houdini_unescape_url)

/* proto string houdini_escape_xml(string str)
   Escapes an XML string */
PHP_HOUDINI_FUNCTION(houdini_escape_xml)

/* proto string houdini_escape_href(string str)
   Escapes an HREF string */
PHP_HOUDINI_FUNCTION(houdini_escape_href)

zend_function_entry houdini_exception_methods[] = {
	PHP_FE_END
};

#if PHP_VERSION_ID < 50200
# define php_houdini_exception_get_default() zend_exception_get_default()
#else
# define php_houdini_exception_get_default() zend_exception_get_default(TSRMLS_C)
#endif

void php_houdini_init(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "HoudiniException", houdini_exception_methods);
	houdini_ce_HoudiniException = zend_register_internal_class_ex(&ce, php_houdini_exception_get_default(), NULL  TSRMLS_CC);
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
