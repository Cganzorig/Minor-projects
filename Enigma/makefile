CXX=g++ -Wall -g
EXE=main.o enigma.o plugboard.o reflector.o rotor.o  helper.o

enigma: $(EXE)
	$(CXX) $(EXE) -o enigma

%.o: %.cpp helper.h
	$(CXX) -c $<

main.o: enigma.h errors.h
enigma.o: enigma.h plugboard.h reflector.h rotor.h

.PHONY: clean
clean:
	rm -f enigma *.o
