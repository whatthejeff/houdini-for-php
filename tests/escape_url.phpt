--TEST--
Test url escaping with `houdini_escape_url()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip: houdini extension is not loaded'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    'http://www.homerun.com/',

    // Tags
    'fo<o>bar',

    // Space
    'a space',
    'a   sp ace ',

    // Mixed characters
    'q1!2"\'w$5&7/z8)?\\',

    // Multibyte
    "\xE3\x81\xBE\xE3\x81\xA4\xE3\x82\x82\xE3\x81\xA8" ,
    "\xE3\x81\xBE\xE3\x81\xA4 \xE3\x82\x82\xE3\x81\xA8",
);

foreach($fixtures as $fixture) {
    var_export(houdini_escape_url($fixture));
    print "\n";
}

?>
--EXPECT--
'http%3A%2F%2Fwww.homerun.com%2F'
'fo%3Co%3Ebar'
'a+space'
'a+++sp+ace+'
'q1%212%22%27w%245%267%2Fz8%29%3F%5C'
'%E3%81%BE%E3%81%A4%E3%82%82%E3%81%A8'
'%E3%81%BE%E3%81%A4+%E3%82%82%E3%81%A8'
