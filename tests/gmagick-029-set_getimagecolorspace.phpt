--TEST--
Set, get imagecolorspace test
--SKIPIF--
<?php
/* $Id: gmagick-029-set_getimagecolorspace.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setImageColorspace(2)->getImageColorspace();
?>
--EXPECTF--
2