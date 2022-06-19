#include <iostream>
//  g++ chess.cpp  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app
#include <string>
#include <fstream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
// int* getindex(int x, int y){
//     int positionindex[1] ;
//     positionindex[0] = (x-(x%80))/80;
//     positionindex[1] = (y-(y%80))/80;
//     return positionindex;
//  }
class keys {
public:
    int x = 9;
    int y = 9;
    int team;
    
    Texture texturekey;
    Sprite spritekey;
    enum keytypes { king, queen, bishop, knight, rook, pawn, empt };
    keytypes keytype;
    string keyname;
    void move(int i, int j) {
        x = i;
        y = j;
    }
    // void checkmove(){
    //     cout << "Im in keys" << endl;
    // }

};
class point {
public:
    keys* mohre;
};
class King : public keys {
public:
    King(int t) {
        team = t;
        keytype = king;
        if (team == 1) {
            keyname = "KW";
            texturekey.loadFromFile("texture/set800/wking.png", IntRect(0, 0, 100, 100));
        }
        else {
            texturekey.loadFromFile("texture/set800/bking.png", IntRect(0, 0, 100, 100));
            keyname = "KB";
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*75), (y*75)));
        
    }
};
class Queen : public keys {
public:
    Queen(int t) {
        team = t;
        keytype = queen;
        if (team == 1) {
            keyname = "QW";
            texturekey.loadFromFile("texture/set800/wqueen.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "QB";
            texturekey.loadFromFile("texture/set800/bqueen.png", IntRect(0, 0, 100, 100));
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*75), (y*75)));
    }
    // int checkmove(int i, int j) {

    // }
};
class Bishop : public keys {
public:
    Bishop(int t) {
        team = t;
        keytype = bishop;
        if (team == 1) {
            keyname = "BW";
            texturekey.loadFromFile("texture/set800/wbishop.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "BB";
            texturekey.loadFromFile("texture/set800/bbishop.png", IntRect(0, 0, 100, 100));
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*75), (y*75)));
    }
    // int checkmove(int i, int j) {

    // }
};
class Knight : public keys {
public:
    Knight(int t) {
        team = t;
        keytype = knight;
        if (team == 1) {
            keyname = "NW";
            texturekey.loadFromFile("texture/set800/wknight.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "NB";
            texturekey.loadFromFile("texture/set800/bknight.png", IntRect(0, 0, 100, 100));
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*75), (y*75)));
    }
    int checkmove(int i, int j) {
        if ((abs(i * j) == 2)) {
            return 1;
        }
    }
};
class Rook : public keys {
public:
    Rook(int t) {
        team = t;
        keytype = rook;
        if (team == 1) {
            keyname = "RW";
            texturekey.loadFromFile("texture/set800/wrook.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "RB";
            texturekey.loadFromFile("texture/set800/brook.png", IntRect(0, 0, 100, 100));
        }
        spritekey.setTexture(texturekey);
        spritekey.setPosition(Vector2f((x*100), (y*100)));
    }
    // int checkmove(int i, int j) {


    // }
};
class Pawn : public keys {
public:
    Pawn(int t) {
        team = t;
        keytype = pawn;
        if (team == 1) {
            keyname = "PW";
            texturekey.loadFromFile("texture/set800/wpawn.png", IntRect(0, 0, 100, 100));
        }
        else {
            keyname = "PB";
            texturekey.loadFromFile("texture/set800/bpawn.png", IntRect(0, 0, 100, 100));
        }
    }
    /*int checkmove(int i, int j) {
        if (board.cellckeck(i, j) == team) {
            return 0;
        }
        if (abs(x - i) == 1 && (y - j) == 1) {
            if (board.cellckeck(i, j) == 0) {
                return 0;
            }
        }
        if (abs(x - i) == 0 && (y - j) == 1)
            return 0;
    }*/
};
class Empty : public keys {
public:
    Empty() {
        team = 0;
        keytype = empt;
        keyname = "--";
    }

};
class selectedCells{
public:
    int x, y;

