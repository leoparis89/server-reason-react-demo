.PHONY: setup build run clean

# First time setup: install all dependencies
setup:
	opam install . --deps-only
	cd client && npm install

# Build everything: server + client bundle
build:
	dune build
	node client/build.mjs _build/default/client/app/client/HydrateRoot.re.js --output=static/ --node-path=client/node_modules --env=development

# Build and start the server
run: build
	dune exec hello-ssr

# Remove all build artifacts
clean:
	dune clean
	rm -rf static/
