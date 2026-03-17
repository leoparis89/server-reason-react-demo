[@react.component]
let make = () =>
  <div>
    <h1> {React.string("Hydration Demo")} </h1>
    <p>
      {React.string(
         "This page is server-rendered, then hydrated on the client. "
         ++ "The counter below becomes interactive after hydration.",
       )}
    </p>
    <Counter />
    <a href="/"> {React.string("Go to Home")} </a>
  </div>;
