//Filename: main.cpp
//Description: OOP Assignment 1 - main file
//Author: Conor Clyde
//Date: 26/10/21
//Last Updated: 27/10/21

#include <iostream>                                        //std namespace
#include <SFML/Graphics.hpp>                               //sf namespace 
#include "graphPoints.h"
#include "MyVal.h"

int main()
{
	int menuChoice, labelChoice, colourChoice = 1;
	std::string csvFileLoc = "HeartRate.csv", graphTitleTxt = "Heart Rate Over Time", xAxisLabelTxt = "Time (seconds)", yAxisLabelTxt = "Heart Rate";

	//Output welcome msg
	std::cout << "Welcome to Graph Loader 3000." << std::endl << std::endl;

#pragma region Window Creation
	//Render a window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Graph", sf::Style::Default, sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);

	//Get window size
	sf::Vector2u winSize = window.getSize();

	//Load in font
	sf::Font font;

	if (!font.loadFromFile(".\\fonts\\arial.ttf"))
		return EXIT_FAILURE;

	//Define main x and y axis lines
	sf::RectangleShape horizAxisLine; sf::RectangleShape vertAxisLine;

	horizAxisLine.setFillColor(sf::Color(0, 0, 0)); horizAxisLine.setSize(sf::Vector2f(900, 2)); horizAxisLine.setPosition(100, winSize.y - 60); horizAxisLine.setRotation(0);
	vertAxisLine.setFillColor(sf::Color(0, 0, 0)); vertAxisLine.setSize(sf::Vector2f(700, 2));  vertAxisLine.setPosition(100, winSize.y - 60); vertAxisLine.setRotation(-90); // anticlockwise

#pragma endregion
	//Create graphPoints object
	graphPoints graphPts;

	//Call method to load points from the file
	graphPts.loadPoints(csvFileLoc, window, colourChoice, horizAxisLine, vertAxisLine);

	//Windows application loop - infinite loop until closed
	while (window.isOpen())
	{

#pragma region Check for Exit
		//Windows is event drive - so this checks for a close event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

#pragma endregion

		//Clear graphics buffer
		window.clear(sf::Color(168, 168, 168));

		//Calls a method to draw the graph axis and labels
		graphPts.drawAxis(window, winSize, font, graphTitleTxt, xAxisLabelTxt, yAxisLabelTxt, horizAxisLine, vertAxisLine);

		//Calls a method to draw the points to the graph
		graphPts.drawPoints(window);

		//Displays the graphics from the buffer to the display
		window.display();

		//Menu - Gets user input
		menuChoice = ccval::ValidRangeInt("1: Enter file to load\n2: Set graph colour\n3: Set graph labels\n4: Exit", 1, 4);

		switch (menuChoice)
		{
		case 1:
			//Get CSV file from user
			std::cout << "Please input the name of the file to be used.\nHint: This project comes with HeartRate.CSV and SecondFile.CSV." << std::endl;
			std::cin >> csvFileLoc;

			graphPts.loadPoints(csvFileLoc, window, colourChoice, horizAxisLine, vertAxisLine);
			break;
		case 2:
			//Get graph colour from user
			colourChoice = ccval::ValidRangeInt("Please select a graph colour by entering the corresponding number.\n1: Red \n2: Blue\n3: Yellow\n4: Green \n5: Orange\n6: Purple\n7: Return to main menu", 1, 7);
			if (colourChoice != 7)
				graphPts.loadPoints(csvFileLoc, window, colourChoice, horizAxisLine, vertAxisLine);
			break;
		case 3:
			//Ask user which label they wish to change
			labelChoice = ccval::ValidRangeInt("Which label would you like to change?\n1: Graph Title \n2: x axis label\n3: y axis labele\n4: Return to main menu", 1, 4);
			switch (labelChoice)
			{

			case 1:
				//Get graph title from user
				std::cout << "Please enter the graph title:" << std::endl;
				std::cin >> graphTitleTxt;
				break;
			case 2:
				//Get x axis label from user
				std::cout << "Please enter the x axis label:" << std::endl;
				std::cin >> xAxisLabelTxt;
				break;
			case 3:
				//Get y axis label from user
				std::cout << "Please enter the y axis label:" << std::endl;
				std::cin >> yAxisLabelTxt;
			}

			break;
		case 4:
			return 0;
		}
	}

	return 0;
}