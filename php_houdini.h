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

#ifndef PHP_HOUDINI_H
#define PHP_HOUDINI_H

#define PHP_HOUDINI_EXT_NAME "houdini"
#define PHP_HOUDINI_EXT_VERSION "1.0.0"

#include "php.h"
#include "ext/standard/info.h"
#include "zend_exceptions.h"
#include "houdini/houdini.h"

extern zend_module_entry houdini_module_entry;
#define phpext_houdini_ptr &houdini_module_entry

PHP_MINIT_FUNCTION(houdini);
PHP_MSHUTDOWN_FUNCTION(houdini);
PHP_MINFO_FUNCTION(houdini);

PHP_FUNCTION(houdini_escape_html);
PHP_FUNCTION(houdini_unescape_html);
PHP_FUNCTION(houdini_escape_js);
PHP_FUNCTION(houdini_unescape_js);
PHP_FUNCTION(houdini_escape_uri);
PHP_FUNCTION(houdini_unescape_uri);
PHP_FUNCTION(houdini_escape_url);
PHP_FUNCTION(houdini_unescape_url);
PHP_FUNCTION(houdini_escape_xml);
PHP_FUNCTION(houdini_escape_href);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
