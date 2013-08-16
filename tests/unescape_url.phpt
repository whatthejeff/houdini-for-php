--TEST--
Test url unescaping with `houdini_unescape_url()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip: houdini extension is not loaded'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    'http%3A%2F%2Fwww.homerun.com%2F',
    'http://www.homerun.com/',

    // Incomplete
    '%',
    'http%',

    // Tags
    'fo%3Co%3Ebar',

    // Spaces
    'a%20space',
    'a%20%20%20sp%20ace%20',
    'a+space',

    // Mixed characters
    'q1%212%22%27w%245%267%2Fz8%29%3F%5C',
    'q1!2%22\'w$5&7/z8)?%5C',
);

foreach($fixtures as $fixture) {
    var_export(houdini_unescape_url($fixture));
    print "\n";
}

$multibyte_fixtures = array(
    '%E3%81%BE%E3%81%A4%E3%82%82%E3%81%A8',
    '%E3%81%BE%E3%81%A4%20%E3%82%82%E3%81%A8',
);

foreach($multibyte_fixtures as $fixture) {
    var_export(bin2hex(houdini_unescape_url($fixture)));
    print "\n";
}

?>
--EXPECT--
'http://www.homerun.com'
'http://www.homerun.com/'
'%'
'http%'
'fo<o>bar'
'a space'
'a   sp ace '
'a space'
'q1!2"\'w$5&7/z8)?\\'
'q1!2"\'w$5&7/z8)?\\'
'e381bee381a4e38282e381a8'
'e381bee381a420e38282e381a8'

