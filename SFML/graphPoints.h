#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>   // sf namespace
#include <SFML/Graphics/Font.hpp>

class graphPoints
{
private:
    std::vector<sf::CircleShape> points;
    std::vector<std::vector<std::string>> cords;

public:
    graphPoints();
    graphPoints(sf::CircleShape _shape);

    // Pass strings and shapes by const reference to avoid copies and ensure signature consistency
    void loadPoints(const std::string& fileName, sf::RenderWindow& window, int colourChoice,
        const sf::RectangleShape& horizAxisLine, const sf::RectangleShape& vertAxisLine);

    void addPoint(sf::Color clr, int radius, sf::Vector2u origin, sf::Vector2f position);

    void setPointColour(int i, int choice);

    void clearPointList();

    void drawPoints(sf::RenderWindow& window);

    void drawAxis(sf::RenderWindow& window, sf::Vector2u winSize, sf::Font font,
        const std::string& graphTitleTxt, const std::string& xAxisLabelTxt, const std::string& yAxisLabelTxt,
        const sf::RectangleShape& horizAxisLine, const sf::RectangleShape& vertAxisLine);

    int getMaxYValue();
    int getMaxXValue();

    float getVertScale(const sf::RectangleShape& vertAxisLine);
    float getHorizScale(const sf::RectangleShape& horizAxisLine);
};
