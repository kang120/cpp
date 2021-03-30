#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "piece.h"
using namespace sf;
using namespace std;

const int width = 768;
const int height = 768;
const int tile = 96;
const string PATH = "images/";

vector<Piece> white;
vector<Piece> black;

bool whiteChecked = false;
bool blackChecked = false;

vector<vector<int>> board = {
    {2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

void init(){
    for(int i = 0; i < 16; i++){
        if(i < 8){
            switch(i){
                case 0: case 7:{
                    Piece piece("black", "rook", PATH+"black rook.png", i*tile, 0*tile);
                    black.push_back(piece);
                    break;
                }
                case 1: case 6:{
                    Piece piece("black", "knight", PATH+"black knight.png", i*tile, 0*tile);
                    black.push_back(piece);
                    break;
                }
                case 2: case 5:{
                    Piece piece("black", "bishop", PATH+"black bishop.png", i*tile, 0*tile);
                    black.push_back(piece);
                    break;
                }
                case 3:{
                    Piece piece("black", "queen", PATH+"black queen.png", i*tile, 0*tile);
                    black.push_back(piece);
                    break;
                }
                case 4:{
                    Piece piece("black", "king", PATH+"black king.png", i*tile, 0*tile);
                    black.push_back(piece);
                    break;
                }
                default:
                    break;
            }
        }else{
            Piece piece("black", "pawn", PATH+"black pawn.png", i%8*tile, 1*tile);
            black.push_back(piece);
        }
    }

    for(int i = 0; i < 16; i++){
        if(i < 8){
            Piece piece("white", "pawn", PATH+"white pawn.png", i*tile, 6*tile);
            white.push_back(piece);
        }else{
            switch(i){
                case 8: case 15:{
                    Piece piece("white", "rook", PATH+"white rook.png", i%8*tile, 7*tile);
                    white.push_back(piece);
                    break;
                }
                case 9: case 14:{
                    Piece piece("white", "knight", PATH+"white knight.png", i%8*tile, 7*tile);
                    white.push_back(piece);
                    break;
                }
                case 10: case 13:{
                    Piece piece("white", "bishop", PATH+"white bishop.png", i%8*tile, 7*tile);
                    white.push_back(piece);
                    break;
                }
                case 11:{
                    Piece piece("white", "queen", PATH+"white queen.png", i%8*tile, 7*tile);
                    white.push_back(piece);
                    break;
                }
                case 12:{
                    Piece piece("white", "king", PATH+"white king.png", i%8*tile, 7*tile);
                    white.push_back(piece);
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void drawBoard(RenderWindow &window){
    bool black = false;
    for(int i = 0; i < window.getSize().y / tile; i++){
        for(int j = 0; j < window.getSize().x / tile; j++){
            RectangleShape block(Vector2f(tile, tile));
            block.setPosition(Vector2f(j*tile, i*tile));
            if(black){
                block.setFillColor(Color(112, 179, 71));
                black = false;
            }else{
                block.setFillColor(Color(210, 235, 195));
                black = true;
            }
            window.draw(block);
        }
        black = !black;
    }
}

void drawPieces(RenderWindow &window){
    for(int i = 0; i < black.size(); i++){
        black[i].draw(window);
    }

    for(int i = 0; i < white.size(); i++){
        white[i].draw(window);
    }
}

bool pieceCheck(Piece piece, Vector2f kingPos){
    string site = piece.getSite();
    string name = piece.getName();
    Vector2f piecePos = piece.getPosition();

    if(name == "pawn"){
        if(site == "white"){
            if((abs(piecePos.x - kingPos.x) == tile) && (piecePos.y - kingPos.y == tile)){
                return true;
            }
        }else if(site == "black"){
            if((abs(piecePos.x - kingPos.x) == tile) && (kingPos.y - piecePos.y == tile)){
                return true;
            }
        }
    }else if(name == "knight"){
        if((abs(kingPos.x - piecePos.x) == tile) && (abs(kingPos.y - piecePos.y) == 2*tile) ||
           (abs(kingPos.x - piecePos.x) == 2*tile) && (abs(kingPos.y - piecePos.y) == tile)){

            return true;
        }
    }else if(name == "rook"){
        // move horizontal
        if(kingPos.y == piecePos.y){
            // move right
            if(kingPos.x > piecePos.x){
                for(int i = piecePos.x/tile+1; i < kingPos.x/tile; i++){
                    if(board[piecePos.y/tile][i] != 0){
                        return false;
                    }
                }

                return true;
            // move left
            }else if(kingPos.x < piecePos.x){
                for(int i = piecePos.x/tile-1; i > kingPos.x/tile; i--){
                    if(board[piecePos.y/tile][i] != 0){
                        return false;
                    }
                }

                return true;
            }
        // move vertical
        }else if(kingPos.x == piecePos.x){
            // move down
            if(kingPos.y > piecePos.y){
                for(int i = piecePos.y/tile+1; i < kingPos.y/tile; i++){
                    if(board[i][piecePos.x/tile] != 0){
                        return false;
                    }
                }

                return true;
            // move up
            }else if(kingPos.y < piecePos.y){
                for(int i = piecePos.y/tile-1; i > kingPos.y/tile; i--){
                    if(board[i][piecePos.x/tile] != 0){
                        return false;
                    }
                }

                return true;
            }
        }
    }else if(name == "bishop"){
        if((abs(kingPos.x - piecePos.x) == abs(kingPos.y - piecePos.y))){
            // move left
            if(kingPos.x < piecePos.x){
                // move left up
                if(kingPos.y < piecePos.y){
                    for(int i = piecePos.y/tile-1, j = piecePos.x/tile-1; i > kingPos.y/tile && j > kingPos.x/tile; i--, j--){
                        if(board[i][j] != 0){
                            return false;
                        }
                    }

                    return true;
                // move left down
                }else if(kingPos.y > piecePos.y){
                    for(int i = piecePos.y/tile+1, j = piecePos.x/tile-1; i < kingPos.y/tile && j > kingPos.x/tile; i++, j--){
                        if(board[i][j] != 0){
                            return false;
                        }
                    }

                    return true;
                }
            // move right
            }else if(kingPos.x > piecePos.x){
                // move right up
                if(kingPos.y < piecePos.y){
                    for(int i = piecePos.y/tile-1, j = piecePos.x/tile+1; i > kingPos.y/tile && j < kingPos.x/tile; i--, j++){
                        if(board[i][j] != 0){
                            return false;
                        }
                    }

                    return true;
                // move right down
                }else if(kingPos.y > piecePos.y){
                    for(int i = piecePos.y/tile+1, j = piecePos.x/tile+1; i < kingPos.y/tile && j < kingPos.x/tile; i++, j++){
                        if(board[i][j] != 0){
                            return false;
                        }
                    }

                    return true;
                }
            }
        }
    }else if(name == "queen"){
        // similar rook move
        // move horizontal
        if(kingPos.y == piecePos.y){
            // move right
            if(kingPos.x > piecePos.x){
                for(int i = piecePos.x/tile+1; i < kingPos.x/tile; i++){
                    if(board[piecePos.y/tile][i] != 0){
                        return false;
                    }
                }

                return true;
            // move left
            }else if(kingPos.x < piecePos.x){
                for(int i = piecePos.x/tile-1; i > kingPos.x/tile; i--){
                    if(board[piecePos.y/tile][i] != 0){
                        return false;
                    }
                }

                return true;
            }
        // move vertical
        }else if(kingPos.x == piecePos.x){
            // move down
            if(kingPos.y > piecePos.y){
                for(int i = piecePos.y/tile+1; i < kingPos.y/tile; i++){
                    if(board[i][piecePos.x/tile] != 0){
                        return false;
                    }
                }

                return true;
            // move up
            }else if(kingPos.y < piecePos.y){
                for(int i = piecePos.y/tile-1; i > kingPos.y/tile; i--){
                    if(board[i][piecePos.x/tile] != 0){
                        return false;
                    }
                }

                return true;
            }
        }
        // similar bishop move
        if(abs(kingPos.x - piecePos.x) == abs(kingPos.y - piecePos.y)){
            // move left
            if(kingPos.x < piecePos.x){
                // move left up
                if(kingPos.y < piecePos.y){
                    for(int i = piecePos.y/tile-1, j = piecePos.x/tile-1; i > kingPos.y/tile && j > kingPos.x/tile; i--, j--){
                        if(board[i][j] != 0){
                            return false;
                        }
                    }

                    return true;
                // move left down
                }else if(kingPos.y > piecePos.y){
                    for(int i = piecePos.y/tile+1, j = piecePos.x/tile-1; i < kingPos.y/tile && j > kingPos.x/tile; i++, j--){
                        if(board[i][j] != 0){
                            return false;
                        }
                    }

                    return true;
                }
            // move right
            }else if(kingPos.x > piecePos.x){
                // move right up
                if(kingPos.y < piecePos.y){
                    for(int i = piecePos.y/tile-1, j = piecePos.x/tile+1; i > kingPos.y/tile && j < kingPos.x/tile; i--, j++){
                        if(board[i][j] != 0){
                            return false;
                        }
                    }

                    return true;
                // move right down
                }else if(kingPos.y > piecePos.y){
                    for(int i = piecePos.y/tile+1, j = piecePos.x/tile+1; i < kingPos.y/tile && j < kingPos.x/tile; i++, j++){
                        if(board[i][j] != 0){
                            return false;
                        }
                    }

                    return true;
                }
            }
        }
    }else if(name == "king"){
        if((abs(piecePos.x - kingPos.x) == tile) && (piecePos.y == kingPos.y) || (abs(piecePos.y - kingPos.y) == tile) && (piecePos.x == kingPos.x) ||
           (abs(piecePos.x - kingPos.x) == tile) && (abs(piecePos.y - kingPos.y) == tile)){

            return true;
        }
    }

    return false;
}

bool isChecking(string site, int eatenIndex){
    Vector2f kingPos;

    if(site == "white"){
        for(int i = 0; i < white.size(); i++){
            if(white[i].getName() == "king"){
                kingPos = white[i].getPosition();
                break;
            }
        }

        for(int i = 0; i < black.size(); i++){
            if(i == eatenIndex){
                continue;
            }
            if(pieceCheck(black[i], kingPos)){
                return true;
            }
        }

    }else if(site == "black"){
        for(int i = 0; i < black.size(); i++){
            if(black[i].getName() == "king"){
                kingPos = black[i].getPosition();
                break;
            }
        }

        for(int i = 0; i < white.size(); i++){
            if(i == eatenIndex){
                continue;
            }
            if(pieceCheck(white[i], kingPos)){
                return true;
            }
        }
    }

    return false;
}

int main(){

    RenderWindow window(VideoMode(width, height), "Chess", Style::Close|Style::Titlebar);

    init();

    // define variables
    bool clicked = false;
    string turn = "white";
    int index = -1;
    Vector2f initialPos;

    while(window.isOpen()){
        Event e;

        while(window.pollEvent(e)){
            switch(e.type){
                case e.Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        // check selected piece
        if((Mouse::isButtonPressed(Mouse::Left)) && !clicked){
            int x = Mouse::getPosition(window).x;
            int y = Mouse::getPosition(window).y;

            if(turn == "white"){
                for(int i = 0; i < white.size(); i++){
                    if((x > white[i].getPosition().x) && (x < white[i].getPosition().x+tile) && (y > white[i].getPosition().y) && (y < white[i].getPosition().y+tile)){
                        index = i;
                        initialPos = white[i].getPosition();
                    }
                }
            }else if(turn == "black"){
                for(int i = 0; i < black.size(); i++){
                    if((x > black[i].getPosition().x) && (x < black[i].getPosition().x+tile) && (y > black[i].getPosition().y) && (y < black[i].getPosition().y+tile)){
                        index = i;
                        initialPos = black[i].getPosition();
                    }
                }
            }
            clicked = true;
        }

        // move selected piece along with mouse
        if((Mouse::isButtonPressed(Mouse::Left)) && (index != -1)){
            if(turn == "white"){
                white[index].setPosition(Mouse::getPosition(window).x - tile/2, Mouse::getPosition(window).y - tile/2);
            }else if(turn == "black"){
                black[index].setPosition(Mouse::getPosition(window).x - tile/2, Mouse::getPosition(window).y - tile/2);
            }
        }

        // set new position of piece
        if(!(Mouse::isButtonPressed(Mouse::Left)) && clicked){
            Vector2i pos = Mouse::getPosition(window);
            int x = pos.x;
            int y = pos.y;

            // check piece has been selected
            if(index != -1){
                // white move
                if(turn == "white"){
                    // check valid move
                    if((white[index].checkValidMove(initialPos, Vector2f(x/tile*tile, y/tile*tile), tile, board)) && (board[y/tile][x/tile] != 1)){
                        white[index].setPosition(x/tile * tile, y/tile * tile);
                        board[initialPos.y/tile][initialPos.x/tile] = 0;
                        board[y/tile][x/tile] = 1;
                        int eatenIndex = -1;
                        for(int i = 0; i < black.size(); i++){
                            if((black[i].getPosition().x == x/tile*tile) && (black[i].getPosition().y == y/tile*tile)){
                                eatenIndex = i;
                            }
                        }
                        // check the move is legal
                        if(!isChecking("white", eatenIndex)){
                            // check is black piece eaten
                            for(int i = 0; i < black.size(); i++){
                                if((black[i].getPosition().x == x/tile*tile) && (black[i].getPosition().y == y/tile*tile)){
                                    black.erase(black.begin()+i);
                                }
                            }
                            turn = "black";
                        // the move is illegal
                        }else{
                            board[initialPos.y/tile][initialPos.x/tile] = 1;
                            board[y/tile][x/tile] = 0;
                            white[index].setPosition(initialPos.x, initialPos.y);
                        }
                    // check white castling
                    }else if((white[index].getName() == "king") && !white[index].getIsMoved()){
                        // right castling
                        if((x/tile*tile == 6*tile) && (y/tile*tile == 7*tile)){
                            bool validCastling = true;
                            for(int i = 0; i < black.size(); i++){
                                if(pieceCheck(black[i], Vector2f(4*tile, 7*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(black[i], Vector2f(5*tile, 7*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(black[i], Vector2f(6*tile, 7*tile))){
                                    validCastling = false;
                                    break;
                                }
                            }

                            if(validCastling){
                                for(int i = 0; i < white.size(); i++){
                                    if((white[i].getName() == "rook") && (white[i].getPosition().x > white[index].getPosition().x) && !white[i].getIsMoved()){
                                        if((board[7][5] == 0) && (board[7][6] == 0)){
                                            board[white[i].getPosition().y/tile][white[i].getPosition().x/tile] = 0;
                                            board[initialPos.y/tile][initialPos.x/tile] = 0;
                                            white[i].setPosition(5*tile, 7*tile);
                                            white[index].setPosition(6*tile, 7*tile);
                                            board[7][5] = 1;
                                            board[7][6] = 1;
                                            white[index].setIsMoved(true);
                                            white[i].setIsMoved(true);
                                            turn = "black";
                                        }else{
                                            white[index].setPosition(initialPos.x, initialPos.y);
                                        }
                                    }
                                }
                            }else{
                                white[index].setPosition(initialPos.x, initialPos.y);
                            }
                        // left castling
                        }else if((x/tile*tile == 2*tile) && (y/tile*tile == 7*tile)){
                            bool validCastling = true;
                            for(int i = 0; i < black.size(); i++){
                                if(pieceCheck(black[i], Vector2f(4*tile, 7*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(black[i], Vector2f(1*tile, 7*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(black[i], Vector2f(2*tile, 7*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(black[i], Vector2f(3*tile, 7*tile))){
                                    validCastling = false;
                                    break;
                                }
                            }

                            if(validCastling){
                                for(int i = 0; i < white.size(); i++){
                                    if((white[i].getName() == "rook") && (white[i].getPosition().x < white[index].getPosition().x) && !white[i].getIsMoved()){
                                        if((board[7][1] == 0) && (board[7][2] == 0) && (board[7][3] == 0)){
                                            board[white[i].getPosition().y/tile][white[i].getPosition().x/tile] = 0;
                                            board[initialPos.y/tile][initialPos.x/tile] = 0;
                                            white[i].setPosition(3*tile, white[i].getPosition().y);
                                            white[index].setPosition(2*tile, white[index].getPosition().y);
                                            board[7][3] = 1;
                                            board[7][2] = 1;
                                            white[index].setIsMoved(true);
                                            white[i].setIsMoved(true);
                                            turn = "black";
                                        }else{
                                            white[index].setPosition(initialPos.x, initialPos.y);
                                        }
                                    }
                                }
                            }else{
                                white[index].setPosition(initialPos.x, initialPos.y);
                            }
                        }else{
                            white[index].setPosition(initialPos.x, initialPos.y);
                        }
                    // reset position
                    }else{
                        white[index].setPosition(initialPos.x, initialPos.y);
                    }
                // black move
                }else if(turn == "black"){
                    // check valid move
                    if((black[index].checkValidMove(initialPos, Vector2f(x/tile*tile, y/tile*tile), tile, board)) && (board[y/tile][x/tile] != 2)){
                        black[index].setPosition(x/tile * tile, y/tile * tile);
                        board[initialPos.y/tile][initialPos.x/tile] = 0;
                        board[y/tile][x/tile] = 2;
                        int eatenIndex = -1;
                        for(int i = 0; i < white.size(); i++){
                            if((white[i].getPosition().x == x/tile*tile) && (white[i].getPosition().y == y/tile*tile)){
                                eatenIndex = i;
                            }
                        }
                        if(!isChecking("black", eatenIndex)){
                            turn = "white";
                            // check is white piece eaten
                            for(int i = 0; i < white.size(); i++){
                                if((white[i].getPosition().x == x/tile*tile) && (white[i].getPosition().y == y/tile*tile)){
                                    white.erase(white.begin()+i);
                                }
                            }
                        }else{
                            black[index].setPosition(initialPos.x, initialPos.y);
                            board[initialPos.y/tile][initialPos.x/tile] = 2;
                            board[y/tile][x/tile] = 0;
                        }
                    // check black castling
                    }else if((black[index].getName() == "king") && !black[index].getIsMoved()){
                        // right castling
                        if((x/tile*tile == 6*tile) && (y/tile*tile == 0*tile)){
                            bool validCastling = true;
                            for(int i = 0; i < white.size(); i++){
                                if(pieceCheck(white[i], Vector2f(4*tile, 0*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(white[i], Vector2f(5*tile, 0*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(white[i], Vector2f(6*tile, 0*tile))){
                                    validCastling = false;
                                    break;
                                }
                            }

                            if(validCastling){
                                for(int i = 0; i < black.size(); i++){
                                    if((black[i].getName() == "rook") && (black[i].getPosition().x > black[index].getPosition().x) && !black[i].getIsMoved()){
                                        if((board[0][5] == 0) && (board[0][6] == 0)){
                                            board[black[i].getPosition().y/tile][black[i].getPosition().x/tile] = 0;
                                            board[initialPos.y/tile][initialPos.x/tile] = 0;
                                            black[i].setPosition(5*tile, 0*tile);
                                            black[index].setPosition(6*tile, 0*tile);
                                            board[0][5] = 2;
                                            board[0][6] = 2;
                                            black[index].setIsMoved(true);
                                            black[i].setIsMoved(true);
                                            turn = "white";
                                        }else{
                                            black[index].setPosition(initialPos.x, initialPos.y);
                                        }
                                    }
                                }
                            }else{
                                black[index].setPosition(initialPos.x, initialPos.y);
                            }
                        // left castling
                        }else if((x/tile*tile == 2*tile) && (y/tile*tile == 0*tile)){
                            bool validCastling = true;
                            for(int i = 0; i < white.size(); i++){
                                if(pieceCheck(white[i], Vector2f(4*tile, 0*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(white[i], Vector2f(1*tile, 0*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(white[i], Vector2f(2*tile, 0*tile))){
                                    validCastling = false;
                                    break;
                                }
                                if(pieceCheck(white[i], Vector2f(3*tile, 0*tile))){
                                    validCastling = false;
                                    break;
                                }
                            }

                            if(validCastling){
                                for(int i = 0; i < black.size(); i++){
                                    if((black[i].getName() == "rook") && (black[i].getPosition().x < black[index].getPosition().x) && !black[i].getIsMoved()){
                                        if((board[0][1] == 0) && (board[0][2] == 0) && (board[0][3] == 0)){
                                            board[black[i].getPosition().y/tile][black[i].getPosition().x/tile] = 0;
                                            board[initialPos.y/tile][initialPos.x/tile] = 0;
                                            black[i].setPosition(3*tile, 0);
                                            black[index].setPosition(2*tile, 0);
                                            board[0][3] = 2;
                                            board[0][2] = 2;
                                            black[index].setIsMoved(true);
                                            black[i].setIsMoved(true);
                                            turn = "white";
                                        }else{
                                            black[index].setPosition(initialPos.x, initialPos.y);
                                        }
                                    }
                                }
                            }else{
                                black[index].setPosition(initialPos.x, initialPos.y);
                            }
                        }else{
                            black[index].setPosition(initialPos.x, initialPos.y);
                        }
                    // reset position
                    }else{
                        black[index].setPosition(initialPos.x, initialPos.y);
                    }
                }
                for(auto i : board){
                    for(auto j : i){
                        cout<<j<<" ";
                    }
                    cout<<endl;
                }
                cout<<endl;
                index = -1;
            }

            clicked = false;
        }

        window.clear(Color::White);

        drawBoard(window);
        drawPieces(window);

        window.display();
    }
}
