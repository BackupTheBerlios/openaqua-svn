<?php
/**
 * OA Box Plugin: Maps blocks in html divs
 *
 * Syntax:     <box classes|id>
 *   classes   one or more classes used to style the box, several predefined styles included in style.css
 *   id     (optional) all text after '|' will be rendered above the main code text with a
 *             different style.
 *
 * Basing on  
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Christopher Smith <chris@jal_oaboxakai.co.uk>  
 */

if(!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if(!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class

 */
class syntax_plugin_oabox extends DokuWiki_Syntax_Plugin {

    var $title_mode = false;

    /**
     * return some info
     */
    function getInfo(){
      return array(
        'author' => 'Claudia Behrens',
        'email'  => 'Claudia.Behrens@openaqua.de',
        'date'   => '2006-11-04',
        'name'   => 'OA Box Plugin',
        'desc'   => 'div Boxes',
        'url'    => '',
      );
    }

    function getType(){ return 'container';}
    function getAllowedTypes() { return array('container','substition','protected','disabled','formatting','paragraphs','baseonly'); }

    function getPType(){ return 'block';}

    // must return a number lower than returned by native 'code' mode (200)
    function getSort(){ return 150; }

    function connectTo($mode) {       
      $this->Lexer->addEntryPattern ('<div.*?>', $mode, 'plugin_oabox');
    }

    function postConnect() {
      $this->Lexer->addExitPattern('</div>', 'plugin_oabox');
    }


    function handle($match, $state, $pos, &$handler){
        switch ($state) {
            case DOKU_LEXER_ENTER:     return array($state, $match);
            case DOKU_LEXER_MATCHED:   return array($state, $match);
            case DOKU_LEXER_UNMATCHED: return array($state, $match);
            case DOKU_LEXER_EXIT:      return array($state, $match);
        }       
        return false;
    }

    
    //create output
    
    function render ($mode, &$renderer, $data)
    {
        list ($state, $param) = $data;
        if ($mode == 'xhtml') {
            switch ($state) {
               case DOKU_LEXER_ENTER:
                  $renderer->doc .= $param;
                  break;
               case DOKU_LEXER_MATCHED:
                  //$renderer->doc .= "DOKU_LEXER_MATCHED data=$param";
                  break;
               case DOKU_LEXER_EXIT:
                  //$renderer->doc .= $param;
                  $renderer->doc .= "</div>\n";

                  break;

               case DOKU_LEXER_UNMATCHED:
                  $renderer->doc .= $renderer->_xmlEntities($param);
                  break;
            }
            return true;
        }
        return false;
    }
    
}


