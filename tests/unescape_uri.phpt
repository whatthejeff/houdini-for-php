--TEST--
Test uri escaping with `houdini_unescape_uri()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    // Incomplete
    '%'     => '%',
    'http%' => 'http%',

    // Tags
    'fo%3Co%3Ebar' => 'fo<o>bar',

    // Space
    'a%20space'             => 'a space',
    'a%20%20%20sp%20ace%20' => 'a   sp ace ',
    'a+space'               => 'a+space',

    // Mixed characters
    'q1%212%22%27w%245%267%2Fz8%29%3F%5C' => 'q1!2"\'w$5&7/z8)?\\',
    'q1!2%22\'w$5&7/z8)?%5C'              =>  'q1!2"\'w$5&7/z8)?\\',

    // Multibyte
    '%E3%81%BE%E3%81%A4%E3%82%82%E3%81%A8'    => "\xE3\x81\xBE\xE3\x81\xA4\xE3\x82\x82\xE3\x81\xA8",
    '%E3%81%BE%E3%81%A4%20%E3%82%82%E3%81%A8' => "\xE3\x81\xBE\xE3\x81\xA4 \xE3\x82\x82\xE3\x81\xA8",
);

foreach($fixtures as $fixture => $expected) {
    var_dump($expected === houdini_unescape_uri($fixture));
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
