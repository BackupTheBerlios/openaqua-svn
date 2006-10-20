<?php
/**
 * Allow storing of blinklist clouds
 * <blinklist whichone>
 *
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Claudia.Behrens (at) openaqua.de>
 *
 */
 
if (!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if (!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');

// ---------- [ Settings ] -----------------------------------------

// define the trigger characters
//   ";" & ":" are the mediawiki settings.
//   "=" & ":" are the settings for the original plugin by Pavel
//if (!defined('DL_DT')) define('DL_DT', ';');     // character to indicate a term (dt)
//if (!defined('DL_DD')) define('DL_DD', ':');     // character to indicate a definition (dd)

// define the html used to generate the definition list
// - set to false or 0 to use simple list html <dl><dt>term</dt><dd>definition</dd> ... </dl>
// - set to true or 1 to use wrap the term element in a span permitting more complex styling
//   <dl><dt><span class='term'>term</span></dt><dd>definition</dd> ... </dl>
//if (!defined('DL_FANCY')) define('DL_FANCY', true); 

// -----------------------------------------------------------------
 
/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_blinklistcloud extends DokuWiki_Syntax_Plugin {

    var $stack = array();
 
    /**
     * return some info
     */
    function getInfo(){
        return array(
            'author' => 'Claudia Behrens',
            'email'  => 'info@openaqua.de',
            'date'   => '2006-10-19',
            'name'   => 'Blinklist Cloud Plugin',
            'desc'   => 'Add a blinklist cloud on to a wiki page',
            'url'    => 'http://wiki.durga-online',
        );
    }
 
 
    function getType() { return 'container'; }
    function getSort() { return 10; }                // before preformatted (20)
 /*
    function getAllowedTypes() { return array('container','substition','protected','disabled','formatting'); }
    function getPType() { return 'normal'; }         // normal, so not surrounded by <p> tags
 */
    /**
     * Connect pattern to lexer
     */
    function connectTo($mode) {
       $this->Lexer->addEntryPattern('\n {2,}<blinklistcloud', $mode, 'plugin_blinklistcloud');
    }
 
    function postConnect() {
        // we end the definition list when we encounter a blank line
        $this->Lexer->addExitPattern('>','plugin_blinklistcloud');
    }
 
    /**
     * Handle the match
     */
    function handle($match, $state, $pos, &$handler) {
        switch ( $state ) {
            case DOKU_LEXER_ENTER:      return array($state, '');
            case DOKU_LEXER_MATCHED:    return array($state, '');
            case DOKU_LEXER_UNMATCHED:  return array($state, $match);
            case DOKU_LEXER_EXIT:       return array($state, '');
        }
    }
 
    /**
     * Create output
     */
     function render($mode, &$renderer, $data) {
       list ($state, $param) = $data;
       if ($mode == 'xhtml') {
            switch ( $state ) {
              case DOKU_LEXER_ENTER:
                $renderer->doc .= '<script type="text/javascript" src="http://www.blinklist.com/';
                //$renderer->doc .= 'HHHHHHHHHHHH<!--';
                break;
              case DOKU_LEXER_MATCHED:
                break;
              case DOKU_LEXER_UNMATCHED:
                $renderer->doc .= trim($renderer->_xmlEntities($param));
                break;
              case DOKU_LEXER_EXIT:
                $renderer->doc .= '/cloud.js&logo=0"></script>';
                //$renderer->doc .= '-->';
                break;
            }
            return true;
        }
        return false;
     }
}
