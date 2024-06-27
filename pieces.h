#include <stdlib.h>
#include <string.h>
enum Type {
  NONE = 0,
  PAWN,
  ROOK,
  KNIGHT,
  KING,
  QUEEN,
  BISHOP,
};
enum Colours {
  BLACK,
  WHITE,
  BLANK,
};
typedef struct  {
  int row;
  int column;
} Position;
struct Piece {
  enum Type type;
  enum Colours Colour;
  char name[13];
  Position currentPosition; 
};

typedef struct {
  struct Piece board[8][8]; 
} GameBoard; 


const struct Piece BLACK_PAWN = { PAWN, BLACK, "BLACK_PAWN" };
const struct Piece BLACK_KNIGHT =  { KNIGHT, BLACK, "BLACK_KNIGHT"};
const struct Piece BLACK_ROOK =  { ROOK, BLACK ,"BLACK_ROOK"};
const struct Piece BLACK_KING =  { KING, BLACK, "BLACK_KING"}; 
const struct Piece BLACK_QUEEN =  { QUEEN, BLACK, "BLACK_QUEEN"}; 
const struct Piece BLACK_BISHOP =  { BISHOP, BLACK, "BLACK_BISHOP"};
const struct Piece EMPTY = { NONE, BLANK, "EMPTY" }; 
const struct Piece WHITE_PAWN =  { PAWN, WHITE, "WHITE_PAWN" };
const struct Piece WHITE_KNIGHT =  { KNIGHT, WHITE, "WHITE_KNIGHT" };
const struct Piece WHITE_ROOK =  { ROOK, WHITE, "WHITE_ROOK"};
const struct Piece WHITE_KING =  { KING, WHITE, "WHITE_KING"}; 
const struct Piece WHITE_QUEEN =  { QUEEN, WHITE, "WHITE_QUEEN" }; 
const struct Piece WHITE_BISHOP =  { BISHOP, WHITE, "WHITE_BISHOP" };

GameBoard movePiece(GameBoard gameBoard, struct Piece piece, Position currentPosition, Position requestedPosition); 
GameBoard createGameBoard(GameBoard gameBoard); 

int canMove(GameBoard gameBoard, Position requestedPosition, struct Piece piece); 
void printGameBoard(GameBoard gameBoard); 
