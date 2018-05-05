
all: blockeditor

blockeditor:
	@echo "Generating a Makefile with qmake.";\
	qmake -o src/Makefile src/icp.pro
	@echo "Compiling the files.";\
	$(MAKE) -C src/ -s
	@printf "";\
	mv src/blockeditor . 2> /dev/null > /dev/null

.PHONY: doxygen
doxygen:
	@echo "Generating documentation";\
	doxygen Doxyfile 2> /dev/null > /dev/null

.PHONY: run
run:
	@printf "";\
	./blockeditor

.PHONY: pack
pack:
	@echo "Packing to the archive.";\
	zip xbenes49-xpolan09.zip Doxyfile src/*.cpp src/*.h src/icp.pro src/bordel/ styles/* doc/*.png doc/*.jpg styles/* examples/* README.txt Makefile 2> /dev/null > /dev/null

.PHONY: clean
clean:
	@echo "Cleaning generated files.";\
	rm -rf src/bordel/moc_* src/bordel/*.o *~ *.gch src/Makefile blockeditor xbenes49_xpolan09.zip doc/html src/.qmake.stash 2> /dev/null > /dev/null
