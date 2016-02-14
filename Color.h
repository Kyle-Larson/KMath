#pragma once

#include <DirectXMath.h>
#include <DirectXColors.h>
#include "Data/Storage/Array.h"

namespace KEngine
{
	namespace Graphics
	{
		enum class ColorLayout
		{
			RGB,
			sRGB,
			HSL,
			HSV,
			XYZ,
			YUV
		};

		template<ColorLayout layout>
		class Color
		{
		public:
			Color();
			Color(float p_xValue, float p_yValue, float p_zValue, float p_alpha);
			Color(const Data::Storage::Array<float, 4>& p_dataArray);
			Color(const DirectX::XMVECTOR& p_vector);

			operator DirectX::XMVECTOR() const;

			bool operator==(const Color& p_rhs) const;
			bool operator!=(const Color& p_rhs) const;

			Color AdjustContrast(float p_contrastFraction) const;
			Color AdjustSaturation(float p_saturationFraction) const;

			template<ColorLayout newLayout, bool highDef>
			Color<newLayout> Convert() const;

			Color Blend(const Color& color) const;

			void Load(const Data::Storage::Array<float, 4>& p_dataArray);
			Data::Storage::Array<float, 4> Unload() const;
		private:
			DirectX::XMVECTOR m_vector;
		};

		template<>
		class Color<ColorLayout::RGB>
		{
		public:
			Color();
			Color(float p_red, float p_green, float p_blue, float p_alpha);
			Color(const Data::Storage::Array<float, 4>& p_dataArray);
			Color(const DirectX::XMVECTOR& p_vector);

			operator DirectX::XMVECTOR() const;

			bool operator==(const Color& p_rhs) const;
			bool operator!=(const Color& p_rhs) const;

			Color AdjustContrast(float p_contrastFraction) const;
			Color AdjustSaturation(float p_saturationFraction) const;

			template<ColorLayout newLayout, bool highDef>
			Color<newLayout> Convert() const;
			Color<ColorLayout::RGB> GetNegative() const;

			Color<ColorLayout::RGB> Blend(const Color<ColorLayout::RGB>& color) const;

			void Load(const Data::Storage::Array<float, 4>& p_dataArray);
			Data::Storage::Array<float, 4> Unload() const;
		private:
			DirectX::XMVECTOR m_vector;
		};

