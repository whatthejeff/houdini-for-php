--TEST--
Test js unescaping with `houdini_unescape_js()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip: houdini extension is not loaded'; ?>
--FILE--
<?php

$fixtures = array(
    // Quotes and newlines
    'This \\"thing\\" is really\\n netos\\n\\n\\\'',

    // Backslashes
    'backslash\\\\test',

    // Close tags
    'keep <open>, but dont <\\/close> tags',
);

foreach($fixtures as $fixture) {
    var_export(houdini_unescape_js($fixture));
    print "\n";
}

?>
--EXPECT--
'This "thing" is really
 netos

\''
'backslash\\test'
'keep <open>, but dont </close> tags'
