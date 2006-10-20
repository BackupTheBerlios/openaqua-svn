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



// -----------------------------------------------------------------

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_blinklistlist extends DokuWiki_Syntax_Plugin
{

    var $stack = array ();

    var $CssHeaderStyle = '';   //CSS Class name for Header
    var $CssContentStyle = '';  //CSS Class name for Details

    var $rssTitle = '';
    var $rssDescription = '';
    var $rssContent = '';
    var $rssLink = '';          //may show to other RSS content
    var $rssDetails = false;

    var $xmlTag;
    var $xmlInItem;
    var $xmlInImage;
    var $xmlInUrl;
    var $xmlImage;


    /**
     * return some info
     */
    function getInfo ()
    {
        return array ('author' =>'Claudia Behrens',
                      'email' =>'info@openaqua.de',
                      'date' =>'2006-10-20',
                      'name' =>'Blinklist List Plugin',
                      'desc' =>'Shows a blinklist list on to a wiki page', 
                      'url' =>'http://wiki.durga-online',
                      );
    }


    function getType ()
    {
        return 'container';
    }


    function getSort ()
    {
        return 10;
    }

    /*
       function getAllowedTypes() { return array('container','substition','protected','disabled','formatting'); }
       function getPType() { return 'normal'; }         // normal, so not surrounded by <p> tags
     */



    /**
     * Connect pattern to lexer
     */

    function connectTo ($mode)
    {
        $this->Lexer->addEntryPattern ('\n {2,}<blinklistlist', $mode, 'plugin_blinklistlist');
    }

    function postConnect ()
    {
        // we end the definition list when we encounter a blank line
        $this->Lexer->addExitPattern ('>', 'plugin_blinklistlist');
    }



    /**
     * Handle the match
     */
    function handle ($match, $state, $pos, &$handler)
    {
        if ($state == DOKU_LEXER_UNMATCHED) {
            return array ($state, $match);
        } else {
            return array ($state, '');
        }
    }



    /**
     * Create output
     */
    function render ($mode, &$renderer, $data)
    {
        list ($state, $param) = $data;
        if ($mode == 'xhtml') {
            switch ($state) {
            case DOKU_LEXER_ENTER:
            case DOKU_LEXER_MATCHED:
            case DOKU_LEXER_EXIT:
                break;
            case DOKU_LEXER_UNMATCHED:
                $renderer->doc .= "<p>davor</p>";
                //collectNews(trim($param), false);
                $this->collectNews ("http://www.blinklist.com/Tukaram/rss.xml");
                $renderer->doc .= $this->rssContent;
                $renderer->doc .= "<p>danach</p>";
                break;
            }
            return true;
        }
        return false;
    }



    /**
    
    */
    function collectNews ($url)
    {
       $this->xmlInUrl = false;
       $this->xmlInImage = false;
       $this->xmlInItem = false;



        //get a XML parser
        $xml_parser = xml_parser_create ();
        xml_set_element_handler ($xml_parser, "startElement", "endElement");
        xml_set_character_data_handler ($xml_parser, "characterData");

        
        
        
        //open URL
        $fp = fopen ($url, 'r');
        if (!$fp) {
           $this->rssContent .= '<span class="'.$this->CssContentStyle.'">Cannot open RSS URL</span>';
           xml_parser_free ($xml_parser);
           return ;
        }
        
        
        //get the content
        while(!feof($fp)) {
           $data = $data . fgets($file, 4096);
           if (! xml_parse ($xml_parser, $data, feof ($fp))) {
                    $this->rssContent .= 'XML error: ' 
                                   . xml_error_string (xml_get_error_code ($xml_parser))
                                   . ' at line '
                                   . xml_get_current_line_number ($xml_parser);
                     fclose ($fp);
                     xml_parser_free ($xml_parser);                                   
                     return;
               }
           
       }
       
       //Close URL
       fclose ($fp);
        
        // Free up memory used by the XML parser
        xml_parser_free ($xml_parser);
    }


    /**
    @brief: Deals with XML start Tags
    */
    function startElement ($parser, $name, $attrs)
    {
        if ($this->xmlInUrl || $this->xmlInImage || $this->xmlInItem) {
            $this->xmlTag = $name;
        }
        if ($name == "ITEM") {
            $this->xmlInItem = true;
        }
        if ($name == "IMAGE") {
            $this->xmlInImage = true;
        }
        if ($name == "URL") {
            $this->xmlInUrl = true;

        }
    }



    /**
    
    @brief: Deal with XML End Tags
    */
    function endElement ($parser, $name)
    {
        if ($name == "URL") {
            $this->xmlInUrl = false;
            $this->rssContent .= '<img src="'. htmlspecialchars (trim ($this->xmlImage)).'"/><br><br>';

        } else if ($name == "ITEM") {
            $this->xmlInItem = false;
            $this->rssContent .=
                '<a href="'.trim ($this->rssLink).'" class="'.$this->cssHeaderStyle.'" target="_blank"><b> '.trim ($this->rssTitle).
                '</b></a><br>';

            if ($this->rssDetails) {
                $this->rssContent .= '<span class="'.$this->cssContentStyle.'"> '.trim ($this->rssDescription).' </span><br>';
            } else {
                $this->rssContent .= "<br>";
            }

            $this->rssTitle = '';
            $this->rssDescription = '';
            $this->rssLink = '';

        } else if ($name == "IMAGE") {
            $this->xmlInImage = false;
            $this->rssContent .= '<img src="'.htmlspecialchars (trim ($this->xmlImage)).'"/><br><br>';
            $this->xmlImage = '';
        }
    }

    function characterData ($parser, $data)
    {

        if ($this->xmlInItem) {
            switch ($this->xmlTag) {
            case "URL":
                $this->xmlImage .= $data;
                break;
            }
        }//if
        
        
        if ($this->xmlInItem) {
            switch ($this->xmlTag) {
            case "TITLE":
                $this->rssTitle .= $data;
                break;
            case "DESCRIPTION":
                $this->rssDescription .= $data;
                break;
            case "LINK":
                if (!is_string ($this->rssLink))
                    $this->rssLink = $data;
                break;
            }//switch
        }//if
    }//function


}
