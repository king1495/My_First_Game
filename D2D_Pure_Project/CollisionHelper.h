#pragma once

namespace nCollision {
	inline bool isPointInRect(float x0, float y0, D2D_RECT_F _rect)
	{
		return x0 <= _rect.right &&
			x0 >= _rect.left &&
			y0 <= _rect.bottom &&
			y0 >= _rect.top;
	}

	inline bool isPointInRect(D2D1_POINT_2F _xy, D2D_RECT_F _rect)
	{
		return _xy.x <= _rect.right &&
			_xy.x >= _rect.left &&
			_xy.y <= _rect.bottom &&
			_xy.y >= _rect.top;
	}

	inline bool isRectInRect(D2D_RECT_F _rect0, D2D_RECT_F _rect1)
	{
		return _rect0.left <= _rect1.right &
			_rect0.right >= _rect1.left &
			_rect0.top <= _rect1.bottom &
			_rect0.bottom >= _rect1.top;
	}

	inline bool isPointInCircle(float x0, float y0, D2D1_ELLIPSE _circle)
	{
		if (_circle.radiusX != _circle.radiusY) return false;
		return GetDistance(x0, y0, _circle.point.x, _circle.point.y) <= _circle.radiusX;
	}

	inline bool isPointInCircle(D2D1_POINT_2F _xy, D2D1_ELLIPSE _circle)
	{
		if (_circle.radiusX != _circle.radiusY) return false;
		return GetDistance(_xy, _circle.point) <= _circle.radiusX;
	}

	inline bool isCircleInCircle(D2D1_ELLIPSE _circle0, D2D1_ELLIPSE _circle1)
	{
		if (_circle0.radiusX != _circle0.radiusY |
			_circle1.radiusX != _circle1.radiusY)
			return false;
		return GetDistance(_circle0.point, _circle1.point) <= (_circle0.radiusX + _circle1.radiusX);
	}

	inline bool isRectInCircle(D2D_RECT_F _rect, D2D1_ELLIPSE _circle)
	{
		if (_circle.radiusX != _circle.radiusY) return false;
		D2D_RECT_F tmp_x = RectF(
			_rect.left - _circle.radiusX,
			_rect.top,
			_rect.right + _circle.radiusX,
			_rect.bottom);

		D2D_RECT_F tmp_y = RectF(
			_rect.left,
			_rect.top - _circle.radiusX,
			_rect.right,
			_rect.bottom + _circle.radiusX);

		return isPointInRect(_circle.point, tmp_x) |
			isPointInRect(_circle.point, tmp_y) |
			isPointInCircle(_rect.left, _rect.top, _circle) |
			isPointInCircle(_rect.left, _rect.bottom, _circle) |
			isPointInCircle(_rect.right, _rect.top, _circle) |
			isPointInCircle(_rect.right, _rect.bottom, _circle);
	}
}