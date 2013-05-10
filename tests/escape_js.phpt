--TEST--
Test js escaping with `houdini_escape_js()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    // Quotes and newlines
    "This \"thing\" is really\n netos\r\n\n'" => 'This \\"thing\\" is really\\n netos\\n\\n\\\'',

    // Backslashes
    'backslash\\test' => 'backslash\\\\test',

    // Close tags
    'keep <open>, but dont </close> tags' => 'keep <open>, but dont <\\/close> tags',
);

foreach($fixtures as $fixture => $expected) {
    var_dump($expected === houdini_escape_js($fixture));
}

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
