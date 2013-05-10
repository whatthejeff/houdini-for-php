--TEST--
Test href escaping with `houdini_escape_href()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    'http://www.homerun.com/' => 'http://www.homerun.com/',

    // Tags
    'fo<o>bar' => 'fo%3Co%3Ebar',

    // Space
    'a space'     => 'a%20space',
    'a   sp ace ' => 'a%20%20%20sp%20ace%20',

    // Mixed characters
    'q1!2"\'w$5&7/z8)?\\' => 'q1!2%22&#x27;w$5&amp;7/z8)?%5C',

    // Multibyte
    "\xE3\x81\xBE\xE3\x81\xA4\xE3\x82\x82\xE3\x81\xA8"  => '%E3%81%BE%E3%81%A4%E3%82%82%E3%81%A8',
    "\xE3\x81\xBE\xE3\x81\xA4 \xE3\x82\x82\xE3\x81\xA8" => '%E3%81%BE%E3%81%A4%20%E3%82%82%E3%81%A8',
);

foreach($fixtures as $fixture => $expected) {
    var_dump($expected === houdini_escape_href($fixture));
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
