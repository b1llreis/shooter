.PHONY: build run clean rebuild setup

build:
	@cmake --build build

run: build
	@./build/game

clean:
	@rm -rf build

rebuild: clean setup build

setup:
	@mkdir -p build
	@cd build && cmake ..
