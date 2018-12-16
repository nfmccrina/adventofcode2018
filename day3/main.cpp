#include "../AoCFramework.hpp"
#include <regex>
#include <functional>

struct Point
{
    int X;
    int Y;

    bool operator==(const Point& p2);
    bool operator!=(const Point& p2);
};

/*
 * Original solution
struct Rectangle
{
    int X;
    int Y;
    int W;
    int H;
};

class InvalidRectangleException
{

};

bool isPointInRectangle(const Point& point, const Rectangle& rectangle);
Rectangle convertInputLineToRectangle(const std::string& line);
int compute(std::vector<std::string> lines);
std::vector<Rectangle> getRectangleList(std::vector<std::string> lines);
int totalWidth(const Rectangle& r);
int totalHeight(const Rectangle& r);
bool compareRectangles(const Rectangle& r1, const Rectangle& r2);
*/

int getFirstOfPair(const std::string& input, const std::string& delimiter);
int getSecondOfPair(const std::string& input, const std::string& delimiter);
std::vector<Point> getPointsFromClaim(const std::string& claim);
bool comparePoints(const Point& p1, const Point& p2);
int alternate_compute(std::vector<std::string> input);
std::function<bool(std::pair<int, std::vector<Point>>)> generateIncludesFunction(const Point& p);
int compute_part_two(const std::vector<std::string>& claims);

int main(int argc, char* argv[])
{
    AoCFramework<int> part1Solution {"data.txt", compute_part_two};

    part1Solution.run();

    return 0;
}

bool Point::operator==(const Point& p2)
{
    return X == p2.X && Y == p2.Y;
}

bool Point::operator!=(const Point& p2)
{
    return !(*this == p2);
}

int compute_part_two(const std::vector<std::string>& claims)
{
    std::vector<std::pair<int, std::vector<Point>>> pointsFromClaims;

    for (auto it = claims.cbegin(); it != claims.cend(); it++)
    {
        int id{0};
        std::stringstream ss;

        ss.str(*it);

        ss.ignore(1, '#');
        ss >> id;

        pointsFromClaims.push_back(std::pair<int, std::vector<Point>>(id, getPointsFromClaim(*it)));
    }

    for (auto it = pointsFromClaims.cbegin(); it != pointsFromClaims.cend(); it++)
    {
        bool isUnique {true};

        for (auto pointIt = it->second.cbegin(); pointIt != it->second.cend(); pointIt++)
        {
            auto testFunc = generateIncludesFunction(*pointIt);

            if (std::any_of(it + 1, pointsFromClaims.cend(), testFunc) ||
                std::any_of(pointsFromClaims.cbegin(), it, testFunc))
            {
                isUnique = false;
                break;
            }
        }

        if (!isUnique)
        {
            continue;
        }
        else
        {
            return it->first;
        }
    }

    return 0;
}

std::function<bool(std::pair<int, std::vector<Point>>)> generateIncludesFunction(const Point& p)
{
    return [p](const std::pair<int, std::vector<Point>>& points) { return std::binary_search(points.second.cbegin(), points.second.cend(), p, comparePoints); };
}

