run : bin/animacion
	./bin/animacion

bin/animacion : src/animacion.cpp include/*.hpp
	@mkdir -p bin
	g++ -Iinclude -o bin/animacion src/animacion.cpp -lftxui-component -lftxui-dom -lftxui-screen