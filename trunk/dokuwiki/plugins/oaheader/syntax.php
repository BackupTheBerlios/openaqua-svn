<?php
/**
 * Plugin Numbered Headings: Plugin to add numbered headings to DokuWiki-Syntax
 * 
 * Usage:   ====== - Heading Level 1======
 *          ===== - Heading Level 2 =====
 *          ===== - Heading Level 2 =====
 *              ...
 * 
 * =>       1 Heading Level 1
 *              1.1 Heading Level 2
 *              1.2 Heading Level 2
 *          ...
 * 
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Lars J. Metz <dokuwiki@meistermetz.de>  
 */
 
if(!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if(!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');
 
class syntax_plugin_oaheader extends DokuWiki_Syntax_Plugin {
 
    // level to start with numbered headings (default = 2)
    var $startlevel = 2;
 
    var $levels = array( '======'=>1,
                         '====='=>2,
                         '===='=>3,
                         '==='=>4,
                         '=='=>5);
      
    function getInfo(){
      return array(
        'author' => 'Claudia Behrens',
        'email'  => 'Claudia.Behrens@openaqua.de',
        'date'   => '2006-11-04',
        'name'   => 'OA Box Plugin',
        'desc'   => 'oa header',
        'url'    => '',
      );
    }
 
    function getType(){
        return 'substition';
    }
    
    function connectTo($mode) {
        $this->Lexer->addSpecialPattern( '[ \t]*={2,6}\s?[^\n]+={2,6}[ \t]*(?=\n)',
                                         $mode,
                                         'plugin_oaheader');
    }
    
    function getSort() {
        return 45; 
    }
 
    function handle($match, $state, $pos, &$handler){
        // just return to the default behaviour
        $handler->header($match, $state, $pos);
        return true;
    }
 
    function render($format, &$renderer, $data) {
        //do nothing (already done by original render-method)
    }
}
//Setup VIM: ex: et ts=4 enc=utf-8 :
?>