bool comparePoints(const Point& p1, const Point& p2)
{
    if (p1.X < p2.X)
    {
        return true;
    }
    else if (p1.X == p2.X && p1.Y < p2.Y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<Point> getPointsFromClaim(const std::string& claim)
{
    std::regex coordinateRegex { "\\d+,\\d+" };
    std::regex areaRegex { "\\d+x\\d+" };
    std::smatch regexMatch;
    int x, y, w, h;
    std::vector<Point> points;

    std::regex_search(claim, regexMatch, coordinateRegex);
    std::string coordinateString = *regexMatch.cbegin();
    x = getFirstOfPair(coordinateString, ",");
    y = getSecondOfPair(coordinateString, ",");

    std::regex_search(claim, regexMatch, areaRegex);
    coordinateString = *regexMatch.cbegin();
    w = getFirstOfPair(coordinateString, "x");
    h = getSecondOfPair(coordinateString, "x");

    for (int i = x; i < x + w; i++)
    {
        for (int j = y; j < y + h; j++)
        {
            Point p;
            p.X = i;
            p.Y = j;
            points.push_back(p);
        }
    }

    return points;
}

int alternate_compute(std::vector<std::string> input)
{
    std::vector<Point> allPoints;

    for (auto it = input.cbegin(); it != input.cend(); it++)
    {
        std::vector<Point> newSet;
        std::vector<Point> newPoints = getPointsFromClaim(*it);
        
        std::merge(
            allPoints.begin(),
            allPoints.end(),
            newPoints.begin(),
            newPoints.end(),
            std::back_inserter(newSet),
            comparePoints);

        allPoints = newSet;
    }

    auto it = allPoints.cbegin();
    int overlapCount{0};

    while (it != allPoints.cend())
    {
        Point current = *it;

        if (current != *(it + 1))
        {
            it++;
        }
        else
        {
            overlapCount++;

            while (current == *it)
            {
                it++;
            }
        }
    }

    return overlapCount;
}

int getFirstOfPair(const std::string& input, const std::string& delimiter)
{
    return std::stoi(input.substr(0, input.find(delimiter)));
}

int getSecondOfPair(const std::string& input, const std::string& delimiter)
{
    return std::stoi(input.substr(input.find(delimiter) + 1));
}

/*
 * Original solution
int compute(std::vector<std::string> lines)
{
    std::vector<Rectangle> rectangles = getRectangleList(lines);
    std::vector<int> widths(rectangles.size(), 0);
    std::vector<int> heights(rectangles.size(), 0);

    std::transform(rectangles.cbegin(), rectangles.cend(), widths.begin(), totalWidth);
    std::transform(rectangles.cbegin(), rectangles.cend(), heights.begin(), totalHeight);
    int maxWidth = *(std::max_element(widths.cbegin(), widths.cend()));
    int maxHeight = *(std::max_element(heights.cbegin(), heights.cend()));

    int overlappingArea = 0;

    for (int x = 0; x < maxWidth; x++)
    {
        for (int y = 0; y < maxHeight; y++)
        {
            int coveredCount = 0;
            Point p;
            p.X = x;
            p.Y = y;

            for (auto it = rectangles.cbegin(); it != rectangles.cend(); it++)
            {
                if (isPointInRectangle(p, *it))
                {
                    coveredCount++;
                }

                if (coveredCount > 1)
                {
                    overlappingArea++;
                    break;
                }
            }
        }
    }

    return overlappingArea;
}

bool isPointInRectangle(const Point& point, const Rectangle& rectangle)
{
    bool isInsideLaterally { point.X >= rectangle.X && point.X < (rectangle.X + rectangle.W) };
    bool isInsideVertically { point.Y >= rectangle.Y && point.Y < (rectangle.Y + rectangle.H) };

    return isInsideLaterally && isInsideVertically;
}

Rectangle convertInputLineToRectangle(const std::string& line)
{
    std::regex coordinateRegex { "\\d+,\\d+" };
    std::regex areaRegex { "\\d+x\\d+" };
    std::smatch regexMatch;
    Rectangle r;

    if (std::regex_search(line, regexMatch, coordinateRegex))
    {
        const std::string& coordinateString = *regexMatch.cbegin();
        r.X = getFirstOfPair(coordinateString, ",");
        r.Y = getSecondOfPair(coordinateString, ",");
    }
    else
    {
        throw InvalidRectangleException{};
    }

    if (std::regex_search(line, regexMatch, areaRegex))
    {
        const std::string& coordinateString = *regexMatch.cbegin();
        r.W = getFirstOfPair(coordinateString, "x");
        r.H = getSecondOfPair(coordinateString, "x");
    }
    else
    {
        throw InvalidRectangleException{};
    }

    return r;
}

std::vector<Rectangle> getRectangleList(std::vector<std::string> lines)
{
    std::vector<Rectangle> rectangles;
    rectangles.resize(lines.size());

    std::transform(lines.cbegin(), lines.cend(), rectangles.begin(), convertInputLineToRectangle);

    return rectangles;
}

int totalWidth(const Rectangle& r)
{
    return r.X + r.W;
}

int totalHeight(const Rectangle& r)
{
    return r.Y + r.H;
}

bool compareRectangles(const Rectangle& r1, const Rectangle& r2)
{
    return r1.X < r2.X;
}
*/
