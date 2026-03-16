Dream.run(~port=8080, ~interface="localhost",
  Dream.logger(
    Dream.router([
      Dream.get("/", _req => Dream.html("Hello from Dream!")),
    ]),
  ),
);
