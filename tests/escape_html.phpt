--TEST--
Test html escaping with `houdini_escape_html()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    '<some_tag/>' => '&lt;some_tag&#47;&gt;',

    // Double quote
    '<some_tag some_attr="some value"/>' => '&lt;some_tag some_attr=&quot;some value&quot;&#47;&gt;',

    // Single quote
    '<some_tag some_attr=\'some value\'/>' => '&lt;some_tag some_attr=&#39;some value&#39;&#47;&gt;',

    // Ampersand
    '<b>Bourbon & Branch</b>' => '&lt;b&gt;Bourbon &amp; Branch&lt;&#47;b&gt;',
);

foreach($fixtures as $fixture => $expected) {
    var_dump($expected === houdini_escape_html($fixture));       // Secure by default
    var_dump($expected === houdini_escape_html($fixture, true)); // Secure set explicitly
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
