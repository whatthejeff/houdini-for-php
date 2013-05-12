--TEST--
Test js escaping with `houdini_escape_js()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip: houdini extension is not loaded'; ?>
--FILE--
<?php

$fixtures = array(
    // Quotes and newlines
    "This \"thing\" is really\n netos\r\n\n'",

    // Backslashes
    'backslash\\test',

    // Close tags
    'keep <open>, but dont </close> tags',
);

foreach($fixtures as $fixture) {
    var_export(houdini_escape_js($fixture));
    print "\n";
}

?>
--EXPECT--
'This \\"thing\\" is really\\n netos\\n\\n\\\''
'backslash\\\\test'
'keep <open>, but dont <\\/close> tags'
