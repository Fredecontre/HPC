
default: test

test: test.c mouvement.c morpho.c
	g++ -o test test.c mouvement.c morpho.c -Inrc2-master/include/ -Lnrc2-master/build/lib/ -IMIPP-master/src -lnrc

test_SIMD: test_SIMD.c mouvement_SIMD.c morpho_SIMD.c
	g++ -o test_SIMD test_SIMD.c mouvement_SIMD.c morpho_SIMD.c -Inrc2-master/include/ -Lnrc2-master/build/lib/ -IMIPP-master/src -lnrc

clean:
	-rm -f test
	-rm -f test_SIMD
	-rm -f *.pgm
	-rm -f *.o