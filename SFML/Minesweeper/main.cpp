#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <iostream>
using namespace sf;
using namespace std;

const int width = 640;
const int height = 640;
const int tile = 32;
const int mineNumber = 50;

vector<vector<int>> showingMap = vector<vector<int>>(20, vector<int>(20, 10));
vector<vector<int>> realMap = vector<vector<int>>(20, vector<int>(20, 0));

void init(){
    srand(time(0));
    // spawn mine
    for(int k = 0; k < mineNumber; k++){
        int i = rand() % 20;
        int j = rand() % 20;
        if(realMap[i][j] != 9){
            realMap[i][j] = 9;
        }else{
            k--;
        }
    }

    // calculate block value
    for(int i = 0; i < realMap.size(); i++){
        for(int j = 0; j < realMap[i].size(); j++){
            if(realMap[i][j] == 9){
                continue;
            }
            int n = 0;
            int rowMax = realMap.size()-1;
            int colMax = realMap[i].size()-1;
            // left up
            if((i > 0) && (j > 0) && (realMap[i-1][j-1] == 9)){
                n++;
            }
            // up
            if((i > 0) && (realMap[i-1][j] == 9)){
                n++;
            }
            // right up
            if((i > 0) && (j < colMax) && (realMap[i-1][j+1] == 9)){
                n++;
            }
            // left
            if((j > 0) && (realMap[i][j-1] == 9)){
                n++;
            }
            // right
            if((j < colMax) && (realMap[i][j+1] == 9)){
                n++;
            }
            // left down
            if((i < rowMax) && (j > 0) && (realMap[i+1][j-1] == 9)){
                n++;
            }
            // down
            if((i < rowMax) && (realMap[i+1][j] == 9)){
                n++;
            }
            // right down
            if((i < rowMax) && (j < colMax) && (realMap[i+1][j+1] == 9)){
                n++;
            }
            realMap[i][j] = n;
        }
    }

    for(auto i : realMap){
        for(auto j : i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

void drawMap(RenderWindow& window){
    for(int i = 0; i < showingMap.size(); i++){
        for(int j = 0; j < showingMap[i].size(); j++){
            Texture texture;
            texture.loadFromFile("images.jpg");

            RectangleShape block(Vector2f(tile, tile));
            block.setPosition(j*tile, i*tile);
            block.setTexture(&texture);
            block.setTextureRect(IntRect(showingMap[i][j]*32, 0, 32, 32));

            window.draw(block);
        }
    }
}

void mineSelected(){
    for(int i = 0; i < realMap.size(); i++){
        for(int j = 0; j < realMap[i].size(); j++){
            if(realMap[i][j] == 9){
                showingMap[i][j] = realMap[i][j];
            }
        }
    }
}

void openBlank(int row, int col){
    if(showingMap[row][col] == 0){
        return;
    }
    if(realMap[row][col] != 0){
        return;
    }

    showingMap[row][col] = realMap[row][col];

    int rowMax = realMap.size()-1;
    int colMax = realMap[row].size()-1;

    if((row > 0) && (col > 0)){
        openBlank(row-1, col-1);
    }
    if(row > 0){
        openBlank(row-1, col);
    }
    if((row > 0) && (col < colMax)){
        openBlank(row-1, col+1);
    }
    if(col > 0){
        openBlank(row, col-1);
    }
    if(col < colMax){
        openBlank(row, col+1);
    }
    if((row < rowMax) && (col > 0)){
        openBlank(row+1, col-1);
    }
    if(row < rowMax){
        openBlank(row+1, col);
    }
    if((row < rowMax) && (col < colMax)){
        openBlank(row+1, col+1);
    }
}

bool checkFinish(){
    for(int i = 0; i < realMap.size(); i++){
        for(int j = 0; j < realMap[i].size(); j++){
            if((realMap[i][j] == 9) && (showingMap[i][j] != 11)){
                return false;
            }
        }
    }

    return true;
}

int main(){
    init();

    RenderWindow window(VideoMode(width, height), "minesweeper");

    // game variables
    bool clicked = false;
    bool gameover = false;

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

        if(!gameover){
            if((Mouse::isButtonPressed(Mouse::Left)) && !clicked){
                Vector2i pos = Mouse::getPosition(window);
                int row = pos.y/tile;
                int col = pos.x/tile;
                if(realMap[row][col] == 9){
                    mineSelected();
                    gameover = true;
                }else if(realMap[row][col] == 0){
                    openBlank(row, col);
                }else{
                    showingMap[row][col] = realMap[row][col];
                }
                clicked = true;
            }

            if((Mouse::isButtonPressed(Mouse::Right)) && !clicked){
                Vector2i pos = Mouse::getPosition(window);
                int row = pos.y/tile;
                int col = pos.x/tile;

                if(showingMap[row][col] == 10){
                    showingMap[row][col] = 11;
                }else if(showingMap[row][col] == 11){
                    showingMap[row][col] = 10;
                }

                gameover = checkFinish();

                clicked = true;
            }

            if(!Mouse::isButtonPressed(Mouse::Left) && !Mouse::isButtonPressed(Mouse::Right)){
                clicked = false;
            }
        }

        window.clear(Color::White);

        drawMap(window);

        window.display();
    }
}
