test_poisson:test_poisson.cpp *.h
	g++ -c *.h
	g++ -o test_poisson test_poisson.cpp

%.o : %.h
	g++ -c $<


clean:
	rm *.o *.h.gch test *.exe html latex -fr

design:
	doxygen Doxyfile
	firefox ./html/index.html
