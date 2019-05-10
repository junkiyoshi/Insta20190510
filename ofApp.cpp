#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(2);
	ofSetCircleResolution(72);

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<pair<glm::vec2, float>> circles;
	circles.push_back(make_pair(glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5), 250));
	for (int i = 0; i < 20; i++) {

		auto location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, ofGetHeight()));
		auto radius = ofRandom(30, 60);

		auto circle = make_pair(location, radius);
		circles.push_back(circle);
	}

	for (auto circle : circles) {

		ofNoFill();
		ofDrawCircle(circle.first, circle.second);
		for (auto other : circles) {

			if (circle == other) { continue; }

			double theta, a;
			if (this->calculate_angle(circle.first, circle.second, other.first, other.second, theta, a)) {

				auto point_1 = circle.first + glm::vec2(circle.second * cos(theta + a), circle.second * sin(theta + a));
				auto point_2 = circle.first + glm::vec2(circle.second * cos(theta - a), circle.second * sin(theta - a));

				ofFill();
				ofDrawCircle(point_1, 7);
				ofDrawCircle(point_2, 7);
			}
		}
	}
	
}

//--------------------------------------------------------------
bool ofApp::calculate_angle(glm::vec2 location_1, float radius_1, glm::vec2 location_2, float radius_2, double& theta, double& a) {

	auto distance = glm::distance(location_1, location_2);
	if (distance > radius_1 + radius_2 || distance < radius_1 - radius_2) { return false; }

	theta = atan2(location_2.y - location_1.y, location_2.x - location_1.x);
	auto cos_a = (pow(distance, 2) + pow(radius_1, 2) - pow(radius_2, 2)) / (2 * distance * radius_1);
	a = acos(cos_a);
	return true;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}