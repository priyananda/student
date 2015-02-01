all: clean
	gnuplot graphs.plot
	gnuplot results.plot
	latex   calf-report.tex
	latex   calf-report.tex
	dvipdf  calf-report.dvi

clean: cleano
	rm -rf *.pdf

cleano:
	rm -rf case*.eps res*.eps *.dvi *.log *.out *.aux
