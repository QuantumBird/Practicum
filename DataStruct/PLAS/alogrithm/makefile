CMPLR = g++ -std=c++11
HEADER_PATH = ../matrix

testLU: test_lu
	./test_lu

TEST_LU_DEP = test_for_LU.cpp \
							LU.hpp\
						 	$(HEADER_PATH)/GEmat.hpp\
							$(HEADER_PATH)/Mat.hpp\
							$(HEADER_PATH)/mats.hpp

test_lu: $(TEST_LU_DEP)
	$(CMPLR) -I $(HEADER_PATH) $(TEST_LU_DEP) -o test_lu


clean:
	rm -f test_lu