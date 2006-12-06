<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']; ?>" lang="<?php echo $conf['lang']; ?>">
	<head>
		<meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8" />
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
			<?php if($ERROR){ print $ERROR; }else{ ?>
				<h1><?php echo hsc(tpl_img_getTag('IPTC.Headline',$IMG))?></h1>
				<p><?php tpl_img(900,700) ?></p>
			    <p>&larr; <?php echo $lang['img_backto']?> <?php tpl_pagelink($ID)?></p>
			<?php } ?>
		</div>
	</body>
</html>