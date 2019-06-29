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

Plane::Plane(const Vector3 & argNormal, float argDistance)
	:normal(argNormal)
	, distance(argDistance)
{
}

Plane::Plane(const Vector3 & argVec1, const Vector3 & argVec2, const Vector3 & argVec3)
{
	Vector3 ab = argVec2 - argVec1;
	Vector3 ac = argVec3 - argVec1;

	normal = Vector3::Cross(ab, ac);
	normal.Normalize();

	distance = -Vector3::Dot(argVec1, normal);

}

float Plane::SignedDistance(const Vector3& argPoint)
{
	return Vector3::Dot(argPoint, normal) - distance;
}

Sphere::Sphere(const Vector3 & argCenter, const float argRadius)
	:center(argCenter)
	, radius(argRadius)
{
}

bool Sphere::Contains(const Vector3 & argPoint) const
{
	float distansSquared = (center - argPoint).LengthSq();
	return distansSquared <= (radius * radius);
}

AABB::AABB(const Vector3 & argMin, const Vector3 & argMax)
	:min(argMin)
	, max(argMax)
{
}

void AABB::UpdateMinMax(const Vector3 & argPoint)
{
	min.x = Math::Min(min.x, argPoint.x);
	min.y = Math::Min(min.y, argPoint.y);
	min.z = Math::Min(min.z, argPoint.z);

	max.x = Math::Max(max.x, argPoint.x);
	max.y = Math::Max(max.y, argPoint.y);
	max.z = Math::Max(max.z, argPoint.z);
}

void AABB::Rotate(const Quaternion & argQuaternion)
{
	std::array<Vector3, 8> points;

	points[0] = min;

	points[1] = Vector3(max.x, min.y, min.z);
	points[2] = Vector3(min.x, max.y, min.z);
	points[3] = Vector3(min.x, min.y, max.z);

	points[4] = Vector3(min.x, max.y, max.z);
	points[5] = Vector3(max.x, min.y, max.z);
	points[6] = Vector3(max.x, max.y, min.z);

	points[7] = Vector3(max);

	Vector3 p = Vector3::Transform(points[0], argQuaternion);

	min = p;
	max = p;

	for (std::size_t i = 1; i < points.size(); i++)
	{
		p = Vector3::Transform(points[i], argQuaternion);
		UpdateMinMax(p);
	}
}

bool AABB::Contains(const Vector3 & argPoint) const
{
	bool outside =
		argPoint.x < min.x ||
		argPoint.y < min.y ||
		argPoint.z < min.x ||
		argPoint.x > max.x ||
		argPoint.y > max.y ||
		argPoint.z > max.z;
	return !outside;
}

float AABB::MinDistanceSquared(const Vector3 & argPoint) const
{
	float dx = Math::Max(min.x - argPoint.x, 0.0f);
	dx = Math::Max(dx, max.x - max.x);
	float dy = Math::Max(min.y - argPoint.y, 0.0f);
	dy = Math::Max(dy, max.y - max.y);
	float dz = Math::Max(min.z - argPoint.z, 0.0f);
	dz = Math::Max(dz, max.z - max.z);
	return dx * dx + dy * dy + dz * dz;
}

Capsule::Capsule(const Vector3 & argStart, const Vector3 & argEnd, float argRadius)
	:segment(argStart, argEnd)
	, radius(argRadius)
{
}

Vector3 Capsule::PointOnSegment(float t) const
{
	return segment.PointOnSegment(t);
}

bool Capsule::Contains(const Vector3 & argPoint) const
{
	float distanceSquared = segment.MinDistanceSquared(argPoint);
	return distanceSquared <= (radius * radius);
}

bool ConvexPolygon::Contains(const Vector2 & argPoint) const
{
	float sum = 0.0f;
	Vector2 a, b;
	for (std::size_t i = 0; i < vertices.size() - 1; i++)
	{
		a = vertices[i] - argPoint;
		a.Normalize();

		b = vertices[i + 1] - argPoint;
		b.Normalize();

		sum += Math::Acos(Vector2::Dot(a, b));
	}

	a = vertices.back() - argPoint;
	a.Normalize();
	b = vertices.front() - argPoint;
	b.Normalize();
	sum += Math::Acos(Vector2::Dot(a, b));

	return Math::NearZero(sum - Math::TwoPi);
}

bool Intersect(const Sphere & argSphere1, const Sphere & argSphere2)
{
	float distanceSquared = (argSphere1.center - argSphere2.center).LengthSq();
	float sumRadius = argSphere1.radius + argSphere2.radius;
	return distanceSquared <= (sumRadius * sumRadius);
}

