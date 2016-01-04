--TEST--
Test Tutorial, deconstructGif
--SKIPIF--
<?php

require_once(dirname(__FILE__) . '/skipif.inc');

checkClassMethods('GmagickDraw', array('circle', 'translate'))

?>
--FILE--
<?php
$aniGif = new \Gmagick();

$colors = ['red', 'white', 'blue'];

foreach ($colors as $color) {
    $imageSize = 200;
    $background = new \Gmagick();
    $background->newImage($imageSize, $imageSize, $color);

    $aniGif->addImage($background);
}

$aniGif->setImageFormat("gif");
//$aniGif->writeImage("./this_worked_question_mark.gif", true);

$bytes = $aniGif->getImagesBlob();
if (strlen($bytes) <= 0) { echo "Failed to generate image.";}

$deconstructedGif = $aniGif->deconstructImages();

$aniGif->setImageFormat("gif");

//This seems a little broken. Writing the gif works - getting the image blob doesn't
//$deconstructedBytes = $deconstructedGif->getImagesBlob();
//if (strlen($deconstructedBytes) <= 0) { echo "Failed to generate image.";}
// $deconstructedGif->writeImage("./this_deconstructed.gif", true);

echo "Number of frames is: "$aniGif->getNumberImages().PHP_EOL;
echo "ok"

exit(0);


$aniGif = new \Gmagick();

    $circleRadius = 20;
    $imageFrames = 20;
    $imageSize = 200;

    $background = new \Gmagick();
    $background->newImage($imageSize, $imageSize, "gray");

    $blackWhite = new \Gmagick();
    $blackWhite->newImage($imageSize, $imageSize, "red");

    $backgroundPalette = clone $background;
    $backgroundPalette->quantizeImage(240, \Gmagick::COLORSPACE_RGB, 8, false, false);

    $blackWhitePalette = clone $blackWhite;
    $blackWhitePalette->quantizeImage(16, \Gmagick::COLORSPACE_RGB, 8, false, false);

    $backgroundPalette->addimage($blackWhitePalette);

    for($count=0 ; $count<$imageFrames ; $count++) {
        echo "Frame: ".$count."\n";
        $drawing = new \GmagickDraw();
        $drawing->setFillColor('white');
        $drawing->setStrokeColor('rgba(64, 64, 64, 0.8)');
        $strokeWidth = 4;
        $drawing->setStrokeWidth($strokeWidth);
        
        $distanceToMove = $imageSize + (($circleRadius + $strokeWidth) * 2);
        $offset = ($distanceToMove * $count / ($imageFrames -1)) - ($circleRadius + $strokeWidth);
        $drawing->annotate(
			 $offset,
			 ($imageSize / 2) + ($imageSize / 3 * cos(20 * $count / $imageFrames)),
			"Hello world"
		);

        $frame = clone $background;
        $frame->drawimage($drawing);
        $frame->setImageDelay(10);
        $aniGif->addImage($frame);
    }

$aniGif->setImageFormat("gif");

$aniGif->writeImage("./this_worked_question_mark.gif", true);

$deconstructedGif = $aniGif->deconstructImages();

$deconstructedGif->writeImage("./this_deconstructed_worked_question_mark.gif", true);

//	$aniGif->setImageFormat("gif");
//    $bytes = $aniGif->getImagesBlob();
//    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
?>
--EXPECTF--
Number of frames is: 3
ok