CMPLR = g++ --std=c++11

testGM: test_gm
	./test_gm

#test_gm: test_for_basic_mat.cpp basic_mat.hpp 
#	$(CMPLR) test_for_basic_mat.cpp basic_mat.hpp -o test_gm
TEST_GM_DEP = test_for_basic_mat.cpp GEmat.hpp #basic_mat_mult.cpp
test_gm: $(TEST_GM_DEP)
	$(CMPLR) -o test_gm $(TEST_GM_DEP)

clean:
	# clear for testGM
	rm -f test_gm 