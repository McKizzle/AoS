REQUIREMENTS_DOC = Requirements
PROOF_CONC	 = ProofOfConcept
ZIP		 = CSCI491McKayMilestone2.zip

req:
	pandoc $(REQUIREMENTS_DOC).md -o $(REQUIREMENTS_DOC).pdf

prf:
	pandoc $(PROOF_CONC).md -o $(PROOF_CONC).pdf

zip:
	zip $(ZIP) $(REQUIREMENTS_DOC).pdf $(PROOF_CONC).pdf

