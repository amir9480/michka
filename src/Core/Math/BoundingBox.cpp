#include "BoundingBox.h"
#include "Core/Math/BoundingSphere.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Matrix3.h"

namespace Michka
{
    BoundingBox& BoundingBox::fix()
    {
        if (check() == false)
        {
            Michka::Vector3 bMin = min;
            Michka::Vector3 bMax = max;

            merge(bMin);
            merge(bMax);
        }

        return *this;
    }

    Vector3 BoundingBox::getCorner(const Corner& _corner) const
    {
        switch (_corner)
        {
            case Corner::leftDownBack:
                return Vector3(min.x, min.y, min.z);
            case Corner::leftDownForward:
                return Vector3(min.x, min.y, max.z);
            case Corner::leftUpBack:
                return Vector3(min.x, max.y, min.z);
            case Corner::leftUpForward:
                return Vector3(min.x, max.y, max.z);
            case Corner::rightDownBack:
                return Vector3(max.x, min.y, min.z);
            case Corner::rightDownForward:
                return Vector3(max.x, min.y, max.z);
            case Corner::rightUpBack:
                return Vector3(max.x, max.y, min.z);
            case Corner::rightUpForward:
                return Vector3(max.x, max.y, max.z);
        };

        return Vector3::zero; // @NOCOVERAGE
    }

    Intersection BoundingBox::getIntersection(const BoundingBox& _other) const
    {
        if (
            max.x < _other.min.x ||
            max.y < _other.min.y ||
            max.z < _other.min.z ||
            min.x > _other.max.x ||
            min.y > _other.max.y ||
            min.z > _other.max.z
        )
        {
            return Intersection::Outside;
        }
        if (
            max.x < _other.max.x ||
            max.y < _other.max.y ||
            max.z < _other.max.z ||
            min.x > _other.min.x ||
            min.y > _other.min.y ||
            min.z > _other.min.z
        )
        {
            return Intersection::Intersect;
        }

        return Intersection::Inside;
    }

    bool BoundingBox::isInside(const Vector3& _point) const
    {
        return !(
            max.x < _point.x ||
            max.y < _point.y ||
            max.z < _point.z ||
            min.x > _point.x ||
            min.y > _point.y ||
            min.z > _point.z
        );
    }

    bool BoundingBox::isInside(const BoundingBox& _other) const
    {
        return !(
            max.x < _other.min.x ||
            max.y < _other.min.y ||
            max.z < _other.min.z ||
            min.x > _other.max.x ||
            min.y > _other.max.y ||
            min.z > _other.max.z
        );
    }

    BoundingBox& BoundingBox::merge(const Vector3& _point)
    {
        if (_point.x < min.x)
        {
            min.x = _point.x;
        }
        if (_point.y < min.y)
        {
            min.y = _point.y;
        }
        if (_point.z < min.z)
        {
            min.z = _point.z;
        }

        if (_point.x > max.x)
        {
            max.x = _point.x;
        }
        if (_point.y > max.y)
        {
            max.y = _point.y;
        }
        if (_point.z > max.z)
        {
            max.z = _point.z;
        }

        return *this;
    }

    bool BoundingBox::isInside(const BoundingSphere& _sphere) const
    {
        Vector3 closestSide;
        if (
            _sphere.position.x >= min.x && _sphere.position.y >= min.y && _sphere.position.z >= min.z &&
            _sphere.position.x <= max.x && _sphere.position.y <= max.y && _sphere.position.z <= max.z
        )
        {
            return true;
        }
        if(_sphere.position.x >= max.x)
        {
            closestSide.x = max.x;
        }
        else if(_sphere.position.x <= min.x)
        {
            closestSide.x = min.x;
        }

        if(_sphere.position.y >= max.y)
        {
            closestSide.y = max.y;
        }
        else if(_sphere.position.y <= min.y)
        {
            closestSide.y = min.y;
        }

        if(_sphere.position.z >= max.z)
        {
            closestSide.z = max.z;
        }
        else if(_sphere.position.z <= min.z)
        {
            closestSide.z = min.z;
        }

        return (closestSide.getDistanceFrom(_sphere.position) <= _sphere.radius);
    }

    BoundingBox& BoundingBox::transform(const Matrix3& _matrix)
    {
        Vector3 vMin = min * _matrix;
        Vector3 vMax = max * _matrix;

        min = Vector3::infinity;
        max = -Vector3::infinity;

        merge(vMin);
        merge(vMax);

        return *this;
    }

    BoundingBox& BoundingBox::transform(const Matrix& _matrix)
    {
        Vector3 vMin = min * _matrix;
        Vector3 vMax = max * _matrix;

        min = Vector3::infinity;
        max = -Vector3::infinity;

        merge(vMin);
        merge(vMax);

        return *this;
    }
}
