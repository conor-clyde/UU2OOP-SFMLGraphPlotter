//Filename: graphPoints.h
//Description: OOP Assignment 1 - Graph points header file
//Author: Conor Clyde
//Date: 26/10/21
//Last Updated: 27/10/21

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>					//sf namespace 
#include <SFML/Graphics/Font.hpp>

class graphPoints
{
private:
	std::vector<sf::CircleShape> points;
	std::vector<std::vector<std::string> > cords;

public:
	graphPoints();
	graphPoints(sf::CircleShape _shape);

	void loadPoints(std::string _fileName, sf::RenderWindow& _win, int colourChoice, sf::RectangleShape horizAxisLine, sf::RectangleShape vertAxisLine);
	void addPoint(sf::Color clr, int radius, sf::Vector2u origin, sf::Vector2f position);
	void setPointColour(int i, int choice);
	void clearPointList();
	void drawPoints(sf::RenderWindow &_win);
	void drawAxis(sf::RenderWindow& _win, sf::Vector2u winSize, sf::Font font, std::string graphTitleTxt, std::string xAxisLabelTxt, std::string yAxisLabelTxt, sf::RectangleShape horizAxisLine, sf::RectangleShape vertAxisLine);
	int getMaxYValue();
	int getMaxXValue();
	float getVertScale(sf::RectangleShape vertAxisLine);
	float getHorizScale(sf::RectangleShape vertAxisLine);
};