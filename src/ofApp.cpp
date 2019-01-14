#include "iostream"
#include "ofApp.h"
#include <stdio.h>

glm::vec3 pacmanPosition;
int currentDirection;
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
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
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
void ofApp::movePacman(int direction){
    switch (direction) {
        case 0:
            // Move Pacman up
            if (pacmanPosition.y > 0) pacmanPosition.y--;
            break;
        case 1:
            // Move Pacman right
            if (pacmanPosition.x < (columns - 1)) pacmanPosition.x++;
            break;
        case 2:
            // Move Pacman down
            if (pacmanPosition.y < (rows - 1)) pacmanPosition.y++;
            break;
        default:
            // Move Pacman left
            if (pacmanPosition.x > 0) pacmanPosition.x--;
            break;
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
