--TEST--
Test fails for invalid utf8
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip: houdini extension is not loaded'; ?>
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
    printf('%s: ', $fixture);

    try {
        call_user_func($fixture, "\xEA");
    } catch(HoudiniException $e) {
        print $e->getMessage();
    }

    print "\n";
}

?>
--EXPECT--
houdini_escape_html: Input string must be valid UTF-8
houdini_unescape_html: Input string must be valid UTF-8
houdini_escape_xml: Input string must be valid UTF-8
houdini_escape_uri: Input string must be valid UTF-8
houdini_escape_url: Input string must be valid UTF-8
houdini_escape_href: Input string must be valid UTF-8
houdini_unescape_uri: Input string must be valid UTF-8
houdini_unescape_url: Input string must be valid UTF-8
houdini_escape_js: Input string must be valid UTF-8
houdini_unescape_js: Input string must be valid UTF-8
