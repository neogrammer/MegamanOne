#ifndef PHYSICS_HPP__
#define PHYSICS_HPP__
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>
#include <utility>
#include <SFML/System/Time.hpp>
#include <Cfg.h>
#include <globals.h>
#include <3rdParty/olcUTIL_Geometry2D.h>
#include <AABB.h>
class Dynamic;
struct Physics
{
	Physics() = delete;
	Physics(const Physics&) = delete;
	Physics& operator=(const Physics&) = delete;

	static bool PointVsRect(olc::utils::geom2d::rect<float> r_, olc::v_2d<float> pt_);
	static bool RectVsRect(olc::utils::geom2d::rect<float> r1_, olc::utils::geom2d::rect<float> r2_);
	static bool RayVsRect(olc::utils::geom2d::ray<float> ray_, olc::utils::geom2d::rect<float> target_, olc::v_2d<float>& l_contact_point_, olc::v_2d<float>& l_contact_normal_, float& t_hit_near_);

	static std::vector<olc::v_2d<float>> RayVsRect(Dynamic& dyno, olc::utils::geom2d::rect<float> collider_, olc::utils::geom2d::ray<float> ray_, float& velx_, float& vely_, olc::utils::geom2d::rect<float> target_, olc::v_2d<float>& l_contact_point_, olc::v_2d<float>& l_contact_normal_, float& t_hit_near_);

	static bool DynamicRectVsRect(olc::utils::geom2d::rect<float> r_, olc::utils::geom2d::rect<float> target_, olc::v_2d<float>& cp_, olc::v_2d<float>& cn_, float& ct_, float dt_);
	static bool HandleCollisions(Dynamic& dyno_, std::vector<std::shared_ptr<Dynamic>>& sprVec_, float dt_);

	static bool PointVsRect(AABB& r_, olc::v_2d<float> pt_);
	static bool RectVsRect(AABB& r1_, AABB& r2_);
	static bool RayVsRect(olc::utils::geom2d::ray<float>& ray_, AABB& target_, olc::v_2d<float>& l_contact_point_, olc::v_2d<float>& l_contact_normal_, float& t_hit_near_);
	static bool DynamicRectVsRect(AABB r_, AABB& target_, olc::v_2d<float>& cp, olc::v_2d<float>& cn_, float& ct_, float dt_);
	static bool HandleCollisions(AABB a_, std::vector<std::shared_ptr<AABB>>& bVec_, float dt_);
};

#endif