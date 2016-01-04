#!/bin/bash

# export LIBS="-Wl,-rpath=/home/travis/gm/graphicsmagick_1.3.22_8/lib"
# export CFLAGS="-I/home/travis/gm/graphicsmagick_1.3.22_8/include/GraphicsMagick"
# export LDFLAGS="-L/home/travis/gm/graphicsmagick_1.3.22_8/lib -L/usr/lib/x86_64-linux-gnu -lGraphicsMagick -ltiff -lfreetype -ljasper -ljpeg -lpng12 -lwmflite -lXext -lSM -lICE -lX11 -lbz2 -lxml2 -lz -lm -lGraphicsMagickWand"


# export LIBS="-Wl,-rpath=/usr/local/lib"
# export CFLAGS="-I/usr/local/include/GraphicsMagick"
# export LDFLAGS="-L/usr/local/lib -lGraphicsMagick -lwebp -ltiff -lfreetype -ljasper -ljpeg -lpng12 -lXext -lSM -lICE -lX11 -lbz2 -lxml2 -lz -lm -lGraphicsMagickWand"

set -e
set -x

WAND_BINARY="/home/travis/gm/graphicsmagick_1.3.23_16/bin/GraphicsMagick-config"

# WAND_BINARY="/usr/local/bin/GraphicsMagick-config"

WAND_DIR=`$WAND_BINARY --prefix`
LIB_DIR="${WAND_DIR}/lib"

LIBS="-Wl,-rpath=${LIB_DIR}"
CFLAGS="`$WAND_BINARY --cppflags`"
LDFLAGS="`$WAND_BINARY --ldflags` `$WAND_BINARY --libs` -lGraphicsMagickWand"

echo "CFLAGS ${CFLAGS}"
echo "LDFLAGS ${LDFLAGS}"
echo "LIBS ${LIBS}"

added_libs="-L${LIB_DIR}/libGraphicsMagickWand.so -L${LIB_DIR}/libGraphicsMagick.so"

echo ""
echo "Full compile line: cc "${CFLAGS}" debug.c -o debug ${added_libs} ${LDFLAGS}  ${LIBS} "


cc $CFLAGS debug.c -o debug $added_libs $LDFLAGS $LIBS 




