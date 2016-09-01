%
% README.TXT
%
% Revision 1.0 1996/02/13 Charles Wikner wikner@nacdh4.nac.ac.za
% Revision 2.0 1996/11/27 Charles Wikner wikner@nacdh4.nac.ac.za
% Revision 2.2 2002/01/02 Charles Wikner wikner@nac.ac.za
%

The package contains the font files and pre-processor for printing
Sanskrit in both devanagari and transliterated roman with diacritics.

Some features of the devanagari are:

 o  Font available in three weights and two slopes.

 o  The i-hooks connect to the consonant at the correct position.

 o  Accents for all Vedas (23 symbols).

 o  Accent marking in colour or grey shading.

 o  Choice of basic character forms, and samyoga.

 o  Dynamic option selection.

 o  Range of inter- and intra-syllable spacing.

 o  Vedic anusvaara and jihvaamuuliiya/upadhmaaniiya.

 o  Crisper characters (to look good at poster size of 150mm/6-inches).

Some features of the transliterated roman:

 o  Transliterated output in roman script with diacritics, using the 
    same encoding scheme as for producing devanaagarii.

 o  Technical transliterated output using four `cases', following the
    style of S.M.Katre in his translation of the A.s.taadhyaayii.

 o  Each transliteration mode has four styles: roman/italic x bold/normal.

The font and supporting files are designed for use with LaTeX2e; it is 
a bitmap font using Metafont.

INSTALLATION

If sktbugxx.txt files exist, you may want to implement any changes or 
patches first.

Run the metafont program on the eight font source files (the typical 
command would be mf "\mode=ljfour; mag=1; input skt8;" to produce 
the .tfm files. If you are using dvips, then the .pk files will be 
produced automatically on demand; if not, then you will need to 
(1) Convert the .gf files with the command gftopk skt8.600gf 
(the number `600' depends upon your printer resolution and the 
magnification) to produce skt8.pk which must be copied to the 
appropriate subdirectory. 
(2) Repeat this process with all eight fonts.
(3) For the six skt*10.mf files the whole process needs 
to be repeated with the mag value in the mf command set 
to 1.095, 1.2, 1.44, 1.728, 2.074 and 2.488.

The mf_inputs path needs to point to the files with a .mf extension; 
the tex_fonts path should point to the .tfm files; the tex_inputs
path should point to the files skt.sty ot1skt.fd. The tex_exe 
(or other appropriate) path should point to skt.exe.

To test the setup on the documentation file: first run the pre-processor 
skt sktdoc and then latex sktdoc. The files ifthen.sty, relsize.sty,
and multicol.sty are also required. If you are not using dvips and
pstricks then first comment out line 12 in sktdoc.skt.

The files that you should have are:

readme.txt   This file.
skt.sty      Style file (LaTeX2e) for the skt-series fonts.
ot1skt.fd    Font descriptor file for the skt-series fonts.
skt.c        Pre-processor source program in ANSI C.
sktdoc.skt   Source file of documentation and samples.
sktdoc.ps    Print file of documentation and samples.
sktdefs.mf   Common definitions of pens, macros, etc. for skt-series fonts.
sktchars.mf  Common character source file for skt-series fonts.
sktligs.mf   Ligature codes (in fact access codes for non-printing
                      ASCII code characters) for skt-series fonts.
skt8.mf      Metafont source file for skt font at 8pt upright.
skt9.mf      Metafont source file for skt font at 9pt upright.
skt10.mf     Metafont source file for skt font at 10pt upright.
sktb10.mf    Metafont source file for skt font at 10pt upright bold.
sktf10.mf    Metafont source file for skt font at 10pt upright feint.
skts10.mf    Metafont source file for skt font at 10pt slanted.
sktbs10.mf   Metafont source file for skt font at 10pt bold slant.
sktfs10.mf   Metafont source file for skt font at 10pt feint slant.
skt*.tfm     Eight .tfm font files for above.
sktbugxx.txt There may be a series of such files, where `xx' is a 
                      two-digit number, listing reported bugs and 
                      (possibly) fixes or patches.

Suggestions and bug reports to:
wikner@nacdh4.nac.ac.za
02 January 2002.

P.S.
I shall be retiring from the world at the end of March 2002,
and shall not be available on the Net.

