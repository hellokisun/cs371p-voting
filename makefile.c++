all:
	make run
	make test

diff: RunVoting
	RunVoting < RunVoting.in > RunVoting.tmp
	diff RunVoting.out RunVoting.tmp
	rm RunVoting.tmp

doc:
	doxygen Doxyfile

log:
	git log > Voting.log

RunVoting: Voting.h Voting.c++ RunVoting.c++
	g++ -pedantic -std=c++0x -Wall Voting.c++ RunVoting.c++ -o RunVoting

run: RunVoting
	RunVoting < RunVoting.in

runv: RunVoting
	valgrind RunVoting < RunVoting.in

TestVoting: Voting.h Voting.c++ TestVoting.c++
	g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lcppunit -ldl

test: TestVoting
	TestVoting

testv: TestVoting
	valgrind TestVoting

turnin-list:
	turnin --list reza cs371ppj2

turnin-submit:
	turnin --submit reza cs371ppj2 Voting.zip

turnin-verify:
	turnin --verify reza cs371ppj2

zip:
	zip -r Voting.zip html/ makefile Voting.c++ Voting.h Voting.log \
	RunVoting.c++ RunVoting.in RunVoting.out UVaVoting.c++ \
	TestVoting.c++ TestVoting.out

clean:
	rm -f RunVoting
	rm -f TestVoting
	rm -f *.tmp
