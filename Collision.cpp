#include "Collision.h"
#include <algorithm>
#include <array>

LineSegment::LineSegment(const Vector3 & argStart, const Vector3 & argEnd)
    :start(argStart)
    , end(argEnd)
{
}

Vector3 LineSegment::PointOnSegment(float t) const
{
    return start + (end - start) * t;
}

float LineSegment::MinDistanceSquared(const Vector3 & argPoint) const
{
    Vector3 ab = end - start;
    Vector3 ba = -1.0f * ab;
    Vector3 ac = argPoint - start;
    Vector3 bc = argPoint - end;

    if (Vector3::Dot(ab, ac) < 0.0f)
    {
        return ac.LengthSq();
    }
    else if (Vector3::Dot(ba, bc) < 0.0f)
    {
        return bc.LengthSq();
    }
    else
    {
        float scalar = Vector3::Dot(ac, ab) / Vector3::Dot(ab, ab);
        Vector3 p = scalar * ab;
        return (ac - p).LengthSq();
    }
}

float LineSegment::MinDistanceSquared(const LineSegment & argLine1, const LineSegment & argLine2)
{
    Vector3 u = argLine1.end - argLine1.start;
    Vector3 v = argLine2.end - argLine2.start;
    Vector3 w = argLine1.start - argLine2.start;
    float   a = Vector3::Dot(u, u);
    float   b = Vector3::Dot(u, v);
    float   c = Vector3::Dot(v, v);
    float   d = Vector3::Dot(u, w);
    float   e = Vector3::Dot(v, w);
    float   D = a * c - b * b;
    float   sc, sN, sD = D;
    float   tc, tN, tD = D;

    if (Math::NearZero(D))
    {
        sN = 0.0f;
        sD = 1.0f;
        tN = e;
        tD = c;
    }
    else
    {
        sN = (b*e - c * d);
        tN = (a*e - b * d);
        if (sN < 0.0) 
        {
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) 
        {
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-d + b) < 0.0)
            sN = 0;
        else if ((-d + b) > a)
            sN = sD;
        else {
            sN = (-d + b);
            sD = a;
        }
    }
    // finally do the division to get sc and tc
    sc = (Math::NearZero(sN) ? 0.0f : sN / sD);
    tc = (Math::NearZero(tN) ? 0.0f : tN / tD);

    // get the difference of the two closest points
    Vector3   dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

    return dP.LengthSq();   // return the closest distance squared
}
