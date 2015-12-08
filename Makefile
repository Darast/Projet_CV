
make:
	qmake-qt4 src/test1.pro
	cd src/
	make 
	cd ../

clean:
	rm build/*