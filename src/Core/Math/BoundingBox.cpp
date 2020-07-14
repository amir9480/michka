#include "BoundingBox.h"

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

        return Vector3::zero;
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
}
