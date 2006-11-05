<?php
/**
 * Box Plugin: Draw highlighting boxes around wiki markup
 *
 * Syntax:     <box width% classes|title>
 *   width%    width of the box, must use % unit
 *   classes   one or more classes used to style the box, several predefined styles included in style.css
 *   title     (optional) all text after '|' will be rendered above the main code text with a
 *             different style.
 *
 * Acknowledgements:
 *  Rounded corners based on snazzy borders by Stu Nicholls (http://www.cssplay.co.uk/boxes/snazzy) 
 *  which is in turn based on nifty corners by Alessandro Fulciniti (http://pro.html.it/esempio/nifty/)
 * 
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Christopher Smith <chris@jalakai.co.uk>  
 */

if(!defined('DOKU_INC')) define('DOKU_INC',realpath(dirname(__FILE__).'/../../').'/');
if(!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_box extends DokuWiki_Syntax_Plugin {

    var $title_mode = false;

    /**
     * return some info
     */
    function getInfo(){
      return array(
        'author' => 'Christopher Smith',
        'email'  => 'chris@jalakai.co.uk',
        'date'   => '2006-03-11',
        'name'   => 'Box Plugin',
        'desc'   => 'Boxes with titles, colour and rounded corners. 
                     Syntax: <box|title> ... </box> title is optional.',
        'url'    => 'http://wiki.splitbrain.org/plugin:boxes',
      );
    }

    function getType(){ return 'protected';}
    function getAllowedTypes() { return array('container','substition','protected','disabled','formatting','paragraphs'); }
    function getPType(){ return 'normal';}

    // must return a number lower than returned by native 'code' mode (200)
    function getSort(){ return 195; }

    // override default accepts() method to allow nesting 
    // - ie, to get the plugin accepts its own entry syntax
    function accepts($mode) {
        if ($mode == substr(get_class($this), 7)) return true;

        return parent::accepts($mode);
    }

    /**
     * Connect pattern to lexer
     */
    function connectTo($mode) {       
      $this->Lexer->addEntryPattern('<box>(?=.*?</box.*?>)',$mode,'plugin_box');
      $this->Lexer->addEntryPattern('<box\s[^\r\n\|]*?>(?=.*?</box.*?>)',$mode,'plugin_box');
      $this->Lexer->addEntryPattern('<box\|(?=[^\r\n]*?\>.*?</box.*?\>)',$mode,'plugin_box');      
      $this->Lexer->addEntryPattern('<box\s[^\r\n\|]*?\|(?=[^\r\n]*?>.*?</box.*?>)',$mode,'plugin_box');      
    }

    function postConnect() {
      $this->Lexer->addPattern('>', 'plugin_box');
      $this->Lexer->addExitPattern('</box.*?>', 'plugin_box');
    }

    /**
     * Handle the match
     */
    function handle($match, $state, $pos, &$handler){

        switch ($state) {
            case DOKU_LEXER_ENTER:
                $data = $this->_boxstyle(trim(substr($match, 4, -1)));
                if (substr($match, -1) == '|') {
                    $this->title_mode = true;
                    return array('title_open',$data);
                } else {
                    return array('box_open',$data);
                }

            case DOKU_LEXER_MATCHED:
                if ($this->title_mode) {
                    $this->title_mode = false;
                    return array('box_open','');
                } else {
                    return array('data', $match);
                }

            case DOKU_LEXER_UNMATCHED:                
                return array('data', $match);

            case DOKU_LEXER_EXIT:
                $data = trim(substr($match, 5, -1));
                $title =  ($data && $data{0} == "|") ? substr($data,1) : '';

                return array('box_close', $title);

        }       
        return false;
    }

    /**
     * Create output
     */
    function render($mode, &$renderer, $indata) {

      list($instr, $data) = $indata;

      if($mode == 'xhtml'){
          switch ($instr) {
          case 'title_open' : 
              $this->title_mode = true;
            $renderer->doc .= "</p>\n".$this->_xhtml_boxopen($data)."<p class='box_title'>";
            break;

          case 'box_open' :   
            if ($this->title_mode) {
                $this->title_mode = false;
                $renderer->doc .= "</p>\n<div class='box_content'><p>";
            } else {
                $renderer->doc .= "</p>\n".$this->_xhtml_boxopen($data)."<div class='box_content'><p>";
            }
            break;

          case 'data' :      
            $renderer->doc .= $renderer->_xmlEntities($data); 
            break;

          case 'box_close' : 
            $renderer->doc .= "</p></div>\n";

            if ($data) { 
              $renderer->doc .= "<p class='box_caption'>".$data."</p>\n";    
            }
            $renderer->doc .= $this->_xhtml_boxclose()."<p>"; 
            break;
        }

        return true;
      }
      return false;
    }

    function _boxstyle($str) {
      if (!strlen($str)) return array();

      $styles = array();

      $tokens = preg_split('/\s+/', $str, 9);                      // limit is defensive
      foreach ($tokens as $token) {
          if (preg_match('/^\d*\.?\d+(%|px|em|ex|pt|cm|mm|pi|in)$/', $token)) {
            $styles['width'] = $token;
            continue;
          }

          // restrict token (class names) characters to prevent any malicious data
          if (preg_match('/[^A-Za-z0-9_-]/',$token)) continue;
          $styles['class'] = (isset($styles['class']) ? $styles['class'].' ' : '').$token;
      }

      return $styles;
    }

    function _xhtml_boxopen($style) {
      $class = "class='box" . (isset($style['class']) ? ' '.$style['class'] : '') . "'";
      $style = isset($style['width']) ? " style='width: {$style['width']};'" : '';

      $html = "<div $class$style>\n";
      $html .="  <b class='xtop'><b class='xb1'></b><b class='xb2'></b><b class='xb3'></b><b class='xb4'></b></b>\n";
      $html .="  <div class='xbox'>\n";

      return $html;
    }

    function _xhtml_boxclose() {

      $html = "  </div>\n";
      $html .= "  <b class='xbottom'><b class='xb4'></b><b class='xb3'></b><b class='xb2'></b><b class='xb1'></b></b>\n";
      $html .= "</div>\n";

      return $html;
    }

}

//Setup VIM: ex: et ts=4 enc=utf-8 :