PROGS = main
CLEANFILES = core core.* *.core *.o temp.* *.out typescript* *.lc *.lh *.bsdi *.sparc *.uw

all : ${PROGS}

CXXFLAGS += -g -std=c++11

main : main.o
  ${CXX} ${CXXFLAGS} -o $@ $^
  @rm *.o
clean:
  rm -f ${PROGS} ${CLEANFILES}
