#!/bin/sh

set -e
set -x

list_files() {
    find ./ps-type1 -type f \
         \( -name '*.pfb' \
         -o -name '*.map' \
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
         \) -print
}

list_files | \
    tar -cvvzf sanskrit.tar.gz \
        -T - \
        --transform 's,^\./,sanskrit/,' \
        --owner=sanskrit \
        --group=ctan
