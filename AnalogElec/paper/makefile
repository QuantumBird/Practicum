Template.pdf: Template.tex Template.aux ref.bib
	xelatex Template.tex
	bibtex Template.aux
	xelatex Template.tex
	xelatex Template.tex

Template.aux: Template.tex
	xelatex Template.tex

clean:
	rm -f Template.pdf 
	rm -f Template.log 
	rm -f Template.aux
	rm -f Template.bbl
	rm -f Template.dvi
	rm -f Template.blg

rebuild:
	rm -f Template.pdf 
	rm -f Template.log 
	rm -f Template.aux
	rm -f Template.bbl
	rm -f Template.dvi
	rm -f Template.blg
	
	xelatex Template.tex
	bibtex Template.aux
	xelatex Template.tex
	xelatex Template.tex
