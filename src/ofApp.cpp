#include "iostream"
#include "ofApp.h"
#include <stdio.h>
#include <stdlib.h> // For abs();
#include <vector>

using namespace std;

glm::vec3 pacmanPosition;

std::vector<glm::vec3> obstacles = {};
std::vector<glm::vec3> coins = {};
std::vector<glm::vec3> enemies = {};

int currentDirection, previousDirection;
int screen;
int points;
int size;
int rows;
int columns;
int currentTenths;
int animationIndex;
int coinIndex;
int enemyIndex;
int characterOption;

ofImage coinSprite;
ofImage enemySprite;
ofImage block;
ofImage screenHome1;
ofImage screenHome2;
ofImage screenHome3;
ofImage screenScore;

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Initialize variables
    screen = 0;
    characterOption = 1;
    size = 25;
    
    // Load screen images
    screenHome1.load("screens/option-1.png");
    screenHome2.load("screens/option-2.png");
    screenHome3.load("screens/option-3.png");
    screenScore.load("screens/end.png");

}

void ofApp::setupGame() {
    
    // Initialize variables
    screen = 0;
    points = 0;
    rows = 31;
    columns = 21;
    currentTenths = (int)(ofGetElapsedTimeMillis() / 100);
    animationIndex = 0;
    coinIndex = 0;
    enemyIndex = 0;
    
    // Empty vectors
    obstacles.clear();
    enemies.clear();
    coins.clear();
    
    pacmanPosition.x = 10;
    pacmanPosition.y = 13;
    
    currentDirection = 1;
    previousDirection = 1;
    
    // Load images
    std::cout << characterOption << "\n";
    if (characterOption == 3) {
        ofBackground(183, 243, 245);
        characterGif.load("images/bird.gif");
        coinGif.load("images/egg.gif");
        enemyGif.load("images/pig.gif");
        block.load("images/log.png");
    } if (characterOption == 1) {
        ofBackground(247, 213, 139);
        characterGif.load("images/ash.gif");
        coinGif.load("images/pokeball.gif");
        enemyGif.load("images/goomba.gif");
        block.load("images/tree.png");
    } else {
        ofBackground(90, 143, 243);
        characterGif.load("images/mario-walking.gif");
        coinGif.load("images/coin.gif");
        enemyGif.load("images/goomba.gif");
        block.load("images/block.png");
    }
    
    // Add obstacles
    int obstacleData[] = { 0, 1, 1, 19, 1, 1, 1, 10, 0, 1, 10, 4, 1, 4, 10, 4, 0, 1, 13, 4, 0, 1, 15, 4, 1, 4, 15, 4, 0, 1, 18, 4, 1, 1, 18, 12, 0, 1, 29, 19, 1, 19, 1, 10, 0, 16, 10, 4, 1, 16, 10, 4, 0, 16, 13, 4, 0, 16, 15, 4, 1, 16, 15, 4, 0, 16, 18, 4, 1, 19, 18, 12, 0, 3, 3, 2, 0, 3, 4, 2, 0, 6, 3, 3, 0, 6, 4, 3, 1, 10, 2, 3, 0, 12, 3, 3, 0, 12, 4, 3, 0, 16, 3, 2, 0, 16, 4, 2, 0, 3, 6, 2, 0, 3, 8, 2, 1, 6, 6, 7, 0, 6, 9, 3, 0, 8, 6, 5, 1, 10, 6, 4, 1, 14, 6, 7, 0, 12, 9, 3, 0, 16, 6, 2, 0, 16, 8, 2, 0, 8, 11, 2, 0, 11, 11, 2, 1, 8, 11, 5, 1, 12, 11, 5, 0, 8, 15, 5, 1, 6, 14, 4, 1, 14, 14, 4, 0, 8, 17, 5, 1, 10, 17, 4, 0, 3, 20, 2, 1, 4, 20, 4, 0, 2, 25, 1, 1, 4, 25, 1, 0, 6, 21, 3, 1, 8, 21, 5, 1, 6, 23, 5, 0, 3, 27, 6, 1, 10, 22, 6, 0, 16, 20, 2, 1, 16, 20, 4, 0, 18, 25, 1, 1, 16, 25, 1, 0, 12, 21, 3, 1, 12, 21, 5, 1, 14, 23, 5, 0, 12, 27, 6 };
    
    // sizeof(arr)/sizeof(arr[0]) returns the true size of the array
    for (int i = 0; i < sizeof(obstacleData) / sizeof(obstacleData[0]); i += 4) {
        ofApp::createWallLine((obstacleData[i] == 0 ? 'h' : 'v'), obstacleData[i + 1], obstacleData[i + 2], obstacleData[i + 3]);
    }
    
    for (int i = 2; i < columns - 2; i++) {
        for (int j = 2; j < rows - 2; j++) {
            int hasSomething = false;
            for (glm::vec3 obstacle : obstacles) {
                if (obstacle.x == i && obstacle.y == j) hasSomething = true;
            }
            if (!hasSomething && (rand() % 5 + 1) == 3) {
                glm::vec3 newCoin;
                newCoin.x = i;
                newCoin.y = j;
                coins.push_back(newCoin);
            }
        }
    }
    
    ofApp:createEnemy(18, 28);
    
}

