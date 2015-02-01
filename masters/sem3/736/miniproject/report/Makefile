# ----------------------------------------------------------------------------
#			  Simple latex makefile
#
#		   Robert Grimm, rgrimm@cs.washington.edu
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
#  Tools
# ----------------------------------------------------------------------------

LATEX	     = latex
DVIPS	     = dvips
PDFLATEX     = pdflatex
BIBTEX	     = bibtex
MV	     = mv
RM	     = rm -f


# ----------------------------------------------------------------------------
#  Source file (without extension)
# ----------------------------------------------------------------------------

SOURCE	     = cs736-miniproject-report


# ----------------------------------------------------------------------------
#  Bibliography
# ----------------------------------------------------------------------------

BIBLIOGRAPHY = cs736-miniproject-report.bib


# ----------------------------------------------------------------------------
#  Rules
# ----------------------------------------------------------------------------

.PHONY: simple pdf ps dvi all clean

default: pdf

it:	pdf
	-killall -HUP Preview
	open $(SOURCE).pdf

	
simple: $(SOURCE).tex
	$(LATEX) $(SOURCE)

pdf: $(SOURCE).tex $(SOURCE).bbl
	$(PDFLATEX) $(SOURCE)
	$(PDFLATEX) $(SOURCE)

ps: $(SOURCE).dvi
	$(DVIPS) $(SOURCE)

dvi: $(SOURCE).dvi

ispell:
	ispell -p ./ispell.dict *.tex
	
all: pdf ps

$(SOURCE).dvi: $(SOURCE).tex $(SOURCE).bbl
	$(LATEX) $(SOURCE)
	$(LATEX) $(SOURCE)

$(SOURCE).bbl: $(SOURCE).tex $(BIBLIOGRAPHY)
	$(PDFLATEX) $(SOURCE)
	$(BIBTEX) $(SOURCE)
	perl -n fixbbl.pl < $(SOURCE).bbl > tmp.bbl
	$(MV) tmp.bbl $(SOURCE).bbl

clean:
	$(RM) $(SOURCE).aux
	$(RM) $(SOURCE).bbl
	$(RM) $(SOURCE).blg
	$(RM) $(SOURCE).dvi
	$(RM) $(SOURCE).log
	$(RM) $(SOURCE).out
	$(RM) $(SOURCE).pdf
	$(RM) $(SOURCE).ps
	$(RM) $(SOURCE).bak
