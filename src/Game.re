open SharedTypes;
open Helpers;

let initialState = {
  board: [
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
  ],
  gameState: Playing(Cross),
};

let winningCombinations = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6],
];

let checkGameState3x3 = checkGameState(winningCombinations);

let updateBoard = (board: board, gameState: gameState, id) =>
  board
  |> List.mapi((ind: int, row: row) =>
       row
       |> List.mapi((index: int, value: field) =>
            string_of_int(ind) ++ string_of_int(index) === id
              ? switch (gameState, value) {
                | (_, Marked(_)) => value
                | (Playing(player), Empty) => Marked(player)
                | (_, Empty) => Empty
                }
              : value
          )
     );

let reducer = (state: state, action: action) =>
  switch (action) {
  | Restart => initialState
  | ClickSquare((id: string)) =>
    let updatedBoard = updateBoard(state.board, state.gameState, id);
    {
      board: updatedBoard,
      gameState:
        checkGameState3x3(updatedBoard, state.board, state.gameState),
    };
  };

[@react.component]
let make = () => {
  let (initialState, _setInitialState) = React.useState(() => initialState);
  let (state, dispatch) = React.useReducer(reducer, initialState);

  <div className="game">
    <Board
      state
      onRestart={_evt => dispatch(Restart)}
      onMark={id => dispatch(ClickSquare(id))}
    />
  </div>;
};
