#pragma once

#include "ECS/View.h"
#include "ECS/MultiView.h"
#include "ECS/ComponentTypeID.h"

#include <memory>

namespace ecs {

	class registry {
	public:
		entity create() {
			m_EntityIDs.emplace_back(m_CurrentId);
			m_CurrentId++;
			return m_EntityIDs[m_CurrentId - 1];
		}

		void clear() {
			for (auto& pool : m_Pools)
				pool->clear();

			m_EntityIDs.clear();
			m_CurrentId = 0;
		}

		void destroy(entity e) {
			for (auto& pool : m_Pools)
				pool->Destroy(e);
		}

		template<typename C>
		void remove(entity e) {
			auto pool = GetPool<C>();
			pool->Destroy(e);
		}

		template<typename C>
		C* get(entity e) {
			auto pool = GetPool<C>();
			return pool->Get(e);
		}

		template<typename C>
		bool has(entity e) {
			auto pool = GetPool<C>();
			return pool->has(e);
		}

		template<typename C, typename... Args>
		void emplace(entity e, Args&&... args) {
			if (!e.IsValid())
				return;

			auto pool = GetPool<C>();

			if (pool->has(e))
				return;

			pool->Emplace(e, std::forward<Args>(args)...);
		}

		template<typename C>
		ecs::view<C> view() {
			return ecs::view<C>(GetPool<C>());
		}

		template<typename... C>
		multi_view<C...> group() {
			return multi_view<C...>(std::make_tuple(GetPool<C>()...));
		}

	private:
		template<typename C>
		component_pool<C>* GetPool() {
			const uint32_t typeId = component_type_id::Get<C>();

			if (typeId >= m_Pools.size()) {
				m_Pools.resize(static_cast<size_t>(typeId) + 1);
			}

			if (!m_Pools[typeId]) {
				m_Pools[typeId] = std::make_unique<component_pool<C>>();
			}

			return static_cast<component_pool<C>*>(m_Pools[typeId].get());
		}

	private:
		std::vector<std::unique_ptr<sparse_set>> m_Pools;

		std::vector<entity> m_EntityIDs;
		uint32_t m_CurrentId = 0;
	};

}