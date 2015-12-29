#!/bin/sh

# Give an error if the download fails.
set -e
# Echo all commands
set -x

graphicsmagick_fetch_and_build () {
    local version=$1

    echo "version is ${version}"
    gm_dir=${HOME}/gm/graphicsmagick-${version}


# Figure out if the version is already there.
    case $version in

        dev)
          echo "Dev always needs updating"
        ;;

        *)
            # Both individual commits, and tagged versions are cacheable
            if [ -d "${gm_dir}" ]; then
                echo "Using cached directory ${gm_dir}"
                return  
            fi
        ;;
    esac


# Fetch the relevant version
    case $version in
        dev)
            set -e
            $hg_dir="${HOME}/gm/graphicsmagick-${version}"
            
            mkdir -p "${hg_dir}"
            cd "${hg_dir}"
            
            hg clone http://hg.code.sf.net/p/graphicsmagick/code GM
            cd GM
            hg pull
            hg update
        ;;
    
        *)
            echo "version is ${version}"
            set +e
            # The next line can error
            start_str=${version:0:6}
            set -e
        
            # Currently hg doesn't allow fetching commits?
            # Leave this in for now - getting individual commits is great for bisecting 
            # problems.
            #if [ "${start_str}" == "commit" ]; then
            #    sha=${version:7:47}
            #    wget -O "ImageMagick-${sha}.tar.gz" "https://github.com/ImageMagick/ImageMagick/archive/${sha}.tar.gz"
            #    tar xvfz ImageMagick-${sha}.tar.gz
            #    cd "ImageMagick-${sha}"
            #else

            wget -O GraphicsMagick-${version}.tar.gz http://sourceforge.net/projects/graphicsmagick/files/graphicsmagick/${version}/GraphicsMagick-${version}.tar.gz/download
           tar xfz GraphicsMagick-${version}.tar.gz
           cd GraphicsMagick-*
            #fi
        ;;
    esac


# Actually build the project

    #ignore compile warnings/errors
    set +e

    ./configure \
    --prefix="${HOME}/gm/graphicsmagick-${version}" \
    --with-quantum-depth=16 \
    --enable-shared \
    --exec-prefix="${HOME}/gm/graphicsmagick-${version}" \
    --disable-openmp \
    --with-perl=no \
    --without-threads \
    --without-magick-plus-plus

    make -j 4
    make install
    cd ..
}

graphicsmagick_fetch_and_build $1