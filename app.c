#include "pieces.h"
#include <stdio.h>

int main() {
    GameBoard chessBoard;
    chessBoard = createGameBoard(&chessBoard);
    printGameBoard(&chessBoard);
}

GameBoard movePiece(GameBoard *gameBoard, struct Piece *piece, Position currentPosition, Position requestedPosition) {
    if (canMove(gameBoard, requestedPosition, piece) == 1) {
        gameBoard->board[requestedPosition.row][requestedPosition.column] = *piece;
        gameBoard->board[requestedPosition.row][requestedPosition.column].currentPosition = requestedPosition;
        gameBoard->board[currentPosition.row][currentPosition.column] = EMPTY;
        return *gameBoard;
    } else {
        printf("\nThat move is illegal; Nothing was changed\n");
        return *gameBoard;
    }
}

GameBoard createGameBoard(GameBoard *gameBoard) {
    for (int i = 0; i < 8; i++) {
        gameBoard->board[1][i] = BLACK_PAWN;
        gameBoard->board[6][i] = WHITE_PAWN;
    }
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            gameBoard->board[i][j] = EMPTY;
        }
    }
    gameBoard->board[0][0] = BLACK_ROOK;
    gameBoard->board[7][0] = WHITE_ROOK;
    gameBoard->board[0][1] = BLACK_KNIGHT;
    gameBoard->board[7][1] = WHITE_KNIGHT;
    gameBoard->board[0][2] = BLACK_BISHOP;
    gameBoard->board[7][2] = WHITE_BISHOP;
    gameBoard->board[0][3] = BLACK_QUEEN;
    gameBoard->board[7][3] = WHITE_QUEEN;
    gameBoard->board[0][4] = BLACK_KING;
    gameBoard->board[7][4] = WHITE_KING;
    gameBoard->board[0][5] = BLACK_BISHOP;
    gameBoard->board[7][5] = WHITE_BISHOP;
    gameBoard->board[0][6] = BLACK_KNIGHT;
    gameBoard->board[7][6] = WHITE_KNIGHT;
    gameBoard->board[0][7] = BLACK_ROOK;
    gameBoard->board[7][7] = WHITE_ROOK;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            gameBoard->board[i][j].currentPosition.row = i;
            gameBoard->board[i][j].currentPosition.column = j;
        }
    }
    return *gameBoard;
}

