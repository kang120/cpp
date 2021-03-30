#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Piece{

private:
    RectangleShape sprite;
    string site;
    string name;
    string texturePath;
    bool isMoved = false;

public:
    Piece(){}

    Piece(string site, string name, string texturePath, int x, int y){
        this->site = site;
        this->name = name;

        this->sprite.setSize(Vector2f(96, 96));
        this->sprite.setPosition(x, y);
        this->texturePath = texturePath;
    }

    void setPosition(int x, int y){
        this->sprite.setPosition(x, y);
    }

    bool checkValidMove(Vector2f initialPos, Vector2f finalPos, int tile, vector<vector<int>> board){
        if(name == "pawn"){
            if(site == "white"){
                // pawn eat
                if((abs(initialPos.x - finalPos.x) == tile) && (initialPos.y - finalPos.y == tile) && (board[finalPos.y/tile][finalPos.x/tile] == 2)){
                    isMoved = true;
                    return true;
                // pawn move 1 or 2
                }else if(!isMoved && (initialPos.x == finalPos.x) && (abs(initialPos.y - finalPos.y) == 2*tile) &&
                        (board[finalPos.y/tile][finalPos.x/tile] == 0) && (board[finalPos.y/tile+1][finalPos.x/tile] == 0) ||
                        (abs(initialPos.y - finalPos.y) == 1*tile) && (initialPos.x == finalPos.x) && (board[finalPos.y/tile][finalPos.x/tile] == 0)){
                    isMoved = true;
                    return true;
                }else{
                    return false;
                }
            }else if(site == "black"){
                // pawn eat
                if((abs(initialPos.x - finalPos.x) == tile) && (finalPos.y - initialPos.y == tile) && (board[finalPos.y/tile][finalPos.x/tile] == 1)){
                    isMoved = true;
                    return true;
                // pawn move 1 or 2
                }else if(!isMoved && (initialPos.x == finalPos.x) && (abs(initialPos.y - finalPos.y) == 2*tile) &&
                        (board[finalPos.y/tile][finalPos.x/tile] == 0) && (board[finalPos.y/tile-1][finalPos.x/tile] == 0) ||
                        (abs(initialPos.y - finalPos.y) == 1*tile) && (initialPos.x == finalPos.x) && (board[finalPos.y/tile][finalPos.x/tile] == 0)){
                    isMoved = true;
                    return true;
                }else{
                    return false;
                }
            }
        }else if(name == "knight"){
            if((abs(initialPos.x - finalPos.x) == tile) && (abs(initialPos.y - finalPos.y) == 2*tile) ||
               (abs(initialPos.x - finalPos.x) == 2*tile) && (abs(initialPos.y - finalPos.y) == tile)){
                isMoved = true;
                return true;
            }else{
                return false;
            }
        }else if(name == "bishop"){
            if(abs(initialPos.x - finalPos.x) == abs(initialPos.y - finalPos.y)){
                // move left
                if(initialPos.x > finalPos.x){
                    // move left up
                    if(initialPos.y > finalPos.y){
                        for(int i = initialPos.x/tile-1, j = initialPos.y/tile-1; i > finalPos.x/tile && j > finalPos.y/tile; i--, j--){
                            if(board[j][i] != 0){
                                return false;
                            }
                        }
                    // move left down
                    }else{
                        for(int i = initialPos.x/tile-1, j = initialPos.y/tile+1; i > finalPos.x/tile && j < finalPos.y/tile; i--, j++){
                            if(board[j][i] != 0){
                                return false;
                            }
                        }
                    }
                // move right
                }else if(initialPos.x < finalPos.x){
                    // move right up
                    if(initialPos.y > finalPos.y){
                        for(int i = initialPos.x/tile+1, j = initialPos.y/tile-1; i < finalPos.x/tile && j > finalPos.y/tile; i++, j--){
                            if(board[j][i] != 0){
                                return false;
                            }
                        }
                    // move right down
                    }else{
                        for(int i = initialPos.x/tile+1, j = initialPos.y/tile+1; i < finalPos.x/tile && j < finalPos.y/tile; i++, j++){
                            if(board[j][i] != 0){
                                return false;
                            }
                        }
                    }
                }
                isMoved = true;
                return true;
            }else{
                return false;
            }
        }else if(name == "rook"){
            // move vertical
            if(initialPos.x == finalPos.x){
                // move up
                if(initialPos.y > finalPos.y){
                    for(int i = initialPos.y/tile-1; i > finalPos.y/tile; i--){
                        if(board[i][initialPos.x/tile] != 0){
                            return false;
                        }
                    }
                // move down
                }else{
                    for(int i = initialPos.y/tile+1; i < finalPos.y/tile; i++){
                        if(board[i][initialPos.x/tile] != 0){
                            return false;
                        }
                    }
                }
                isMoved = true;
                return true;
            // move horizontal
            }else if(initialPos.y == finalPos.y){
                // move left
                if(initialPos.x > finalPos.x){
                    for(int i = initialPos.x/tile-1; i > finalPos.x/tile; i--){
                        if(board[initialPos.y/tile][i] != 0){
                            return false;
                        }
                    }
                // move right
                }else{
                    for(int i = initialPos.x/tile+1; i < finalPos.x/tile; i++){
                        if(board[initialPos.y/tile][i] != 0){
                            return false;
                        }
                    }
                }
                isMoved = true;
                return true;
            }else{
                return false;
            }
        }else if(name == "queen"){
            // bishop move
            if(abs(initialPos.x - finalPos.x) == abs(initialPos.y - finalPos.y)){
                // move left
                if(initialPos.x > finalPos.x){
                    // move left up
                    if(initialPos.y > finalPos.y){
                        for(int i = initialPos.x/tile-1, j = initialPos.y/tile-1; i > finalPos.x/tile && j > finalPos.y/tile; i--, j--){
                            if(board[j][i] != 0){
                                return false;
                            }
                        }
                    // move left down
                    }else{
                        for(int i = initialPos.x/tile-1, j = initialPos.y/tile+1; i > finalPos.x/tile && j < finalPos.y/tile; i--, j++){
                            if(board[j][i] != 0){
                                return false;
                            }
                        }
                    }
                // move right
                }else if(initialPos.x < finalPos.x){
                    // move right up
                    if(initialPos.y > finalPos.y){
                        for(int i = initialPos.x/tile+1, j = initialPos.y/tile-1; i < finalPos.x/tile && j > finalPos.y/tile; i++, j--){
                            if(board[j][i] != 0){
                                return false;
                            }
                        }
                    // move right down
                    }else{
                        for(int i = initialPos.x/tile+1, j = initialPos.y/tile+1; i < finalPos.x/tile && j < finalPos.y/tile; i++, j++){
                            if(board[j][i] != 0){
                                return false;
                            }
                        }
                    }
                }
                isMoved = true;
                return true;
            // move vertical
            }else if(initialPos.x == finalPos.x){
                // move up
                if(initialPos.y > finalPos.y){
                    for(int i = initialPos.y/tile-1; i > finalPos.y/tile; i--){
                        if(board[i][initialPos.x/tile] != 0){
                            return false;
                        }
                    }
                // move down
                }else{
                    for(int i = initialPos.y/tile+1; i < finalPos.y/tile; i++){
                        if(board[i][initialPos.x/tile] != 0){
                            return false;
                        }
                    }
                }
                isMoved = true;
                return true;
            // move horizontal
            }else if(initialPos.y == finalPos.y){
                // move left
                if(initialPos.x > finalPos.x){
                    for(int i = initialPos.x/tile-1; i > finalPos.x/tile; i--){
                        if(board[initialPos.y/tile][i] != 0){
                            return false;
                        }
                    }
                // move right
                }else{
                    for(int i = initialPos.x/tile+1; i < finalPos.x/tile; i++){
                        if(board[initialPos.y/tile][i] != 0){
                            return false;
                        }
                    }
                }
                isMoved = true;
                return true;
            }else{
                return false;
            }
        }else if(name == "king"){
            if((abs(finalPos.x - initialPos.x) == tile) || (abs(finalPos.y - initialPos.y) == tile)){
                isMoved = true;
                return true;
            }else{
                return false;
            }
        }

        return false;
    }

    void setIsMoved(bool isMoved){
        this->isMoved = isMoved;
    }

    void draw(RenderWindow &window){
        Texture texture;
        texture.loadFromFile(texturePath);

        this->sprite.setTexture(&texture);

        window.draw(sprite);
    }

    string getName(){
        return this->name;
    }

    string getSite(){
        return this->site;
    }

    Vector2f getPosition(){
        return this->sprite.getPosition();
    }

    bool getIsMoved(){
        return this->isMoved;
    }
};

#endif // PIECE_H
