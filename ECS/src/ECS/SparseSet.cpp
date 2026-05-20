#include "ECS/SparseSet.h"

namespace ecs {
	
	void sparse_set::clear() {
		m_Sparse.clear();
		m_EntitiesWithComponent.clear();
	}

	bool sparse_set::has(entity e) {
		const uint32_t id = e.GetID();

		uint32_t page = id / s_Limit;
		uint32_t position = id % s_Limit;

		if (page >= m_Sparse.size() || m_Sparse[page].empty())
			return false;

		uint32_t denseIdx = m_Sparse[page][position];

		return denseIdx < m_EntitiesWithComponent.size() && m_EntitiesWithComponent[denseIdx].GetID() == id;
	}

}