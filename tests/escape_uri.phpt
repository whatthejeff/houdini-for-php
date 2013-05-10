--TEST--
Test uri escaping with `houdini_escape_uri()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    // Tags
    'fo<o>bar' => 'fo%3Co%3Ebar',

    // Space
    'a space'     => 'a%20space',
    'a   sp ace ' => 'a%20%20%20sp%20ace%20',

    // Multibyte
    "\xE3\x81\xBE\xE3\x81\xA4\xE3\x82\x82\xE3\x81\xA8"  => '%E3%81%BE%E3%81%A4%E3%82%82%E3%81%A8',
    "\xE3\x81\xBE\xE3\x81\xA4 \xE3\x82\x82\xE3\x81\xA8" => '%E3%81%BE%E3%81%A4%20%E3%82%82%E3%81%A8',
);

foreach($fixtures as $fixture => $expected) {
    var_dump($expected === houdini_escape_uri($fixture));
}

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
