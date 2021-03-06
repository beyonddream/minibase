/=./

include config.mk

DESTDIR ?= ./out

.SUFFIXES:

all: libs build

libs: lib/all.a

lib/all.a:
	$(MAKE) -C lib

build: lib/all.a
	$(MAKE) -C src

install: libs
	$(MAKE) -C src DESTDIR=$(abspath $(DESTDIR)) install

clean: clean-lib clean-src clean-test clean-temp clean-test clean-out

clean-out:
	rm -fr out/ src/out src/*/out

clean-%:
	$(MAKE) -C $* clean

test:
	$(MAKE) -C test run

.PHONY: test
.SILENT: build lib/all.a clean-lib clean-src clean-test

# Allow building files from the top dir
# Usefule for :make in vim

src/%.o lib/%.o temp/%.o test/%.o:
	$(MAKE) -C $(dir $@) $(notdir $@)
