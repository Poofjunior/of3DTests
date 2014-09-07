/**
 * point.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014 to August 3, 2014
 */

#ifndef POINT_HPP 
#define POINT_HPP 

/**
 * \class Point
 * \brief a mini class of basically just coordinates
 */
class Point {
    public:
        Point(float x = 0, float y = 0, bool lineTo = false);
        ~Point();
        bool operator==(const Point& otherPoint); ///< overload equality
        float x_;
        float y_;
    };
#endif // POINT_HPP 
