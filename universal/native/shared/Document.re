[@react.component]
let make = (~children, ~title="Hello SSR", ~script=?) => {
  <html>
    <head>
      <meta charSet="UTF-8" />
      <meta name="viewport" content="width=device-width, initial-scale=1.0" />
      <title> {React.string(title)} </title>
      {switch (script) {
       | None => React.null
       | Some(src) => <script type_="module" src />
       }}
    </head>
    <body> <div id="root"> children </div> </body>
  </html>;
};
