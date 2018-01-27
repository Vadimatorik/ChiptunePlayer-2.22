CWD= $(shell pwd)
UNAME_S := $(shell uname -s)
FILE := software_design_documents

ifeq ($(UNAME_S),Linux)
    INKSCAPE=inkscape
    PLANTUML=plantuml
    PDFLATEX=pdflatex
    OPEN_PDF_UTIL=evince
endif
ifeq ($(UNAME_S),Darwin)
    INKSCAPE=/Applications/Inkscape.app/Contents/Resources/script
    PDFLATEX=/usr/local/texlive//2015/bin/universal-darwin/pdflatex
    OPEN_PDF_UTIL=open
endif


GRP=graphics
SVGS = $(shell find $(CWD)/ -name '*.svg')
SVGS2PDF := ${SVGS:.svg=.pdf}
SVGS2PNG := ${SVGS:.svg=.png}
SVGS2EPS := ${SVGS:.svg=.eps}

UML=uml
PU = $(shell find $(CWD)/ -name '*.pu')
PU2EPS := ${PU:.pu=.eps}

all: pdf
	@echo Success!

%.pdf : %.svg
	$(INKSCAPE) -D -z --file=$< --export-pdf=$@ --export-latex --export-area-drawing

%.png : %.svg
	$(INKSCAPE) -D -z $< -e $@ --export-area-drawing  -d 200

%.eps : %.svg
	$(INKSCAPE)-D  $< -E $@ --export-ignore-filters --export-ps-level=3

%.eps : %.pu
	$(PLANTUML) -teps $< $@

pdf_tex: $(SVGS2PDF)
	@echo SVGs to PDF_TEX are done!

png: $(SVGS2PNG)
	@echo SVGs to PNG are done!

eps: $(SVGS2EPS) $(PU2EPS)
	@echo SVGs and PlantUML to EPS are done!

clean_graphics:
	rm -vf $(GRP)/*.eps
	rm -vf $(GRP)/*.pdf
	rm -vf $(UML)/*.eps
	rm -vf $(UML)/*.pdf
	rm -vf $(UML)/*.png
	
# for a first time
$(FILE).pdf: $(SVGS2EPS) $(PU2EPS) 
	$(PDFLATEX) -halt-on-error --shell-escape $(FILE).tex
	

pdf: $(FILE).pdf
	$(PDFLATEX) -halt-on-error --shell-escape $(FILE).tex


clean: clean_graphics
	rm -fv *.out  *.toc *.log *.aux *.pdf *.tmp *.fdb_latexmk *.fls

rebuild: clean all

test: all
	$(OPEN_PDF_UTIL) $(FILE).pdf
