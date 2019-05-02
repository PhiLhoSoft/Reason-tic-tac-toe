open Helpers;

[@react.component]
let make = () => {
  <div>
      <h1 className="title">
        (toString("Tic Tac Toe"))
      </h1>
      <Game/>
  </div>
};
