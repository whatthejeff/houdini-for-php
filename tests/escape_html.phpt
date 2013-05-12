--TEST--
Test html escaping with `houdini_escape_html()`
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
    var_export(houdini_escape_html($fixture));        // Secure by default
    print "\n";
    var_export(houdini_escape_html($fixture, true));  // Secure set explicitly
    print "\n";
}

?>
--EXPECT--
'&lt;some_tag&#47;&gt;'
'&lt;some_tag&#47;&gt;'
'&lt;some_tag some_attr=&quot;some value&quot;&#47;&gt;'
'&lt;some_tag some_attr=&quot;some value&quot;&#47;&gt;'
'&lt;some_tag some_attr=&#39;some value&#39;&#47;&gt;'
'&lt;some_tag some_attr=&#39;some value&#39;&#47;&gt;'
'&lt;b&gt;Bourbon &amp; Branch&lt;&#47;b&gt;'
'&lt;b&gt;Bourbon &amp; Branch&lt;&#47;b&gt;'
