.PHONY: curl
.PHONY: simpl
.PHONY: index
.PHONY: about
.PHONY: pnf
.PHONY: about-simple
.PHONY: index-simple
all:
	gcc main.c -o curl
	gcc about.c -o about
	gcc simple.c -o simpl
clear:
	rm curl || true
	rm about || true
	rm simpl || true
curl:
	rm curl || true
	gcc main.c -o curl
	./curl
simpl:
	rm simpl || true
	gcc simple.c -o simpl
	./simpl
about:
	rm about || true
	gcc about.c -o about
	./about
about-simple:
	rm about-simple || true
	gcc about-simple.c -o about-simple
	./about-simple
index:
	rm index || true
	gcc index.c -o index
	./index
index-simple:
	rm index-simple || true
	gcc index-simple.c -o index-simple
	./index-simple
pnf:
	rm pnf || true
	gcc pnf.c -o pnf
	./pnf
