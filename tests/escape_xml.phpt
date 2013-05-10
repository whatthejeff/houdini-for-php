--TEST--
Test xml escaping with `houdini_escape_xml()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    '<some_tag/>' => '&lt;some_tag/&gt;',

    // Double quote
    '<some_tag some_attr="some value"/>' => '&lt;some_tag some_attr=&quot;some value&quot;/&gt;',

    // Single quote
    '<some_tag some_attr=\'some value\'/>' => '&lt;some_tag some_attr=&apos;some value&apos;/&gt;',

    // Ampersand
    '<b>Bourbon & Branch</b>' => '&lt;b&gt;Bourbon &amp; Branch&lt;/b&gt;',
);

foreach($fixtures as $fixture => $expected) {
    var_dump($expected === houdini_escape_xml($fixture));
}

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
