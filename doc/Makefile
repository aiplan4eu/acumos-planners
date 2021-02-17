
ASCIIDOCTOR = asciidoctor

ADOCS = $(wildcard *.adoc)

HTMLS =  $(patsubst %.adoc,%.html,$(wildcard *.adoc))


all: $(HTMLS)

%.html: %.adoc
	$(ASCIIDOCTOR) $(ASCIIDOCTOR_ARGS) -b html5 -o $@ $<
