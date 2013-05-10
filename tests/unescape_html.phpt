--TEST--
Test html unescaping with `houdini_unescape_html()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    '&lt;some_tag&#47;&gt;' => '<some_tag/>',

    // Double quote
    '&lt;some_tag some_attr=&quot;some value&quot;&#47;&gt;' => '<some_tag some_attr="some value"/>',

    // Single quote
    '&lt;some_tag some_attr=&#39;some value&#39;&#47;&gt;' => '<some_tag some_attr=\'some value\'/>',

    // Ampersand
    '&lt;b&gt;Bourbon &amp; Branch&lt;&#47;b&gt;' => '<b>Bourbon & Branch</b>',

    // Incompletely escaped
    '&'   => '&',
    '&lt' => '&lt',
);

foreach($fixtures as $fixture => $expected) {
    var_dump($expected === houdini_unescape_html($fixture));
}

?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
