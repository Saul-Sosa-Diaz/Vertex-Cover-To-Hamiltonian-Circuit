CFLAGS = -g -std=c++20 -Wall -Wextra -pedantic -O3
LDFLAGS = # Agrega flags de enlace si es necesario
src_dir = src
obj_dir = obj
bin_dir = bin

src1 = $(src_dir)/main.cc
src2 = $(src_dir)/graph/vertex.cc 
src3 = $(src_dir)/graph/graph.cc
src4 = $(src_dir)/graph/graphParser.cc
src5 = $(src_dir)/graph/vertexPair.cc
src6 = $(src_dir)/utils/menu.cc
src7 = $(src_dir)/graph/gadget.cc
src8 = $(src_dir)/algorithms/polyReduction.cc
src_files = $(src1) $(src2) $(src3) $(src4) $(src5) $(src6) $(src7) $(src8)
obj_files = $(patsubst $(src_dir)/%.cc,$(obj_dir)/%.o,$(src_files))

# compile
$(bin_dir)/pReduction: $(obj_files)
	g++ $(CFLAGS) -o $@ $(obj_files) $(LDFLAGS)

# compilar archivos de objeto
$(obj_dir)/%.o: $(src_dir)/%.cc | $(obj_dir)
	g++ $(CFLAGS) -c $< -o $@

# crear directorio de objetos si no existe
$(obj_dir):
	mkdir -p $(obj_dir)/graph
	mkdir -p $(obj_dir)/algorithms
	mkdir -p $(obj_dir)/utils
	mkdir -p $(bin_dir)

# crear directorio de binarios si no existe
$(bin_dir):
	mkdir -p $(bin_dir)

# run driver program
run: $(bin_dir)/pReduction
	mkdir -p graphResults
	./$<

# Debian based distros
dependencies:
	sudo apt install build-essential
	sudo apt install nlohmann-json3-dev

update:
	git add .
	git commit -m "update"
	git push

Ignore:
	git add .gitignore

clean:
	rm -r obj
	rm -r bin