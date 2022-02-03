# Rename from `build` to `a_build` so it stays above `behavioral` :)
build_folder=a_build 

all:
	mkdir -p ${build_folder}
	cd ${build_folder}; cmake -G "Unix Makefiles" ../; make

clean:
	rm -r ${build_folder}
