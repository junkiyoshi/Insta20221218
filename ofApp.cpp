#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->mesh.clear();

	ofColor color;
	auto noise_seed = ofRandom(1000);
	for (int i = 0; i < 4; i++) {

		for (int x = 0; x <= ofGetWindowWidth(); x += 5) {

			auto base_y = ofNoise(noise_seed, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002) * 820 - 100;
			
			auto y = base_y + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -50, 50);
			this->mesh.addVertex(glm::vec3(x, y, 0));

			color.setHsb(ofMap(x, 0, ofGetWindowWidth(), 0, 255), 200, 255);
			this->mesh.addColor(color);
		}
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto min_distance = 30;
		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			float distance = glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k));
			if (distance < 30) {

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);

				if (distance < min_distance) {

					min_distance = distance;
				}
			}
		}

		this->mesh.setColor(i, ofColor(this->mesh.getColor(i), ofMap(min_distance, 0, 30, 255, 0)));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.drawWireframe();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawCircle(this->mesh.getVertex(i), 2);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}