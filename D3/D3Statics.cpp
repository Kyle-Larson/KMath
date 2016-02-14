#include "Line.h"
#include "Plane.h"
#include "Quaternion.h"
#include "Ray.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			const Quaternion Quaternion::Identity = Quaternion(DirectX::XMQuaternionIdentity());
		}
	}
}