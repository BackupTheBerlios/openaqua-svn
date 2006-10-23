<?php
/**
 * Empty Plugin which supports the Adobe Spry Axaj Library for other projects
 *
 * @License: BSD License http://www.opensource.org/licenses/bsd-license.php
 * @Author: Adobe http://labs.adobe.com/wiki/index.php/Spry
 * @Version: Pre-Release 1.3
 */
 
if (!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if (!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');


// -----------------------------------------------------------------


/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_adobespry extends DokuWiki_Syntax_Plugin {

    var $stack = array();
 
    /**
     * return some info
     */
    function getInfo(){
        return array(
            'author' => 'Adobe Labs',
            'email'  => 'info@openaqua.de',
            'date'   => '2006-10-23',
            'name'   => 'Adobe Spry Plugin',
            'desc'   => 'An empty Plugin which offers Ajax functionality to other projects',
            'url'    => 'http://labs.adobe.com/wiki/index.php/Spry',
        );
    }
 
 
    function getType() { return 'container'; }
    function getSort() { return 10; }                // before preformatted (20)
    function connectTo($mode) {}
    function postConnect() { }
    function handle($match, $state, $pos, &$handler) { array($state, ''); }
    function render($mode, &$renderer, $data) { return false; }
}
