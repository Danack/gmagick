#!/bin/sh

#give an error if the download fails.
set -e

graphicsmagick_fetch_and_build () {
    local version=$1

    echo "version is ${version}"
    gm_dir=${HOME}/gm/graphicsmagick-${version}

    case $version in
        git7)
            ;;
        git6)
            ;;
        dev)
            ;;
        *)
    # Both individual commits, and tagged versions are cacheable
        if [ -d "${im_dir}" ]; then
            echo "Using cached directory ${im_dir}"
            return  
        fi
        ;;
    esac


    case $version in

#    git6)
#        wget -O ImageMagick-6.tar.gz https://github.com/ImageMagick/ImageMagick/archive/ImageMagick-6.tar.gz
#        tar xvfz ImageMagick-6.tar.gz
#        cd ImageMagick-ImageMagick-6
#        ;;
#    dev)
#        svn co https://www.imagemagick.org/subversion/ImageMagick/branches/ImageMagick-6/ imagemagick-dev
#        cd imagemagick-dev
#        ;;

    *)
        echo "version is ${version}"
        set +e
        #this can error
        start_str=${version:0:6}
        set -e
        
        # if [ "${start_str}" == "commit" ]; then
        #    sha=${version:7:47}
        #    wget -O "ImageMagick-${sha}.tar.gz" "https://github.com/ImageMagick/ImageMagick/archive/${sha}.tar.gz"
        #    tar xvfz ImageMagick-${sha}.tar.gz
        #    
        #    cd "ImageMagick-${sha}"
        #else
        
        
           wget http://sourceforge.net/projects/graphicsmagick/files/graphicsmagick/${version}/GraphicsMagick-${version}.tar.gz/download
           tar xvfz GraphicsMagick-${version}.tar.gz
           cd GraphicsMagick-*
        #fi
        ;;
    esac

#ignore compile warnings/errors
set +e

    ./configure \
    --prefix="${HOME}/gm/graphicsmagick-${version}" \
    --with-quantum-depth=16 \
    --enable-shared \
    --exec-prefix=/usr \
    --prefix=/usr/lib \
    --disable-openmp \
    --with-perl=no \
    --without-threads \
    --without-magick-plus-plus

    make -j 4
    make install
    cd ..

}

graphicsmagick_fetch_and_build $1