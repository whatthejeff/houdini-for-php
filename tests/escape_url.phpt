--TEST--
Test url escaping with `houdini_escape_url()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    'http://www.homerun.com/' => 'http%3A%2F%2Fwww.homerun.com%2F',

    // Tags
    'fo<o>bar' => 'fo%3Co%3Ebar',

    // Space
    'a space'     => 'a+space',
    'a   sp ace ' => 'a+++sp+ace+',

    // Mixed characters
    'q1!2"\'w$5&7/z8)?\\' => 'q1%212%22%27w%245%267%2Fz8%29%3F%5C',

    // Multibyte
    "\xE3\x81\xBE\xE3\x81\xA4\xE3\x82\x82\xE3\x81\xA8"  => '%E3%81%BE%E3%81%A4%E3%82%82%E3%81%A8',
    "\xE3\x81\xBE\xE3\x81\xA4 \xE3\x82\x82\xE3\x81\xA8" => '%E3%81%BE%E3%81%A4+%E3%82%82%E3%81%A8',
);

foreach($fixtures as $fixture => $expected) {
    var_dump($expected === houdini_escape_url($fixture));
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
