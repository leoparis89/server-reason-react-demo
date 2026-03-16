let page =
  <html>
    <body>
      <h1> {React.string("Hello from server-reason-react!")} </h1>
    </body>
  </html>;

Dream.run(~port=8080, ~interface="localhost",
  Dream.logger(
    Dream.router([
      Dream.get("/", _req => Dream.html(ReactDOM.renderToString(page))),
    ]),
  ),
);
