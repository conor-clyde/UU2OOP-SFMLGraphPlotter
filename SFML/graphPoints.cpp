#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "graphPoints.h"
#include "common.h"

graphPoints::graphPoints() = default;
graphPoints::graphPoints(sf::CircleShape shape) {}

void graphPoints::loadPoints(const std::string& fileName, sf::RenderWindow& window, int colourChoice,
	const sf::RectangleShape& horizAxisLine, const sf::RectangleShape& vertAxisLine)
{
	std::ifstream dataStream(fileName);
	if (not dataStream.is_open()) {
		std::cerr << "Error: File \"" << fileName << "\" not found.\n";
		return;
	}

	clearPointList();
	std::string line;

	while (std::getline(dataStream, line)) {
		std::stringstream lineStream(line);
		std::vector<std::string> row;
		std::string value;

		while (std::getline(lineStream, value, ',')) {
			row.push_back(value);
		}
		if (!row.empty()) cords.push_back(row);
	}


	dataStream.close();

	for (size_t i = 0; i < cords.size(); ++i) {
		addPoint(sf::Color::Red, 2, sf::Vector2u(1, 1), sf::Vector2f(0.f, 0.f));
		float x = 0.f, y = 0.f;

		if (cords[i].size() >= 2) {
			try {
				x = std::stof(cords[i][0]);
				y = std::stof(cords[i][1]);
			}
			catch (const std::exception& e) {
				std::cerr << "Invalid data in CSV: " << e.what() << '\n';
				continue;
			}
		}

		float scaledX = 100 + getHorizScale(horizAxisLine) * x;
		float scaledY = window.getSize().y - (60 + getVertScale(vertAxisLine) * y);
		points[i].setPosition({ scaledX, scaledY });

		setPointColour(i, colourChoice);
	}


}

void graphPoints::addPoint(sf::Color clr, int radius, sf::Vector2u, sf::Vector2f position) {
	sf::CircleShape pt(radius);
	pt.setFillColor(clr);
	pt.setOrigin(radius, radius);
	pt.setPosition(position);
	points.push_back(pt);
}

void graphPoints::drawAxis(sf::RenderWindow& window, sf::Vector2u winSize, sf::Font font,
	const std::string& graphTitleTxt, const std::string& xAxisLabelTxt, const std::string& yAxisLabelTxt,
	const sf::RectangleShape& horizAxisLine, const sf::RectangleShape& vertAxisLine)
{
	auto drawText = [&](const std::string& str, unsigned size, sf::Vector2f pos, sf::Vector2f origin = sf::Vector2f(0.f, 0.f)) {
		sf::Text text(str, font, size);
		text.setFillColor(sf::Color::Black);
		text.setPosition(pos);
		text.setOrigin(origin);
		window.draw(text);
		};

	drawText(graphTitleTxt, 24, sf::Vector2f(horizAxisLine.getSize().x / 2.f, 6.f));
	drawText(yAxisLabelTxt, 14, sf::Vector2f(50.f, vertAxisLine.getSize().x / 2.f), sf::Vector2f(0.f, 7.f));
	drawText(xAxisLabelTxt, 14, sf::Vector2f(horizAxisLine.getSize().x / 2.f, static_cast<float>(winSize.y) - 24.f));

	window.draw(horizAxisLine);
	window.draw(vertAxisLine);

	float yStep = vertAxisLine.getSize().x / 10.f;
	int yMax = utilities::roundUp(getMaxYValue(), 10) + 20;

	for (int i = 1; i <= 10; ++i) {
		float yPos = static_cast<float>(winSize.y) - (60.f + yStep * i);
		sf::RectangleShape line({ 900.f, 1.f });
		line.setFillColor(sf::Color::Black);
		line.setPosition(100.f, yPos);
		window.draw(line);

		drawText(std::to_string(i * yMax / 10), 14, sf::Vector2f(95.f, yPos), sf::Vector2f(5.f, 7.f));
	}

	float xStep = horizAxisLine.getSize().x / 7.f;
	int xMax = utilities::roundUp(getMaxXValue(), 10) + 20;

	for (int i = 1; i <= 7; ++i) {
		float xPos = 100.f + xStep * i;
		sf::RectangleShape line({ 700.f, 1.f });
		line.setFillColor(sf::Color::Black);
		line.setPosition(xPos, static_cast<float>(winSize.y) - 60.f);
		line.setRotation(-90.f);
		window.draw(line);

		drawText(std::to_string(i * xMax / 7), 14, sf::Vector2f(xPos, static_cast<float>(winSize.y) - 60.f), sf::Vector2f(0.f, 7.f));
	}
}

void graphPoints::setPointColour(int index, int choice) {
	static const std::vector<sf::Color> colors = {
		sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color::Green, sf::Color(255, 165, 0), sf::Color(160, 32, 240)
	};
	if (index >= 0 && index < points.size() && choice > 0 && choice <= colors.size()) {
		points[index].setFillColor(colors[choice - 1]);
	}
}

void graphPoints::clearPointList() {
	points.clear();
	cords.clear();
}


void graphPoints::drawPoints(sf::RenderWindow& window) {
	for (const auto& point : points) {
		window.draw(point);
	}
}


int graphPoints::getMaxYValue()  {
	int maxVal = 0;
	for (const auto& row : cords) {
		if (row.size() >= 2) {
			maxVal = std::max(maxVal, std::stoi(row[1]));
		}
	}
	return maxVal;
}

int graphPoints::getMaxXValue()  {
	int maxVal = 0;
	for (const auto& row : cords) {
		if (!row.empty()) {
			maxVal = std::max(maxVal, std::stoi(row[0]));
		}
	}
	return maxVal;
}

float graphPoints::getVertScale(const sf::RectangleShape& vertAxisLine) {
	return vertAxisLine.getSize().x / (utilities::roundUp(getMaxYValue(), 10) + 20);
}

float graphPoints::getHorizScale(const sf::RectangleShape& horizAxisLine) {
	return horizAxisLine.getSize().x / (utilities::roundUp(getMaxXValue(), 10) + 20);
}