bool Intersect(const AABB & argAABB1, const AABB & argAABB2)
{
	bool no =
		argAABB1.max.x < argAABB2.min.x ||
		argAABB1.max.y < argAABB2.min.y ||
		argAABB1.max.z < argAABB2.min.z ||
		argAABB2.max.x > argAABB1.min.x ||
		argAABB2.max.y > argAABB1.min.y ||
		argAABB2.max.z > argAABB1.min.z;

	return !no;
}

bool Intersect(const Capsule & argCapsule1, const Capsule & argCapsule2)
{
	float distanceSquared = LineSegment::MinDistanceSquared(argCapsule1.segment,
		argCapsule2.segment);
	float sumRadius = argCapsule1.radius + argCapsule2.radius;
	return distanceSquared <= (sumRadius * sumRadius);
}

bool Intersect(const Sphere & argSphere, const AABB & argAABB)
{
	float distanceSquared = argAABB.MinDistanceSquared(argSphere.center);
	return distanceSquared <= (argSphere.radius * argSphere.radius);
}

bool Intersect(const LineSegment & argLine, const Sphere & argSphere, float & outT)
{
	Vector3 X = argLine.start - argSphere.center;
	Vector3 Y = argLine.end - argLine.start;
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float c = Vector3::Dot(X, X) - argSphere.radius * argSphere.radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		discriminant = Math::Sqrt(discriminant);

		float tMin = (-b - discriminant) / (2.0f * a);
		float tMax = (-b + discriminant) / (2.0f * a);

		if (tMin >= 0.0f && tMin <= 1.0f)
		{
			outT = tMin;
			return true;
		}
		else if (tMax >= 0.0f && tMax <= 1.0f)
		{
			outT = tMax;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Intersect(const LineSegment & argLine, const Plane & argPlane, float & outT)
{
	float denom = Vector3::Dot(argLine.end - argLine.start,
		argPlane.normal);
	if (Math::NearZero(denom))
	{
		if (Math::NearZero(Vector3::Dot(argLine.start, argPlane.normal) - argPlane.distance))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float numer = -Vector3::Dot(argLine.start, argPlane.normal) - argPlane.distance;
		outT = numer / denom;
		if (outT >= 0.0f && outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TestSidePlane(float argStart, float argEnd, float argNegd, const Vector3& argNorm,
	std::vector<std::pair<float, Vector3>>& out)
{
	float denom = argEnd - argStart;
	if (Math::NearZero(denom))
	{
		return false;
	}
	else
	{
		float numer = -argStart + argNegd;
		float t = numer / denom;
		// Test that t is within bounds
		if (t >= 0.0f && t <= 1.0f)
		{
			out.emplace_back(t, argNorm);
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Intersect(const LineSegment & argLine, const AABB & argAABB, float & outT, Vector3 & outNorm)
{
	std::vector<std::pair<float, Vector3>> values;

	TestSidePlane(argLine.start.x, argLine.end.x, argAABB.min.x, Vector3::NegUnitX, values);
	TestSidePlane(argLine.start.x, argLine.end.x, argAABB.max.x, Vector3::UnitX, values);
	TestSidePlane(argLine.start.y, argLine.end.y, argAABB.min.y, Vector3::NegUnitY, values);
	TestSidePlane(argLine.start.y, argLine.end.y, argAABB.max.y, Vector3::UnitY, values);
	TestSidePlane(argLine.start.z, argLine.end.z, argAABB.min.z, Vector3::NegUnitZ, values);
	TestSidePlane(argLine.start.z, argLine.end.z, argAABB.max.z, Vector3::UnitZ, values);

	std::sort(values.begin(), values.end(), [](
		const std::pair<float, Vector3>& a,
		const std::pair<float, Vector3>& b) {
			return a.first < b.first;
		});
	Vector3 point;
	for (auto& t : values)
	{
		point = argLine.PointOnSegment(t.first);
		if (argAABB.Contains(point))
		{
			outT = t.first;
			outNorm = t.second;
			return true;
		}
	}
	return false;
}

bool SweptSphere(const Sphere & argSphere1, const Sphere & argSphere2, const Sphere & argSphere3, const Sphere & argSphere4, float & outT)
{
	Vector3 X = argSphere1.center - argSphere3.center;
	Vector3 Y = argSphere2.center - argSphere1.center - (argSphere4.center - argSphere3.center);
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float sumRadius = argSphere1.radius + argSphere3.radius;
	float c = Vector3::Dot(X, X) - sumRadius * sumRadius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		discriminant = Math::Sqrt(discriminant);

		outT = (-b - discriminant) / (2.0f * a);
		if (outT >= 0.0f && outT <= 0.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
