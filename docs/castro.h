/**
 * MIT License
 * 
 * Copyright (c) 2025 Konstantinos Despoinidis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ============================================================================
 *
⠀*⠀⠀⠀⠀⢠⣤⣤⡀⠀⠀⢀⣤⣤⣤⣤⡀⠀⠀⢀⣤⣤⡄⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⢸⣿⣿⣿⣿⡇⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⢸⣿⣿⣧⣤⣤⣼⣿⣿⣿⣿⣧⣤⣤⣼⣿⣿⡇⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⠀⠀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⠀⠀⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀
⠀*⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉
 *
 * Castro is a chess move generation library written in C
 *
 * -Contents-
 * 1.  SQUARE
 * 2.  BITBOARD
 * 3.  HASHING
 * 4.  HISTORY
 * 5.  BOARD
 * 6.  ZOBRIST
 * 7.  MASKS
 * 8.  MOVE
 * 9.  PIECE
 * 10. NOTATION
 * 11. RESULT
 * 12. MOVEGEN
 * 13. PERFT
 * 14. POLYGLOT
 *
 * Written by Konstantinos Despoinidis <despoinidisk@gmail.com> (KDesp73)
 */

#ifndef CASTRO_H
#define CASTRO_H

// Includes
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CASTRO_VERSION_MAJOR 0
#define CASTRO_VERSION_MINOR 3
#define CASTRO_VERSION_PATCH 0

#define CASTRO_VERSION_STRING "0.3.0"

#define CASTRO_VERSION_HEX ((CASTRO_VERSION_MAJOR * 10000) + (CASTRO_VERSION_MINOR * 100) + CASTRO_VERSION_PATCH)

/**
 * @brief Fills in the provided pointers with the current version numbers.
 * 
 * @param major Pointer to an int to store the major version
 * @param minor Pointer to an int to store the minor version
 * @param patch Pointer to an int to store the patch version
 */
static inline void castro_version(int* major, int* minor, int* patch)
{
    if (major) *major = CASTRO_VERSION_MAJOR;
    if (minor) *minor = CASTRO_VERSION_MINOR;
    if (patch) *patch = CASTRO_VERSION_PATCH;
}


/*------------------------------------.
| *SQUARE*                            |
| ----------------------------------- |
| Bitboard representation of squares. |
| Square is an 8-bit integer ranging  |
| from 0-63.                          |
|                                     |
| We start counting from a8 and       |
| finish with h1                      |
`------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/// Represents a square on the chessboard (0-63).
typedef uint8_t Square;

/**
 * @brief Prints a square's name and index to stdout.
 * 
 * Example output: `e4 = E4 28`
 */
