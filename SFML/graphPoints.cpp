//Filename: graphPoints.cpp
//Description: OOP Assignment 1 - Graph points implementation file
//Author: Conor Clyde
//Date: 26/10/21
//Last Updated: 27/10/21

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "graphPoints.h"
#include "My.h"

//Constructors
graphPoints::graphPoints() {};
graphPoints::graphPoints(sf::CircleShape _shape) {};

void graphPoints::loadPoints(std::string _fileName, sf::RenderWindow& _win, int colourChoice, sf::RectangleShape horizAxisLine, sf::RectangleShape vertAxisLine)
{
	std::ifstream dataStream;
	std::string line;

#pragma region CSV File Reading
	//Open file to a data stream for readinh
	dataStream.open(_fileName);

	//Check if file opened
	if (dataStream.is_open())                                        
	{
		//Calls a method to clear point list - for if a file has already been loaded in
		clearPointList();

		//Take a peek at next data character
		char next = dataStream.peek(); 

		//If next character is not the end of file, continue to read data
		while (next != EOF)                                            
		{
			//Get line of text from file
			std::getline(dataStream, line); 

			//Create line stream
			std::stringstream lineStream(line);                                       
			std::string character;

			//2D vector - rows of point cords
			std::vector<std::string> parsedRow; 

			//Read one row at a time, and parse it to get rid of the comma
			while (std::getline(lineStream, character, ','))            
			{
				//Push one character at a time into the vector row (x and y coordinates)
				parsedRow.push_back(character);                        
			}

			//Push the parsed row into the vector list of cords
			cords.push_back(parsedRow);                                

			//Take a peek at next data character to see if it is the end of file
			next = dataStream.peek();    
		}

	}
	else
		//Error msg if the file was not found
		std::cout << "The file entered doesn't exist." << std::endl;

	dataStream.close();
#pragma endregion

#pragma region Create Graph points 
	for (int i = 0; i < cords.size(); ++i) //For number of rows in vector
	{
		//Call method to add a SFML circle object to the points vector
		addPoint(sf::Color::Red, 2, sf::Vector2u(1, 1), sf::Vector2f(0, 0));
		for (int j = 0; j < cords[j].size(); ++j) //For number of columns in vector
		{
			//Set (x, y) position for each graph circle (SFML circle object)
			//_win.getSize().y - is used to draw the y cords from the bottom of the screen
			if (j == 0) points[i].setPosition(sf::Vector2f(float(stoi(cords[i][j])), 0)); //Set x cord
			if (j == 1) points[i].setPosition(sf::Vector2f(100 + getHorizScale(horizAxisLine) * points[i].getPosition().x, _win.getSize().y - (60 + getVertScale(vertAxisLine) * float(stoi(cords[i][j]))))); //Set y cord
		}

		//Set point colour based on user's input
		setPointColour(i, colourChoice);
	}
#pragma endregion
}

void graphPoints::addPoint(sf::Color clr, int radius, sf::Vector2u origin, sf::Vector2f position)
{
	//Define SFML circle object
	sf::CircleShape pt; pt.setFillColor(clr); pt.setRadius(radius); pt.setOrigin(radius, radius); pt.setPosition(sf::Vector2f(position));

	//Add object to points vector
	points.push_back(pt);
}

