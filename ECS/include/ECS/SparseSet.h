#pragma once

#include "Entity.h"

#include <vector>

namespace ecs {

	class sparse_set {
	public:
		virtual ~sparse_set() = default;

		virtual void clear();
		virtual void Destroy(entity e) = 0;

		bool has(entity e);

		static uint32_t Limit() { return s_Limit; }

	protected:
		static constexpr uint32_t s_Limit = 1000;

		std::vector<std::vector<uint32_t>> m_Sparse;
		std::vector<entity> m_EntitiesWithComponent;
	};

}