void ofApp::createEnemy(int x, int y) {
    glm::vec3 enemyPosition;
    enemyPosition.x = x;
    enemyPosition.y = y;
    enemies.push_back(enemyPosition);
}

//--------------------------------------------------------------
void ofApp::createWallLine(char direction, int x, int y, int length, bool obstacle){
    for (int i = 0; i < length; i++) {
        glm::vec3 newObstacle;
        int updatedX = x;
        int updatedY = y;
        if (direction == 'h') updatedX += i;
        if (direction == 'v') updatedY += i;
        newObstacle.x = updatedX;
        newObstacle.y = updatedY;
        if (obstacle) {
            obstacles.push_back(newObstacle);
        } else {
            coins.push_back(newObstacle);
        }
    }
}

//--------------------------------------------------------------
void ofApp::createCoins(char direction, int x, int y, int length){
    ofApp::createWallLine(direction, x, y, length, false);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

    switch (screen) {
        case 1:
            ofApp::drawGame();
            break;
        default:
            ofApp::drawImageScreen(screen);
            break;
    }

}

void ofApp::drawImageScreen(int index) {
    if (index == 2) {
        screenScore.draw(0, 0);
        string pointsString = std::to_string(points);
        for (int i = 0; i < pointsString.length(); i++) {
            ofImage number;
            // Convert char to string and display image
            number.load("numbers/" + string(1, pointsString.at(i)) + ".png");
            number.draw(200 + 64 * i, 305);
        }
    } else {
        switch (characterOption) {
            case 1:
                screenHome1.draw(0, 0);
                break;
            case 2:
                screenHome2.draw(0, 0);
                break;
            case 3:
                screenHome3.draw(0, 0);
                break;
        }
    }
}

