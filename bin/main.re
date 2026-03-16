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

let render = component => Dream.html(ReactDOM.renderToString(component));

Dream.run(~port=8080, ~interface="localhost",
  Dream.logger(
    Dream.router([
      Dream.get("/", _req => render(<Home />)),
      Dream.get("/about", _req => render(<About />)),
    ]),
  ),
);
