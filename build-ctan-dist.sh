#!/bin/sh

set -e
set -x

command_exists() {
    type "$1" &> /dev/null ;
}

if command_exists pandoc ; then
    pandoc --smart \
           --verbose \
           -f markdown-raw_tex \
           -t latex \
           -o README.pdf \
           README.md
fi

${CC:-cc} -o skt skt.c

./skt sktdoc.skt sktdoc.tex

latexmk -gg -ps sktdoc.tex

latexmk -g -pdf sktdoc.tex

rm -f ./ps-type1/sktdoc.pdf
ln ./sktdoc.pdf ./ps-type1/sktdoc.pdf

chmod -R +r .

list_files() {
    find ./ps-type1 -type f \
         \( -name '*.pfb' \
         -o -name '*.map' \
         -o -name 'sktdoc.pdf' \
         -o -name 'README' \
         \) -print

    find . -maxdepth 1 -type f \
         \( -name '*.sh' \
         -o -name '*.mf' \
         -o -name '*.tfm' \
         -o -name '*.fd' \
         -o -name '*.sty' \
         -o -name '*.c' \
         -o -name 'sktdoc.ps' \
         -o -name 'sktdoc.pdf' \
         -o -name 'sktdoc.skt' \
         -o -name 'README.md' \
         -o -name 'README.pdf' \
         \) -print
}

list_files | sort | \
    tar -cvvzf sanskrit.tar.gz \
        -T - \
        --transform 's,^\./,sanskrit/,' \
        --owner=sanskrit \
        --group=ctan
