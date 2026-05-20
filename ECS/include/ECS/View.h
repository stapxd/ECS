#pragma once

#include "ComponentPool.h"

namespace ecs {

	template<typename C>
	class view {
	public:
		view(component_pool<C>* pool)
			: m_Pool(pool)
		{}

		C* get(entity e) const {
			return m_Pool->Get(e);
		}

		auto begin() { return m_Pool->begin(); }
		auto end()   { return m_Pool->end();   }

	private:
		component_pool<C>* m_Pool;
	};

}