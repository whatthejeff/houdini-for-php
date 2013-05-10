Houdini for PHP
===============

[Houdini](https://github.com/vmg/houdini/) is a simple API for escaping text for the web. And unescaping it.
But that kind of breaks the joke in the name so nevermind.

## Requirements

Houdini for PHP works with PHP 5.2 or later.

## Installation

    phpize
    ./configure --enable-houdini
    make
    sudo make install

## Tests

    make test

## Functions

```php
/**
 * Escape an HTML string
 *
 * @param  string $string   The HTML string to escape
 * @param  boolean $secure  If forward slashes should be trusted
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_escape_html($string, $secure = true);

/**
 * Unescape an HTML string
 *
 * @param  string $string   The HTML string to unescape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_unescape_html($string);

/**
 * Escape a JavaScript string
 *
 * @param  string $string   The JavaScript string to escape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_escape_js($string);

/**
 * Unescape JavaScript string
 *
 * @param  string $string   The JavaScript string to unescape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_unescape_js($string);

/**
 * Escape a URI string
 *
 * @param  string $string   The URI string to Escape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_escape_uri($string);

/**
 * Unescape a URI string
 *
 * @param  string $string   The URI string to unescape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_unescape_uri($string);

/**
 * Escape a URL string
 *
 * @param  string $string   The URL string to Escape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_escape_url($string);

/**
 * Unescape a URL string
 *
 * @param  string $string   The URL string to unescape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_unescape_url($string);

/**
 * Escape an XML string
 *
 * @param  string $string   The XML string to Escape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_escape_xml($string);

/**
 * Escape an href string
 *
 * @param  string $string   The href string to escape
 * @return string
 *
 * @throws HoudiniException If input is not valid UTF-8
 */
houdini_escape_href($string);
```

## Acknowledgements

This extension simply wraps [houdini](https://github.com/vmg/houdini/). Please give all praise to its author, [@vmg](https://twitter.com/vmg).

## License

Houdini for PHP is licensed under the [PHP license](LICENSE).