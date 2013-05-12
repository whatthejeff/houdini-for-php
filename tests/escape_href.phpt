--TEST--
Test href escaping with `houdini_escape_href()`
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
    "\xE3\x81\xBE\xE3\x81\xA4\xE3\x82\x82\xE3\x81\xA8",
    "\xE3\x81\xBE\xE3\x81\xA4 \xE3\x82\x82\xE3\x81\xA8",
);

foreach($fixtures as $fixture) {
    var_export(houdini_escape_href($fixture));
    print "\n";
}

?>
--EXPECT--
'http://www.homerun.com/'
'fo%3Co%3Ebar'
'a%20space'
'a%20%20%20sp%20ace%20'
'q1!2%22&#x27;w$5&amp;7/z8)?%5C'
'%E3%81%BE%E3%81%A4%E3%82%82%E3%81%A8'
'%E3%81%BE%E3%81%A4%20%E3%82%82%E3%81%A8'
