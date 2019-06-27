#pragma once
#include "Math.h"
#include <vector>

//ê¸ï™
struct LineSegment
{
    LineSegment(const Vector3& argStart, const Vector3& argEnd);
    Vector3 PointOnSegment(float t) const;
    float MinDistanceSquared(const Vector3& argPoint)const;
    static float MinDistanceSquared(const LineSegment& argLine1,const LineSegment& argLine2);

    Vector3 start;
    Vector3 end;
};

//ïΩñ 
struct Plane
{
    Plane(const Vector3& argNormal, float argDistance);
    Plane(const Vector3& argVec1, const Vector3& argVec2, const Vector3& argVec3);

    float SignedDistance(const Vector3& argPoint);

    Vector3 normal;
    float distance;
};

struct Sphere
{
    Sphere(const Vector3& argCenter, const float argRadius);
    bool Contains(const Vector3& argPoint)const;

    Vector3 center;
    float radius;
};

//Axis-Aligned Bounding Box
struct AABB
{
    AABB(const Vector3& argMin,const Vector3& argMax);

    void UpdateMinMax(const Vector3& argPoint);

    void Rotate(const Quaternion& argQuaternion);
    bool Contains(const Vector3& argPoint)const;
    float MinDistanceSquared(const Vector3& argPoint)const;

    Vector3 min;
    Vector3 max;
};

struct OBB
{
    Vector3 center;
    Quaternion rotation;
    Vector3 extents;
};

struct Capsule
{
    Capsule(const Vector3& argStart,const Vector3& argEnd,float argRadius);

    Vector3 PointOnSegment(float t)const;
    bool Contains(const Vector3& argPoint)const;

    LineSegment segment;
    float radius;
};

struct ConvexPolygon
{
    bool Contains(const Vector2& argPoint)const;

    std::vector<Vector2> vertices;
};

bool Intersect(const Sphere& argSphere1,const Sphere& argSphere2);
bool Intersect(const AABB& argAABB1, const AABB& argAABB2);
bool Intersect(const Capsule& argCapsule1, const Capsule& argCapsule2);
bool Intersect(const Sphere& argSphere, const AABB& argAABB);

bool Intersect(const LineSegment& argLine, const Sphere& argSphere, float& outT);
bool Intersect(const LineSegment& argLine, const Plane& argPlane, float& outT);
bool Intersect(const LineSegment& argLine, const AABB& argAABB, float& outT,
    Vector3& outNorm);

bool SweptSphere(const Sphere& argSphere1, const Sphere& argSphere2,
    const Sphere& argSphere3, const Sphere& argSphere4, float& outT);