int canMove(GameBoard *gameBoard, Position requestedPosition, struct Piece *piece) {
    switch (piece->type) {
    case PAWN:
        if (piece->Colour == BLACK) {
            if (piece->currentPosition.row + 1 == requestedPosition.row) {
                if (requestedPosition.column == piece->currentPosition.column && gameBoard->board[requestedPosition.row][requestedPosition.column].type == NONE) {
                    return 1;
                }
                if (requestedPosition.column == piece->currentPosition.column + 1 || requestedPosition.column == piece->currentPosition.column - 1) {
                    if (gameBoard->board[requestedPosition.row][requestedPosition.column].type == NONE || gameBoard->board[requestedPosition.row][requestedPosition.column].Colour == piece->Colour) {
                        return 0;
                    } else {
                        return 1;
                    }
                }
            } else {
                return 0;
            }
        } else if (piece->Colour == WHITE) {
            if (requestedPosition.row == piece->currentPosition.row - 1) {
                if (requestedPosition.column == piece->currentPosition.column && gameBoard->board[requestedPosition.row][requestedPosition.column].type == NONE) {
                    return 1;
                }
                if (requestedPosition.column == piece->currentPosition.column + 1 || requestedPosition.column == piece->currentPosition.column - 1) {
                    if (gameBoard->board[requestedPosition.row][requestedPosition.column].type == NONE || gameBoard->board[requestedPosition.row][requestedPosition.column].Colour == piece->Colour) {
                        return 0;
                    }
                    return 0;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        }
        break;
    case KNIGHT:
        if (piece->currentPosition.row == requestedPosition.row + 2 || piece->currentPosition.row == requestedPosition.row - 2) {
            if (piece->currentPosition.column == requestedPosition.column + 1 || piece->currentPosition.column == requestedPosition.column - 1) {
                int result = gameBoard->board[requestedPosition.row][requestedPosition.column].Colour == piece->Colour ? 0 : 1;
                return result;
            }
            return 0;
        } else {
            return 0;
        }
    break;
  case ROOK:
   if (gameBoard->board[requestedPosition.row][requestedPosition.column].Colour == piece->Colour) {
            return 0;
        } else {
            // Moving vertically
            if (requestedPosition.row != piece->currentPosition.row && requestedPosition.column == piece->currentPosition.column) {
                if (requestedPosition.row > piece->currentPosition.row) {
                    // Moving down
                    for (int i = piece->currentPosition.row + 1; i < requestedPosition.row; i++) {
                        if (gameBoard->board[i][requestedPosition.column].type != NONE) {
                            return 0;
                        }
                    }
                } else {
                    // Moving up
                    for (int i = requestedPosition.row + 1; i < piece->currentPosition.row; i++) {
                        if (gameBoard->board[i][requestedPosition.column].type != NONE) {
                            return 0;
                        }
                    }
                }
                return 1;
            }
            // Moving horizontally
            else if (requestedPosition.column != piece->currentPosition.column && requestedPosition.row == piece->currentPosition.row) {
                if (requestedPosition.column > piece->currentPosition.column) {
                    // Moving right
                    for (int i = piece->currentPosition.column + 1; i < requestedPosition.column; i++) {
                        if (gameBoard->board[requestedPosition.row][i].type != NONE) {
                            return 0;
                        }
                    }
                } else {
                    // Moving left
                    for (int i = requestedPosition.column + 1; i < piece->currentPosition.column; i++) {
                        if (gameBoard->board[requestedPosition.row][i].type != NONE) {
                            return 0;
                        }
                    }
                }
                return 1;
            }
            // Invalid move
            else {
                return 0;
            }
        }
    break;
    case BISHOP:
      if (gameBoard->board[requestedPosition.row][requestedPosition.column].Colour == piece->Colour) {
        return 0;
      }
      if (requestedPosition.row - piece->currentPosition.row == requestedPosition.column - piece->currentPosition.column) {
        if (requestedPosition.row > piece->currentPosition.row) {
          if (requestedPosition.column > piece->currentPosition.column) {
            for (int i = piece->currentPosition.row + 1; i < requestedPosition.row; i++) {
              for (int j = piece->currentPosition.column + 1; j < requestedPosition.column; j++) {
                if (gameBoard->board[i][j].type != NONE) {
                  return 0; 
                }
              }
            }
          } else {
            for (int i = piece->currentPosition.row + 1; i < requestedPosition.row; i++) {
              for (int j = piece->currentPosition.column + 1; i < requestedPosition.column; j++) {
                if (gameBoard->board[i][j].type != NONE) {
                  return 0; 
                }
              }
            }
          } 
        } else {
          if (requestedPosition.column > piece->currentPosition.column) {
            for (int i = requestedPosition.row + 1; i < piece->currentPosition.row; i++) {
              for (int j = piece->currentPosition.column + 1; j < requestedPosition.column; j++) {
                if (gameBoard->board[i][j].type != NONE) {
                  return 0;
                }
              }
            }
          } else {
            for (int i = requestedPosition.row + 1; i < piece->currentPosition.row; i++) {
              for (int j = requestedPosition.column + 1; j < piece->currentPosition.column; j++) {
                if (gameBoard->board[i][j].type != NONE) {
                  return 0;
                }
              }
            }
          }
        }
        return 1;
      } else {
        return 0;
      }
    break;
    case QUEEN: 
      if (gameBoard->board[requestedPosition.row][requestedPosition.column].Colour == piece->Colour) {
        return 0;
      }
      struct Piece rook = { ROOK, piece->Colour, "", piece->currentPosition };
      struct Piece bishop = { BISHOP, piece->Colour, "", piece->currentPosition };
      struct Piece pawn = { PAWN, piece->Colour, "", piece->currentPosition };
      if (
        canMove(gameBoard, requestedPosition, &rook) ||
        canMove(gameBoard, requestedPosition, &bishop) ||
        canMove(gameBoard, requestedPosition, &pawn)
      ) {
        return 1;
      } else {
        return 0;
      }
    break;
  }    
    return 0;
}
 
void printGameBoard(GameBoard *gameBoard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%s | ", gameBoard->board[i][j].name);
        }
        printf("\n");
    }
}
// 3,2 -> 
