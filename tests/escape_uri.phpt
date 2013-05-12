--TEST--
Test uri escaping with `houdini_escape_uri()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip: houdini extension is not loaded'; ?>
--FILE--
<?php

$fixtures = array(
    // Tags
    'fo<o>bar',

    // Space
    'a space',
    'a   sp ace ',

    // Multibyte
    "\xE3\x81\xBE\xE3\x81\xA4\xE3\x82\x82\xE3\x81\xA8",
    "\xE3\x81\xBE\xE3\x81\xA4 \xE3\x82\x82\xE3\x81\xA8",
);

foreach($fixtures as $fixture) {
    var_export(houdini_escape_uri($fixture));
    print "\n";
}

?>
--EXPECT--
'fo%3Co%3Ebar'
'a%20space'
'a%20%20%20sp%20ace%20'
'%E3%81%BE%E3%81%A4%E3%82%82%E3%81%A8'
'%E3%81%BE%E3%81%A4%20%E3%82%82%E3%81%A8'