		namespace PresetColors
		{
#define AddPresetColor(colorName) extern const Color<ColorLayout::sRGB> colorName;
			AddPresetColor(AliceBlue);
			AddPresetColor(AntiqueWhite);
			AddPresetColor(Aqua);
			AddPresetColor(Aquamarine);
			AddPresetColor(Azure);
			AddPresetColor(Beige);
			AddPresetColor(Bisque);
			AddPresetColor(Black);
			AddPresetColor(BlanchedAlmond);
			AddPresetColor(Blue);
			AddPresetColor(BlueViolet);
			AddPresetColor(Brown);
			AddPresetColor(BurlyWood);
			AddPresetColor(CadetBlue);
			AddPresetColor(Chartreuse);
			AddPresetColor(Chocolate);
			AddPresetColor(Coral);
			AddPresetColor(CornflowerBlue);
			AddPresetColor(Cornsilk);
			AddPresetColor(Crimson);
			AddPresetColor(Cyan);
			AddPresetColor(DarkBlue);
			AddPresetColor(DarkCyan);
			AddPresetColor(DarkGoldenrod);
			AddPresetColor(DarkGray);
			AddPresetColor(DarkGreen);
			AddPresetColor(DarkKhaki);
			AddPresetColor(DarkMagenta);
			AddPresetColor(DarkOliveGreen);
			AddPresetColor(DarkOrange);
			AddPresetColor(DarkOrchid);
			AddPresetColor(DarkRed);
			AddPresetColor(DarkSalmon);
			AddPresetColor(DarkSeaGreen);
			AddPresetColor(DarkSlateBlue);
			AddPresetColor(DarkSlateGray);
			AddPresetColor(DarkTurquoise);
			AddPresetColor(DarkViolet);
			AddPresetColor(DeepPink);
			AddPresetColor(DeepSkyBlue);
			AddPresetColor(DimGray);
			AddPresetColor(DodgerBlue);
			AddPresetColor(Firebrick);
			AddPresetColor(FloralWhite);
			AddPresetColor(ForestGreen);
			AddPresetColor(Fuchsia);
			AddPresetColor(Gainsboro);
			AddPresetColor(GhostWhite);
			AddPresetColor(Gold);
			AddPresetColor(Goldenrod);
			AddPresetColor(Gray);
			AddPresetColor(Green);
			AddPresetColor(GreenYellow);
			AddPresetColor(Honeydew);
			AddPresetColor(HotPink);
			AddPresetColor(IndianRed);
			AddPresetColor(Indigo);
			AddPresetColor(Ivory);
			AddPresetColor(Khaki);
			AddPresetColor(Lavender);
			AddPresetColor(LavenderBlush);
			AddPresetColor(LawnGreen);
			AddPresetColor(LemonChiffon);
			AddPresetColor(LightBlue);
			AddPresetColor(LightCoral);
			AddPresetColor(LightCyan);
			AddPresetColor(LightGoldenrodYellow);
			AddPresetColor(LightGreen);
			AddPresetColor(LightGray);
			AddPresetColor(LightPink);
			AddPresetColor(LightSalmon);
			AddPresetColor(LightSeaGreen);
			AddPresetColor(LightSkyBlue);
			AddPresetColor(LightSlateGray);
			AddPresetColor(LightSteelBlue);
			AddPresetColor(LightYellow);
			AddPresetColor(Lime);
			AddPresetColor(LimeGreen);
			AddPresetColor(Linen);
			AddPresetColor(Magenta);
			AddPresetColor(Maroon);
			AddPresetColor(MediumAquamarine);
			AddPresetColor(MediumBlue);
			AddPresetColor(MediumOrchid);
			AddPresetColor(MediumPurple);
			AddPresetColor(MediumSlateBlue);
			AddPresetColor(MediumSpringGreen);
			AddPresetColor(MediumTurquoise);
			AddPresetColor(MediumVioletRed);
			AddPresetColor(MidnightBlue);
			AddPresetColor(MintCream);
			AddPresetColor(MistyRose);
			AddPresetColor(Moccasin);
			AddPresetColor(NavajoWhite);
			AddPresetColor(Navy);
			AddPresetColor(OldLace);
			AddPresetColor(Olive);
			AddPresetColor(OliveDrab);
			AddPresetColor(Orange);
			AddPresetColor(OrangeRed);
			AddPresetColor(Orchid);
			AddPresetColor(PaleGoldenrod);
			AddPresetColor(PaleGreen);
			AddPresetColor(PaleTurquoise);
			AddPresetColor(PaleVioletRed);
			AddPresetColor(PapayaWhip);
			AddPresetColor(PeachPuff);
			AddPresetColor(Peru);
			AddPresetColor(Pink);
			AddPresetColor(Plum);
			AddPresetColor(PowderBlue);
			AddPresetColor(Purple);
			AddPresetColor(Red);
			AddPresetColor(RosyBrown);
			AddPresetColor(RoyalBlue);
			AddPresetColor(SaddleBrown);
			AddPresetColor(Salmon);
			AddPresetColor(SandyBrown);
			AddPresetColor(SeaGreen);
			AddPresetColor(SeaShell);
			AddPresetColor(Sienna);
			AddPresetColor(Silver);
			AddPresetColor(SkyBlue);
			AddPresetColor(SlateBlue);
			AddPresetColor(SlateGray);
			AddPresetColor(Snow);
			AddPresetColor(SpringGreen);
			AddPresetColor(SteelBlue);
			AddPresetColor(Tan);
			AddPresetColor(Teal);
			AddPresetColor(Thistle);
			AddPresetColor(Tomato);
			AddPresetColor(Transparent);
			AddPresetColor(Turquoise);
			AddPresetColor(Violet);
			AddPresetColor(Wheat);
			AddPresetColor(White);
			AddPresetColor(WhiteSmoke);
			AddPresetColor(Yellow);
			AddPresetColor(YellowGreen);
		}
	}
}

#include "Color.inl"