#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

// Class point
struct Point
{
    double x;
    double y;

    Point(double x, double y):x(x),y(y){};

    bool operator<(const Point& other)const{
        if (x != other.x) return x < other.x; // by x
        return y < other.y;                   // otherwise by y
    }
};

// Add distance function
double distance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

// Recursive function
double closestPair(vector<Point>& points, int left, int right) {
    // Base case: 1 or 2 points
    if (right - left <= 1) {
        return INFINITY;  // Not enough points for a pair
    }
    if (right - left == 2) {
        return distance(points[left], points[left + 1]);
    }

    if (right - left == 3) {
        double d1 = distance(points[left], points[left + 1]);
        double d2 = distance(points[left + 1], points[left + 2]);
        double d3 = distance(points[left], points[left + 2]);
        return min({d1, d2, d3});
    }
    
    // Divide
    int mid = (left + right) / 2; // Middle index of points list
    double midX = points[mid].x; // Position of middle point* on graph {(1,2),(3,2)...(2,4)*...(1.2),(2,3)}
    
    // Conquer
    double dLeft = closestPair(points, left, mid); // recursive t(n/2) for finding closest in left side 
    double dRight = closestPair(points, mid, right); // recursive t(n/2) for finding closest in right side
    double d = min(dLeft, dRight); // the minimal point from these
    
    /*
    if a point is farther than d from the line, any pair crossing the line would be farther than d.
    */
    // Combine (strip check)
    vector<Point> strip;
    for (int i = left; i < right; i++) { // loop from left index to right {...(1,2)....(2.3)...}
        if (abs(points[i].x - midX) < d) { // if the point x of middle point (x,y) less then minimum distans add to strip
            strip.push_back(points[i]);
        }
    }
    
    /*
    now time check the point vertically on y axis
    For each point, you only need to check the next 6-7 points
    Geometry proof: In a d × d square, there can be at most 6-7 points. Any point farther in y would have distance > d.
    */
    sort(strip.begin(), strip.end(),
         [](const Point& a, const Point& b) { return a.y < b.y; }); // sorting the the strp by y axis.
    
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++) {
            d = min(d, distance(strip[i], strip[j]));
        }
    }
    
    return d;
}

int main() {
    int size;
    cin >> size;
    
    vector<Point> points;
    points.reserve(size);
    
    for (int i = 0; i < size; i++) {
        double x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    
    sort(points.begin(), points.end());
    
    double result = closestPair(points, 0, points.size());
    
    cout.precision(6); // the persicsion of dobule printing out 1.0000000000
    cout << fixed << result << endl;
    
    return 0;
}
