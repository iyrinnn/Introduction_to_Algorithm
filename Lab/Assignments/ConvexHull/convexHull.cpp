#include <bits/stdc++.h>
using namespace std;

struct Point
{
    double x;
    double y;
};

int orientation(const Point &a, const Point &b, const Point &c)
{
    double val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

double distSq(const Point &a, const Point &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

const Point &nextToTop(vector<Point> &st)
{
    return st[st.size() - 2];
}

vector<Point> findConvexHull(vector<Point> points)
{
    int n = points.size();
    if (n < 3)
    {
        Point p;
        p.x = -1;
        p.y = -1;
        vector<Point> res;
        res.push_back(p);
        return res;
    }

    int idx = 0;
    for (int i = 1; i < n; ++i)
    {
        if (points[i].y < points[idx].y ||
            (points[i].y == points[idx].y && points[i].x < points[idx].x))
        {
            idx = i;
        }
    }

    swap(points[0], points[idx]);
    Point p0 = points[0];

    sort(points.begin() + 1, points.end(), [p0](Point &a, Point &b)
         {
             int o = orientation(p0, a, b);
             if (o == 0)
             {
                 return distSq(p0, a) < distSq(p0, b);
             }
             return o == 1; });

    vector<Point> filtered;
    filtered.reserve(points.size());
    filtered.push_back(points[0]);
    for (int i = 1; i < n; ++i)
    {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
        {
            ++i;
        }
        filtered.push_back(points[i]);
    }

    int m = filtered.size();
    if (m < 3)
    {
        Point p;
        p.x = -1;
        p.y = -1;
        vector<Point> res;
        res.push_back(p);
        return res;
    }

    vector<Point> st;
    st.reserve(m);
    st.push_back(filtered[0]);
    st.push_back(filtered[1]);
    st.push_back(filtered[2]);

    for (int i = 3; i < m; ++i)
    {
        while (st.size() > 1 &&
               orientation(nextToTop(st), st.back(), filtered[i]) <= 0)
        {
            st.pop_back();
        }
        st.push_back(filtered[i]);
    }

    if (st.size() < 3)
    {
        Point p;
        p.x = -1;
        p.y = -1;
        vector<Point> res;
        res.push_back(p);
        return res;
    }

    return st;
}

int main()
{
    int n;
    if (!(cin >> n))
    {
        return 0;
    }

    vector<Point> points;
    points.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        Point p;
        cin >> p.x >> p.y;
        points.push_back(p);
    }

    vector<Point> hull = findConvexHull(points);

    if (hull.size() == 1 && hull[0].x == -1 && hull[0].y == -1)
    {
        cout << -1 << "\n";
    }
    else
    {
        for (int i = 0; i < hull.size(); ++i)
        {
            cout << hull[i].x << " " << hull[i].y << "\n";
        }
    }

    return 0;
}