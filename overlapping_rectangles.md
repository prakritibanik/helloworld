## Write a function to find the rectangular intersection of two given rectangles.

The rectangles are always "straight" and never "diagonal." More rigorously: each side is parallel with either the x-axis or the y-axis.

### The Rectangle Class C++
```c++
include <iostream>
#include <algorithm>
// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

class Rectangle
{
private:
    // coordinates of bottom left corner
    int leftX_;
    int bottomY_;

    // dimensions
    int width_;
    int height_;

public:
    Rectangle() :
        leftX_(0),
        bottomY_(0),
        width_(0),
        height_(0)
    {
    }

    Rectangle(int leftX, int bottomY, int width, int height) :
        leftX_(leftX),
        bottomY_(bottomY),
        width_(width),
        height_(height)
    {
    }

    int getLeftX() const
    {
        return  leftX_;
    }

    int getBottomY() const
    {
        return  bottomY_;
    }

    int getWidth() const
    {
        return  width_;
    }

    int getHeight() const
    {
        return  height_;
    }

    bool operator==(const Rectangle& other) const
    {
        return
            leftX_ == other.leftX_
            && bottomY_ == other.bottomY_
            && width_ == other.width_
            && height_ == other.height_;
    }

    bool operator!=(const Rectangle& other) const
    {
        return !(*this == other);
    }
};

ostream& operator<<(ostream& os, const Rectangle& rect)
{
    os  << "(leftX: " << rect.getLeftX() << ", bottomY: " << rect.getBottomY()
        << ", width: " << rect.getWidth() << ", height: " << rect.getHeight() << ")";
    return os;
}
```

### Solution 1
```c++
bool findOverlap(int point1, int length1, int point2, int length2, int& p, int& length)
{
    p = 0;
    length = 0;
    bool overlap = false;
    if (point1 <= point2 && point2 < point1 + length1)
    {
        int min_len = std::min(point1+length1, point2+length2);
        p = point2;
        length = min_len - p;
        overlap = true;
    }
    return overlap;
}

Rectangle findRectangularOverlap(const Rectangle& rect1, const Rectangle& rect2)
{
    // calculate the overlap between the two rectangles
    int x=0, y=0, w=0, h=0;
    bool vertical = false;
    if (rect1.getLeftX() <= rect2.getLeftX()) {
        if (findOverlap(rect1.getLeftX(), rect1.getWidth(), rect2.getLeftX(), rect2.getWidth(), x, w)) {
            vertical = findOverlap(rect1.getBottomY(), rect1.getHeight(),
                                    rect2.getBottomY(), rect2.getHeight(), y, h);
        }
    } else {
        if (findOverlap(rect2.getLeftX(), rect2.getWidth(), rect1.getLeftX(), rect1.getWidth(), x, w)) {
            vertical = findOverlap(rect2.getBottomY(), rect2.getHeight(),
                                    rect1.getBottomY(), rect1.getHeight(), y, h);
        }
    }
    if (!vertical) {
        x = 0;
        w = 0;
    }
    Rectangle rect(x, y, w, h);
    return rect;
}
```
The above solution seems a little messy. We are calling findOverlap twice. Lets make it little more simpler in next solution
### Solution 2
```c++
bool findOverlap(int point1, int length1, int point2, int length2, int& p, int& length)
{
    p = 0;
    length = 0;
    bool overlap = false;
    int maxStart = std::max(point1, point2);
    int minEnd = std::min(point1+length1, point2+length2);
    if (maxStart < minEnd)
    {
        p = maxStart;
        length = minEnd - maxStart;
        overlap = true;
    }
    return overlap;
}

Rectangle findRectangularOverlap(const Rectangle& rect1, const Rectangle& rect2)
{
    // calculate the overlap between the two rectangles
    int x=0, y=0, w=0, h=0;
    bool vertical = false;
    
    if (findOverlap(rect1.getLeftX(), rect1.getWidth(), rect2.getLeftX(), rect2.getWidth(), x, w)) {
        vertical = findOverlap(rect1.getBottomY(), rect1.getHeight(),
                                    rect2.getBottomY(), rect2.getHeight(), y, h);
    }
    
    if (!vertical) {
        x = 0;
        w = 0;
    }
    Rectangle rect(x, y, w, h);
    return rect;
}
```