#define SQUARE_PRINT(square)\
    do {\
        char __square_name__[3];\
        castro_SquareToName(__square_name__, square);\
        printf("%s = %s %d\n", #square, __square_name__, square);\
    } while(0)

/**
 * @brief Macro to convert a square index to (row, col) coordinates.
 * 
 * Use as: `board[COORDS(s)] = ...;` → expands to `board[(s)/8][(s)%8]`
 */
#define COORDS(square) (square) / 8][(square) % 8

/**
 * @brief Converts a square index (0-63) to algebraic notation (e.g. "e4").
 * 
 * @param[out] buffer A 3-character buffer (e.g., `char name[3]`) to store the result.
 * @param[in] square Square index from 0 to 63.
 */
void castro_SquareToName(char buffer[3], Square square);

/**
 * @brief Converts algebraic notation (e.g. "e4") to a square index (0-63).
 * 
 * @param[in] buffer A null-terminated string containing the square name.
 * @return Square index corresponding to the name, or SQUARE_NONE if invalid.
 */
Square castro_NameToSquare(const char buffer[3]);

/**
 * @brief Returns the rank (0–7) of a square index.
 */
int castro_Rank(Square square);

/**
 * @brief Returns the file (0–7) of a square index.
 */
int castro_File(Square square);

/**
 * @brief Checks whether a square index is valid (0–63).
 */
bool castro_IsSquareValid(Square square);

/**
 * @brief Converts (rank, file) coordinates to a square index.
 * 
 * @param y Rank (0 = rank 1, 7 = rank 8)
 * @param x File (0 = file A, 7 = file H)
 * @return Square index.
 */
Square castro_SquareFromCoords(size_t y, size_t x);

/**
 * @brief Converts a square name (e.g. "d2") to an index.
 * 
 * @param name A 2-character string like "e4".
 * @return Square index or SQUARE_NONE.
 */
Square castro_SquareFromName(const char* name);

/**
 * @brief Flips a square vertically (used for mirror board logic).
 * 
 * E.g., SR(E2) returns the square index of E7.
 */
#define SR(s) (7 - ((s) / 8)) * 8 + ((s) % 8)

/// Square indices (0–63), rank by rank from A1 to H8

// Rank 1
#define A1  0
#define B1  1
#define C1  2
#define D1  3
#define E1  4
#define F1  5
#define G1  6
#define H1  7

// Rank 2
#define A2  8
#define B2  9
#define C2 10
#define D2 11
#define E2 12
#define F2 13
#define G2 14
#define H2 15

// Rank 3
#define A3 16
#define B3 17
#define C3 18
#define D3 19
#define E3 20
#define F3 21
#define G3 22
#define H3 23

// Rank 4
#define A4 24
#define B4 25
#define C4 26
#define D4 27
#define E4 28
#define F4 29
#define G4 30
#define H4 31

// Rank 5
#define A5 32
#define B5 33
#define C5 34
#define D5 35
#define E5 36
#define F5 37
#define G5 38
#define H5 39

// Rank 6
#define A6 40
#define B6 41
#define C6 42
#define D6 43
#define E6 44
#define F6 45
#define G6 46
#define H6 47

// Rank 7
#define A7 48
#define B7 49
#define C7 50
#define D7 51
#define E7 52
#define F7 53
#define G7 54
#define H7 55

// Rank 8
#define A8 56
#define B8 57
#define C8 58
#define D8 59
#define E8 60
#define F8 61
#define G8 62
#define H8 63

/// Special marker for an invalid or uninitialized square
#define SQUARE_NONE 64


/*------------------------------------.
| *BITBOARD*                          |
|-------------------------------------|
| Low-level bitboard manipulation     |
`------------------------------------*/

/// A 64-bit bitboard where each bit represents a square.
typedef uint64_t Bitboard;

/**
 * @brief Cardinal and diagonal directions for sliding piece movement or bitboard shifting.
 */
typedef enum {
    NORTH       = 8,   ///< One rank up
    SOUTH       = -8,  ///< One rank down
    EAST        = 1,   ///< One file right
    WEST        = -1,  ///< One file left
    NORTH_EAST  = 9,   ///< Diagonal up-right
    NORTH_WEST  = 7,   ///< Diagonal up-left
    SOUTH_EAST  = -7,  ///< Diagonal down-right
    SOUTH_WEST  = -9   ///< Diagonal down-left
} Direction;

/**
 * @brief Converts a square index to a bitboard with a single set bit.
 * 
 * Returns 0ULL if the square is SQUARE_NONE (64).
 */
#define BB(square) (((square) == 64) ? 0ULL : 1ULL << (square))

/**
 * @brief Returns the index of the least significant bit set (LSB).
 * 
 * @param b Input bitboard.
 * @return Square index (0–63) of the lowest bit set.
 */
Square lsb(Bitboard b);

/**
 * @brief Returns the index of the most significant bit set (MSB).
 * 
 * @param b Input bitboard.
 * @return Square index (0–63) of the highest bit set.
 */
Square msb(Bitboard b);

/**
 * @brief Shifts a bitboard in a specified direction.
 * 
 * @param b Input bitboard.
 * @param D Direction to shift in.
 * @return Resulting shifted bitboard.
 */
Bitboard shift(Bitboard b, Direction D);

/**
 * @brief Pops and returns the index of the least significant bit set.
 * 
 * The bit is cleared from the input bitboard.
 * 
 * @param b Pointer to bitboard.
 * @return Square index that was popped.
 */
Square poplsb(Bitboard* b);

/**
 * @brief Counts the number of bits set in the bitboard.
 * 
 * @param bb Input bitboard.
 * @return Number of set bits.
 */
int popcount(Bitboard bb);

/**
 * @brief Sets the bit corresponding to the square in the bitboard.
 */
void on(Bitboard* bitboard, Square square);

/**
 * @brief Clears the bit corresponding to the square in the bitboard.
 */
void off(Bitboard* bitboard, Square square);


/*-----------------------------------------.
| *PSEUDO LEGAL ATTACK MAP GENERATION*     |
`-----------------------------------------*/

/**
 * @brief Computes pseudo-legal pawn attacks.
 * 
 * @param pawn Square of pawn.
 * @param enemySquares Bitboard of enemy pieces.
 * @param color 0 = white, 1 = black.
 */
Bitboard castro_PawnAttacks(Square pawn, Bitboard enemySquares, uint8_t color);

/**
 * @brief Computes pseudo-legal pawn forward pushes.
 * 
 * @param pawn Square of pawn.
 * @param emptySquares Bitboard of empty squares.
 * @param color 0 = white, 1 = black.
 */
Bitboard castro_PawnPushes(Square pawn, Bitboard emptySquares, uint8_t color);

/**
 * @brief Computes pawn promotions (non-capturing).
 * 
 * @param pawns Bitboard of pawns eligible to promote.
 * @param emptySquares Bitboard of empty target squares.
 * @param color 0 = white, 1 = black.
 */
Bitboard castro_PawnPromotions(Square pawns, Bitboard emptySquares, uint8_t color);

/**
 * @brief Computes pawn promotion captures.
 * 
 * @param pawns Bitboard of pawns eligible to promote by capture.
 * @param opponentPieces Bitboard of capturable opponent pieces.
 * @param color 0 = white, 1 = black.
 */
Bitboard castro_PawnPromotionCaptures(Square pawns, Bitboard opponentPieces, uint8_t color);

/**
 * @brief Computes knight attacks from a given square.
 */
Bitboard castro_KnightAttacks(Square knights, Bitboard emptySquares, Bitboard enemySquares);

/**
 * @brief Computes king attacks from a given square.
 */
Bitboard castro_KingAttacks(Square king, Bitboard emptySquares, Bitboard enemySquares);

Bitboard castro_BishopAttacksFromOccupancy(Square square, Bitboard occupancy);
Bitboard castro_RookAttacksFromOccupancy(Square square, Bitboard occupancy);

/**
 * @brief Computes bishop attacks using a sliding attack method.
 */
Bitboard castro_BishopAttacks(Square bishops, Bitboard emptySquares, Bitboard enemySquares);

/**
 * @brief Computes rook attacks using a sliding attack method.
 */
Bitboard castro_RookAttacks(Square rooks, Bitboard emptySquares, Bitboard enemySquares);

void castro_InitMagic(void);
Bitboard castro_BishopAttacksMagic(Square square, Bitboard occupancy);
Bitboard castro_RookAttacksMagic(Square square, Bitboard occupancy);

/**
 * @brief Computes queen attacks as the union of rook and bishop attacks.
 */
Bitboard castro_QueenAttacks(Square queens, Bitboard emptySquares, Bitboard enemySquares);


/*------------------------.
| *KING SAFETY / CHECKS*  |
`------------------------*/

/**
 * @brief Checks whether the king is in check.
 * 
 * @param kingPosition Bitboard with one bit set where the king is.
 * @param enemyAttacks Bitboard of all enemy attacks.
 */
bool castro_IsKingInCheck(Bitboard kingPosition, Bitboard enemyAttacks);

/**
 * @brief Returns the bitboard of pinned pieces relative to the king.
 * 
 * @param kingPosition Bitboard with king’s square.
 * @param slidingAttacks Bitboard of enemy rooks/bishops/queens.
 * @param occupancy Bitboard of all occupied squares.
 */
Bitboard _PinnedPieces(Bitboard kingPosition, Bitboard slidingAttacks, Bitboard occupancy);


/*-------------.
| *PRINTING*   |
`-------------*/

/**
 * @brief Prints a 32-bit unsigned integer (e.g. in binary or hex).
 */
void castro_Uint32Print(uint32_t value);

/**
 * @brief Prints a 64-bit unsigned integer (e.g. in binary or hex).
 */
void castro_Uint64Print(uint64_t value);

/**
 * @brief Prints a visual representation of a bitboard.
 * 
 * Useful for debugging. Marks set bits on an 8x8 grid.
 */
void castro_BitboardPrint(Bitboard bitboard);


/*------------------------------------.
| *HASHING*                           |
|-------------------------------------|
| Position repetition tracking        |
`------------------------------------*/

/**
 * @brief Represents a single hash entry (position and repetition count).
 */
typedef struct {
    uint64_t hash;  ///< Zobrist hash of the position
    int count;      ///< Number of times this position has occurred
} HashEntry;

/** Capacity of the repetition hash table (power of two for fast modulo). */
#define HASH_TABLE_CAPACITY 4096

/**
 * @brief Tracks position repetition using Zobrist hashes.
 * Uses open addressing (linear probing). Empty buckets have hash == 0.
 */
typedef struct {
    uint64_t last_added;   ///< Last added hash (used when decrementing on unmake)
    HashEntry* entries;    ///< Buckets: index = hash & (capacity - 1), probe on collision
    size_t capacity;       ///< Number of buckets (power of two)
} HashTable;

/**
 * @brief Initializes a hash table from a FEN string.
 * 
 * Parses the FEN, computes the initial Zobrist hash, and sets up the table.
 * 
 * @param table Pointer to an uninitialized HashTable
 * @param starting_fen FEN string of the initial position
 */
void castro_InitHashTable(HashTable* table, const char* starting_fen);

/**
 * @brief Initializes a hash table directly from a known Zobrist hash.
 * 
 * @param table Pointer to HashTable
 * @param starting_hash Precomputed Zobrist hash of the position
 */
void castro_InitHashTableHash(HashTable* table, uint64_t starting_hash);

/**
 * @brief Adds a new position hash or updates an existing entry.
 * 
 * If the hash already exists, increments the count.
 * 
 * @param table Pointer to HashTable
 * @param hash New Zobrist hash to insert
 * @return true if repetition >= 3 (e.g., threefold repetition), false otherwise
 */
_Bool castro_UpdateHashTable(HashTable* table, uint64_t hash);

/**
 * @brief Decrements the repetition count for a position (used on unmake).
 * Call with the hash that was last added before the move being undone.
 */
void castro_HashTableDecrement(HashTable* table, uint64_t hash);

/**
 * @brief Frees all memory used by the hash table.
 */
void castro_FreeHashTable(HashTable* table);


/*------------------------------------.
| *HISTORY*                           |
|-------------------------------------|
| Move history and undo management    |
`------------------------------------*/

/// Maximum number of moves stored in history
#define MAX_MOVES (2 * 1024)

/**
 * @brief Stores the necessary data to undo a move.
 */
typedef struct {
    uint32_t move;       ///< Encoded move representation
    uint8_t castling;    ///< Castling rights before the move
    Square enpassant;    ///< En passant square before the move
    size_t fiftyMove;    ///< Fifty-move rule counter before the move
    char captured;       ///< Captured piece type (if any), 0 if none
} Undo;

/// Null undo object representing no previous move
#define NULL_UNDO (Undo){.move = NULL_MOVE}

/**
 * @brief Prints the contents of an Undo struct (for debugging).
 */
void castro_UndoPrint(Undo undo);

/**
 * @brief Stores full game history for repetition detection and undo functionality.
 */
typedef struct {
    HashTable positions;       ///< Hash table tracking seen positions
    Undo moves[MAX_MOVES];     ///< Stack of undo records
    size_t count;              ///< Number of moves in history
} History;

/**
 * @brief Removes the last move from history (pop operation).
 * 
 * Updates position table and count.
 */
void castro_HistoryRemove(History* history);

/**
 * @brief Returns the most recent Undo record from history.
 * 
 * @param history History object
 * @return Undo struct of the last move; undefined if history is empty.
 */
Undo castro_HistoryGetLast(History history);


/*------------------------------------.
| *BOARD*                             |
|-------------------------------------|
| Game state and board representation |
`------------------------------------*/

/// Piece character definitions (FEN-compatible)
#define BLACK_ROOK   'r'
#define BLACK_KNIGHT 'n'
#define BLACK_BISHOP 'b'
#define BLACK_KING   'k'
#define BLACK_QUEEN  'q'
#define BLACK_PAWN   'p'

#define WHITE_ROOK   'R'
#define WHITE_KNIGHT 'N'
#define WHITE_BISHOP 'B'
#define WHITE_KING   'K'
#define WHITE_QUEEN  'Q'
#define WHITE_PAWN   'P'

/// Piece type used for indexing and logic
typedef enum {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
} PieceType;

/// Used to indicate no piece on a square
#define EMPTY_SQUARE ' '

/// Standard starting position in Forsyth-Edwards Notation (FEN)
#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define BOARD_SIZE   8
#define PIECE_TYPES  12

/*---------------------------.
| Hybrid Representation      |
| `grid` is used for fast    |
| piece lookup               |
`---------------------------*/

/**
 * @brief Core board structure combining bitboards and grid for performance and simplicity.
 */
typedef struct {
    Bitboard bitboards[PIECE_TYPES]; ///< One bitboard per piece type (white/black)
    char grid[8][8];                 ///< ASCII piece grid for quick access
    Bitboard white;                 ///< Cached: all white pieces
    Bitboard black;                 ///< Cached: all black pieces
    Bitboard empty;                 ///< Cached: empty squares (~(white|black))

    // Game state
    Square enpassant_square;        ///< En passant target square, if any
    bool turn;                      ///< true = white to move, false = black
    uint8_t castling_rights;        ///< Castling rights bitfield
    size_t halfmove;                ///< Halfmove clock for 50-move rule
    size_t fullmove;                ///< Fullmove number (starts at 1)

    History history;                ///< Move history
    uint64_t hash;                  ///< Zobrist hash of current position
} Board;

/**
 * @brief Records an undo step into the board's history.
 * 
 * @param board The board to update
 * @param move The move to be undone later
 * @return true on success
 */
bool castro_AddUndo(Board* board, uint32_t move);

/**
 * @brief Loads and removes the last undo record.
 * 
 * @param board The board to restore
 * @return Undo information for the last move
 */
Undo castro_LoadLastUndo(Board* board);

/// All 12 supported pieces, as characters
#define PIECES "pnbrqkPNBRQK"

/// Bitboard index constants for each piece type
enum {
    INDEX_BLACK_PAWN,
    INDEX_BLACK_KNIGHT,
    INDEX_BLACK_BISHOP,
    INDEX_BLACK_ROOK,
    INDEX_BLACK_QUEEN,
    INDEX_BLACK_KING,
    INDEX_WHITE_PAWN,
    INDEX_WHITE_KNIGHT,
    INDEX_WHITE_BISHOP,
    INDEX_WHITE_ROOK,
    INDEX_WHITE_QUEEN,
    INDEX_WHITE_KING,
};

// Aliases for working with types generically (e.g. loops)
#define INDEX_PAWN   INDEX_BLACK_PAWN
#define INDEX_KNIGHT INDEX_BLACK_KNIGHT
#define INDEX_BISHOP INDEX_BLACK_BISHOP
#define INDEX_ROOK   INDEX_BLACK_ROOK
#define INDEX_QUEEN  INDEX_BLACK_QUEEN
#define INDEX_KING   INDEX_BLACK_KING

/// Color of pieces
typedef enum {
    COLOR_NONE = -1,
    COLOR_BLACK = 0,
    COLOR_WHITE
} PieceColor;

/**
 * @brief Converts a promotion code to its corresponding character.
 * 
 * @param promotion Numeric code (0 = queen, 1 = rook, etc.)
 * @return Promotion piece character ('q', 'r', ...)
 */
char castro_PromotionToChar(uint8_t promotion);

/**
 * @brief Converts a promotion piece character to a numeric code.
 * 
 * @param promotion Piece character (e.g., 'q', 'n')
 * @return Numeric code
 */
uint8_t castro_CharToPromotion(char promotion);

/**
 * @brief Initializes a board from a FEN string.
 */
void castro_BoardInitFen(Board* board, const char* fen);

/**
 * @brief Heap-allocates and initializes a board from FEN.
 * 
 * Must be freed with BoardFree().
 */
Board* castro_BoardInitFenHeap(const char* fen);

/**
 * @brief Frees heap-allocated board (from BoardInitFenHeap).
 */
void castro_BoardFree(Board* board);

/** Recomputes and stores white, black, empty from bitboards. Call after any direct bitboard change. */
void castro_BoardUpdateOccupancy(Board* board);

/**
 * @brief Returns a bitboard of all white pieces.
 */
Bitboard castro_GetWhite(const Board* board);

/**
 * @brief Returns a bitboard of all black pieces.
 */
Bitboard castro_GetBlack(const Board* board);

/**
 * @brief Returns a bitboard of all opponent pieces.
 */
Bitboard castro_GetEnemyColor(const Board* board, PieceColor us);

/**
 * @brief Returns a bitboard of all enemy pieces (based on current turn).
 */
Bitboard castro_GetEnemy(const Board* board);

/**
 * @brief Returns a bitboard of all empty squares.
 */
Bitboard castro_GetEmpty(const Board* board);

/**
 * @brief Counts the number of a specific piece color/type on the board.
 */
int castro_CountPieces(const Board* board, PieceColor color, PieceType type);

/**
 * @brief Checks if a board has certain castling rights.
 */
int castro_HasCastlingRights(const Board* board, uint8_t castling_rights);

/**
 * @brief Revokes specific castling rights from a board.
 */
void castro_RevokeCastlingRights(Board* board, uint8_t castling_rights);

/**
 * @brief Checks if a square is attacked by a given color.
 */
bool castro_IsSquareAttacked(const Board* board, Square square, PieceColor color);

/**
 * @brief Checks if a square is empty.
 */
bool castro_IsSquareEmpty(const Board* board, Square square);

/**
 * @brief Checks if a square is occupied by a given color.
 */
bool castro_IsSquareOccupiedBy(const Board* board, Square square, PieceColor color);

/**
 * @brief Returns the number of pieces on the board for a given color.
 */
size_t castro_NumberOfPieces(const Board* board, PieceColor color);

/**
 * @brief Checks if a color is in check.
 */
bool castro_IsInCheckColor(const Board* board, PieceColor color);

/**
 * @brief Checks if the player to move is in check.
 */
bool castro_IsInCheck(const Board* board);

/**
 * @brief Prints a list of squares (e.g. legal moves) on the board.
 */
void castro_BoardPrintSquares(const Board* board, Square* squares, size_t count);

/**
 * @brief Highlights a bitboard on the board (used for debugging).
 */
void castro_BoardPrintBitboard(const Board* board, Bitboard highlight);

/**
 * @brief Prints the board with a list of highlighted squares.
 * 
 * Usage: `BoardPrint(board, E4, G5, A2, ...)`
 */
void castro_BoardPrint(const Board* board, Square first, ...);

/**
 * @brief Prints all bitboards in the board structure (for debugging).
 */
void castro_BoardPrintBitboards(Board board);

/**
 * @brief Prints the character grid of the board.
 */
void castro_BoardPrintGrid(const Board* board);

/**
 * @brief Returns a deep copy of the board.
 */
Board castro_BoardCopy(const Board* board);

/*------------------------------------.
| *ZOBRIST*                           |
|-------------------------------------|
| Zobrist hashing for board states    |
`------------------------------------*/

/// Total number of castling rights encoded (K, Q, k, q)
#define CASTLING_OPTIONS 4

/**
 * @brief Zobrist random numbers for each piece on each square.
 * 
 * Dimensions:
 * - PIECE_TYPES: 12 (black/white * 6 types)
 * - BOARD_SIZE: 8x8 squares
 * 
 * Indexed as [piece][rank][file]
 */
extern uint64_t zobrist_table[PIECE_TYPES][BOARD_SIZE][BOARD_SIZE] __attribute__((unused));

/// Zobrist keys for each of the 4 castling rights (K, Q, k, q)
extern uint64_t zobrist_castling[CASTLING_OPTIONS] __attribute__((unused));

/// Zobrist keys for each en passant file (a-h)
extern uint64_t zobrist_en_passant[BOARD_SIZE] __attribute__((unused));

/// Zobrist key to represent "black to move"
extern uint64_t zobrist_black_to_move __attribute__((unused));

/**
 * @brief Initializes the Zobrist tables.
 */
void castro_InitZobrist();

/**
 * @brief Calculates the Zobrist hash of a board.
 * 
 * This includes:
 * - Pieces on the board
 * - Side to move
 * - Castling rights
 * - En passant square
 * 
 * @param board Pointer to the Board structure
 * @return 64-bit Zobrist hash
 */
uint64_t castro_CalculateZobristHash(const Board* board);

/**
 * @brief Convenience function to calculate a Zobrist hash directly from a FEN string.
 * 
 * @param fen Forsyth-Edwards Notation string
 * @return 64-bit Zobrist hash
 */
uint64_t castro_CalculateZobristHashFen(const char* fen);

/**
 * @brief Translates piece as a character to expected zobrist index
 */
int castro_ZobristPieceToIndex(char piece);

/*------------------------------------.
| *MASKS*                             |
| ----------------------------------- |
|                                     |
`------------------------------------*/

typedef uint64_t Bitboard;

#define FILE_A  0x0101010101010101ULL  // File A (a1, a2, ..., a8)
#define FILE_B  0x0202020202020202ULL  // File B (b1, b2, ..., b8)
#define FILE_C  0x0404040404040404ULL  // File C (c1, c2, ..., c8)
#define FILE_D  0x0808080808080808ULL  // File D (d1, d2, ..., d8)
#define FILE_E  0x1010101010101010ULL  // File E (e1, e2, ..., e8)
#define FILE_F  0x2020202020202020ULL  // File F (f1, f2, ..., f8)
#define FILE_G  0x4040404040404040ULL  // File G (g1, g2, ..., g8)
#define FILE_H  0x8080808080808080ULL  // File H (h1, h2, ..., h8)

#define RANK_1  0x00000000000000FFULL  // Rank 1 (a1-h1)
#define RANK_2  0x000000000000FF00ULL  // Rank 2 (a2-h2)
#define RANK_3  0x0000000000FF0000ULL  // Rank 3 (a3-h3)
#define RANK_4  0x00000000FF000000ULL  // Rank 4 (a4-h4)
#define RANK_5  0x000000FF00000000ULL  // Rank 5 (a5-h5)
#define RANK_6  0x0000FF0000000000ULL  // Rank 6 (a6-h6)
#define RANK_7  0x00FF000000000000ULL  // Rank 7 (a7-h7)
#define RANK_8  0xFF00000000000000ULL  // Rank 8 (a8-h8)

#define WHITE_KINGSIDE_CASTLE_EMPTY  0x60ULL  // {f1, g1}
#define WHITE_QUEENSIDE_CASTLE_EMPTY 0xeULL   // {d1, c1, b1}
#define BLACK_KINGSIDE_CASTLE_EMPTY  0x6000000000000000ULL  // {f8, g8}
#define BLACK_QUEENSIDE_CASTLE_EMPTY 0xe00000000000000ULL   // {d8, c8, b8}

#define WHITE_KINGSIDE_ATTACKS  0x70ULL // {e1, f1, g1}
#define WHITE_QUEENSIDE_ATTACKS 0x1cULL // {e1, d1, c1}
#define BLACK_KINGSIDE_ATTACKS  0x7000000000000000ULL // {e8, f8, g8}
#define BLACK_QUEENSIDE_ATTACKS 0x1c00000000000000ULL // {e8, d8, c8}

#define BB_ANY_MATCH(bb1, bb2) ((bb1) & (bb2))
#define BB_NO_MATCH(bb1, bb2) !(BB_ANY_MATCH(bb1, bb2))
#define BB_ALL_MATCH(bb1, bb2) (((bb1) & (bb2)) == (bb1))

static Bitboard DIAGONAL_MASKS[64]      __attribute__((unused));
static Bitboard ANTI_DIAGONAL_MASKS[64] __attribute__((unused));
static Bitboard HORIZONTAL_MASKS[64]    __attribute__((unused));
static Bitboard VERTICAL_MASKS[64]      __attribute__((unused));

static Bitboard PAWN_PUSH_MASKS[2][64]             __attribute__((unused));
static Bitboard PAWN_DOUBLE_PUSH_MASKS[2][64]      __attribute__((unused));
static Bitboard PAWN_ATTACK_MASKS[2][64]           __attribute__((unused));
static Bitboard PAWN_PROMOTION_MASKS[2][64]        __attribute__((unused));
static Bitboard PAWN_PROMOTION_ATTACK_MASKS[2][64] __attribute__((unused));

static Bitboard KNIGHT_MOVE_MASKS[64] __attribute__((unused));
static Bitboard BISHOP_MOVE_MASKS[64] __attribute__((unused));
static Bitboard ROOK_MOVE_MASKS[64]   __attribute__((unused));
static Bitboard QUEEN_MOVE_MASKS[64]  __attribute__((unused));
static Bitboard KING_MOVE_MASKS[64]   __attribute__((unused));

typedef enum {
    DIAGONAL,
    VERTICAL,
    HORIZONTAL
} RayType;

void castro_InitMasks();

Bitboard castro_GeneralOccupancy(Bitboard whitePieces, Bitboard blackPieces);
Bitboard castro_BlockerMasks(Bitboard slidingPiece, Bitboard occupancy);

/*** Ray Masks ***/
Bitboard castro_ComputeDiagonalMask(Square square);
Bitboard castro_ComputeAntiDiagonalMask(Square square);
Bitboard castro_ComputeHorizontalMask(Square);
Bitboard castro_ComputeVerticalMask(Square);

Bitboard castro_DiagonalMask(Square square);
Bitboard castro_AntiDiagonalMask(Square square);
Bitboard castro_HorizontalMask(Square square);
Bitboard castro_VerticalMask(Square square);

/*** Piece Masks ***/
Bitboard castro_ComputePawnPushMask(Square square, PieceColor color);
Bitboard castro_ComputePawnDoublePushMask(Square square, PieceColor color);
Bitboard castro_ComputePawnPromotionMask(Square square, PieceColor color);
Bitboard castro_ComputePawnPromotionAttackMask(Square square, PieceColor color);
Bitboard castro_ComputePawnAttackMask(Square square, PieceColor color);
Bitboard castro_ComputeKnightMoveMask(Square square);
Bitboard castro_ComputeBishopMoveMask(Square square);
Bitboard castro_ComputeRookMoveMask(Square square);
Bitboard castro_ComputeQueenMoveMask(Square square);
Bitboard castro_ComputeKingMoveMask(Square square);

Bitboard castro_PawnPushMask(Square square, PieceColor color);
Bitboard castro_PawnDoublePushMask(Square square, PieceColor color);
Bitboard castro_PawnPromotionMask(Square square, PieceColor color);
Bitboard castro_PawnPromotionAttackMask(Square square, PieceColor color);
Bitboard castro_PawnAttackMask(Square square, PieceColor color);
Bitboard castro_KnightMoveMask(Square square);
Bitboard castro_BishopMoveMask(Square square);
Bitboard castro_RookMoveMask(Square square);
Bitboard castro_QueenMoveMask(Square square);
Bitboard castro_KingMoveMask(Square square);

/*--------------------------------------.
| *MOVE*                                |
| ------------------------------------- |
| Moves are 32-bit integers             |
| where bits:                           |
| - 0-5 represent the source            |
| - 6-11 represent the destination      |
| - 12-15 represent the promotion piece |
| - 16-21 represent the flags           |
`--------------------------------------*/

// TODO: Make Move 16bits if an application is not found for the flags

/**
 * @brief Flags representing special move types.
 */
typedef enum {
    FLAG_NORMAL = 0,              ///< Regular move
    FLAG_CASTLING,                ///< Castling move
    FLAG_ENPASSANT,               ///< En passant capture
    FLAG_PAWN_DOUBLE_MOVE,        ///< Initial two-square pawn push
    FLAG_PROMOTION,               ///< Promotion without capture
    FLAG_PROMOTION_WITH_CAPTURE   ///< Promotion with capture
} Flag;

/**
 * @brief Types of piece promotions.
 */
typedef enum {
    PROMOTION_NONE = 0,           ///< No promotion
    PROMOTION_KNIGHT,
    PROMOTION_BISHOP,
    PROMOTION_ROOK,
    PROMOTION_QUEEN
} Promotion;

/**
 * @brief Bit flags representing castling rights.
 */
enum {
    CASTLE_WHITE_KINGSIDE  = 0b0001,
    CASTLE_WHITE_QUEENSIDE = 0b0010,
    CASTLE_BLACK_KINGSIDE  = 0b0100,
    CASTLE_BLACK_QUEENSIDE = 0b1000
};

/**
 * @brief Used to store minimal board state when making a null move.
 */
typedef struct {
    PieceColor turn;
    int halfmoveClock;
    int fullmoveNumber;
    Square epSquare;
} NullMoveState;

/// Stores the state of the board before a null move is made
extern NullMoveState nullState;

/**
 * @brief Encoded move type (bitfield). Format:
 * - bits 0–5:   from square
 * - bits 6–11:  to square
 * - bits 12–14: promotion type
 * - bits 15–17: move flag
 */
typedef uint32_t Move;

/// Special constant representing no move
#define NULL_MOVE ((Move) 0)

/// Max number of moves in a move list
#define MOVES_CAPACITY 256

/**
 * @brief Represents a dynamic list of moves.
 */
typedef struct {
    Move list[MOVES_CAPACITY];
    size_t count;
} Moves;

/// Empty move list constant
#define NO_MOVES ((Moves){.count = 0})

/**
 * @brief Appends a move to a move list.
 */
void castro_MovesAppend(Moves* moves, Move move);

/**
 * @brief Appends one move list to another.
 */
void castro_MovesAppendList(Moves* dest, Moves src);

/**
 * @brief Combines two move lists into a new one.
 */
Moves castro_MovesCombine(Moves m1, Moves m2);

/**
 * @brief Creates an Undo struct representing a move played on a board.
 */
Undo castro_MakeUndo(const Board* board, Move move);

/*-----------------------------------------------.
| Piece-specific movement offsets (mailbox 0x88) |
`-----------------------------------------------*/

#define KNIGHT_OFFSETS_COUNT 8
static const int KNIGHT_OFFSETS[] = {
    -17, -15, -10, -6, 6, 10, 15, 17
};

#define BISHOP_OFFSETS_COUNT 4
static const int BISHOP_OFFSETS[] = {
    -9, -7, 7, 9
};

#define ROOK_OFFSETS_COUNT 4
static const int ROOK_OFFSETS[] = {
    -8, -1, 1, 8
};

#define KING_OFFSETS_COUNT 8
static const int KING_OFFSETS[] = {
    -9, -8, -7, -1, 1, 7, 8, 9
};

/**
 * @brief Decodes a move into its components (used inside a scope).
 */
#define MOVE_DECODE(move) \
    Square src, dst; \
    uint8_t promotion, flag; \
    castro_MoveDecode(move, &src, &dst, &promotion, &flag)

/*-----------------------------.
| Move encoding/decoding/util  |
`-----------------------------*/

/**
 * @brief Checks whether a move is legal and does not leave the king in check.
 */
_Bool castro_MoveIsValid(const Board* board, Move move, PieceColor color);

/**
 * @brief Returns true if the move captures a piece (or en passant).
 */
_Bool castro_MoveIsCapture(const Board* board, Move move);

/**
 * @brief Returns true if the move gives check. Temporarily modifies the board (make/unmake).
 */
_Bool castro_MoveGivesCheck(Board* board, Move move);

/**
 * @brief Piece value for MVV-LVA (pawn=1, knight/bishop=3, rook=5, queen=9, king=0).
 */
int castro_PieceValueFromType(char piece_type);

/**
 * @brief Reorders a legal move list for search: hash move first, then captures (MVV-LVA), killers, then checks (if score_checks), then quiet.
 * Pass NULL_MOVE for hash_move or killers if not used. Set score_checks to false to avoid MakeMove/Unmake per move.
 */
void castro_OrderLegalMoves(Board* board, Moves* moves, Move hash_move, Move killer0, Move killer1, bool score_checks);

/**
 * @brief Encodes a move from components into a 32-bit integer.
 */
Move castro_MoveEncode(Square from, Square to, uint8_t promotion, uint8_t flag);

/**
 * @brief Encodes a move from algebraic names ("e2", "e4", etc.).
 */
Move castro_MoveEncodeNames(const char* from, const char* to, uint8_t promotion, uint8_t flag);

/**
 * @brief Decodes a move into from-square, to-square, promotion, and flag.
 */
void castro_MoveDecode(Move move, Square* from, Square* to, uint8_t* promotion, uint8_t* flag);

/**
 * @brief Sets the move flag field.
 */
void castro_MoveSetFlag(Move* move, Flag flag);

/**
 * @brief Sets the promotion field in a move.
 */
void castro_MoveSetPromotion(Move* move, Promotion promotion);

/*-------------------------------.
| Bitboard Move Application API  |
`-------------------------------*/

/**
 * @brief Applies a move on a bitboard.
 */
Bitboard castro_DoMove(Bitboard* current, Move move);

/**
 * @brief Undoes a move on a bitboard.
 */
Bitboard castro_UndoMove(Bitboard* current, Move move);

/*-----------------------------.
| Full board move application  |
`-----------------------------*/

/**
 * @brief Makes a move and updates board state accordingly.
 */
bool castro_MakeMove(Board* board, Move move);

/**
 * @brief Unmakes the last move and restores previous board state.
 */
void castro_UnmakeMove(Board* board);

/**
 * @brief Performs a null move (used in search algorithms).
 */
void castro_MakeNullMove(Board* board);

/**
 * @brief Reverts a null move.
 */
void castro_UnmakeNullMove(Board* board);

/*-------------------------------.
| Move-type specific helpers     |
`-------------------------------*/

/**
 * @brief Executes castling move.
 */
bool castro_Castle(Board* board, Move move);

/**
 * @brief Checks if a move is a castling move.
 */
bool castro_IsCastle(const Board* board, Move* move);

/**
 * @brief Executes en passant capture.
 */
bool castro_Enpassant(Board* board, Move move);

/**
 * @brief Checks if a move is an en passant capture.
 */
bool castro_IsEnpassant(const Board* board, Move* move);

/**
 * @brief Checks if a move is a two-square pawn advance.
 */
bool castro_IsDoublePawnPush(Board* board, Move move);

/**
 * @brief Checks if a move is a promotion.
 */
bool castro_IsPromotion(Board* board, Move* move);

/**
 * @brief Checks if a move is a capture (regular or en passant).
 */
bool castro_IsCapture(const Board* board, Move move);

/**
 * @brief Checks if executing a move leaves the king in check.
 */
bool castro_IsInCheckAfterMove(Board *board, Move move);

/**
 * @brief Makes a move with full legality rules.
 */
_Bool castro_MoveMake(Board* board, Move move);

/**
 * @brief Applies a move directly (ignores turn/check legality).
 */
void castro_MoveFreely(Board* board, Move move, PieceColor color);

/**
 * @brief Prints a move to stdout in algebraic format.
 */
void castro_MovePrint(Move move);

/**
 * @brief Converts an algebraic string (e.g., "e2e4") to a move.
 */
Move castro_StringToMove(const char* str);

/**
 * @brief Converts a move to a string in algebraic format (e.g., "e2e4").
 */
void castro_MoveToString(Move move, char* buffer);

/*--------------------.
| Move comparisons    |
`--------------------*/

/**
 * @brief Compares two moves for equality (ignores metadata).
 */
bool castro_MoveCmp(Move m1, Move m2);

/**
 * @brief Compares two moves strictly (includes metadata).
 */
bool castro_MoveCmpStrict(Move m1, Move m2);

/*--------------------.
| Move field getters  |
`--------------------*/

/**
 * @brief Gets the source square of a move.
 */
Square castro_GetFrom(Move move);

/**
 * @brief Gets the destination square of a move.
 */
Square castro_GetTo(Move move);

/**
 * @brief Gets the promotion type of a move.
 */
uint8_t castro_GetPromotion(Move move);

/**
 * @brief Gets the move flag.
 */
uint8_t castro_GetFlag(Move move);

/*----------------------------.
| Board state update helpers  |
`----------------------------*/

/**
 * @brief Updates the 50-move counter based on the move.
 */
void castro_UpdateHalfmove(Board* board, Move move, size_t piece_count_before, size_t piece_count_after, char piece);

/**
 * @brief Updates castling rights after a move.
 */
uint8_t castro_UpdateCastlingRights(Board* board, Move move);

/**
 * @brief Updates en passant target square.
 */
Square castro_UpdateEnpassantSquare(Board* board, Move move);

/*-------------------------.
| Bitboard-Move conversion |
`-------------------------*/

/**
 * @brief Converts a bitboard of destinations to move list from a source square.
 */
Moves castro_BitboardToMoves(Bitboard bitboard, Square from);

/**
 * @brief Converts a move list to a bitboard of destinations.
 */
Bitboard castro_MovesToBitboard(Moves moves);

/*-------------------------.
| Board Debugging Helpers  |
`-------------------------*/

/**
 * @brief Prints a move on a board (highlighted view).
 */
void castro_BoardPrintMove(const Board* board, Move move);

/// Debug macro alias for MovePrint
#define MOVE_PRINT(move) MovePrint(move)


/*------------------------------------.
| *PIECE*                             |
|-------------------------------------|
| Piece abstraction and utilities     |
`------------------------------------*/

/**
 * @brief Represents a chess piece.
 * 
 * Each piece is defined by a type (character) and a color.
 * - Uppercase letters: white pieces (e.g., 'P', 'N')
 * - Lowercase letters: black pieces (e.g., 'p', 'n')
 */
typedef struct {
    char type;         ///< Character representing the piece ('P', 'n', etc.)
    PieceColor color;  ///< COLOR_WHITE or COLOR_BLACK
} Piece;

/**
 * @brief Prints the contents of a Piece struct (for debugging).
 */
#define PIECE_PRINT(piece)\
    printf("%s = {.type=%c, .color=%d}\n", #piece, piece.type, piece.color)

/*------------------------------.
| Piece type identification     |
`------------------------------*/

/**
 * @brief Checks if a piece is a pawn.
 */
#define IS_PAWN(piece) \
    (tolower(piece.type) == 'p')

/**
 * @brief Checks if a piece is a knight.
 */
#define IS_KNIGHT(piece) \
    (tolower(piece.type) == 'n')

/**
 * @brief Checks if a piece is a bishop.
 */
#define IS_BISHOP(piece) \
    (tolower(piece.type) == 'b')

/**
 * @brief Checks if a piece is a rook.
 */
#define IS_ROOK(piece) \
    (tolower(piece.type) == 'r')

/**
 * @brief Checks if a piece is a queen.
 */
#define IS_QUEEN(piece) \
    (tolower(piece.type) == 'q')

/**
 * @brief Checks if a piece is a king.
 */
#define IS_KING(piece) \
    (tolower(piece.type) == 'k')

/**
 * @brief Checks if a piece has a given color.
 */
#define IS_COLOR(piece, c) \
    (piece.color == c)

/**
 * @brief Checks if a piece is white.
 */
#define IS_WHITE(piece) \
    IS_COLOR(piece, COLOR_WHITE)

/**
 * @brief Checks if a piece is black.
 */
#define IS_BLACK(piece) \
    IS_COLOR(piece, COLOR_BLACK)

/*------------------------------.
| Piece utility functions       |
`------------------------------*/

/**
 * @brief Gets the color of a piece given its character representation.
 * 
 * @param piece The character representing a piece
 * @return COLOR_WHITE, COLOR_BLACK, or COLOR_NONE
 */
int castro_GetPieceColor(char piece);

/**
 * @brief Returns the Piece located at a specific square on the board.
 * 
 * @param board Pointer to the board
 * @param square Square index (0–63)
 * @return Piece struct representing the piece at that square
 */
Piece castro_PieceAt(const Board* board, Square square);

/**
 * @brief Compares two Piece structs for type and color equality.
 * 
 * @param p1 First piece
 * @param p2 Second piece
 * @return true if both pieces are the same type and color
 */
bool castro_PieceCmp(Piece p1, Piece p2);

/*------------------------------------.
| *NOTATION*                          |
|-------------------------------------|
| Handles FEN/PGN I/O and SAN parsing |
`------------------------------------*/

/*-------------.
| FEN Support  |
`-------------*/

/**
 * @brief Imports a FEN string into a board.
 * 
 * Sets up position, castling rights, side to move, en passant, etc.
 * 
 * @param board Pointer to the board to initialize
 * @param fen FEN string
 */
void castro_FenImport(Board* board, const char* fen);

/**
 * @brief Exports the current board state to a FEN string.
 * 
 * @param board Board to serialize
 * @param fen Output buffer (must be large enough)
 */
void castro_FenExport(const Board* board, char fen[]);

/**
 * @brief Maximum length for PGN header fields (Event, Site, etc.)
 */
#define MAX_HEADER_LENGTH 256

/*-----------------.
| SAN and PGN I/O  |
`-----------------*/

/**
 * @brief Represents a move in Standard Algebraic Notation (e.g., "e4", "Nf3").
 */
typedef struct {
    char move[16];
} SanMove;

/**
 * @brief PGN/notation-based game format.
 * 
 * Stores metadata and the list of SAN moves.
 */
typedef struct {
    char event[MAX_HEADER_LENGTH];   ///< Event name
    char site[MAX_HEADER_LENGTH];    ///< Site/location
    char date[MAX_HEADER_LENGTH];    ///< Date of game
    char white[MAX_HEADER_LENGTH];   ///< White player name
    char black[MAX_HEADER_LENGTH];   ///< Black player name
    char result[MAX_HEADER_LENGTH];  ///< Result string (e.g., "1-0")
    char fen[MAX_HEADER_LENGTH];     ///< Initial FEN position (optional)
    SanMove moves[MAX_MOVES];        ///< List of SAN moves
    size_t move_count;               ///< Number of moves made
} Game;

/**
 * @brief Parses a SAN move and applies it to the board and game state.
 * 
 * @param board Current board
 * @param game Game context
 * @param move_str SAN move string (e.g., "e4", "O-O")
 * @return true on success
 */
bool castro_move_name(const Board* board, Game* game, const char* move_str);

/**
 * @brief Shorthand for move_name(board, game, move)
 */
#define MOVE(board, game, move) \
        move_name(board, game, move)

/*------------------------.
| Game metadata handling  |
`------------------------*/

/**
 * @brief Initializes a Game object with basic metadata and FEN.
 */
void castro_GameInit(Game* game, 
    const char* event,
    const char* site,
    const char* white,
    const char* black,
    const char* fen
);

/**
 * @brief Runs a game move-by-move, showing each updated board (for debugging/visualization).
 */
void castro_GameRun(Game game);

/**
 * @brief Prints the full PGN representation of a game.
 */
void castro_GamePrint(Game game);

/**
 * @brief Appends a SAN move to the game.
 */
void castro_GameAddMove(Game* game, SanMove move);

/**
 * @brief Setters for PGN metadata fields.
 */
void castro_GameSetEvent(Game* game, const char* event);
void castro_GameSetSite(Game* game, const char* site);
void castro_GameSetDate(Game* game, const char* date);
void castro_GameSetWhite(Game* game, const char* white);
void castro_GameSetBlack(Game* game, const char* black);
void castro_GameSetFen(Game* game, const char* fen);
void castro_GameSetResult(Game* game, const char* result);

/*--------------------------.
| PGN Import/Export Support |
`--------------------------*/

/**
 * @brief Parses a PGN string and populates the game object.
 */
void castro_PgnImport(Game* game, const char* pgn);

/**
 * @brief Serializes a Game to PGN format.
 */
void castro_PgnExport(Game* game, char* pgn);

/**
 * @brief Saves a PGN game to a file.
 */
void castro_PgnExportFile(Game* game, const char* path);

/*-----------------------------.
| SAN <-> Move conversions     |
`-----------------------------*/

/**
 * @brief Converts a Move to a SAN notation string (e.g., "Nf3", "O-O").
 */
void castro_Notate(Board* board, Move move, SanMove* san);

/**
 * @brief Converts a SAN move to an internal Move.
 */
Move castro_SanToMove(Board* board, SanMove san);


/*------------------------------------.
| *RESULT*                            |
|-------------------------------------|
| Game termination and result logic   |
`------------------------------------*/

/**
 * @brief Enumeration of possible game outcomes.
 */
typedef enum {
    RESULT_NONE = 0,                               ///< Game is still ongoing
    RESULT_WHITE_WON,                              ///< White won by checkmate or resignation
    RESULT_BLACK_WON,                              ///< Black won by checkmate or resignation
    RESULT_STALEMATE,                              ///< Game ended in stalemate
    RESULT_DRAW_BY_REPETITION,                     ///< Game drawn by threefold repetition
    RESULT_DRAW_DUE_TO_INSUFFICIENT_MATERIAL,      ///< Draw due to insufficient mating material
    RESULT_DRAW_DUE_TO_50_MOVE_RULE,               ///< Draw due to 50-move rule (no pawn move or capture)
    RESULT_COUNT                                    ///< Internal count for range checking
} Result;

/**
 * @brief String representations of results for PGN output.
 * 
 * Matches the Result enum index:
 * - "*" for ongoing
 * - "1-0", "0-1" for wins
 * - "1/2-1/2" for all draws
 */
static const char result_score[][8] = {
    "*",
    "1-0",
    "0-1",
    "1/2-1/2",
    "1/2-1/2",
    "1/2-1/2",
    "1/2-1/2"
};

/**
 * @brief Human-readable messages describing the result.
 * 
 * Matches the Result enum index.
 */
static const char result_message[][256] = {
    "No result yet",
    "White won",
    "Black won",
    "Stalemate",
    "Draw by repetition",
    "Draw due to insufficient material",
    "Draw due to 50 move rule"
};

/*-----------------------------.
| Result Detection Functions   |
`-----------------------------*/

/**
 * @brief Determines the current result of the game.
 * 
 * Checks for checkmate, stalemate, 3-fold repetition, 50-move rule, or insufficient material.
 * 
 * @param board Current board state
 * @return Corresponding Result enum
 */
Result castro_IsResult(Board* board);

/**
 * @brief Determines if the current position is checkmate.
 * 
 * @param board Pointer to the board
 * @return true if checkmate
 */
bool castro_IsCheckmate(const Board* board);

/**
 * @brief Determines if the current position is stalemate.
 * 
 * @param board Pointer to the board
 * @return true if stalemate
 */
bool castro_IsStalemate(const Board* board);

/**
 * @brief Checks if neither player has sufficient material to checkmate.
 * 
 * Includes cases like:
 * - King vs King
 * - King and Bishop vs King
 * - King and Knight vs King
 * 
 * @param board Pointer to the board
 * @return true if the game should be drawn due to insufficient material
 */
bool castro_IsInsufficientMaterial(const Board* board);

/**
 * @brief Determines if the current position has occurred three times (3-fold repetition).
 * 
 * Uses the board's `History` and `HashTable` to detect repeated positions.
 * 
 * @param board Pointer to the board
 * @return true if position repeated three times
 */
bool castro_IsThreefoldRepetition(Board* board);

/*------------------------------------.
| *MOVEGEN*                           |
|-------------------------------------|
| Move generation for legal and       |
| pseudo-legal moves in the engine    |
`------------------------------------*/

/**
 * @brief Enumeration of move types to control legality enforcement.
 */
typedef enum {
    MOVE_LEGAL,   ///< Fully legal moves that leave the king safe
    MOVE_PSEUDO,  ///< Pseudo-legal moves, ignoring king safety
    MOVE_CAPTURE,
    MOVE_ATTACK,
} MoveType;

/*-----------------------------.
| Pseudo-Legal Move Generation |
`-----------------------------*/

/**
 * @brief Generates all pseudo-legal moves for the current position.
 * 
 * Includes moves that may leave the king in check.
 */
Moves castro_GeneratePseudoLegalMoves(const Board* board);

/**
 * @brief Generates a bitboard representing all pseudo-legal moves.
 */
Bitboard castro_GeneratePseudoLegalMovesBitboard(const Board* board);

/**
 * @brief Pseudo-legal push moves for pawns.
 */
Bitboard castro_GeneratePseudoLegalPawnMoves(Bitboard pawns, Bitboard enemy, PieceColor color);

/**
 * @brief Pseudo-legal pawn attacks.
 * 
 * If `strict` is true, diagonal movement is restricted to squares with capturable enemies.
 */
Bitboard castro_GeneratePseudoLegalPawnAttacks(Bitboard pawns, Bitboard enemy, PieceColor color, bool strict);

/**
 * @brief Pseudo-legal attacks for specific pieces.
 */
Bitboard castro_GeneratePseudoLegalKnightAttacks(Bitboard knights, Bitboard empty, Bitboard enemy);
Bitboard castro_GeneratePseudoLegalBishopAttacks(Bitboard bishops, Bitboard empty, Bitboard enemy);
Bitboard castro_GeneratePseudoLegalRookAttacks(Bitboard rooks, Bitboard empty, Bitboard enemy);
Bitboard castro_GeneratePseudoLegalQueenAttacks(Bitboard queens, Bitboard empty, Bitboard enemy);
Bitboard castro_GeneratePseudoLegalKingAttacks(Bitboard kings, Bitboard empty, Bitboard enemy);

/**
 * @brief Generates all pseudo-legal attacks for a given color.
 */
Bitboard castro_GeneratePseudoLegalAttacks(const Board* board, PieceColor color);

/**
 * @brief Generates potential moves for a single piece square.
 */
Bitboard castro_GeneratePawnMoves(const Board* board, Square piece, PieceColor color);
Bitboard castro_GenerateKnightMoves(const Board* board, Square piece, PieceColor color);
Bitboard castro_GenerateBishopMoves(const Board* board, Square piece, PieceColor color);
Bitboard castro_GenerateRookMoves(const Board* board, Square piece, PieceColor color);
Bitboard castro_GenerateQueenMoves(const Board* board, Square piece, PieceColor color);
Bitboard castro_GenerateKingMoves(const Board* board, Square piece, PieceColor color);

/*------------------------.
| Legal Move Generation   |
`------------------------*/

typedef struct {
    Bitboard check_mask;      // Squares that stop a check
    Bitboard pin_masks[64];   // Allowed movement mask for every square
    int check_count;
} LegalityContext;

LegalityContext castro_CalculateLegality(const Board* board);

/**
 * @brief Returns whether a move is fully legal (doesn't leave the king in check).
 */
bool castro_IsLegal(const Board* board, Move move);

/**
 * @brief Generates all legal moves for the current board position.
 */
Moves castro_GenerateLegalMoves(const Board* board);

/**
 * @brief Generates only legal captures (and en passant). Use for quiescence search.
 */
Moves castro_GenerateLegalCaptures(const Board* board);

/**
 * @brief Generates legal moves that originate from a specific square.
 */
Moves castro_GenerateLegalMovesSquare(const Board* board, Square square);

/**
 * @brief Returns a bitboard of all legal destination squares.
 */
Bitboard castro_GenerateLegalMovesBitboard(const Board* board);

/**
 * @brief Generates legal moves for piece sets by type.
 * If captures_only is true, only moves that capture a piece (or en passant) are added.
 */
void castro_GenerateLegalPawnMoves(const Board* board, Bitboard pieces, PieceColor color, const LegalityContext* ctx, Moves* moves, bool captures_only);
void castro_GenerateLegalKnightMoves(const Board* board, Bitboard pieces, PieceColor color, const LegalityContext* ctx, Moves* moves, bool captures_only);
void castro_GenerateLegalBishopMoves(const Board* board, Bitboard pieces, PieceColor color, const LegalityContext* ctx, Moves* moves, bool captures_only);
void castro_GenerateLegalRookMoves(const Board* board, Bitboard pieces, PieceColor color, const LegalityContext* ctx, Moves* moves, bool captures_only);
void castro_GenerateLegalQueenMoves(const Board* board, Bitboard pieces, PieceColor color, const LegalityContext* ctx, Moves* moves, bool captures_only);
void castro_GenerateLegalKingMoves(const Board* board, Bitboard pieces, PieceColor color, const LegalityContext* ctx, Moves* moves, bool captures_only);

/*---------------------------------------------.
| Convenience inline dispatcher for move types |
`---------------------------------------------*/

/**
 * @brief Dispatches to legal or pseudo-legal move generation.
 * 
 * @param board The board to generate moves from
 * @param type MoveType
 * @return Moves struct containing the resulting moves
 */
Moves castro_GenerateMoves(const Board* board, MoveType type);

/*------------------------------------.
| *PERFT*                             |
| ----------------------------------- |
|                                     |
`------------------------------------*/

typedef unsigned long long u64;

// NOTE: See https://www.chessprogramming.org/Perft
u64 castro_Perft(Board* board, int depth, bool root);

/** Pseudo-legal perft: same node count as legal perft, faster (no pin/check pre-filter). */
u64 castro_PerftPseudoLegal(Board* board, int depth);



/*------------------------------------.
| *POLYGLOT*                          |
| ----------------------------------- |
|                                     |
`------------------------------------*/

typedef struct {
    uint64_t zobrist_hash;
    uint16_t move;
    uint16_t weight;
    uint32_t learn;
} PolyglotEntry;

// NOTE: See http://hgm.nubati.net/book_format.html
#ifdef _MSC_VER
#  define U64(u) (u##ui64)
#else
#  define U64(u) (u##ULL)
#endif
static const uint64_t Random64[781] = {
   U64(0x9D39247E33776D41), U64(0x2AF7398005AAA5C7), U64(0x44DB015024623547), U64(0x9C15F73E62A76AE2),
   U64(0x75834465489C0C89), U64(0x3290AC3A203001BF), U64(0x0FBBAD1F61042279), U64(0xE83A908FF2FB60CA),
   U64(0x0D7E765D58755C10), U64(0x1A083822CEAFE02D), U64(0x9605D5F0E25EC3B0), U64(0xD021FF5CD13A2ED5),
   U64(0x40BDF15D4A672E32), U64(0x011355146FD56395), U64(0x5DB4832046F3D9E5), U64(0x239F8B2D7FF719CC),
   U64(0x05D1A1AE85B49AA1), U64(0x679F848F6E8FC971), U64(0x7449BBFF801FED0B), U64(0x7D11CDB1C3B7ADF0),
   U64(0x82C7709E781EB7CC), U64(0xF3218F1C9510786C), U64(0x331478F3AF51BBE6), U64(0x4BB38DE5E7219443),
   U64(0xAA649C6EBCFD50FC), U64(0x8DBD98A352AFD40B), U64(0x87D2074B81D79217), U64(0x19F3C751D3E92AE1),
   U64(0xB4AB30F062B19ABF), U64(0x7B0500AC42047AC4), U64(0xC9452CA81A09D85D), U64(0x24AA6C514DA27500),
   U64(0x4C9F34427501B447), U64(0x14A68FD73C910841), U64(0xA71B9B83461CBD93), U64(0x03488B95B0F1850F),
   U64(0x637B2B34FF93C040), U64(0x09D1BC9A3DD90A94), U64(0x3575668334A1DD3B), U64(0x735E2B97A4C45A23),
   U64(0x18727070F1BD400B), U64(0x1FCBACD259BF02E7), U64(0xD310A7C2CE9B6555), U64(0xBF983FE0FE5D8244),
   U64(0x9F74D14F7454A824), U64(0x51EBDC4AB9BA3035), U64(0x5C82C505DB9AB0FA), U64(0xFCF7FE8A3430B241),
   U64(0x3253A729B9BA3DDE), U64(0x8C74C368081B3075), U64(0xB9BC6C87167C33E7), U64(0x7EF48F2B83024E20),
   U64(0x11D505D4C351BD7F), U64(0x6568FCA92C76A243), U64(0x4DE0B0F40F32A7B8), U64(0x96D693460CC37E5D),
   U64(0x42E240CB63689F2F), U64(0x6D2BDCDAE2919661), U64(0x42880B0236E4D951), U64(0x5F0F4A5898171BB6),
   U64(0x39F890F579F92F88), U64(0x93C5B5F47356388B), U64(0x63DC359D8D231B78), U64(0xEC16CA8AEA98AD76),
   U64(0x5355F900C2A82DC7), U64(0x07FB9F855A997142), U64(0x5093417AA8A7ED5E), U64(0x7BCBC38DA25A7F3C),
   U64(0x19FC8A768CF4B6D4), U64(0x637A7780DECFC0D9), U64(0x8249A47AEE0E41F7), U64(0x79AD695501E7D1E8),
   U64(0x14ACBAF4777D5776), U64(0xF145B6BECCDEA195), U64(0xDABF2AC8201752FC), U64(0x24C3C94DF9C8D3F6),
   U64(0xBB6E2924F03912EA), U64(0x0CE26C0B95C980D9), U64(0xA49CD132BFBF7CC4), U64(0xE99D662AF4243939),
   U64(0x27E6AD7891165C3F), U64(0x8535F040B9744FF1), U64(0x54B3F4FA5F40D873), U64(0x72B12C32127FED2B),
   U64(0xEE954D3C7B411F47), U64(0x9A85AC909A24EAA1), U64(0x70AC4CD9F04F21F5), U64(0xF9B89D3E99A075C2),
   U64(0x87B3E2B2B5C907B1), U64(0xA366E5B8C54F48B8), U64(0xAE4A9346CC3F7CF2), U64(0x1920C04D47267BBD),
   U64(0x87BF02C6B49E2AE9), U64(0x092237AC237F3859), U64(0xFF07F64EF8ED14D0), U64(0x8DE8DCA9F03CC54E),
   U64(0x9C1633264DB49C89), U64(0xB3F22C3D0B0B38ED), U64(0x390E5FB44D01144B), U64(0x5BFEA5B4712768E9),
   U64(0x1E1032911FA78984), U64(0x9A74ACB964E78CB3), U64(0x4F80F7A035DAFB04), U64(0x6304D09A0B3738C4),
   U64(0x2171E64683023A08), U64(0x5B9B63EB9CEFF80C), U64(0x506AACF489889342), U64(0x1881AFC9A3A701D6),
   U64(0x6503080440750644), U64(0xDFD395339CDBF4A7), U64(0xEF927DBCF00C20F2), U64(0x7B32F7D1E03680EC),
   U64(0xB9FD7620E7316243), U64(0x05A7E8A57DB91B77), U64(0xB5889C6E15630A75), U64(0x4A750A09CE9573F7),
   U64(0xCF464CEC899A2F8A), U64(0xF538639CE705B824), U64(0x3C79A0FF5580EF7F), U64(0xEDE6C87F8477609D),
   U64(0x799E81F05BC93F31), U64(0x86536B8CF3428A8C), U64(0x97D7374C60087B73), U64(0xA246637CFF328532),
   U64(0x043FCAE60CC0EBA0), U64(0x920E449535DD359E), U64(0x70EB093B15B290CC), U64(0x73A1921916591CBD),
   U64(0x56436C9FE1A1AA8D), U64(0xEFAC4B70633B8F81), U64(0xBB215798D45DF7AF), U64(0x45F20042F24F1768),
   U64(0x930F80F4E8EB7462), U64(0xFF6712FFCFD75EA1), U64(0xAE623FD67468AA70), U64(0xDD2C5BC84BC8D8FC),
   U64(0x7EED120D54CF2DD9), U64(0x22FE545401165F1C), U64(0xC91800E98FB99929), U64(0x808BD68E6AC10365),
   U64(0xDEC468145B7605F6), U64(0x1BEDE3A3AEF53302), U64(0x43539603D6C55602), U64(0xAA969B5C691CCB7A),
   U64(0xA87832D392EFEE56), U64(0x65942C7B3C7E11AE), U64(0xDED2D633CAD004F6), U64(0x21F08570F420E565),
   U64(0xB415938D7DA94E3C), U64(0x91B859E59ECB6350), U64(0x10CFF333E0ED804A), U64(0x28AED140BE0BB7DD),
   U64(0xC5CC1D89724FA456), U64(0x5648F680F11A2741), U64(0x2D255069F0B7DAB3), U64(0x9BC5A38EF729ABD4),
   U64(0xEF2F054308F6A2BC), U64(0xAF2042F5CC5C2858), U64(0x480412BAB7F5BE2A), U64(0xAEF3AF4A563DFE43),
   U64(0x19AFE59AE451497F), U64(0x52593803DFF1E840), U64(0xF4F076E65F2CE6F0), U64(0x11379625747D5AF3),
   U64(0xBCE5D2248682C115), U64(0x9DA4243DE836994F), U64(0x066F70B33FE09017), U64(0x4DC4DE189B671A1C),
   U64(0x51039AB7712457C3), U64(0xC07A3F80C31FB4B4), U64(0xB46EE9C5E64A6E7C), U64(0xB3819A42ABE61C87),
   U64(0x21A007933A522A20), U64(0x2DF16F761598AA4F), U64(0x763C4A1371B368FD), U64(0xF793C46702E086A0),
   U64(0xD7288E012AEB8D31), U64(0xDE336A2A4BC1C44B), U64(0x0BF692B38D079F23), U64(0x2C604A7A177326B3),
   U64(0x4850E73E03EB6064), U64(0xCFC447F1E53C8E1B), U64(0xB05CA3F564268D99), U64(0x9AE182C8BC9474E8),
   U64(0xA4FC4BD4FC5558CA), U64(0xE755178D58FC4E76), U64(0x69B97DB1A4C03DFE), U64(0xF9B5B7C4ACC67C96),
   U64(0xFC6A82D64B8655FB), U64(0x9C684CB6C4D24417), U64(0x8EC97D2917456ED0), U64(0x6703DF9D2924E97E),
   U64(0xC547F57E42A7444E), U64(0x78E37644E7CAD29E), U64(0xFE9A44E9362F05FA), U64(0x08BD35CC38336615),
   U64(0x9315E5EB3A129ACE), U64(0x94061B871E04DF75), U64(0xDF1D9F9D784BA010), U64(0x3BBA57B68871B59D),
   U64(0xD2B7ADEEDED1F73F), U64(0xF7A255D83BC373F8), U64(0xD7F4F2448C0CEB81), U64(0xD95BE88CD210FFA7),
   U64(0x336F52F8FF4728E7), U64(0xA74049DAC312AC71), U64(0xA2F61BB6E437FDB5), U64(0x4F2A5CB07F6A35B3),
   U64(0x87D380BDA5BF7859), U64(0x16B9F7E06C453A21), U64(0x7BA2484C8A0FD54E), U64(0xF3A678CAD9A2E38C),
   U64(0x39B0BF7DDE437BA2), U64(0xFCAF55C1BF8A4424), U64(0x18FCF680573FA594), U64(0x4C0563B89F495AC3),
   U64(0x40E087931A00930D), U64(0x8CFFA9412EB642C1), U64(0x68CA39053261169F), U64(0x7A1EE967D27579E2),
   U64(0x9D1D60E5076F5B6F), U64(0x3810E399B6F65BA2), U64(0x32095B6D4AB5F9B1), U64(0x35CAB62109DD038A),
   U64(0xA90B24499FCFAFB1), U64(0x77A225A07CC2C6BD), U64(0x513E5E634C70E331), U64(0x4361C0CA3F692F12),
   U64(0xD941ACA44B20A45B), U64(0x528F7C8602C5807B), U64(0x52AB92BEB9613989), U64(0x9D1DFA2EFC557F73),
   U64(0x722FF175F572C348), U64(0x1D1260A51107FE97), U64(0x7A249A57EC0C9BA2), U64(0x04208FE9E8F7F2D6),
   U64(0x5A110C6058B920A0), U64(0x0CD9A497658A5698), U64(0x56FD23C8F9715A4C), U64(0x284C847B9D887AAE),
   U64(0x04FEABFBBDB619CB), U64(0x742E1E651C60BA83), U64(0x9A9632E65904AD3C), U64(0x881B82A13B51B9E2),
   U64(0x506E6744CD974924), U64(0xB0183DB56FFC6A79), U64(0x0ED9B915C66ED37E), U64(0x5E11E86D5873D484),
   U64(0xF678647E3519AC6E), U64(0x1B85D488D0F20CC5), U64(0xDAB9FE6525D89021), U64(0x0D151D86ADB73615),
   U64(0xA865A54EDCC0F019), U64(0x93C42566AEF98FFB), U64(0x99E7AFEABE000731), U64(0x48CBFF086DDF285A),
   U64(0x7F9B6AF1EBF78BAF), U64(0x58627E1A149BBA21), U64(0x2CD16E2ABD791E33), U64(0xD363EFF5F0977996),
   U64(0x0CE2A38C344A6EED), U64(0x1A804AADB9CFA741), U64(0x907F30421D78C5DE), U64(0x501F65EDB3034D07),
   U64(0x37624AE5A48FA6E9), U64(0x957BAF61700CFF4E), U64(0x3A6C27934E31188A), U64(0xD49503536ABCA345),
   U64(0x088E049589C432E0), U64(0xF943AEE7FEBF21B8), U64(0x6C3B8E3E336139D3), U64(0x364F6FFA464EE52E),
   U64(0xD60F6DCEDC314222), U64(0x56963B0DCA418FC0), U64(0x16F50EDF91E513AF), U64(0xEF1955914B609F93),
   U64(0x565601C0364E3228), U64(0xECB53939887E8175), U64(0xBAC7A9A18531294B), U64(0xB344C470397BBA52),
   U64(0x65D34954DAF3CEBD), U64(0xB4B81B3FA97511E2), U64(0xB422061193D6F6A7), U64(0x071582401C38434D),
   U64(0x7A13F18BBEDC4FF5), U64(0xBC4097B116C524D2), U64(0x59B97885E2F2EA28), U64(0x99170A5DC3115544),
   U64(0x6F423357E7C6A9F9), U64(0x325928EE6E6F8794), U64(0xD0E4366228B03343), U64(0x565C31F7DE89EA27),
   U64(0x30F5611484119414), U64(0xD873DB391292ED4F), U64(0x7BD94E1D8E17DEBC), U64(0xC7D9F16864A76E94),
   U64(0x947AE053EE56E63C), U64(0xC8C93882F9475F5F), U64(0x3A9BF55BA91F81CA), U64(0xD9A11FBB3D9808E4),
   U64(0x0FD22063EDC29FCA), U64(0xB3F256D8ACA0B0B9), U64(0xB03031A8B4516E84), U64(0x35DD37D5871448AF),
   U64(0xE9F6082B05542E4E), U64(0xEBFAFA33D7254B59), U64(0x9255ABB50D532280), U64(0xB9AB4CE57F2D34F3),
   U64(0x693501D628297551), U64(0xC62C58F97DD949BF), U64(0xCD454F8F19C5126A), U64(0xBBE83F4ECC2BDECB),
   U64(0xDC842B7E2819E230), U64(0xBA89142E007503B8), U64(0xA3BC941D0A5061CB), U64(0xE9F6760E32CD8021),
   U64(0x09C7E552BC76492F), U64(0x852F54934DA55CC9), U64(0x8107FCCF064FCF56), U64(0x098954D51FFF6580),
   U64(0x23B70EDB1955C4BF), U64(0xC330DE426430F69D), U64(0x4715ED43E8A45C0A), U64(0xA8D7E4DAB780A08D),
   U64(0x0572B974F03CE0BB), U64(0xB57D2E985E1419C7), U64(0xE8D9ECBE2CF3D73F), U64(0x2FE4B17170E59750),
   U64(0x11317BA87905E790), U64(0x7FBF21EC8A1F45EC), U64(0x1725CABFCB045B00), U64(0x964E915CD5E2B207),
   U64(0x3E2B8BCBF016D66D), U64(0xBE7444E39328A0AC), U64(0xF85B2B4FBCDE44B7), U64(0x49353FEA39BA63B1),
   U64(0x1DD01AAFCD53486A), U64(0x1FCA8A92FD719F85), U64(0xFC7C95D827357AFA), U64(0x18A6A990C8B35EBD),
   U64(0xCCCB7005C6B9C28D), U64(0x3BDBB92C43B17F26), U64(0xAA70B5B4F89695A2), U64(0xE94C39A54A98307F),
   U64(0xB7A0B174CFF6F36E), U64(0xD4DBA84729AF48AD), U64(0x2E18BC1AD9704A68), U64(0x2DE0966DAF2F8B1C),
   U64(0xB9C11D5B1E43A07E), U64(0x64972D68DEE33360), U64(0x94628D38D0C20584), U64(0xDBC0D2B6AB90A559),
   U64(0xD2733C4335C6A72F), U64(0x7E75D99D94A70F4D), U64(0x6CED1983376FA72B), U64(0x97FCAACBF030BC24),
   U64(0x7B77497B32503B12), U64(0x8547EDDFB81CCB94), U64(0x79999CDFF70902CB), U64(0xCFFE1939438E9B24),
   U64(0x829626E3892D95D7), U64(0x92FAE24291F2B3F1), U64(0x63E22C147B9C3403), U64(0xC678B6D860284A1C),
   U64(0x5873888850659AE7), U64(0x0981DCD296A8736D), U64(0x9F65789A6509A440), U64(0x9FF38FED72E9052F),
   U64(0xE479EE5B9930578C), U64(0xE7F28ECD2D49EECD), U64(0x56C074A581EA17FE), U64(0x5544F7D774B14AEF),
   U64(0x7B3F0195FC6F290F), U64(0x12153635B2C0CF57), U64(0x7F5126DBBA5E0CA7), U64(0x7A76956C3EAFB413),
   U64(0x3D5774A11D31AB39), U64(0x8A1B083821F40CB4), U64(0x7B4A38E32537DF62), U64(0x950113646D1D6E03),
   U64(0x4DA8979A0041E8A9), U64(0x3BC36E078F7515D7), U64(0x5D0A12F27AD310D1), U64(0x7F9D1A2E1EBE1327),
   U64(0xDA3A361B1C5157B1), U64(0xDCDD7D20903D0C25), U64(0x36833336D068F707), U64(0xCE68341F79893389),
   U64(0xAB9090168DD05F34), U64(0x43954B3252DC25E5), U64(0xB438C2B67F98E5E9), U64(0x10DCD78E3851A492),
   U64(0xDBC27AB5447822BF), U64(0x9B3CDB65F82CA382), U64(0xB67B7896167B4C84), U64(0xBFCED1B0048EAC50),
   U64(0xA9119B60369FFEBD), U64(0x1FFF7AC80904BF45), U64(0xAC12FB171817EEE7), U64(0xAF08DA9177DDA93D),
   U64(0x1B0CAB936E65C744), U64(0xB559EB1D04E5E932), U64(0xC37B45B3F8D6F2BA), U64(0xC3A9DC228CAAC9E9),
   U64(0xF3B8B6675A6507FF), U64(0x9FC477DE4ED681DA), U64(0x67378D8ECCEF96CB), U64(0x6DD856D94D259236),
   U64(0xA319CE15B0B4DB31), U64(0x073973751F12DD5E), U64(0x8A8E849EB32781A5), U64(0xE1925C71285279F5),
   U64(0x74C04BF1790C0EFE), U64(0x4DDA48153C94938A), U64(0x9D266D6A1CC0542C), U64(0x7440FB816508C4FE),
   U64(0x13328503DF48229F), U64(0xD6BF7BAEE43CAC40), U64(0x4838D65F6EF6748F), U64(0x1E152328F3318DEA),
   U64(0x8F8419A348F296BF), U64(0x72C8834A5957B511), U64(0xD7A023A73260B45C), U64(0x94EBC8ABCFB56DAE),
   U64(0x9FC10D0F989993E0), U64(0xDE68A2355B93CAE6), U64(0xA44CFE79AE538BBE), U64(0x9D1D84FCCE371425),
   U64(0x51D2B1AB2DDFB636), U64(0x2FD7E4B9E72CD38C), U64(0x65CA5B96B7552210), U64(0xDD69A0D8AB3B546D),
   U64(0x604D51B25FBF70E2), U64(0x73AA8A564FB7AC9E), U64(0x1A8C1E992B941148), U64(0xAAC40A2703D9BEA0),
   U64(0x764DBEAE7FA4F3A6), U64(0x1E99B96E70A9BE8B), U64(0x2C5E9DEB57EF4743), U64(0x3A938FEE32D29981),
   U64(0x26E6DB8FFDF5ADFE), U64(0x469356C504EC9F9D), U64(0xC8763C5B08D1908C), U64(0x3F6C6AF859D80055),
   U64(0x7F7CC39420A3A545), U64(0x9BFB227EBDF4C5CE), U64(0x89039D79D6FC5C5C), U64(0x8FE88B57305E2AB6),
   U64(0xA09E8C8C35AB96DE), U64(0xFA7E393983325753), U64(0xD6B6D0ECC617C699), U64(0xDFEA21EA9E7557E3),
   U64(0xB67C1FA481680AF8), U64(0xCA1E3785A9E724E5), U64(0x1CFC8BED0D681639), U64(0xD18D8549D140CAEA),
   U64(0x4ED0FE7E9DC91335), U64(0xE4DBF0634473F5D2), U64(0x1761F93A44D5AEFE), U64(0x53898E4C3910DA55),
   U64(0x734DE8181F6EC39A), U64(0x2680B122BAA28D97), U64(0x298AF231C85BAFAB), U64(0x7983EED3740847D5),
   U64(0x66C1A2A1A60CD889), U64(0x9E17E49642A3E4C1), U64(0xEDB454E7BADC0805), U64(0x50B704CAB602C329),
   U64(0x4CC317FB9CDDD023), U64(0x66B4835D9EAFEA22), U64(0x219B97E26FFC81BD), U64(0x261E4E4C0A333A9D),
   U64(0x1FE2CCA76517DB90), U64(0xD7504DFA8816EDBB), U64(0xB9571FA04DC089C8), U64(0x1DDC0325259B27DE),
   U64(0xCF3F4688801EB9AA), U64(0xF4F5D05C10CAB243), U64(0x38B6525C21A42B0E), U64(0x36F60E2BA4FA6800),
   U64(0xEB3593803173E0CE), U64(0x9C4CD6257C5A3603), U64(0xAF0C317D32ADAA8A), U64(0x258E5A80C7204C4B),
   U64(0x8B889D624D44885D), U64(0xF4D14597E660F855), U64(0xD4347F66EC8941C3), U64(0xE699ED85B0DFB40D),
   U64(0x2472F6207C2D0484), U64(0xC2A1E7B5B459AEB5), U64(0xAB4F6451CC1D45EC), U64(0x63767572AE3D6174),
   U64(0xA59E0BD101731A28), U64(0x116D0016CB948F09), U64(0x2CF9C8CA052F6E9F), U64(0x0B090A7560A968E3),
   U64(0xABEEDDB2DDE06FF1), U64(0x58EFC10B06A2068D), U64(0xC6E57A78FBD986E0), U64(0x2EAB8CA63CE802D7),
   U64(0x14A195640116F336), U64(0x7C0828DD624EC390), U64(0xD74BBE77E6116AC7), U64(0x804456AF10F5FB53),
   U64(0xEBE9EA2ADF4321C7), U64(0x03219A39EE587A30), U64(0x49787FEF17AF9924), U64(0xA1E9300CD8520548),
   U64(0x5B45E522E4B1B4EF), U64(0xB49C3B3995091A36), U64(0xD4490AD526F14431), U64(0x12A8F216AF9418C2),
   U64(0x001F837CC7350524), U64(0x1877B51E57A764D5), U64(0xA2853B80F17F58EE), U64(0x993E1DE72D36D310),
   U64(0xB3598080CE64A656), U64(0x252F59CF0D9F04BB), U64(0xD23C8E176D113600), U64(0x1BDA0492E7E4586E),
   U64(0x21E0BD5026C619BF), U64(0x3B097ADAF088F94E), U64(0x8D14DEDB30BE846E), U64(0xF95CFFA23AF5F6F4),
   U64(0x3871700761B3F743), U64(0xCA672B91E9E4FA16), U64(0x64C8E531BFF53B55), U64(0x241260ED4AD1E87D),
   U64(0x106C09B972D2E822), U64(0x7FBA195410E5CA30), U64(0x7884D9BC6CB569D8), U64(0x0647DFEDCD894A29),
   U64(0x63573FF03E224774), U64(0x4FC8E9560F91B123), U64(0x1DB956E450275779), U64(0xB8D91274B9E9D4FB),
   U64(0xA2EBEE47E2FBFCE1), U64(0xD9F1F30CCD97FB09), U64(0xEFED53D75FD64E6B), U64(0x2E6D02C36017F67F),
   U64(0xA9AA4D20DB084E9B), U64(0xB64BE8D8B25396C1), U64(0x70CB6AF7C2D5BCF0), U64(0x98F076A4F7A2322E),
   U64(0xBF84470805E69B5F), U64(0x94C3251F06F90CF3), U64(0x3E003E616A6591E9), U64(0xB925A6CD0421AFF3),
   U64(0x61BDD1307C66E300), U64(0xBF8D5108E27E0D48), U64(0x240AB57A8B888B20), U64(0xFC87614BAF287E07),
   U64(0xEF02CDD06FFDB432), U64(0xA1082C0466DF6C0A), U64(0x8215E577001332C8), U64(0xD39BB9C3A48DB6CF),
   U64(0x2738259634305C14), U64(0x61CF4F94C97DF93D), U64(0x1B6BACA2AE4E125B), U64(0x758F450C88572E0B),
   U64(0x959F587D507A8359), U64(0xB063E962E045F54D), U64(0x60E8ED72C0DFF5D1), U64(0x7B64978555326F9F),
   U64(0xFD080D236DA814BA), U64(0x8C90FD9B083F4558), U64(0x106F72FE81E2C590), U64(0x7976033A39F7D952),
   U64(0xA4EC0132764CA04B), U64(0x733EA705FAE4FA77), U64(0xB4D8F77BC3E56167), U64(0x9E21F4F903B33FD9),
   U64(0x9D765E419FB69F6D), U64(0xD30C088BA61EA5EF), U64(0x5D94337FBFAF7F5B), U64(0x1A4E4822EB4D7A59),
   U64(0x6FFE73E81B637FB3), U64(0xDDF957BC36D8B9CA), U64(0x64D0E29EEA8838B3), U64(0x08DD9BDFD96B9F63),
   U64(0x087E79E5A57D1D13), U64(0xE328E230E3E2B3FB), U64(0x1C2559E30F0946BE), U64(0x720BF5F26F4D2EAA),
   U64(0xB0774D261CC609DB), U64(0x443F64EC5A371195), U64(0x4112CF68649A260E), U64(0xD813F2FAB7F5C5CA),
   U64(0x660D3257380841EE), U64(0x59AC2C7873F910A3), U64(0xE846963877671A17), U64(0x93B633ABFA3469F8),
   U64(0xC0C0F5A60EF4CDCF), U64(0xCAF21ECD4377B28C), U64(0x57277707199B8175), U64(0x506C11B9D90E8B1D),
   U64(0xD83CC2687A19255F), U64(0x4A29C6465A314CD1), U64(0xED2DF21216235097), U64(0xB5635C95FF7296E2),
   U64(0x22AF003AB672E811), U64(0x52E762596BF68235), U64(0x9AEBA33AC6ECC6B0), U64(0x944F6DE09134DFB6),
   U64(0x6C47BEC883A7DE39), U64(0x6AD047C430A12104), U64(0xA5B1CFDBA0AB4067), U64(0x7C45D833AFF07862),
   U64(0x5092EF950A16DA0B), U64(0x9338E69C052B8E7B), U64(0x455A4B4CFE30E3F5), U64(0x6B02E63195AD0CF8),
   U64(0x6B17B224BAD6BF27), U64(0xD1E0CCD25BB9C169), U64(0xDE0C89A556B9AE70), U64(0x50065E535A213CF6),
   U64(0x9C1169FA2777B874), U64(0x78EDEFD694AF1EED), U64(0x6DC93D9526A50E68), U64(0xEE97F453F06791ED),
   U64(0x32AB0EDB696703D3), U64(0x3A6853C7E70757A7), U64(0x31865CED6120F37D), U64(0x67FEF95D92607890),
   U64(0x1F2B1D1F15F6DC9C), U64(0xB69E38A8965C6B65), U64(0xAA9119FF184CCCF4), U64(0xF43C732873F24C13),
   U64(0xFB4A3D794A9A80D2), U64(0x3550C2321FD6109C), U64(0x371F77E76BB8417E), U64(0x6BFA9AAE5EC05779),
   U64(0xCD04F3FF001A4778), U64(0xE3273522064480CA), U64(0x9F91508BFFCFC14A), U64(0x049A7F41061A9E60),
   U64(0xFCB6BE43A9F2FE9B), U64(0x08DE8A1C7797DA9B), U64(0x8F9887E6078735A1), U64(0xB5B4071DBFC73A66),
   U64(0x230E343DFBA08D33), U64(0x43ED7F5A0FAE657D), U64(0x3A88A0FBBCB05C63), U64(0x21874B8B4D2DBC4F),
   U64(0x1BDEA12E35F6A8C9), U64(0x53C065C6C8E63528), U64(0xE34A1D250E7A8D6B), U64(0xD6B04D3B7651DD7E),
   U64(0x5E90277E7CB39E2D), U64(0x2C046F22062DC67D), U64(0xB10BB459132D0A26), U64(0x3FA9DDFB67E2F199),
   U64(0x0E09B88E1914F7AF), U64(0x10E8B35AF3EEAB37), U64(0x9EEDECA8E272B933), U64(0xD4C718BC4AE8AE5F),
   U64(0x81536D601170FC20), U64(0x91B534F885818A06), U64(0xEC8177F83F900978), U64(0x190E714FADA5156E),
   U64(0xB592BF39B0364963), U64(0x89C350C893AE7DC1), U64(0xAC042E70F8B383F2), U64(0xB49B52E587A1EE60),
   U64(0xFB152FE3FF26DA89), U64(0x3E666E6F69AE2C15), U64(0x3B544EBE544C19F9), U64(0xE805A1E290CF2456),
   U64(0x24B33C9D7ED25117), U64(0xE74733427B72F0C1), U64(0x0A804D18B7097475), U64(0x57E3306D881EDB4F),
   U64(0x4AE7D6A36EB5DBCB), U64(0x2D8D5432157064C8), U64(0xD1E649DE1E7F268B), U64(0x8A328A1CEDFE552C),
   U64(0x07A3AEC79624C7DA), U64(0x84547DDC3E203C94), U64(0x990A98FD5071D263), U64(0x1A4FF12616EEFC89),
   U64(0xF6F7FD1431714200), U64(0x30C05B1BA332F41C), U64(0x8D2636B81555A786), U64(0x46C9FEB55D120902),
   U64(0xCCEC0A73B49C9921), U64(0x4E9D2827355FC492), U64(0x19EBB029435DCB0F), U64(0x4659D2B743848A2C),
   U64(0x963EF2C96B33BE31), U64(0x74F85198B05A2E7D), U64(0x5A0F544DD2B1FB18), U64(0x03727073C2E134B1),
   U64(0xC7F6AA2DE59AEA61), U64(0x352787BAA0D7C22F), U64(0x9853EAB63B5E0B35), U64(0xABBDCDD7ED5C0860),
   U64(0xCF05DAF5AC8D77B0), U64(0x49CAD48CEBF4A71E), U64(0x7A4C10EC2158C4A6), U64(0xD9E92AA246BF719E),
   U64(0x13AE978D09FE5557), U64(0x730499AF921549FF), U64(0x4E4B705B92903BA4), U64(0xFF577222C14F0A3A),
   U64(0x55B6344CF97AAFAE), U64(0xB862225B055B6960), U64(0xCAC09AFBDDD2CDB4), U64(0xDAF8E9829FE96B5F),
   U64(0xB5FDFC5D3132C498), U64(0x310CB380DB6F7503), U64(0xE87FBB46217A360E), U64(0x2102AE466EBB1148),
   U64(0xF8549E1A3AA5E00D), U64(0x07A69AFDCC42261A), U64(0xC4C118BFE78FEAAE), U64(0xF9F4892ED96BD438),
   U64(0x1AF3DBE25D8F45DA), U64(0xF5B4B0B0D2DEEEB4), U64(0x962ACEEFA82E1C84), U64(0x046E3ECAAF453CE9),
   U64(0xF05D129681949A4C), U64(0x964781CE734B3C84), U64(0x9C2ED44081CE5FBD), U64(0x522E23F3925E319E),
   U64(0x177E00F9FC32F791), U64(0x2BC60A63A6F3B3F2), U64(0x222BBFAE61725606), U64(0x486289DDCC3D6780),
   U64(0x7DC7785B8EFDFC80), U64(0x8AF38731C02BA980), U64(0x1FAB64EA29A2DDF7), U64(0xE4D9429322CD065A),
   U64(0x9DA058C67844F20C), U64(0x24C0E332B70019B0), U64(0x233003B5A6CFE6AD), U64(0xD586BD01C5C217F6),
   U64(0x5E5637885F29BC2B), U64(0x7EBA726D8C94094B), U64(0x0A56A5F0BFE39272), U64(0xD79476A84EE20D06),
   U64(0x9E4C1269BAA4BF37), U64(0x17EFEE45B0DEE640), U64(0x1D95B0A5FCF90BC6), U64(0x93CBE0B699C2585D),
   U64(0x65FA4F227A2B6D79), U64(0xD5F9E858292504D5), U64(0xC2B5A03F71471A6F), U64(0x59300222B4561E00),
   U64(0xCE2F8642CA0712DC), U64(0x7CA9723FBB2E8988), U64(0x2785338347F2BA08), U64(0xC61BB3A141E50E8C),
   U64(0x150F361DAB9DEC26), U64(0x9F6A419D382595F4), U64(0x64A53DC924FE7AC9), U64(0x142DE49FFF7A7C3D),
   U64(0x0C335248857FA9E7), U64(0x0A9C32D5EAE45305), U64(0xE6C42178C4BBB92E), U64(0x71F1CE2490D20B07),
   U64(0xF1BCC3D275AFE51A), U64(0xE728E8C83C334074), U64(0x96FBF83A12884624), U64(0x81A1549FD6573DA5),
   U64(0x5FA7867CAF35E149), U64(0x56986E2EF3ED091B), U64(0x917F1DD5F8886C61), U64(0xD20D8C88C8FFE65F),
   U64(0x31D71DCE64B2C310), U64(0xF165B587DF898190), U64(0xA57E6339DD2CF3A0), U64(0x1EF6E6DBB1961EC9),
   U64(0x70CC73D90BC26E24), U64(0xE21A6B35DF0C3AD7), U64(0x003A93D8B2806962), U64(0x1C99DED33CB890A1),
   U64(0xCF3145DE0ADD4289), U64(0xD0E4427A5514FB72), U64(0x77C621CC9FB3A483), U64(0x67A34DAC4356550B),
   U64(0xF8D626AAAF278509),
};


/*
 *  "move" is a bit field with the following meaning (bit 0 is the least significant bit)
 *
 *  bits                meaning
 *  ===================================
 *  0,1,2               to file
 *  3,4,5               to row
 *  6,7,8               from file
 *  9,10,11             from row
 *  12,13,14            promotion piece
 *
 *  "promotion piece" is encoded as follows
 *
 *  none       0
 *  knight     1
 *  bishop     2
 *  rook       3
 *  queen      4
 *
 *  If the move is "0" (a1a1) then it should simply be ignored. 
 *  It seems to me that in that case one might as well delete the entry from the book. 
 */


/**
 * @brief Converts polyglot's 16bit format to my 32bit one
 */
Move castro_ConvertMove(uint16_t polyglotMove);

/**
 * @brief Returns the next book move based on the current polyglot hash
 */
Move castro_LookupBookMove(uint64_t position_hash, const char* book_path);


#ifdef __cplusplus
}
#endif

#ifdef CASTRO_STRIP_PREFIX

#define SquareToName castro_SquareToName
#define NameToSquare castro_NameToSquare
#define Rank castro_Rank
#define File castro_File
#define IsSquareValid castro_IsSquareValid
#define SquareFromCoords castro_SquareFromCoords
#define SquareFromName castro_SquareFromName
#define PawnAttacks castro_PawnAttacks
#define PawnPushes castro_PawnPushes
#define PawnPromotions castro_PawnPromotions
#define PawnPromotionCaptures castro_PawnPromotionCaptures
#define KnightAttacks castro_KnightAttacks
#define KingAttacks castro_KingAttacks
#define BishopAttacks castro_BishopAttacks
#define RookAttacks castro_RookAttacks
#define QueenAttacks castro_QueenAttacks
#define IsKingInCheck castro_IsKingInCheck
#define Uint32Print castro_Uint32Print
#define Uint64Print castro_Uint64Print
#define BitboardPrint castro_BitboardPrint
#define InitHashTable castro_InitHashTable
#define InitHashTableHash castro_InitHashTableHash
#define UpdateHashTable castro_UpdateHashTable
#define HashTableDecrement castro_HashTableDecrement
#define FreeHashTable castro_FreeHashTable
#define UndoPrint castro_UndoPrint
#define HistoryRemove castro_HistoryRemove
#define HistoryGetLast castro_HistoryGetLast
#define AddUndo castro_AddUndo
#define LoadLastUndo castro_LoadLastUndo
#define PromotionToChar castro_PromotionToChar
#define CharToPromotion castro_CharToPromotion
#define BoardInitFen castro_BoardInitFen
#define BoardBoardInitFenHeap Boardcastro_BoardInitFenHeap
#define BoardFree castro_BoardFree
#define GetWhite castro_GetWhite
#define GetBlack castro_GetBlack
#define GetEnemyColor castro_GetEnemyColor
#define GetEnemy castro_GetEnemy
#define GetEmpty castro_GetEmpty
#define CountPieces castro_CountPieces
#define HasCastlingRights castro_HasCastlingRights
#define RevokeCastlingRights castro_RevokeCastlingRights
#define IsSquareAttacked castro_IsSquareAttacked
#define IsSquareEmpty castro_IsSquareEmpty
#define IsSquareOccupiedBy castro_IsSquareOccupiedBy
#define NumberOfPieces castro_NumberOfPieces
#define IsInCheckColor castro_IsInCheckColor
#define IsInCheck castro_IsInCheck
#define BoardPrintSquares castro_BoardPrintSquares
#define BoardPrintBitboard castro_BoardPrintBitboard
#define BoardPrint castro_BoardPrint
#define BoardPrintBitboards castro_BoardPrintBitboards
#define BoardPrintGrid castro_BoardPrintGrid
#define BoardCopy castro_BoardCopy
#define InitZobrist castro_InitZobrist
#define CalculateZobristHash castro_CalculateZobristHash
#define CalculateZobristHashFen castro_CalculateZobristHashFen
#define InitMasks castro_InitMasks
#define GeneralOccupancy castro_GeneralOccupancy
#define BlockerMasks castro_BlockerMasks
#define ComputeDiagonalMask castro_ComputeDiagonalMask
#define ComputeAntiDiagonalMask castro_ComputeAntiDiagonalMask
#define ComputeHorizontalMask castro_ComputeHorizontalMask
#define ComputeVerticalMask castro_ComputeVerticalMask
#define DiagonalMask castro_DiagonalMask
#define AntiDiagonalMask castro_AntiDiagonalMask
#define HorizontalMask castro_HorizontalMask
#define VerticalMask castro_VerticalMask
#define ComputePawnPushMask castro_ComputePawnPushMask
#define ComputePawnDoublePushMask castro_ComputePawnDoublePushMask
#define ComputePawnPromotionMask castro_ComputePawnPromotionMask
#define ComputePawnPromotionAttackMask castro_ComputePawnPromotionAttackMask
#define ComputePawnAttackMask castro_ComputePawnAttackMask
#define ComputeKnightMoveMask castro_ComputeKnightMoveMask
#define ComputeBishopMoveMask castro_ComputeBishopMoveMask
#define ComputeRookMoveMask castro_ComputeRookMoveMask
#define ComputeQueenMoveMask castro_ComputeQueenMoveMask
#define ComputeKingMoveMask castro_ComputeKingMoveMask
#define PawnPushMask castro_PawnPushMask
#define PawnDoublePushMask castro_PawnDoublePushMask
#define PawnPromotionMask castro_PawnPromotionMask
#define PawnPromotionAttackMask castro_PawnPromotionAttackMask
#define PawnAttackMask castro_PawnAttackMask
#define KnightMoveMask castro_KnightMoveMask
#define BishopMoveMask castro_BishopMoveMask
#define RookMoveMask castro_RookMoveMask
#define QueenMoveMask castro_QueenMoveMask
#define KingMoveMask castro_KingMoveMask
#define MovesAppend castro_MovesAppend
#define MovesAppendList castro_MovesAppendList
#define MovesCombine castro_MovesCombine
#define MakeUndo castro_MakeUndo
#define MoveIsValid castro_MoveIsValid
#define MoveIsCapture castro_MoveIsCapture
#define MoveGivesCheck castro_MoveGivesCheck
#define PieceValueFromType castro_PieceValueFromType
#define OrderLegalMoves castro_OrderLegalMoves
#define MoveEncode castro_MoveEncode
#define MoveEncodeNames castro_MoveEncodeNames
#define MoveDecode castro_MoveDecode
#define MoveSetFlag castro_MoveSetFlag
#define MoveSetPromotion castro_MoveSetPromotion
#define DoMove castro_DoMove
#define UndoMove castro_UndoMove
#define MakeMove castro_MakeMove
#define UnmakeMove castro_UnmakeMove
#define MakeNullMove castro_MakeNullMove
#define UnmakeNullMove castro_UnmakeNullMove
#define Castle castro_Castle
#define IsCastle castro_IsCastle
#define Enpassant castro_Enpassant
#define IsEnpassant castro_IsEnpassant
#define IsDoublePawnPush castro_IsDoublePawnPush
#define IsPromotion castro_IsPromotion
#define IsCapture castro_IsCapture
#define IsInCheckAfterMove castro_IsInCheckAfterMove
#define MoveMake castro_MoveMake
#define MoveFreely castro_MoveFreely
#define MovePrint castro_MovePrint
#define StringToMove castro_StringToMove
#define MoveToString castro_MoveToString
#define MoveCmp castro_MoveCmp
#define MoveCmpStrict castro_MoveCmpStrict
#define GetFrom castro_GetFrom
#define GetTo castro_GetTo
#define GetPromotion castro_GetPromotion
#define GetFlag castro_GetFlag
#define UpdateHalfmove castro_UpdateHalfmove
#define UpdateCastlingRights castro_UpdateCastlingRights
#define UpdateEnpassantSquare castro_UpdateEnpassantSquare
#define BitboardToMoves castro_BitboardToMoves
#define MovesToBitboard castro_MovesToBitboard
#define BoardPrintMove castro_BoardPrintMove
#define GetPieceColor castro_GetPieceColor
#define PieceAt castro_PieceAt
#define PieceCmp castro_PieceCmp
#define FenImport castro_FenImport
#define FenExport castro_FenExport
#define move_name castro_move_name
#define GameInit castro_GameInit
#define GameRun castro_GameRun
#define GamePrint castro_GamePrint
#define GameAddMove castro_GameAddMove
#define GameSetEvent castro_GameSetEvent
#define GameSetSite castro_GameSetSite
#define GameSetDate castro_GameSetDate
#define GameSetWhite castro_GameSetWhite
#define GameSetBlack castro_GameSetBlack
#define GameSetFen castro_GameSetFen
#define GameSetResult castro_GameSetResult
#define PgnImport castro_PgnImport
#define PgnExport castro_PgnExport
#define PgnExportFile castro_PgnExportFile
#define Notate castro_Notate
#define SanToMove castro_SanToMove
#define IsResult castro_IsResult
#define IsCheckmate castro_IsCheckmate
#define IsStalemate castro_IsStalemate
#define IsInsufficientMaterial castro_IsInsufficientMaterial
#define IsThreefoldRepetition castro_IsThreefoldRepetition
#define GeneratePseudoLegalMoves castro_GeneratePseudoLegalMoves
#define GeneratePseudoLegalMovesBitboard castro_GeneratePseudoLegalMovesBitboard
#define GeneratePseudoLegalPawnMoves castro_GeneratePseudoLegalPawnMoves
#define GeneratePseudoLegalPawnAttacks castro_GeneratePseudoLegalPawnAttacks
#define GeneratePseudoLegalKnightAttacks castro_GeneratePseudoLegalKnightAttacks
#define GeneratePseudoLegalBishopAttacks castro_GeneratePseudoLegalBishopAttacks
#define GeneratePseudoLegalRookAttacks castro_GeneratePseudoLegalRookAttacks
#define GeneratePseudoLegalQueenAttacks castro_GeneratePseudoLegalQueenAttacks
#define GeneratePseudoLegalKingAttacks castro_GeneratePseudoLegalKingAttacks
#define GeneratePseudoLegalAttacks castro_GeneratePseudoLegalAttacks
#define GeneratePawnMoves castro_GeneratePawnMoves
#define GenerateKnightMoves castro_GenerateKnightMoves
#define GenerateBishopMoves castro_GenerateBishopMoves
#define GenerateRookMoves castro_GenerateRookMoves
#define GenerateQueenMoves castro_GenerateQueenMoves
#define GenerateKingMoves castro_GenerateKingMoves
#define IsLegal castro_IsLegal
#define GenerateLegalMoves castro_GenerateLegalMoves
#define GenerateLegalCaptures castro_GenerateLegalCaptures
#define GenerateLegalMovesSquare castro_GenerateLegalMovesSquare
#define GenerateLegalMovesBitboard castro_GenerateLegalMovesBitboard
#define GenerateLegalPawnMoves castro_GenerateLegalPawnMoves
#define GenerateLegalKnightMoves castro_GenerateLegalKnightMoves
#define GenerateLegalBishopMoves castro_GenerateLegalBishopMoves
#define GenerateLegalRookMoves castro_GenerateLegalRookMoves
#define GenerateLegalQueenMoves castro_GenerateLegalQueenMoves
#define GenerateLegalKingMoves castro_GenerateLegalKingMoves
#define GenerateMoves castro_GenerateMoves
#define Perft castro_Perft
#define ConvertMove castro_ConvertMove
#define LookupBookMove castro_LookupBookMove

#endif // CASTRO_STRIP_PREFIX

#endif // CASTRO_H
