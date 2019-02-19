.PHONY: common

common:
	$(MAKE) -f make/Makefile.frag $(MAKECMDGOALS)
	TARGET=os $(MAKE) -f make/Makefile.frag $(MAKECMDGOALS)

all: common

clean: common

install: common

tests: common
