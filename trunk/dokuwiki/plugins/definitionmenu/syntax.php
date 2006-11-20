<?php
/**
 * Allow creation of  definition list menus:
 * <dl>
 *   <dt>term</dt>
 *   <dd>definition</dd>
 * </dl>
 *
 * Syntax:
 *   ; term : definition
 *   ; term
 *   : definition
 *
 * As with other dokuwiki lists, each line must start with 2 spaces or a tab
 * Nested definition lists are not supported at this time
 *
 * This plugin is heavily based on the definitions plugin by Pavel Vitis which 
 * in turn drew from the original definition list plugin by Stephane Chamberland.
 * A huge thanks to both of them.
 *
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Chris Smith <chris [at] jalakai [dot] co [dot] uk>
 *
 */
 
if (!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if (!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');

// ---------- [ Settings ] -----------------------------------------

// define the trigger characters
//   ";" & ":" are the mediawiki settings.
//   "=" & ":" are the settings for the original plugin by Pavel
if (!defined('DL_DT')) define('DL_DT', 'm;');     // character to indicate a term (dt)
if (!defined('DL_DD')) define('DL_DD', 'm:');     // character to indicate a definition (dd)

// define the html used to generate the definition list
// - set to false or 0 to use simple list html <dl><dt>term</dt><dd>definition</dd> ... </dl>
// - set to true or 1 to use wrap the term element in a span permitting more complex styling
//   <dl><dt><span class='term'>term</span></dt><dd>definition</dd> ... </dl>
if (!defined('DL_FANCY')) define('DL_FANCY', true); 

// -----------------------------------------------------------------
 
/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_definitionmenu extends DokuWiki_Syntax_Plugin {

    var $stack = array();
 
    /**
     * return some info
     */
    function getInfo(){
        return array(
            'author' => 'Christopher Smith',
            'email'  => 'chris@jalakai.co.uk',
            'date'   => '2005-09-17',
            'name'   => 'Definition list based Menu',
            'desc'   => 'Add HTML style definition list '.DL_DT.' term '.DL_DD.' definition',
            'url'    => 'http://wiki.splitbrain.org/plugin:definitions',
        );
    }
 
    function getType() { return 'container'; }
    function getAllowedTypes() { return array('container','substition','protected','disabled','formatting'); }
    function getPType() { return 'normal'; }         // normal, so not surrounded by <p> tags
    function getSort() { return 10; }                // before preformatted (20)
 
    /**
     * Connect pattern to lexer
     */
    function connectTo($mode) {
    
       $this->Lexer->addEntryPattern('\n {2,}'.DL_DT, $mode, 'plugin_definitionmenu');
       $this->Lexer->addEntryPattern('\n\t{1,}'.DL_DT, $mode, 'plugin_definitionmenu');

       $this->Lexer->addPattern('(?: '.DL_DD.' )', 'plugin_definitionmenu');
       $this->Lexer->addPattern('\n {2,}(?:'.DL_DT.'|'.DL_DD.')', 'plugin_definitionmenu');
       $this->Lexer->addPattern('\n\t{1,}(?:'.DL_DT.'|'.DL_DD.')', 'plugin_definitionmenu');
    }
 
    function postConnect() {
        // we end the definition list when we encounter a blank line
        $this->Lexer->addExitPattern('\n[ \t]*\n','plugin_definitionmenu');
    }
 
    /**
     * Handle the match
     */
    function handle($match, $state, $pos, &$handler) {
        switch ( $state ) {
            case DOKU_LEXER_ENTER:      return array($state, 'dt');
            case DOKU_LEXER_MATCHED:    return array($state, (substr($match, -1) == DL_DT) ? 'dt' : 'dd');
            case DOKU_LEXER_UNMATCHED:  return array($state, $match);
            case DOKU_LEXER_EXIT:       return array($state, '');
        }
    }
 
    /**
     * Create output
     */
    function render($mode, &$renderer, $data) {
        list ($state, $param) = $data;
        
        if($mode == 'xhtml'){
            switch ( $state ) {
              case DOKU_LEXER_ENTER:
                $renderer->doc .= "</p>\n<li><dl>\n";
                $renderer->doc .= $this->_open($param);
                break;
              case DOKU_LEXER_MATCHED:
                $renderer->doc .= $this->_close();
                $renderer->doc .= $this->_open($param);
                break;
              case DOKU_LEXER_UNMATCHED:
                $renderer->doc .= $renderer->_xmlEntities($param);
                break;
              case DOKU_LEXER_EXIT:
                $renderer->doc .= $this->_close();
                $renderer->doc .= "</dl>\n<p>";
                break;
            }
            return true;
        }
        return false;
    }
    
    function _open($tag) {
        array_push($this->stack, $tag);
        $wrap = (DL_FANCY && $tag == 'dt') ? "<span class='term'>" : "";
        return "<$tag>$wrap";
    }
    
    function _close() {
        $tag = array_pop($this->stack);
        $wrap = (DL_FANCY && $tag == 'dt') ? "</span>" : "";
        return "$wrap</$tag>\n";
    }
    
}
 
//Setup VIM: ex: et ts=4 enc=utf-8 :
