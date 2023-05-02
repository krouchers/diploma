#include "utils/camera.hpp"
#include "utils/log.hpp"
#include "glm/gtc/matrix_transform.hpp"

static glm::vec4 kUp{0.f, 1.f, 0.f, 0.f};

Camera::Camera(glm::vec2 const &dim)
{
	SetAs(dim.x / dim.y);
	Reset();
}

void Camera::Reset()
{
	fov_ = 90.f;
	radius_ = 12;
	near_plane_ = 1.f;
	far_plane_ = 110.f;
	rotation_speed_ = translation_speed_ = 9.f;
	radius_speed_ = 4.0f;

	rotation_ = math::Quat::euler(glm::vec3{0.f, 0.f, 0});
	projection_ = glm::perspective(glm::radians(fov_), aspect_ratio_, near_plane_, far_plane_);

	UpdatePos();
	translation_ = glm::translate(glm::mat4x4(1.f), position_);
	view_ = glm::inverse(translation_ * rotation_.to_mat());
}

void Camera::SetAs(float as)
{
	aspect_ratio_ = as;
}

glm::mat4x4 Camera::GetView()
{
	return view_;
}

glm::mat4x4 Camera::GetProjection()
{
	return projection_;
}

glm::vec3 Camera::Front()
{
	return glm::normalize(position_ - glm::vec3(0.f, 0.f, 0.f));
}

void Camera::MoveThroughOrbit(glm::vec2 const &offset)
{
	auto up = glm::normalize(rotation_.rotate(kUp));
	auto dir = Front();
	auto right = glm::normalize(glm::cross(glm::vec3(up), dir));
	rotation_ = math::Quat::axis_angle(kUp, glm::radians(-offset.x * rotation_speed_)) *
				math::Quat::axis_angle(right, glm::radians(offset.y * rotation_speed_)) *
				rotation_;
	UpdatePos();
	UpdateView();

	info("Orbit is moving");
}

void Camera::UpdateView()
{
	translation_ = glm::translate(glm::mat4x4(1.f), position_);
	view_ = glm::inverse(translation_ * rotation_.to_mat());
}

void Camera::MoveThroughRadius(float offset)
{
	radius_ += offset * radius_speed_;
	UpdatePos();
	UpdateView();
}
void Camera::UpdatePos()
{
	position_ = glm::normalize(rotation_.rotate(glm::vec4{0.f, 0.f, 1.f, 0.f}));
	position_ = position_ * radius_;
}

glm::vec3 Camera::GetPosition()
{
	return position_;
}