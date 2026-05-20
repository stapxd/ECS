#include "ECS/Registry.h"

#include <iostream>

class vec2 {
public:
	vec2()
		: x(0), y(0)
	{}

	vec2(float v)
		: x(v), y(v)
	{}

	vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

public:
	float x;
	float y;
};

struct Transform {
	vec2 position = vec2(0.0f);
	vec2 scale = vec2(1.0f);

	Transform(vec2 pos, vec2 s)
		: position(pos), scale(s)
	{}
};

struct RigidBody2D {
	vec2 velocity = vec2(0.0f);
	float density = 1.0f;

	RigidBody2D(vec2 vel, float d)
		: velocity(vel), density(d)
	{}
};

int main() {

	ecs::registry registry;

	ecs::entity entity = registry.create();
	ecs::entity entity2 = registry.create();
	ecs::entity entity3 = registry.create();

	registry.emplace<Transform>(entity, vec2(20.0f), vec2(15.0f));

	registry.emplace<Transform>(entity2, vec2(10.0f), vec2(10.0f));
	registry.emplace<RigidBody2D>(entity2, vec2(0.0f), 2.0f);

	registry.emplace<Transform>(entity3, vec2(55.0f), vec2(55.0f));
	registry.emplace<RigidBody2D>(entity3, vec2(0.0f), 2.0f);

	auto tmAndRbView = registry.group<Transform, RigidBody2D>();

	int i = 0;
	for (auto&& [e, tm, rb] : tmAndRbView) {
		std::cout << "Entity: #" << e.GetID() << "\n";
		std::cout << tm.position.x << " " << tm.position.y << "\n";
		std::cout << tm.scale.x << " " << tm.scale.y << "\n";
		std::cout << "\n";

		tm.position.x += 100;
	}

	registry.destroy(entity2);

	std::cout << "\n\n All Transforms: \n\n";
	auto view = registry.view<Transform>();
	
	i = 0;
	for (auto& transformC : view) {
		printf("component #%d\n", ++i);
		std::cout << transformC.position.x << " " << transformC.position.y << "\n";
		std::cout << transformC.scale.x << " " << transformC.scale.y << "\n";
	}

	std::cout << "\n\n\n";

	Transform* tm = view.get(entity);

	if (tm) {
		std::cout << "Before:\n";
		std::cout << tm->position.x << " " << tm->position.y << "\n";
		std::cout << tm->scale.x    << " " << tm->scale.y    << "\n";

		tm->position.x = 45.0f;
	}

	view = registry.view<Transform>();
	tm = view.get(entity);

	if (tm) {
		std::cout << "After:\n";
		std::cout << tm->position.x << " " << tm->position.y << "\n";
		std::cout << tm->scale.x << " " << tm->scale.y << "\n";
	}

	return 0;
}