void graphPoints::drawAxis(sf::RenderWindow& _win, sf::Vector2u winSize, sf::Font font, std::string graphTitleTxt, std::string xAxisLabelTxt, std::string yAxisLabelTxt, sf::RectangleShape horizAxisLine, sf::RectangleShape vertAxisLine)
{
	sf::RectangleShape horizLine; sf::RectangleShape vertLine;

	//Define and draw graph title
	sf::Text graphTitle(graphTitleTxt, font, 24); graphTitle.setFillColor(sf::Color::Black); graphTitle.setPosition(horizAxisLine.getLocalBounds().width / 2, 6);
	

	_win.draw(graphTitle);

	//Define and draw y axis label
	sf::Text yAxisLabel(yAxisLabelTxt, font, 14); yAxisLabel.setFillColor(sf::Color::Black); yAxisLabel.setPosition(50, vertAxisLine.getLocalBounds().width / 2); yAxisLabel.setOrigin(yAxisLabel.getLocalBounds().width / 2, yAxisLabel.getLocalBounds().height - 14);
	_win.draw(yAxisLabel);

	//Define and draw x axis label
	sf::Text xAxisLabel(xAxisLabelTxt, font, 14); xAxisLabel.setFillColor(sf::Color::Black); xAxisLabel.setPosition(horizAxisLine.getLocalBounds().width / 2, winSize.y - 24);
	_win.draw(xAxisLabel);

	//Draw main horizontal axis line
	_win.draw(horizAxisLine);

	//Draw main vertical axis line
	_win.draw(vertAxisLine);

	//For loop to create 10 minor horizontal graph axis lines
	for (int i = 1; i <= 10; i++)
	{
		//Define and draw axis line
		horizLine.setFillColor(sf::Color(0, 0, 0)); horizLine.setSize(sf::Vector2f(900, 1)); horizLine.setPosition(100, winSize.y - (60 + (vertAxisLine.getLocalBounds().width / 10) * i)); horizLine.setRotation(0);
		_win.draw(horizLine);

		//Define and draw axis line value label
		sf::Text yAxisValue(std::to_string((i* (ccmy::roundUp(getMaxYValue(), 10) + 20) / 10)), font, 14); yAxisValue.setFillColor(sf::Color::Black); yAxisValue.setPosition(100, winSize.y - (60 + (vertAxisLine.getLocalBounds().width/10)*i)); yAxisValue.setOrigin(yAxisValue.getLocalBounds().width + 5, yAxisValue.getLocalBounds().height / 2);
		_win.draw(yAxisValue);
	}

	//For loop to create 7 minor vertical graph axis lines
	for (int i = 1; i <= 7; i++)
	{
		//Define and draw axis line
		vertLine.setFillColor(sf::Color(0, 0, 0)); vertLine.setSize(sf::Vector2f(700, 1)); vertLine.setPosition(100 + (horizAxisLine.getLocalBounds().width / 7) * i, winSize.y - 60); vertLine.setRotation(-90);
		_win.draw(vertLine);

		//Define and draw axis line value label
		sf::Text xAxisValue(std::to_string((i * (ccmy::roundUp(getMaxXValue(), 10) + 20) / 7)), font, 14); xAxisValue.setFillColor(sf::Color::Black); xAxisValue.setPosition(100 + (horizAxisLine.getLocalBounds().width/7)* i, winSize.y - 60); xAxisValue.setOrigin(xAxisValue.getLocalBounds().width / 2, xAxisValue.getLocalBounds().height - 14);
		_win.draw(xAxisValue);
	}
}

void graphPoints::setPointColour(int i, int choice)
{
	sf::Color graphColour;

	switch (choice)
	{
	case 1:
		graphColour = sf::Color::Red;
		break;
	case 2:
		graphColour = sf::Color::Blue;
		break;
	case 3:
		graphColour = sf::Color::Yellow;
		break;
	case 4:
		graphColour = sf::Color::Green;
		break;
	case 5:
		graphColour = sf::Color(255, 165, 0);
		break;
	case 6:
		graphColour = sf::Color(160, 32, 240);
		break;
	}

	points[i].setFillColor(graphColour);
};

void graphPoints::clearPointList()
{
	points.clear();
	cords.clear();
};

void graphPoints::drawPoints(sf::RenderWindow& _win)
{
	//Loop through the points vector, and draw the points
	for (int i = 0; i < points.size(); ++i)
		_win.draw(points[i]);
}

int graphPoints::getMaxYValue()
{
	int max = 0;

	//Loop through each Y value in the cords vector and return the highest value - to help with graph scaling
	for (int i = 0; i < cords.size(); ++i) //For number of rows
	{
		for (int j = 0; j < cords[j].size(); ++j) //For number of columns
		{
			if (j == 1)
			{
				auto test = cords[i][j];
				if (stoi(cords[i][j]) > max)
					max = stoi(cords[i][j]);
			}
		}
	}

	return max;
}

int graphPoints::getMaxXValue()
{
	int max = 0;

	//Loop through each X value in the cords vector and return the highest value - to help with graph scaling
	for (int i = 0; i < cords.size(); ++i) //For number of rows
	{
		for (int j = 0; j < cords[j].size(); ++j) //For number of columns
		{
			if (j == 0)
			{
				auto test = cords[i][j];
				if (stoi(cords[i][j]) > max)
					max = stoi(cords[i][j]);
			}
		}
	}

	return max;
}

float graphPoints::getVertScale(sf::RectangleShape vertAxisLine)
{
	//Calculate the scale needed to plot the y cords in line with the graph labels
	return vertAxisLine.getLocalBounds().width / (ccmy::roundUp(getMaxYValue(), 10) + 20);
}

float graphPoints::getHorizScale(sf::RectangleShape horizAxisLine)
{
	//Calculate the scale needed to plot the x coords in line with the graph labels
	return horizAxisLine.getLocalBounds().width / (ccmy::roundUp(getMaxXValue(), 10) + 20);
}

