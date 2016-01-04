#include <wand/wand_api.h>

int main(int argc, char *argv[])
{
	MagickWand *magick_wand;
	unsigned int status;

	InitializeMagick((char *)NULL);
	magick_wand = NewMagickWand();
	MagickReadImage(magick_wand, "magick:rose");
	status = MagickSetImagePage(magick_wand, 50, 50, 0, 0);
	DestroyMagick();

	printf("Test program - fin\n");

	return 0;
}