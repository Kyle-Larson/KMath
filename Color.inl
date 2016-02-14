#pragma once

#include "Color.h"

namespace KEngine
{
	namespace Graphics
	{
		template<ColorLayout layout>
		inline Color<layout>::Color() : m_vector() {}
		inline Color<ColorLayout::RGB>::Color() : m_vector() {}

		template<ColorLayout layout>
		inline Color<layout>::Color(float p_xValue, float p_yValue, float p_zValue, float p_alpha)
			: m_vector(DirectX::XMVectorSet(p_xValue, p_yValue, p_zValue, p_alpha)) {}
		inline Color<ColorLayout::RGB>::Color(float p_red, float p_green, float p_blue, float p_alpha)
			: m_vector(DirectX::XMVectorSet(p_red, p_green, p_blue, p_alpha)) {}
		template<ColorLayout layout>
		inline Color<layout>::Color(const Data::Storage::Array<float, 4>& p_dataArray)
			: m_vector(DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(p_dataArray.data()))) {}
		inline Color<ColorLayout::RGB>::Color(const Data::Storage::Array<float, 4>& p_dataArray)
			: m_vector(DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(p_dataArray.data()))) {}

		template<ColorLayout layout>
		inline Color<layout>::Color(const DirectX::XMVECTOR& p_vector)
			: m_vector(p_vector) {}
		inline Color<ColorLayout::RGB>::Color(const DirectX::XMVECTOR& p_vector)
			: m_vector(p_vector) {}

		template<ColorLayout layout>
		inline Color<layout>::operator DirectX::XMVECTOR() const
		{
			return m_vector;
		}
		inline Color<ColorLayout::RGB>::operator DirectX::XMVECTOR() const
		{
			return m_vector;
		}

		template<ColorLayout layout>
		inline bool Color<layout>::operator==(const Color<layout>& p_rhs) const
		{
			return DirectX::XMColorEqual(m_vector, p_rhs);
		}
		inline bool Color<ColorLayout::RGB>::operator==(const Color<ColorLayout::RGB>& p_rhs) const
		{
			return DirectX::XMColorEqual(m_vector, p_rhs);
		}

		template<ColorLayout layout>
		inline bool Color<layout>::operator!=(const Color<layout>& p_rhs) const
		{
			return DirectX::XMColorNotEqual(m_vector, p_rhs);
		}
		inline bool Color<ColorLayout::RGB>::operator!=(const Color<ColorLayout::RGB>& p_rhs) const
		{
			return DirectX::XMColorNotEqual(m_vector, p_rhs);
		}

		template<ColorLayout layout>
		inline Color<layout> Color<layout>::AdjustContrast(float p_contrastFraction) const
		{
			return Color<layout>(DirectX::XMColorAdjustContrast(m_vector, p_contrastFraction));
		}
		inline Color<ColorLayout::RGB> Color<ColorLayout::RGB>::AdjustContrast(float p_contrastFraction) const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorAdjustContrast(m_vector, p_contrastFraction));
		}

		template<ColorLayout layout>
		inline Color<layout> Color<layout>::AdjustSaturation(float p_saturationFraction) const
		{
			return Color<layout>(DirectX::XMColorAdjustSaturation(m_vector, p_saturationFraction));
		}
		inline Color<ColorLayout::RGB> Color<ColorLayout::RGB>::AdjustSaturation(float p_saturationFraction) const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorAdjustSaturation(m_vector, p_saturationFraction));
		}

		template<ColorLayout layout>
		template<ColorLayout newLayout, bool highDef>
		inline Color<newLayout> Color<layout>::Convert() const
		{
			//Can default to convert to RGB,
			//Then convert to target layout
			Color<ColorLayout::RGB> midpointColor = Convert<ColorLayout::RGB, highDef>();
			return midpointColor.Convert<newLayout, highDef>();
		}

		template<>
		inline Color<ColorLayout::sRGB> Color<ColorLayout::RGB>::Convert<ColorLayout::sRGB, true>() const
		{
			return Color<ColorLayout::sRGB>(DirectX::XMColorRGBToSRGB(m_vector));
		}
		template<>
		inline Color<ColorLayout::sRGB> Color<ColorLayout::RGB>::Convert<ColorLayout::sRGB, false>() const
		{
			return Color<ColorLayout::sRGB>(DirectX::XMColorRGBToSRGB(m_vector));
		}
		template<>
		inline Color<ColorLayout::HSL> Color<ColorLayout::RGB>::Convert<ColorLayout::HSL, true>() const
		{
			return Color<ColorLayout::HSL>(DirectX::XMColorRGBToHSL(m_vector));
		}
		template<>
		inline Color<ColorLayout::HSL> Color<ColorLayout::RGB>::Convert<ColorLayout::HSL, false>() const
		{
			return Color<ColorLayout::HSL>(DirectX::XMColorRGBToHSL(m_vector));
		}
		template<>
		inline Color<ColorLayout::HSV> Color<ColorLayout::RGB>::Convert<ColorLayout::HSV, true>() const
		{
			return Color<ColorLayout::HSV>(DirectX::XMColorRGBToHSV(m_vector));
		}
		template<>
		inline Color<ColorLayout::HSV> Color<ColorLayout::RGB>::Convert<ColorLayout::HSV, false>() const
		{
			return Color<ColorLayout::HSV>(DirectX::XMColorRGBToHSV(m_vector));
		}
		template<>
		inline Color<ColorLayout::XYZ> Color<ColorLayout::RGB>::Convert<ColorLayout::XYZ, true>() const
		{
			return Color<ColorLayout::XYZ>(DirectX::XMColorRGBToXYZ(m_vector));
		}
		template<>
		inline Color<ColorLayout::XYZ> Color<ColorLayout::RGB>::Convert<ColorLayout::XYZ, false>() const
		{
			return Color<ColorLayout::XYZ>(DirectX::XMColorRGBToXYZ(m_vector));
		}
		template<>
		inline Color<ColorLayout::YUV> Color<ColorLayout::RGB>::Convert<ColorLayout::YUV, false>() const
		{
			return Color<ColorLayout::YUV>(DirectX::XMColorRGBToYUV(m_vector));
		}
		template<>
		inline Color<ColorLayout::YUV> Color<ColorLayout::RGB>::Convert<ColorLayout::YUV, true>() const
		{
			return Color<ColorLayout::YUV>(DirectX::XMColorRGBToYUV_HD(m_vector));
		}

		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::sRGB>::Convert<ColorLayout::RGB, true>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorSRGBToRGB(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::sRGB>::Convert<ColorLayout::RGB, false>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorSRGBToRGB(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::XYZ> Color<ColorLayout::sRGB>::Convert<ColorLayout::XYZ, true>() const
		{
			return Color<ColorLayout::XYZ>(DirectX::XMColorSRGBToXYZ(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::XYZ> Color<ColorLayout::sRGB>::Convert<ColorLayout::XYZ, false>() const
		{
			return Color<ColorLayout::XYZ>(DirectX::XMColorSRGBToXYZ(m_vector));
		}

		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::HSL>::Convert<ColorLayout::RGB, true>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorHSLToRGB(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::HSL>::Convert<ColorLayout::RGB, false>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorHSLToRGB(m_vector));
		}

		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::HSV>::Convert<ColorLayout::RGB, true>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorHSVToRGB(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::HSV>::Convert<ColorLayout::RGB, false>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorHSVToRGB(m_vector));
		}

		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::XYZ>::Convert<ColorLayout::RGB, true>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorXYZToRGB(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::XYZ>::Convert<ColorLayout::RGB, false>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorXYZToRGB(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::sRGB> Color<ColorLayout::XYZ>::Convert<ColorLayout::sRGB, true>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorXYZToSRGB(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::sRGB> Color<ColorLayout::XYZ>::Convert<ColorLayout::sRGB, false>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorXYZToSRGB(m_vector));
		}

		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::YUV>::Convert<ColorLayout::RGB, false>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorYUVToRGB(m_vector));
		}
		template<>
		template<>
		inline Color<ColorLayout::RGB> Color<ColorLayout::YUV>::Convert<ColorLayout::RGB, true>() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorYUVToRGB_HD(m_vector));
		}

		template<ColorLayout layout>
		inline Color<layout> Color<layout>::Blend(const Color<layout>& color) const
		{
			return Color<layout>(DirectX::XMColorModulate(m_vector, color.m_vector));
		}
		inline Color<ColorLayout::RGB> Color<ColorLayout::RGB>::Blend(const Color<ColorLayout::RGB>& color) const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorModulate(m_vector, color.m_vector));
		}

		template<ColorLayout layout>
		inline void Color<layout>::Load(const Data::Storage::Array<float, 4>& p_dataArray)
		{
			m_vector = DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(p_dataArray.data()));
		}
		inline void Color<ColorLayout::RGB>::Load(const Data::Storage::Array<float, 4>& p_dataArray)
		{
			m_vector = DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(p_dataArray.data()));
		}

		template<ColorLayout layout>
		inline Data::Storage::Array<float, 4> Color<layout>::Unload() const
		{
			Data::Storage::Array<float, 4> returnValue;
			DirectX::XMFLOAT4* containerPtr = reinterpret_cast<DirectX::XMFLOAT4*>(returnValue.data());
			DirectX::XMStoreFloat4(containerPtr, m_vector);
			return returnValue;
		}
		inline Data::Storage::Array<float, 4> Color<ColorLayout::RGB>::Unload() const
		{
			Data::Storage::Array<float, 4> returnValue;
			DirectX::XMFLOAT4* containerPtr = reinterpret_cast<DirectX::XMFLOAT4*>(returnValue.data());
			DirectX::XMStoreFloat4(containerPtr, m_vector);
			return returnValue;
		}

		inline Color<ColorLayout::RGB> Color<ColorLayout::RGB>::GetNegative() const
		{
			return Color<ColorLayout::RGB>(DirectX::XMColorNegative(m_vector));
		}
	}
}