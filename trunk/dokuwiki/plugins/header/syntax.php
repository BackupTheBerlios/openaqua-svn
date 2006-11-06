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
 
class syntax_plugin_header extends DokuWiki_Syntax_Plugin {
 
    // level to start with numbered headings (default = 2)
    var $startlevel = 2;
 
    var $levels = array( '======'=>1,
                         '====='=>2,
                         '===='=>3,
                         '==='=>4,
                         '=='=>5);
      
    var $count = array(  1=>0,
                         2=>0,
                         3=>0,
                         4=>0,
                         5=>0);
   
    function getInfo(){
        return array( 'author' => 'Lars J. Metz',
                      'email'  => 'dokuwiki@meistermetz.de',
                      'date'   => '2006-08-24',
                      'name'   => 'Plugin: Numbered Headings',
                      'desc'   => 'Adds numbered headings to DokuWiki',
                      'url'    => 'http://wiki.splitbrain.org/plugin:NumberedHeadings');
    }
 
    function getType(){
        return 'substition';
    }
    
    function connectTo($mode) {
        $this->Lexer->addSpecialPattern( '[ \t]*={2,6}\s?\-[^\n]+={2,6}[ \t]*(?=\n)',
                                         $mode,
                                         'plugin_header');
    }
    
    function getSort() {
        return 45; 
    }
 
    function handle($match, $state, $pos, &$handler){
        
        // define the level of the heading
        $heading = '';
        preg_match('/(={2,})/', $match, $heading);
        $level = $this->levels[$heading[0]];
          
        // increment the number of the heading
        $this->headingCount[$level]++; 
      
        $headingNumber = '';
        for ($i=$this->startlevel;$i<=5;$i++) {
             
            // reset the number of the subheadings
            if ($i>$level) {
                $this->headingCount[$i] = 0;
            }
             
            // build the number of the heading
            $headingNumber .= ($this->headingCount[$i]!=0) ? $this->headingCount[$i].'.' : '';
        }
        
        // insert the number (without the last '.')...        
        $match = preg_replace('/(={2,}\s?)\-/', '${1}'.substr($headingNumber,0,-1), $match);
          
        // ... and return to original behavior
        $handler->header($match, $state, $pos);
                   
        return true;
    }
 
    function render($format, &$renderer, $data) {
        //do nothing (already done by original render-method)
    }
}
//Setup VIM: ex: et ts=4 enc=utf-8 :
?>

