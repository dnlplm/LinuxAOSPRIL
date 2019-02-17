all:
	make -C reference-ril
	make -C tests

clean:
	make -C reference-ril clean
	make -C tests clean

