--TEST--
Test html unescaping with `houdini_unescape_html()`
--SKIPIF--
<?php if (!extension_loaded('houdini')) print 'skip: houdini extension is not loaded'; ?>
--FILE--
<?php

$fixtures = array(
    // Basic
    '&lt;some_tag&#47;&gt;',

    // Double quote
    '&lt;some_tag some_attr=&quot;some value&quot;&#47;&gt;',

    // Single quote
    '&lt;some_tag some_attr=&#39;some value&#39;&#47;&gt;',

    // Ampersand
    '&lt;b&gt;Bourbon &amp; Branch&lt;&#47;b&gt;',

    // Incompletely escaped
    '&',
    '&lt',
);

foreach($fixtures as $fixture) {
    var_export(houdini_unescape_html($fixture));
    print "\n";
}

?>
--EXPECT--
'<some_tag/>'
'<some_tag some_attr="some value"/>'
'<some_tag some_attr=\'some value\'/>'
'<b>Bourbon & Branch</b>'
'&'
'&lt'
