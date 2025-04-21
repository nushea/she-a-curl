.PHONY: curl
.PHONY: simpl
.PHONY: about
.PHONY: about-simple
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
