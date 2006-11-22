<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']; ?>" lang="<?php echo $conf['lang']; ?>">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<meta http-equiv="Content-Style-Type" content="text/css" />
		<meta name="author" content="neolao" />
		<?php tpl_metaheaders(); ?>
		<link rel="stylesheet" type="text/css" href="<?php echo DOKU_TPL; ?>layout.css" />
		<link rel="stylesheet" type="text/css" href="<?php echo DOKU_TPL; ?>style.css" />
		<link rel="stylesheet" type="text/css" href="<?php echo DOKU_TPL; ?>style_dw.css" />
		<title><?php echo hsc(tpl_img_getTag('IPTC.Headline',$IMG))?>[<?php echo hsc($conf['title'])?>]</title>
	</head>
	<body>
		<div id="body">
			<?php html_msgarea()?>
			<h1><?php echo hsc($lang['mediaselect'])?> <code><?php echo hsc($NS)?></code></h1>
			<div>
				<strong><a href="<?php echo DOKU_BASE?>lib/exe/media.php?ns="><?php echo hsc($lang['namespaces'])?></a></strong>
				<?tpl_medianamespaces()?>
			</div>
			<hr/>
			<div>
			<?php tpl_mediafilelist()?>
			<div class="uploadform">
				<?php tpl_mediauploadform()?>
			</div>
		</div>
		</div>
	</body>
</html>
