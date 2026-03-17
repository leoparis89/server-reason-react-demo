# universal/

Components here are compiled **twice** from the same source:

1. To **native OCaml** (runs on the server)
2. To **JavaScript** via Melange (runs in the browser)

## Why two directories?

dune (the build tool) only allows one config file per directory, and each
compiler needs its own config. So we need two directories:

```
universal/
  native/
    shared/
      Counter.re       <- source files live here
      Document.re
      HydratePage.re
    dune               <- config: compile with OCaml (native)
  js/
    dune               <- config: compile with Melange (JS)
                          + copy_files to borrow .re files from native/shared/
```

`js/` contains **no source files**. Its `dune` has a `copy_files` rule that
grabs the `.re` files from `native/shared/` and compiles them with Melange.

## Why native/shared/?

The demo in oglib uses `shared/` to separate components that run on both
server and client from server-only files (like `DB.re`). In this example
all components are shared, but we keep the convention for consistency.

## How it works

The same `Counter.re` produces different behavior on each target:

- **Server (native)**: `React.useState` returns `(0, noop)` — renders static HTML
- **Browser (JS)**: `React.useState` is real React — clicks update state

The server library is `hello_shared_native` (used by `bin/main.re`).
The JS library is `hello_shared_js` (used by `client/HydrateRoot.re`).
