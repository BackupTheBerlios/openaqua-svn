<html>
<head>
    <title>RSS Dump</title>
    <style>
        body, pre > b { font-size: medium; }
        pre { font-size: small; }
    </style>
</head>
<body>
<?php
// This example shows how the RSS_parser class can be used.
include_once("class_rss_parser.php");

$rss = new RSS_parser();
$rss->rss_parse("http://www.phpclasses.org/browse.html/latest/latest.xml");
$ch = $rss->get_channel_data();
$ch_im = $rss->get_channel_image_data();
$ch_ti = $rss->get_channel_textinput_data();
$items = $rss->get_items_data();
// Print the information here:
?>
<b>Channel data:</b><br/>
<pre>
<? print_r($ch) ?>
</pre><br/>
<b>Channel image data:</b><br/>
<pre>
<? print_r($ch_im) ?>
</pre><br/>
<b>Channel textinput data:</b><br/>
<pre>
<? print_r($ch_ti) ?>
</pre><br/>
<b>Items data:</b><br/>
<pre>
<?
foreach($items as $item) {
    echo "----<br/>\n";
    foreach($item as $key=>$val) {
        echo "<b>$key:</b> $val\n";
    }
}
?>
</pre>
</body>
</html>