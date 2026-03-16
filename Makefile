build:
	dune build

run: build
	dune exec hello-ssr

clean:
	dune clean
