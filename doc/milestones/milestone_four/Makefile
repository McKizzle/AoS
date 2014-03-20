ASS=CSCI491McKayMilestoneFour
UI_DES=CSCI491McKayAoSUIDesign
MDFILE=$(ASS).md
OUTFILE=$(ASS)

pdf:
	pandoc $(MDFILE) -o $(OUTFILE).pdf
	#tar -zcvf $(OUTFILE).tar.gz $(OUTFILE).pdf
	zip $(OUTFILE).zip $(OUTFILE).pdf $(UI_DES).pdf


