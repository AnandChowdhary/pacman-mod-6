#include "iostream"
#include "ofApp.h"
#include <stdio.h>

using namespace std;

glm::vec3 pacmanPosition;

glm::vec3 obstacles[3];

int currentDirection, previousDirection;
int size = 25;
int rows = 30;
int columns = 20;
int currentSeconds = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    pacmanPosition.x = 0;
    pacmanPosition.y = 0;
    // Directions: 0 => up, 1 => right, 2 => down, 3 => left
    currentDirection = 1;
    previousDirection = 1;
    obstacles[0].x = 10;
    obstacles[0].y = 10;
    obstacles[1].x = 10;
    obstacles[1].y = 11;
    obstacles[2].x = 10;
    obstacles[2].y = 12;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    // Draw grid
    ofSetColor(150, 150, 150);
    ofSetLineWidth(1);
    ofNoFill();
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            glm::vec3 position;
            position.x = i * size;
            position.y = j * size;
            ofDrawRectangle(position, size, size);
        }
    }

    // Draw Pacman
    ofSetColor(150, 0, 0);
    ofFill();
    glm::vec3 truePacmanPosition;
    truePacmanPosition.x = pacmanPosition.x * size;
    truePacmanPosition.y = pacmanPosition.y * size;
    ofDrawRectangle(truePacmanPosition, size, size);

    // Move Pacman, once per second
    // ofGetElapsedTimef(); returns a float, convert it to int
    int elapsedSeconds = (int)(ofGetElapsedTimeMillis() / 100);
    if (elapsedSeconds > currentSeconds) {
        currentSeconds++;
        ofApp::movePacman(currentDirection);
    }

    // Make an obstacle
    ofSetColor(50, 50, 50);
    ofFill();
    // (sizeof(obstacles) / sizeof(obstacles[0])) is used to get the true size of the array
    for (int i = 0; i < (sizeof(obstacles) / sizeof(obstacles[0])); i++) {
        glm::vec3 trueObstaclePosition;
        trueObstaclePosition.x = obstacles[i].x * size;
        trueObstaclePosition.y = obstacles[i].y * size;
        ofDrawRectangle(trueObstaclePosition, size, size);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
}

//--------------------------------------------------------------
bool ofApp::hasCollision(glm::vec3 position){
    int collisionDetected = false;
    for (int i = 0; i < (sizeof(obstacles) / sizeof(obstacles[0])); i++) {
        if (obstacles[i].x == position.x && obstacles[i].y == position.y) collisionDetected = true;
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
        default:
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
    } else {
//        currentDirection = previousDirection;
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
