#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->font.loadFont("fonts/Kazesawa-bold.ttf", 180, true, true, true);

	this->x_noise = glm::vec3(0.f, 0.f, 0.f);
	this->y_noise = glm::vec3(0.f, 0.f, 0.f);

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	this->fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetColor(255);
	string word = "RGB";
	this->font.drawString(word, this->font.stringWidth(word) * -0.5, ofGetHeight() * -0.25 + this->font.stringHeight(word) * 0.5);
	word = "DRIFT";
	this->font.drawString(word, this->font.stringWidth(word) * -0.5, ofGetHeight() * 0.25 + this->font.stringHeight(word) * 0.5);

	this->fbo.end();

	ofSeedRandom(39);

	this->x_noise.r = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.01), 0, 1, -1, 1);
	this->x_noise.g = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.01), 0, 1, -1, 1);
	this->x_noise.b = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.01), 0, 1, -1, 1);

	this->y_noise.r = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.01), 0, 1, -1, 1);
	this->y_noise.g = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.01), 0, 1, -1, 1);
	this->y_noise.b = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.01), 0, 1, -1, 1);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex", this->fbo.getTexture(), 1);
	this->shader.setUniform3f("x_noise", this->x_noise);
	this->shader.setUniform3f("y_noise", this->y_noise);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}