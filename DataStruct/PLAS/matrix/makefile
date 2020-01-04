CMPLR = g++ -std=c++11

testGM: test_gm
	./test_gm

#test_gm: test_for_basic_mat.cpp basic_mat.hpp 
#	$(CMPLR) test_for_basic_mat.cpp basic_mat.hpp -o test_gm
TEST_GM_DEP = test_for_basic_mat.cpp GEmat.hpp #basic_mat_mult.cpp
test_gm: $(TEST_GM_DEP)
	$(CMPLR) -o test_gm $(TEST_GM_DEP)

testMat: test_mat
	./test_mat


TEST_MAT_DEP = test_for_mat.cpp Mat.hpp GEmat.hpp
test_mat: $(TEST_MAT_DEP)
	$(CMPLR) -o test_mat $(TEST_MAT_DEP)

testET: test_extratype
	./test_extratype

TEST_ET_DEP = test_for_extratype.cpp extratype.hpp GEmat.hpp
test_extratype: $(TEST_ET_DEP)
	$(CMPLR) -o test_extratype $(TEST_ET_DEP)


testMatLU: test_mat_LU
	./test_mat_LU


TEST_MATLU_DEP = test_for_mat_LU.cpp Mat.hpp GEmat.hpp
test_mat_LU: $(TEST_MATLU_DEP)
	$(CMPLR) -o test_mat_LU $(TEST_MATLU_DEP)

clean:
	# clear for testGM
	rm -f test_gm 
	# clean for testMat
	rm -f test_mat
	# clean for testET
	rm -rf test_extratype
	rm -f test_for_mat_LU