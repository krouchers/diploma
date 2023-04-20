#include "camera.hpp"

Camera::Camera(Vec2 dim)
	: view_{Mat4x4::GetRotationMatrix(Vec3{0, 0, 45})},
	  proj_{Mat4x4::GetProjectionMatrix(2, 10, 45, dim.y / dim.x)}
{
	Reset();
	SetAs(dim.y / dim.x);
}

void Camera::Reset()
{
	fov_ = 45.f;
	near_plane_ = 2.f;
	far_plane_ = 2.f;
}

void Camera::SetAs(float as)
{
	aspect_ratio_ = as;
}

Mat4x4 Camera::GetProjection()
{
	return Mat4x4::GetProjectionMatrix(
		near_plane_, far_plane_, fov_, aspect_ratio_);
}

Mat4x4 Camera::GetView()
{
	return Mat4x4::GetRotationMatrix(Vec3{0, 0, 45});
}