Some test cases for the above
```c++
// tests

const lest::test tests[] = {
    CASE("Overlap along both axes") {
        const Rectangle rect1(1, 1, 6, 3);
        const Rectangle rect2(5, 2, 3, 6);
        const Rectangle expected(5, 2, 2, 2);
        const Rectangle actual = findRectangularOverlap(rect1, rect2);
        EXPECT(actual == expected);
    },
    CASE("One rectangle inside another") {
        const Rectangle rect1(1, 1, 6, 6);
        const Rectangle rect2(3, 3, 2, 2);
        const Rectangle expected(3, 3, 2, 2);
        const Rectangle actual = findRectangularOverlap(rect1, rect2);
        EXPECT(actual == expected);
    },
    CASE("Both rectangles the same") {
        const Rectangle rect1(2, 2, 4, 4);
        const Rectangle rect2(2, 2, 4, 4);
        const Rectangle expected(2, 2, 4, 4);
        const Rectangle actual = findRectangularOverlap(rect1, rect2);
        EXPECT(actual == expected);
    },
    CASE("Touch on horizontal edge") {
        const Rectangle rect1(1, 2, 3, 4);
        const Rectangle rect2(2, 6, 2, 2);
        const Rectangle expected(0, 0, 0, 0);
        const Rectangle actual = findRectangularOverlap(rect1, rect2);
        EXPECT(actual == expected);
    },
    CASE("Touch on vertical edge") {
        const Rectangle rect1(1, 2, 3, 4);
        const Rectangle rect2(4, 3, 2, 2);
        const Rectangle expected(0, 0, 0, 0);
        const Rectangle actual = findRectangularOverlap(rect1, rect2);
        EXPECT(actual == expected);
    },
    CASE("Touch at a corner") {
        const Rectangle rect1(1, 1, 2, 2);
        const Rectangle rect2(3, 3, 2, 2);
        const Rectangle expected(0, 0, 0, 0);
        const Rectangle actual = findRectangularOverlap(rect1, rect2);
        EXPECT(actual == expected);
    },
    CASE("No overlap") {
        const Rectangle rect1(1, 1, 2, 2);
        const Rectangle rect2(4, 6, 3, 6);
        const Rectangle expected(0, 0, 0, 0);
        const Rectangle actual = findRectangularOverlap(rect1, rect2);
        EXPECT(actual == expected);
    },
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
```

### The Python class

The Rectangle class looks like
```python

my_rectangle = {

    # Coordinates of bottom-left corner
    'left_x'   : 1,
    'bottom_y' : 1,

    # Width and height
    'width'    : 6,
    'height'   : 3,

}
```
### Solution
```python
def find_range_overlap(point1, length1, point2, length2):
    # Find the highest start point and lowest end point.
    # The highest ("rightmost" or "upmost") start point is
    # the start point of the overlap.
    # The lowest end point is the end point of the overlap.
    highest_start_point = max(point1, point2)
    lowest_end_point = min(point1 + length1, point2 + length2)

    # Return null overlap if there is no overlap
    if highest_start_point >= lowest_end_point:
        return (None, None)

    # Compute the overlap length
    overlap_length = lowest_end_point - highest_start_point

    return (highest_start_point, overlap_length)


def find_rectangular_overlap(rect1, rect2):
    # Get the x and y overlap points and lengths
    x_overlap_point, overlap_width  = find_range_overlap(rect1['left_x'],
                                                         rect1['width'],
                                                         rect2['left_x'],
                                                         rect2['width'])
    y_overlap_point, overlap_height = find_range_overlap(rect1['bottom_y'],
                                                         rect1['height'],
                                                         rect2['bottom_y'],
                                                         rect2['height'])

    # Return null rectangle if there is no overlap
    if not overlap_width or not overlap_height:
        return {
            'left_x'   : None,
            'bottom_y' : None,
            'width'    : None,
            'height'   : None,
        }

    return {
        'left_x'   : x_overlap_point,
        'bottom_y' : y_overlap_point,
        'width'    : overlap_width,
        'height'   : overlap_height,
    }
```
