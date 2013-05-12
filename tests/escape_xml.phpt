--TEST--
Test xml escaping with `houdini_escape_xml()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip: houdini extension is not loaded'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    '<some_tag/>',

    // Double quote
    '<some_tag some_attr="some value"/>',

    // Single quote
    '<some_tag some_attr=\'some value\'/>',

    // Ampersand
    '<b>Bourbon & Branch</b>',
);

foreach($fixtures as $fixture) {
    var_export(houdini_escape_xml($fixture));
    print "\n";
}


?>
--EXPECT--
'&lt;some_tag/&gt;'
'&lt;some_tag some_attr=&quot;some value&quot;/&gt;'
'&lt;some_tag some_attr=&apos;some value&apos;/&gt;'
'&lt;b&gt;Bourbon &amp; Branch&lt;/b&gt;'
