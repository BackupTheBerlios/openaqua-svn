< ? php
/**
 * Allow storing of blinklist clouds
 * <blinklist whichone>
 *
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Claudia.Behrens (at) openaqua.de>
 *
 */
    if (!defined ('DOKU_INC')) {
    define ('DOKU_INC', realpath (dirname (__FILE__).'/../../').'/');
}
if (!defined ('DOKU_PLUGIN')) {
    define ('DOKU_PLUGIN', DOKU_INC.'lib/plugins/');
}
require_once (DOKU_PLUGIN.'syntax.php');



// -----------------------------------------------------------------

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_blinklistlist extends DokuWiki_Syntax_Plugin
{

    var $stack = array ();
    var $headerStyle = '';	//CSS Class name for Header
    var $contentStyle = '';	//CSS Class name for Details
    var $insideitem, $insideimage;	//internal use
    var $rssTitle = '';
    var $rssDescription = '';
    var $rssContent = '';


    /**
     * return some info
     */
    function getInfo ()
    {
	return array ('author' = >'Claudia Behrens',
		      'email' = >'info@openaqua.de',
		      'date' = >'2006-10-20',
		      'name' = >'Blinklist List Plugin',
		      'desc' = >'Shows a blinklist list on to a wiki page', 'url' = >'http://wiki.durga-online',);
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
		$renderer->doc. = "<p>davor</p>";
		//collectNews(trim($param), false);
		collectNews ("http://zvonnews.sourceforge.net/news/rss.php");
		$renderer->doc. = $rssContent;
		$renderer->doc. = "<p>danach</p>";
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
	$insideitem = false;
	$insideimage = false;


	//configure the XML parser
	$xml_parser = xml_parser_create ();
	xml_set_element_handler ($xml_parser, "startElement", "endElement");
	xml_set_character_data_handler ($xml_parser, "characterData");

	//get the content
	$fp = @fopen ($url, "r");
	if ($fp) {
	    while ($data = fread ($fp, 4096))
		xml_parse ($xml_parser, $data, feof ($fp))
		    $rssContent = 'XML error: '.xml_error_string (xml_get_error_code ($xml_parser))
		    .' at line '.xml_get_current_line_number ($xml_parser);
	    fclose ($fp);
	} else {
	    $news. = '<span class="'.$detail_style.'">Syndicated content not available</span>';
	}

	// Free up memory used by the XML parser
	xml_parser_free ($xml_parser);
    }


    function startElement ($parser, $name, $attrs)
    {
	//global $insideitem, $tag, $title, $description, $link, $image, $insideimage;
	if ($insideitem || $insideimage) {
	    $tag = $name;
	}
	if ($name == "ITEM") {
	    $insideitem = true;
	}
	if ($name == "IMAGE") {
	    $insideimage = true;

	}
    }

    function endElement ($parser, $name)
    {
	global $insideitem, $tag, $title, $description, $link, $image, $insideimage, $show_detail, $headline_style,
	    $detail_style, $count, $max;

	if ($name == "URL") {
	    $news. = '<img src="'.htmlspecialchars (trim ($image)).'"/><br><br>';
	    $insideimage = false;
	    $image = "";
	} else if ($name == "ITEM") {
	    $count++;
	    $news. =
		('<a href="' '" class="'.$headline_style.'" target="_blank"><b>%s</b></a><br>', trim ($link),
		 trim ($title));
	    if ($show_detail)
		$news. = ('<span class="'.$detail_style.'">%s</span><br>', trim ($description));
	    else {
		$news. = "<br>";
	    }
	    $title = "";
	    $description = "";
	    $link = "";
	    $insideitem = false;
	} else if ($count >= $max) {
	    $title = "";
	    $description = "";
	    $link = "";
	    $insideitem = false;
	}
    }

    function characterData ($parser, $data)
    {
	global $insideitem, $tag, $title, $description, $link, $image, $insideimage;
	if ($insideimage) {
	    switch ($tag) {
	    case "URL":
		$image. = $data;
		break;
	    }
	}
	if ($insideitem) {
	    switch ($tag) {
	    case "TITLE":
		$title. = $data;
		break;
	    case "DESCRIPTION":
		$description. = $data;
		break;
	    case "LINK":
		if (!is_string ($link))
		    $link = "";
		$link. = $data;
		break;
	    }
	}
    }


}