    selectedCells(int x1, int y1){
        x = x1 * 100 + 10; 
        y = y1 * 100 + 10;



    }
};
class defboard {
public:
    int mouseclicked = 0;
    int mousex = 0;
    int mousey = 0;
    defboard() {
        board = new point * [8];
        for (int i = 0; i < 8; i++) {
            board[i] = new point[8];
        }
    }
    point** board;
    void printchess() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << board[i][j].mohre->keyname << " ";
            }
            cout << '\n';
        }
        cout << '\n';
    }
    void move(int i, int j, int x, int y) {
        // if (board[x][y].mohre->team == board[i][j].mohre->team) {
        //     cout << "Cant do that" << endl;
        // }
        // else {
        //board[i][j].mohre->x = x;
        //board[i][j].mohre->y = y;
        cout << board[i][j].mohre->keyname << " -> " << board[y][x].mohre->keyname << endl;
        board[y][x].mohre = board[i][j].mohre;
        board[i][j].mohre = new Empty;
    }
    vector<vector<int>> checkmove(int x, int y) {
        int temp_ckeck_empty;
        vector<vector<int>> accessible (8, vector<int>(8,0));
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                temp_ckeck_empty = 1;
                if(board[i][j].mohre->team != board[x][y].mohre->team){
                    if (board[x][y].mohre->keytype == keys::king){
                        if ((abs(x - i) < 2 and abs(y - j) < 2)){
                            accessible[i][j] = 1;
                        }
                    }
                    else if (board[x][y].mohre->keytype == keys::queen){

                    }
                    else if (board[x][y].mohre->keytype == keys::rook){
                        if (x == i){
                            if (y > j){
                                for (int l = y-1; l > j; l--){
                                    if (board[x][l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            else if (y < j){
                                for (int l = y+1; l < j; l++){
                                    if (board[x][l].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                        }
                        else if (y == j){
                            if (x > i){
                                for (int l = x-1; l > i; l--){
                                    if (board[l][y].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            if (x < i){
                                for (int l = x+1; l < i; l++){
                                    if (board[l][y].mohre->keytype != keys::empt){
                                        temp_ckeck_empty = 0;
                                        // if (board[i][y].mohre->team != board[x][y].mohre->team){
                                        //     temp_ckeck_empty = 1;
                                        // }
                                        break;
                                    }
                                }
                                if (temp_ckeck_empty == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            
                        }
                    }
                    else if (board[x][y].mohre->keytype == keys::knight){

                    }
                    else if (board[x][y].mohre->keytype == keys::bishop){
                        if (abs(x-i) == abs(y-j)){
                            if (x < i){
                                if (y < j){
                                    for (int l = 1; l < i-x; l++){
                                        if (board[x+l][y+l].mohre->keytype != keys::empt){
                                            temp_ckeck_empty = 0;
                                            break;
                                        }
                                    }
                                }
                                else if ( y > j){
                                    for (int l = 1; l < i-x; l++){
                                        if (board[x+l][y-l].mohre->keytype != keys::empt){
                                            temp_ckeck_empty = 0;
                                            break;
                                        }
                                    }
                                }
                            }
                            else if (x > i){
                                if (y < j){
                                    for (int l = 1; l < x-i; l++){
                                        if (board[x-l][y+l].mohre->keytype != keys::empt){
                                            temp_ckeck_empty = 0;
                                            break;
                                        }
                                    }
                                }
                                else if ( y > j){
                                    for (int l = 1; l < x-i; l++){
                                        if (board[x-l][y-l].mohre->keytype != keys::empt){
                                            temp_ckeck_empty = 0;
                                            break;
                                        }
                                    }
                                }
                            }
                            if (temp_ckeck_empty == 1){
                                accessible[i][j] = 1;
                            }
                        }

                    }
                    else if (board[x][y].mohre->keytype == keys::pawn){
                        if (board[x][y].mohre->team == 1){
                            if (board[i][j].mohre->team == 2 and (x - i == 1)){
                                if (abs(y - j) == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            else{
                                if (x == 6){
                                    if (y == j and (i == 5 or i == 4)){
                                        accessible[i][j] = 1;
                                    }
                                }
                                else if(x != 6 and y == j and x-i == 1){
                                        accessible[i][j] = 1;
                                    }
                                }
                            }
                        else if (board[x][y].mohre->team == 2){
                            if (board[i][j].mohre->team == 1 and (i - x == 1)){
                                if (abs(y - j) == 1){
                                    accessible[i][j] = 1;
                                }
                            }
                            else{
                                if (x == 1){
                                    if (y == j and (i == 3 or i == 2)){
                                        accessible[i][j] = 1;
                                    }
                                }
                                else if(x != 1 and y == j and i-x == 1){
                                        accessible[i][j] = 1;
                                }
                            }
                        }
                    }
                }
                cout << accessible[i][j] << " ";
            }
            cout << endl;
        }
        return accessible;
    }
        
    // void mousemove(Vector2i mousestate){
    //     int tx = mousestate.y;
    //     int ty = mousestate.x;
    //     mousex = (tx-(tx%100))/100;
    //     mousey = (ty-(ty%100))/100;
    //     selectedCells selectedcell(mousex, mousey);
    //     cout << mousex << "-" << mousey << endl;
    //     }
        // else {
        //     mouseclicked = 0;
        //     move (mousex , mousey , ((tx-(tx%100))/100), ((ty-(ty%100))/100));W
    // int cellckeck(int i, int j) {
    //     if (board[i][j].keytype == 0) {
    //         return 0;
    //     }
    //     if (board[i][j].team == 1) {
    //         return 1;
    //     }
    //     if (board[i][j].team == 2) {
    //         return 2;
    //     }
    // }

};
class GraphicCore{
public:
    void runGraphic(defboard myboard){
        RenderWindow window(VideoMode(800 ,800), "My Chess :)", Style::Titlebar | Style::Close);
        //CircleShape shape(50);
        window.setFramerateLimit(60);
        Texture textureboard;
        textureboard.loadFromFile("texture/set800/boardblue.jpg", IntRect(0, 0, 800, 800));
        Sprite spriteboard;
        spriteboard.setTexture(textureboard);
        RectangleShape selectioncell1(Vector2f((86), (86)));
        selectioncell1.setOutlineThickness(7);
        selectioncell1.setOutlineColor(Color(0, 255, 0, 255));
        selectioncell1.setFillColor(Color(0, 0, 0, 0));
        selectioncell1.setPosition(Vector2f((1900), (1900)));
        Texture temp4; 
        vector<vector<int>> accessible_cells;
        Sprite temp4sprite;
        // CircleShape accessible_cell(25);
        // accessible_cell.setFillColor(Color(0, 250, 0, 170));
        // accessible_cell.setPosition(Vector2f((3*100 + 25), (3*100 + 25)));
        int temp2[4];
        int mousecounter = 0;
        int tempmousex;
        int tempmousey;
        //cout << myboard[0][0].mohre->keyname << endl;
        while (window.isOpen()){
            Event event;
            window.clear();
            window.draw(spriteboard);
            while (window.pollEvent(event))
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::MouseButtonPressed){
                    if (Mouse::isButtonPressed(Mouse::Left)){
                        Vector2i mousestate = Mouse::getPosition(window);
                        int mousey = (mousestate.x-(mousestate.x%100))/100;
                        int mousex = (mousestate.y-(mousestate.y%100))/100;
                        cout << mousex << " " << mousey << endl;
                        if ((mousex >= 0 and mousex < 8) and ( mousey >= 0 and mousey < 8)){
                            //cout << "Enter 1" << endl;
                            if (mousecounter == 0){
                                //cout << "Enter 2" << endl;
                                if (myboard.board[mousex][mousey].mohre->keyname != "--"){
                                    //cout << "Enter 3" << endl;
                                    selectioncell1.setPosition(Vector2f((mousey*100 + 7), (mousex*100 + 7)));
                                    mousecounter = 1;
                                    tempmousex = mousex;
                                    tempmousey = mousey;
                                    cout << "cell selected" << endl;
                                    accessible_cells = myboard.checkmove(mousex, mousey);
                                }
                            }
                            else {
                                //cout << "Enter 4" << endl;
                                if (tempmousex != mousex or tempmousey != mousey){
                                    //cout << "Enter 5" << endl;
                                    cout << tempmousex << " " << tempmousey << " -> " << mousey << " " << mousex << endl;
                                    myboard.move(tempmousex, tempmousey, mousey, mousex);
                                    cout << "end of move" << endl;
                                    mousecounter = 0;
                                    selectioncell1.setPosition(Vector2f((1900), (1900)));
                                    // int temp5;
                                    // cin >> temp5;
                                    // cout << "next move" << endl;
                                }
                            }
                        }
                    }
                    if (Mouse::isButtonPressed(Mouse::Right)){
                        mousecounter = 0;
                        selectioncell1.setPosition(Vector2f((1900), (1900)));
                        myboard.printchess();
                    }
                }
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    if ( myboard.board[i][j].mohre->keyname != "--"){
                        temp4 = myboard.board[i][j].mohre->texturekey;
                        temp4sprite.setTexture(temp4);
                        temp4sprite.setPosition(Vector2f((j*100), (i*100)));
                        window.draw(temp4sprite);
                    }
                }
            }
            if (mousecounter == 1){
                for (int i = 0; i < 8; i++){
                    for (int j = 0; j < 8; j++){
                        if (accessible_cells[i][j] == 1){
                            CircleShape accessible_cell(25);
                            accessible_cell.setFillColor(Color(0, 255, 0, 200));
                            accessible_cell.setPosition(Vector2f((j*100 + 25), (i*100 + 25)));
                            window.draw(accessible_cell);
                        }
                    }
                }
            }
            window.draw(selectioncell1);
            window.display();
            // cout << "Enter the key origin and destination. for example: i j x y" << endl;
            // for (int i = 0; i < 4; i++) {
            //     cin >> temp2[i];
            // }
            // myboard.move(temp2[0]-1, temp2[1]-1, temp2[2]-1, temp2[3]-1);
            // myboard.printchess();
        }
    }

};
int main() {
    cout << " -- starting -- \n";
    defboard mainboard;
    ifstream inputFile;
    inputFile.open("input.text");
    if (!inputFile){
        cout << "we fucked up :(" << endl;
    }
    string temp_input;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            inputFile >> temp_input;
            if (temp_input == "--") {
                mainboard.board[i][j].mohre = new Empty;
            }
            else if (temp_input[0] == 'K') {
                if (temp_input[1] == 'W') {
                    mainboard.board[i][j].mohre = new King(1);
                }
                else {
                    mainboard.board[i][j].mohre = new King(2);
                }
            }
            else if (temp_input[0] == 'Q') {
                if (temp_input[1] == 'W') {
                    mainboard.board[i][j].mohre = new Queen(1);
                }
                else {
                    mainboard.board[i][j].mohre = new Queen(2);
                }
            }
            else if (temp_input[0] == 'B') {
                if (temp_input[1] == 'W') {
                    mainboard.board[i][j].mohre = new Bishop(1);
                }
                else {
                    mainboard.board[i][j].mohre = new Bishop(2);
                }
            }

            else if (temp_input[0] == 'N') {
                if (temp_input[1] == 'W') {
                    mainboard.board[i][j].mohre = new Knight(1);
                }
                else {
                    mainboard.board[i][j].mohre = new Knight(2);
                }
            }
            else if (temp_input[0] == 'R') {
                if (temp_input[1] == 'W') {
                    mainboard.board[i][j].mohre = new Rook(1);
                }
                else {
                    mainboard.board[i][j].mohre = new Rook(2);
                }
            }
            else if (temp_input[0] == 'P') {
                if (temp_input[1] == 'W') {
                    mainboard.board[i][j].mohre = new Pawn(1);
                }
                else {
                    mainboard.board[i][j].mohre = new Pawn(2);
                }
            }
            mainboard.board[i][j].mohre->x = i;
            mainboard.board[i][j].mohre->y = j;
        }
    }
    cout << '\n';
    GraphicCore maingraphics;
    maingraphics.runGraphic(mainboard);
    // int temp2[4];
    //cout << "Enter the key origin and destination. for example: i j x y" << endl;
    // while (1) {
    //     for (int i = 0; i < 4; i++) {
    //         cin >> temp2[i];
    //     }
    //     cout << "Enter the key origin and destination. for example: i j x y" << endl;
    //     mainboard.move(temp2[0]-1, temp2[1]-1, temp2[2]-1, temp2[3]-1);
    //     mainboard.printchess();
    //     maingraphics.runGraphic(mainboard.board);
    // }
    cout << "end of program" << endl;
    return 0;
}