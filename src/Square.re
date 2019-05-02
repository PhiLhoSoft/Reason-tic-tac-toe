open SharedTypes;
open Helpers;

[@react.component]
let make = (~value: field, ~gameState: gameState, ~onMark) => {
  <button
    className=(getClass(gameState, value))
    disabled=(gameState |> isFinished)
    onClick=(_evt => onMark())>
    (value |> toValue |> toString)
  </button>
};
