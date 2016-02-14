#include "Vector.h"
#include "Matrix.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			const Vector<2> Vector<2>::Zero = Vector<2>(DirectX::XMVectorZero());
			const Vector<3> Vector<3>::Zero = Vector<3>(DirectX::XMVectorZero());
			const Vector<4> Vector<4>::Zero = Vector<4>(DirectX::XMVectorZero());

			const Vector<2> Vector<2>::One = Vector<2>(DirectX::XMVectorSplatOne());
			const Vector<3> Vector<3>::One = Vector<3>(DirectX::XMVectorSplatOne());
			const Vector<4> Vector<4>::One = Vector<4>(DirectX::XMVectorSplatOne());

			const Vector<2> Vector<2>::UnitX = Vector<2>(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));
			const Vector<3> Vector<3>::UnitX = Vector<3>(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));
			const Vector<4> Vector<4>::UnitX = Vector<4>(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));

			const Vector<2> Vector<2>::UnitY = Vector<2>(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
			const Vector<3> Vector<3>::UnitY = Vector<3>(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
			const Vector<4> Vector<4>::UnitY = Vector<4>(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

			const Vector<3> Vector<3>::UnitZ = Vector<3>(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
			const Vector<4> Vector<4>::UnitZ = Vector<4>(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));

			const Vector<4> Vector<4>::UnitW = Vector<4>(DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

			const Matrix<3, 3> Matrix<3, 3>::Identity = Matrix<3, 3>(DirectX::XMMatrixIdentity());
			const Matrix<3, 4> Matrix<3, 4>::Identity = Matrix<3, 4>(DirectX::XMMatrixIdentity());
			const Matrix<4, 3> Matrix<4, 3>::Identity = Matrix<4, 3>(DirectX::XMMatrixIdentity());
			const Matrix<4, 4> Matrix<4, 4>::Identity = Matrix<4, 4>(DirectX::XMMatrixIdentity());
		}
	}
}