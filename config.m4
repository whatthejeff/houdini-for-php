dnl $Id$
dnl config.m4 for extension houdini

PHP_ARG_ENABLE(houdini, whether to enable houdini support,
[  --enable-houdini           Enable houdini support])

if test "$PHP_HOUDINI" != "no"; then
  PHP_NEW_EXTENSION(houdini, houdini.c houdini_href_e.c houdini_html_e.c houdini_html_u.c houdini_js_e.c houdini_js_u.c houdini_uri_e.c houdini_uri_u.c houdini_xml_e.c buffer.c, $ext_shared)
fi