void ofApp::drawGame(){
    
    // Draw Pacman
    ofApp::drawPacman();
    
    // Move Pacman, ten times per second
    // ofGetElapsedTimef(); returns a float, convert it to int
    int elapsedTenths = (int)(ofGetElapsedTimeMillis() / 100);
    if (elapsedTenths > currentTenths) {
        currentTenths++;
        ofApp::movePacman(currentDirection);
        if (currentTenths % 2 == 0) ofApp::moveEnemies();
        animationIndex++;
        if (animationIndex > characterGif.pages.size() - 1) animationIndex = 0;
        coinIndex++;
        if (coinIndex > coinGif.pages.size() - 1) coinIndex = 0;
        enemyIndex++;
        if (enemyIndex > enemyGif.pages.size() - 1) enemyIndex = 0;
    }
    
    // Make an obstacle
    for (glm::vec3 obstacle : obstacles) {
        glm::vec3 trueObstaclePosition;
        trueObstaclePosition.x = obstacle.x * size;
        trueObstaclePosition.y = obstacle.y * size;
        block.draw(trueObstaclePosition, size, size);
    }
    
    // The following fixes a bug with RGB transforming to BGR in the library
    // Source: https://forum.openframeworks.cc/t/ofimage-from-gif-displays-with-blue-tint/22989/6
    /* fix */ ofSetColor(255, 255, 255, 255);
    /* fix */ coinSprite = coinGif.pages[coinIndex];
    /* fix */ ofPixels pix = coinSprite.getPixels();
    /* fix */ coinSprite.setFromPixels(pix);
    /* fix */ enemySprite = enemyGif.pages[enemyIndex];
    /* fix */ ofPixels pix2 = enemySprite.getPixels();
    /* fix */ enemySprite.setFromPixels(pix2);
    
    // Make a coin
    int coinPadding = 5;
    for (glm::vec3 coin : coins) {
        glm::vec3 trueCoinPosition;
        trueCoinPosition.x = coin.x * size + coinPadding;
        trueCoinPosition.y = coin.y * size + coinPadding;
        coinSprite.draw(trueCoinPosition.x, trueCoinPosition.y, size - coinPadding * 2, size - coinPadding * 2);
    }
    
    // Make an enemy
    for (glm::vec3 enemy : enemies) {
        glm::vec3 trueEnemyPosition;
        trueEnemyPosition.x = enemy.x * size;
        trueEnemyPosition.y = enemy.y * size;
        enemySprite.draw(trueEnemyPosition.x, trueEnemyPosition.y, size, size);
    }
    
}

int ofApp::manhattanDistance(glm::vec3 A, glm::vec3 B) {
    return abs(A.y - B.y) + abs(A.x - B.x);
}

void ofApp::moveEnemies() {
    int minDistance = rows + columns;
    int position = -1;
    int index = 0;
    for (glm::vec3 enemy : enemies) {

        glm::vec3 up;
        up.x = enemy.x;
        up.y = enemy.y - 1;
        int manhattanDistanceUp = manhattanDistance(pacmanPosition, up);
        if (!hasCollision(up) && manhattanDistanceUp <= minDistance) {
            minDistance = manhattanDistanceUp;
            position = 0;
        }
        
        glm::vec3 right;
        right.x = enemy.x + 1;
        right.y = enemy.y;
        int manhattanDistanceRight = manhattanDistance(pacmanPosition, right);
        if (!hasCollision(right) && manhattanDistanceRight <= minDistance) {
            minDistance = manhattanDistanceRight;
            position = 1;
        }
        
        glm::vec3 down;
        down.x = enemy.x;
        down.y = enemy.y + 1;
        int manhattanDistanceDown = manhattanDistance(pacmanPosition, down);
        if (!hasCollision(down) && manhattanDistanceDown <= minDistance) {
            minDistance = manhattanDistanceDown;
            position = 2;
        }
        
        glm::vec3 left;
        left.x = enemy.x - 1;
        left.y = enemy.y;
        int manhattanDistanceLeft = manhattanDistance(pacmanPosition, left);
        if (!hasCollision(left) && manhattanDistanceLeft <= minDistance) {
            minDistance = manhattanDistanceLeft;
            position = 3;
        }

        switch (position) {
            case 0:
                enemies[index].x = up.x;
                enemies[index].y = up.y;
                break;
            case 1:
                enemies[index].x = right.x;
                enemies[index].y = right.y;
                break;
            case 2:
                enemies[index].x = down.x;
                enemies[index].y = down.y;
                break;
            case 3:
                enemies[index].x = left.x;
                enemies[index].y = left.y;
                break;
        }

        // Check for collisions
        if (
            enemies[index].x == pacmanPosition.x &&
            enemies[index].y == pacmanPosition.y
        ) screen = 2;

        index++;

    }
}

