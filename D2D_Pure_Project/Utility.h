#pragma once

typedef struct sFrame {
	int frameX, frameY;
	int frameMaxX, frameMaxY;
} Frame;

namespace nMakeShapes {
	inline D2D_RECT_F MakeRect(float x, float y, float width, float height) {
		return RectF(x, y, x + width, y + height);
	}

	inline D2D_RECT_F MakeRectCenter(float x, float y, float width, float height) {
		return RectF(x - (width / 2.f), y - (height / 2.f),
			x + (width / 2.f), y + (height / 2.f));
	}

	inline D2D1_ELLIPSE MakeCircle(float x, float y, float radiusX, float radiusY = 0.f) {
		if (radiusY == 0.f) radiusY = radiusX;
		D2D1_ELLIPSE temp = { x, y, radiusX, radiusY };
		return temp;
	}
}

namespace nString {
	/*inline wstring StringToWstring(const string& str) {
		size_t len = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), nullptr, 0);
		wstring Temp(len, 0);

		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &Temp[0], len);
		return Temp;
	}*/

	inline string WstringToString(const wstring& str) {
		std::string Temp;
		Temp.append(str.begin(), str.end());
		return Temp;
	}

	inline wstring StringToWstring(const string& str) {
		std::wstring Temp;
		Temp.append(str.begin(), str.end());
		return Temp;
	}
}

inline float GetDistance(float x0, float y0, float x1 = 0.f, float y1 = 0.f) {
	return sqrtf(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

inline float GetDistance(D2D1_POINT_2F xy0, D2D1_POINT_2F xy1 = { 0,0 }) {
	return sqrtf(pow(xy1.x - xy0.x, 2) + pow(xy1.y - xy0.y, 2));
}

inline float GetAngle(float x0, float y0, float x1 = 0.f, float y1 = 0.f) {
	return atan2f(y1 - y0, x1 - x0);
}

inline float GetAngle(D2D1_POINT_2F xy0, D2D1_POINT_2F xy1 = { 0,0 }) {
	return atan2f(xy1.y - xy0.y, xy1.x - xy0.x);
}

inline float DegreeToRadian(float fDegree) {
	return fDegree * PI / 180.0f;
}

inline float RadianToDegree(float fRadian) {
	return fRadian * 180.0f / PI;
}

inline Frame NextFrame(Frame _frame) {
	_frame.frameX++;
	if (_frame.frameX >= _frame.frameMaxX) {
		_frame.frameX = 0;
		_frame.frameY++;
		if (_frame.frameY >= _frame.frameMaxY) {
			_frame.frameY = 0;
		}
	}
	return _frame;
}

inline D2D_COLOR_F SetColor(int red, int green, int blue, float opacity = 1.0f) {
	float R = red / 255.f;
	float G = green / 255.f;
	float B = blue / 255.f;

	return ColorF(R, G, B, opacity);
}