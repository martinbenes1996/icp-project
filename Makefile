
all: src/Makefile

src/Makefile:
	@echo "Generating a Makefile with qmake.";\
	qmake -o src/Makefile src/icp.pro 2> /dev/null > /dev/null
	@echo "Compiling the files.";\
	$(MAKE) -C src/ -s 2> /dev/null > /dev/null
	@printf "";\
	cp src/blockeditor . 2> /dev/null > /dev/null


.PHONY: run
run:
	@printf "";\
	./blockeditor

.PHONY: zip
zip:
	@printf "";\
	zip xbenes49_xpolan09.zip src/*.cpp src/*.h src/icp.pro src/gen/ README.md Makefile 2> /dev/null > /dev/null

.PHONY: clean
clean:
	@echo "Cleaning generated files.";\
	rm -rf src/gen/moc_* src/gen/*.o *~ *.gch src/Makefile src/blockeditor blockeditor xbenes49_xpolan09.zip 2> /dev/null > /dev/null
