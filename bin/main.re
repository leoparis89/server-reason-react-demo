// Shared layout component, wraps every page with <html> and <body>
module Layout = {
  [@react.component]
  let make = (~title, ~children) =>
    <html>
      <head> <title> {React.string(title)} </title> </head>
      <body> children </body>
    </html>;
};

module Home = {
  [@react.component]
  let make = () =>
    <Layout title="Home">
      <h1> {React.string("Home")} </h1>
      <p> {React.string("Welcome to hello-ssr!")} </p>
      <a href="/about"> {React.string("Go to About")} </a>
      <a href="/stream"> {React.string(" | Go to Streaming")} </a>
    </Layout>;
};

module About = {
  [@react.component]
  let make = () =>
    <Layout title="About">
      <h1> {React.string("About")} </h1>
      <p> {React.string("This is server-side rendered with Reason + React.")} </p>
      <a href="/"> {React.string("Go to Home")} </a>
    </Layout>;
};

// [@react.async.component] means this component returns Lwt.t(React.element)
// instead of React.element. It can do async work before returning JSX.
module SlowData = {
  [@react.async.component]
  let make = () => {
    // Simulate a slow database/API call (3 second delay)
    let%lwt () = Lwt_unix.sleep(3.0);
    Lwt.return(
      <p> {React.string("This data took 3 seconds to load!")} </p>,
    );
  };
};

module Stream = {
  [@react.component]
  let make = () =>
    <Layout title="Streaming">
      <h1> {React.string("Streaming SSR")} </h1>
      <p> {React.string("The HTML below will stream in after 3 seconds:")} </p>
      // React.Suspense shows the fallback ("Loading...") immediately,
      // then swaps in the real content once SlowData resolves.
      <React.Suspense fallback={<p> {React.string("Loading...")} </p>}>
        <SlowData />
      </React.Suspense>
      <a href="/"> {React.string("Go to Home")} </a>
    </Layout>;
};

// renderToString: builds the entire HTML string, then sends it all at once.
let render = component => Dream.html(ReactDOM.renderToString(component));

// renderToStream: sends HTML in chunks as they become ready.
// The browser can start rendering the page before all the data has loaded.
let streamRender = component =>
  Dream.stream(
    ~headers=[("Content-Type", "text/html")],
    stream => {
      // renderToStream returns an Lwt_stream of string chunks + an abort fn.
      // Each chunk is a piece of HTML (shell first, then Suspense results).
      let%lwt (htmlStream, _abort) = ReactDOM.renderToStream(component);
      Lwt_stream.iter_s(
        chunk => {
          let%lwt () = Dream.write(stream, chunk);
          Dream.flush(stream);
        },
        htmlStream,
      );
    },
  );

Dream.run(~port=8080, ~interface="localhost",
  Dream.logger(
    Dream.router([
      Dream.get("/", _req => render(<Home />)),
      Dream.get("/about", _req => render(<About />)),
      Dream.get("/stream", _req => streamRender(<Stream />)),
    ]),
  ),
);
