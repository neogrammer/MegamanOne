#include <pch.h>
#include <physics.h>
#include <Dynamic.h>
using namespace olc::utils::geom2d;
bool Physics::PointVsRect(rect<float> r_, olc::v_2d<float> pt_)
{
	if (contains(r_, pt_))
	{
		return true;
	}

	return false;
}

bool Physics::RectVsRect(const rect<float>& r1, const rect<float>& r2)
{
	return (r1.pos.x <  r2.right().start.x && r1.right().start.x > r2.pos.x &&
		r1.pos.y <  r2.bottom().start.y && r1.bottom().start.y > r2.pos.y);
}

bool Physics::RectVsRect2(rect<float> r1_, rect<float> r2_)
{
	if (overlaps(r1_, r2_))
		return true;
	return false;
}

bool Physics::RayVsRect(ray<float> ray_, rect<float> target_, olc::v_2d<float>& l_contact_point_, olc::v_2d<float>& l_contact_normal_, float& t_hit_near_)
{
	return false;
}

std::vector<olc::v_2d<float>> Physics::RayVsRect(Dynamic& dyno,rect<float> collider_, ray<float> ray_, float& velx_, float& vely_ , rect<float> target_, olc::v_2d<float>& l_contact_point_, olc::v_2d<float>& l_contact_normal_, float& t_hit_near_)
{

	float lengthOfMove = (float)(sqrt(pow(ray_.origin.x + velx_ * gTime - ray_.origin.x, 2) + pow(ray_.origin.y + vely_ * gTime - ray_.origin.y, 2)));

	auto moveTo = ray_.origin + ray_.direction * lengthOfMove; 
	
	
	
	line<float> aLine{ {ray_.origin},{moveTo} };

	
	std::vector<olc::v_2d<float>> tmpVec;
	line<float> corners[4];

	auto tl = line<float>{ {aLine.start.x - (aLine.start.x - collider_.pos.x),aLine.start.y - (aLine.start.y - collider_.pos.y)}, {aLine.end.x - (aLine.end.x - collider_.pos.x) ,aLine.end.y - (aLine.end.y - collider_.pos.y)} };
	tl.start.x -= aLine.start.x - collider_.pos.x;
	tl.start.y -= aLine.start.y - collider_.pos.y;
	tl.end.x -= aLine.start.x - collider_.pos.x;
	tl.end.y -= aLine.start.y - collider_.pos.y;
	corners[0] = tl;
	auto tr = line<float>{ {aLine.start.x + (collider_.pos.x - aLine.start.x),aLine.start.y - (aLine.start.y - collider_.pos.y)}, {aLine.end.x + (collider_.pos.x - aLine.end.x) ,aLine.end.y - (aLine.end.y - collider_.pos.y)} };
	
	tr.start.x += aLine.start.x - collider_.pos.x;
	tr.start.y -= aLine.start.y - collider_.pos.y;
	tr.end.x += aLine.start.x - collider_.pos.x;
	tr.end.y -= aLine.start.y - collider_.pos.y;
	corners[1] = tr;
	auto bl = line<float>{ {aLine.start.x - (aLine.start.x - collider_.pos.x),aLine.start.y + (collider_.pos.y - aLine.start.y)}, {aLine.end.x - (aLine.end.x - collider_.pos.x) ,aLine.end.y + (collider_.pos.y - aLine.end.y)} };
	bl.start.x -= aLine.start.x - collider_.pos.x;
	bl.start.y += aLine.start.y - collider_.pos.y;
	bl.end.x -= aLine.start.x - collider_.pos.x;
	bl.end.y += aLine.start.y - collider_.pos.y;
	corners[2] = bl;
	auto br = line<float>{ {aLine.start.x + (collider_.pos.x - aLine.start.x),aLine.start.y + (collider_.pos.y - aLine.start.y)}, {aLine.end.x + (collider_.pos.x - aLine.end.x) ,aLine.end.y + (collider_.pos.y - aLine.end.y)} };
	br.start.x += aLine.start.x - collider_.pos.x;
	br.start.y += aLine.start.y - collider_.pos.y;
	br.end.x += aLine.start.x - collider_.pos.x;
	br.end.y += aLine.start.y - collider_.pos.y;
	corners[3] = br;

	tmpVec.clear();

	bool isTL{}, isBR{}, isBL{}, isTR{};
	if (overlaps(corners[0], target_))
	{
		isTL = true;
		auto ray = ray_;
		ray.origin = tl.start;
		ray.direction = {(tl.end.x - ray_.origin.x) / tl.length(),(tl.end.y - ray_.origin.y) / tl.length() };
		tmpVec = intersects(ray, target_);
	}
	else if (overlaps(corners[1], target_))
	{
		isTR = true;
		auto ray = ray_;
		ray.origin = tr.start;
		ray.direction = { (tr.end.x - ray_.origin.x) / tr.length(),(tr.end.y - ray_.origin.y) / tr.length() };
		tmpVec = intersects(ray, target_);
	}
	else if (overlaps(corners[2], target_))
	{
		isBL = true;
		auto ray = ray_;
		ray.origin = bl.start;
		ray.direction = { (bl.end.x - ray_.origin.x) / bl.length(),(bl.end.y - ray_.origin.y) / bl.length() };
		tmpVec = intersects(ray, target_);
	}
	else if (overlaps(corners[3], target_))
	{
		isBR = true;
		auto ray = ray_;
		ray.origin = br.start;
		ray.direction = { (br.end.x - ray_.origin.x) / br.length(),(br.end.y - ray_.origin.y) / br.length() };
		tmpVec = intersects(ray, target_);
	}
	olc::v_2d<float>* shortest{};
	if (tmpVec.size() > 0)
	{
		shortest = &tmpVec[0];

	}
	for (int i = 1; i < tmpVec.size(); i++)
	{
		float length1 =(float)( sqrt(pow(shortest->x - ray_.origin.x, 2) + pow(shortest->y - ray_.origin.y, 2)));
		float length2 =(float)( sqrt(pow(tmpVec[i].x - ray_.origin.x, 2) + pow(tmpVec[i].y - ray_.origin.y, 2)));
		if (length2 < length1)
		{
			shortest = &tmpVec[i];
		}
	}
	if (shortest != nullptr)
	{
		//shortest is the point depicting the displacement needed to move
		float dispX{}, dispY{};
		if (isTL)
		{
			dispX = shortest->x - tl.start.x;
			dispY = shortest->y - tl.start.y;

		}
		else if (isBL)
		{
			dispX = shortest->x - bl.start.x;
			dispY = shortest->y - bl.start.y;
		}
		else if (isBR)
		{
			dispX = shortest->x - br.start.x;
			dispY = shortest->y - br.start.y;
		}
		else if (isTR)
		{
			dispX = shortest->x - tr.start.x;
			dispY = shortest->y - tr.start.y;
		}
		if (dispX != 0.f)
		{
			velx_ = 0.f;
		}
		if (dispY != 0.f)
		{
			vely_ = 0.f;
		}
		dyno.pos.x += dispX;
		dyno.pos.y += dispY;
	}
	return tmpVec;
}

bool Physics::DynamicRectVsRect(rect<float> r_, rect<float> target_, olc::v_2d<float>& cp_, olc::v_2d<float>& cn_, float& ct_, float dt_)
{
	return false;
}

bool Physics::HandleCollisions(Dynamic& dyno_, std::vector<std::shared_ptr<Dynamic>>& sprVec_, float dt_)
{
	return false;
}

bool Physics::PointVsRect(AABB& r_, olc::v_2d<float> pt_)
{
	return false;
}

bool Physics::RectVsRect(AABB& r1_, AABB& r2_)
{
	return false;
}

bool Physics::RayVsRect(ray<float>& ray_, AABB& target_, olc::v_2d<float>& l_contact_point_, olc::v_2d<float>& l_contact_normal_, float& t_hit_near_)
{
	return false;
}

bool Physics::DynamicRectVsRect(AABB r_, AABB& target_, olc::v_2d<float>& cp, olc::v_2d<float>& cn_, float& ct_, float dt_)
{
	return false;
}

bool Physics::HandleCollisions(AABB a_, std::vector<std::shared_ptr<AABB>>& bVec_, float dt_)
{
	return false;
}
