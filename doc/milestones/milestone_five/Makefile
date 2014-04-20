ASS=CSCI491McKayMilestoneFive
MDIN=Setup Timeline StatusReport
MARKDOWN=$(MDIN:%=%.md)
PDF=$(MDIN:%=%.pdf)
MDFILE=$(ASS).md
OUTFILE=$(ASS)

all: $(PDF)
	wget --no-clobber https://github.com/McKizzle/AoS/archive/v0.5.0.zip
	zip $(OUTFILE).zip $(PDF) v0.5.0.zip

%.pdf: %.md
	pandoc $< -o $@

clean:
	rm -rf *.pdf



