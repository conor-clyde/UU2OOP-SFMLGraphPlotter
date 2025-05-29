#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include "graphPoints.h"
#include "Validation.h"



// Configurations
const std::string FONT_FILE = "./fonts/arial.ttf";
const int WIDTH = 1200, HEIGHT = 800;
const sf::Color BACKGROUND_COLOR(168, 168, 168);
const sf::Color AXIS_COLOR = sf::Color::Black;
const sf::Vector2f HORIZONTAL_AXIS_SIZE(900.f, 2.f);
const sf::Vector2f VERTICAL_AXIS_SIZE(700.f, 2.f);
const float HORIZONTAL_AXIS_Y_OFFSET = 60.f;

// Shared variables
std::atomic<bool> windowOpen(false);
std::atomic<bool> shouldCloseWindow(false);
std::atomic<bool> needsReload(true);
std::mutex csvMutex;

// Graph drawing functions
void drawGraph(sf::RenderWindow& window, graphPoints& graphPts, const sf::Font& font,
    const std::string& title, const std::string& xLabel, const std::string& yLabel,
    const sf::RectangleShape& horizAxis, const sf::RectangleShape& vertAxis) {
    window.clear(BACKGROUND_COLOR);
    graphPts.drawAxis(window, window.getSize(), font, title, xLabel, yLabel, horizAxis, vertAxis);
    graphPts.drawPoints(window);
    window.display();
}

void createAxisLines(sf::RectangleShape& horizAxisLine, sf::RectangleShape& vertAxisLine, sf::RenderWindow& window) {
    horizAxisLine.setSize(HORIZONTAL_AXIS_SIZE);
    horizAxisLine.setFillColor(AXIS_COLOR);
    horizAxisLine.setPosition(100.f, window.getSize().y - HORIZONTAL_AXIS_Y_OFFSET);
    vertAxisLine.setSize(VERTICAL_AXIS_SIZE);
    vertAxisLine.setFillColor(AXIS_COLOR);
    vertAxisLine.setPosition(100.f, window.getSize().y - HORIZONTAL_AXIS_Y_OFFSET);
    vertAxisLine.setRotation(-90.f);
}

void sfmlWindowThread(std::string& csvFileLoc, int& colourChoice, graphPoints& graphPts,
    sf::Font& font, std::string& graphTitle, std::string& xAxisLabel, std::string& yAxisLabel) {

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Graph");
    window.setVerticalSyncEnabled(true);
    windowOpen = true;

    sf::RectangleShape horizAxisLine, vertAxisLine;
    createAxisLines(horizAxisLine, vertAxisLine, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (shouldCloseWindow.load()) {
            window.close();
        }

        if (needsReload.load()) {
            std::string currentCSV;
            {
                std::lock_guard<std::mutex> lock(csvMutex);
                currentCSV = csvFileLoc;
            }
            graphPts.loadPoints(currentCSV, window, colourChoice, horizAxisLine, vertAxisLine);
            needsReload = false;
        }

        drawGraph(window, graphPts, font, graphTitle, xAxisLabel, yAxisLabel, horizAxisLine, vertAxisLine);
    }

    windowOpen = false;
}

void changeLabels(std::string& graphTitle, std::string& xLabel, std::string& yLabel) {
    int labelChoice = utilities::ValidRangeInt(
        "\nWhich label would you like to change?\n"
        "1: Graph Title\n"
        "2: X-axis Label\n"
        "3: Y-axis Label\n"
        "0: Return to Main Menu\n",
        0, 3
    );

    if (labelChoice == 0) return;

    std::cin.ignore();
    std::string newLabel;
    std::cout << "Enter new label: ";
    std::getline(std::cin, newLabel);

    switch (labelChoice) {
    case 1: graphTitle = newLabel; break;
    case 2: xLabel = newLabel; break;
    case 3: yLabel = newLabel; break;
    }
}

int main() {
    std::string csvFileLoc = "HeartRate.csv";
    std::string graphTitle = "Heart Rate over Time", xAxisLabel = "Time (sec.)", yAxisLabel = "Heart Rate";
    int colourChoice = 1;
    graphPoints graphPts;
    sf::Font font;

    if (!font.loadFromFile(FONT_FILE)) {
        std::cerr << "Failed to load font from " << FONT_FILE << std::endl;
        return EXIT_FAILURE;
    }

    std::thread windowThread;

    while (true) {
        int menuChoice = utilities::ValidRangeInt(
            "\nMenu:\n"
            "1: Show Graph Window\n"
            "2: Change Graph Data\n"
            "3: Change Graph Colour\n"
            "4: Change Graph Labels\n"
            "0: Exit\n",
            0, 4
        );

        if (menuChoice == 0) break;

        switch (menuChoice) {
        case 1:
            if (!windowOpen.load()) {
                windowThread = std::thread(sfmlWindowThread, std::ref(csvFileLoc), std::ref(colourChoice),
                    std::ref(graphPts), std::ref(font), std::ref(graphTitle),
                    std::ref(xAxisLabel), std::ref(yAxisLabel));
            }
            else {
                std::cout << "Window is already open!\n";
            }
            break;

        case 2:
        {
            std::string newFile = utilities::ValidLetterNumber("Please enter a valid file name...") + ".csv";
            {
                std::lock_guard<std::mutex> lock(csvMutex);
                csvFileLoc = newFile;
            }
            needsReload = true;
        }
        break;

        case 3:
            colourChoice = utilities::ValidRangeInt(
                "\nSelect a graph colour:\n"
                "1: Red\n"
                "2: Blue\n"
                "3: Yellow\n"
                "4: Green\n"
                "5: Orange\n"
                "6: Purple\n"
                "0: Return to main menu\n",
                0, 6
            );
            if (colourChoice != 0) needsReload = true;
            break;

        case 4:
            changeLabels(graphTitle, xAxisLabel, yAxisLabel);
            break;
        }
    }

    if (windowOpen.load()) {
        shouldCloseWindow = true;
    }

    if (windowThread.joinable()) {
        windowThread.join();
    }

    return 0;
}
