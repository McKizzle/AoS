ASS=CSCI491McKayMilestoneFive
MDIN=Setup Timeline StatusReport
MARKDOWN=$(MDIN:%=%.md)
MDFILE=$(ASS).md
OUTFILE=$(ASS)

$(info $(MDIN))
$(info $(MARKDOWN))

all: $(MARKDOWN)
	echo $^
	#echo 'all'

$(MARKDOWN):
	echo $@

# make pdf from markdowns
md_pdf: 
	echo $(MARKDOWN)
	#pandoc $(MDFILE) -o $(OUTFILE).pdf
	#zip $(OUTFILE).zip $(OUTFILE).pdf $(UI_DES).pdf