void ofApp::drawPacman() {
    // The following fixes a bug with RGB transforming to BGR in the library
    // Source: https://forum.openframeworks.cc/t/ofimage-from-gif-displays-with-blue-tint/22989/6
    /* fix */ ofSetColor(255, 255, 255, 255);
    /* fix */ ofImage img = characterGif.pages[animationIndex];
    /* fix */ ofPixels pix = img.getPixels();
    /* fix */ img.setFromPixels(pix);
    glm::vec3 truePacmanPosition;
    truePacmanPosition.x = pacmanPosition.x * size;
    truePacmanPosition.y = pacmanPosition.y * size;
    img.draw(truePacmanPosition.x, truePacmanPosition.y, size, size);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (screen == 1) {
        previousDirection = currentDirection;
        switch (key) {
            case 57356:
                // Move left
                currentDirection = 3;
                break;
            case 57357:
                // Move up
                currentDirection = 0;
                break;
            case 57358:
                // Move right
                currentDirection = 1;
                break;
            case 57359:
                // Move down
                currentDirection = 2;
                break;
        }
    } else if (screen == 0) {
        switch (key) {
            case 57356:
                // Move left
                if (characterOption != 1) {
                    characterOption -= 1;
                } else {
                    characterOption = 3;
                }
                break;
            case 57358:
                // Move right
                if (characterOption != 3) {
                    characterOption += 1;
                } else {
                    characterOption = 1;
                }
                break;
            case 13: // Enter
                ofApp::setupGame();
                screen = 1;
                break;
            case 32: // Spacebar
                ofApp::setupGame();
                screen = 1;
                break;
        }
    } else if (screen == 2) {
        ofApp::setup();
        screen = 0;
    }
}

//--------------------------------------------------------------
bool ofApp::hasCollision(glm::vec3 position){
    int collisionDetected = false;
    if (position.x < 0) collisionDetected = true;
    if (position.y < 0) collisionDetected = true;
    for (glm::vec3 obstacle : obstacles) {
        if (obstacle.x == position.x && obstacle.y == position.y) collisionDetected = true;
    }
    return collisionDetected;
}

//--------------------------------------------------------------
void ofApp::movePacman(int direction){
    glm::vec3 testPosition;
    switch (direction) {
        case 0:
            // Move Pacman up
            testPosition.x = pacmanPosition.x;
            testPosition.y = pacmanPosition.y - 1;
            break;
        case 1:
            // Move Pacman right
            testPosition.x = pacmanPosition.x + 1;
            testPosition.y = pacmanPosition.y;
            break;
        case 2:
            // Move Pacman down
            testPosition.x = pacmanPosition.x;
            testPosition.y = pacmanPosition.y + 1;
            break;
        case 3:
            // Move Pacman left
            testPosition.x = pacmanPosition.x - 1;
            testPosition.y = pacmanPosition.y;
            break;
    }
    if (
        testPosition.x < columns &&
        testPosition.y < rows &&
        testPosition.x > -1 &&
        testPosition.y > -1 &&
        !ofApp::hasCollision(testPosition)
    ) {
        pacmanPosition.x = testPosition.x;
        pacmanPosition.y = testPosition.y;
    }
    // Collect coins
    ofApp::collectCoin();
    // If you go all the way right, you reach left
    if (testPosition.x == columns) pacmanPosition.x = 0;
    if (testPosition.y == rows) pacmanPosition.y = 0;
    if (testPosition.x == -1) pacmanPosition.x = columns;
    if (testPosition.y == -1) pacmanPosition.y = rows;

}

//--------------------------------------------------------------
void ofApp::collectCoin(){
    int coinIndex = 0;
    for (glm::vec3 coin : coins) {
        if (coin.x == pacmanPosition.x && coin.y == pacmanPosition.y) {
            points++;
            coins.erase(coins.begin() + coinIndex);
            break;
        }
        coinIndex++;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // Know which "block" you've pressed on (for development)
    std::cout << (x / size) << " " << (y / size) << "\n";
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------ofSetLineWidth(1);------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
