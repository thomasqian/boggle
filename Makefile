test: bogtest.cpp boggleplayer.cpp boggleplayer.h boggleutil.cpp boggleutil.h
	g++ -g -o test bogtest.cpp boggleplayer.cpp boggleplayer.h boggleutil.cpp boggleutil.h

boggle: boggle.cpp boggleplayer.cpp boggleplayer.h boggleutil.cpp boggleutil.h
	g++ -std=c++11 -g -o boggle boggle.cpp boggleplayer.cpp boggleplayer.h boggleutil.cpp boggleutil.h

clean:
	rm -f boggle *.o
