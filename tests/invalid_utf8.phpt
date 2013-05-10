--TEST--
Test fails for invalid utf8
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    'houdini_escape_html',
    'houdini_unescape_html',
    'houdini_escape_xml',
    'houdini_escape_uri',
    'houdini_escape_url',
    'houdini_escape_href',
    'houdini_unescape_uri',
    'houdini_unescape_url',
    'houdini_escape_js',
    'houdini_unescape_js',
);

foreach($fixtures as $fixture) {
    try {
        call_user_func($fixture, "\xEA");
    } catch(HoudiniException $e) {
        var_dump('Input string must be valid UTF-8' === $e->getMessage());
    }
}

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
