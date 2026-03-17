[@react.component]
let make = () => {
  let (count, setCount) = React.useState(() => 0);

  <div>
    <p> {React.string("Count: " ++ Int.to_string(count))} </p>
    <button onClick={_ => setCount(c => c + 1)}>
      {React.string("Increment")}
    </button>
  </div>;
};
