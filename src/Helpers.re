open SharedTypes;

let toString = React.string;

let getWinner = (flattenedBoard, coordinates) =>
  switch (
    List.nth(flattenedBoard, List.nth(coordinates, 0)),
    List.nth(flattenedBoard, List.nth(coordinates, 1)),
    List.nth(flattenedBoard, List.nth(coordinates, 2)),
  ) {
  | (Marked(Cross), Marked(Cross), Marked(Cross)) => Cross
  | (Marked(Circle), Marked(Circle), Marked(Circle)) => Circle
  | (_, _, _) => NoOne
  };

let gameEnded = board =>
  List.for_all(
    field => field == Marked(Circle) || field == Marked(Cross),
    board,
  );

let isFinished = (value: gameState) =>
  switch (value) {
  | Winner(_) => true
  | _ => false
  };

let whosPlaying = (gameState: gameState) =>
  switch (gameState) {
  | Playing(Cross) => Playing(Circle)
  | _ => Playing(Cross)
  };

let checkGameState =
    (
      winningRows: winningRows,
      updatedBoard: board,
      oldBoard: board,
      gameState: gameState,
    ) =>
  oldBoard == updatedBoard
    ? gameState
    : {
      let flattenedBoard = List.flatten(updatedBoard);
      let rec check = (rest: winningRows) => {
        let head = List.hd(rest);
        let tail = List.tl(rest);
        switch (
          getWinner(flattenedBoard, head),
          gameEnded(flattenedBoard),
          tail,
        ) {
        | (Cross, _, _) => Winner(Cross)
        | (Circle, _, _) => Winner(Circle)
        | (_, true, []) => Draw
        | (_, false, []) => whosPlaying(gameState)
        | _ => check(tail)
        };
      };
      check(winningRows);
    };

let toValue = (field: field) =>
  switch (field) {
  | Marked(Cross) => "X"
  | Marked(Circle) => "O"
  | Empty => ""
  };

let getClass = (gameState: gameState, field: field) =>
  switch (gameState) {
  | Winner(player) => field == Marked(player) ? "winner square" : "square"
  | _ => "square"
  };
