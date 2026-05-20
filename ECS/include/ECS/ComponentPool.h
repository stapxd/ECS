#pragma once

#include "SparseSet.h"

namespace ecs {

	template<typename Component>
	class component_pool : public sparse_set {
	public:
		component_pool()
		{}

		template<typename... Args>
		void Emplace(entity e, Args&&... args) {
			uint32_t id = e.GetID();

			uint32_t page = id / s_Limit;
			uint32_t position = id % s_Limit;

			if (page >= m_Sparse.size()) {
				m_Sparse.resize(static_cast<size_t>(page) + 1);
			}

			if (m_Sparse[page].empty()) {
				m_Sparse[page].resize(s_Limit, entity::invalid_entity);
			}

			m_Sparse[page][position] = static_cast<uint32_t>(m_Components.size());

			m_EntitiesWithComponent.push_back(e);
			m_Components.push_back(Component(std::forward<Args>(args)...));
		}

		virtual void Destroy(entity e) override {
			uint32_t id = e.GetID();

			uint32_t page = id / s_Limit;
			uint32_t position = id % s_Limit;

			if (page >= m_Sparse.size() || m_Sparse[page].empty())
				return;

			uint32_t indexToRemove = m_Sparse[page][position]; 
			if (indexToRemove == entity::invalid_entity)
				return;

			uint32_t lastIndex = static_cast<uint32_t>(m_Components.size()) - 1;

			if (indexToRemove != lastIndex) {
				m_EntitiesWithComponent[indexToRemove] = std::move(m_EntitiesWithComponent[lastIndex]);
				m_Components[indexToRemove] = std::move(m_Components[lastIndex]);

				entity movedEntity = m_EntitiesWithComponent[indexToRemove];
				uint32_t movedId = movedEntity.GetID();

				uint32_t movedPage = movedId / s_Limit;
				uint32_t movedPosition = movedId % s_Limit;

				m_Sparse[movedPage][movedPosition] = indexToRemove;
			}

			m_EntitiesWithComponent.pop_back();
			m_Components.pop_back();

			m_Sparse[page][position] = entity::invalid_entity;
		}

		Component* Get(entity e) {
			uint32_t id = e.GetID();

			uint32_t page = id / s_Limit;
			uint32_t position = id % s_Limit;

			if (page >= m_Sparse.size() || m_Sparse[page].empty())
				return nullptr;

			uint32_t index = m_Sparse[page][position];
			if (index == entity::invalid_entity)
				return nullptr;

			return &m_Components[index];
		}

		size_t Size() const { return m_EntitiesWithComponent.size(); }
		const std::vector<entity>& GetEntities() const { return m_EntitiesWithComponent; }

		virtual void clear() override {
			m_Sparse.clear();
			m_EntitiesWithComponent.clear();
			m_Components.clear();
		}

		auto begin() { return m_Components.begin(); }
		auto end()   { return m_Components.end();   }

	private:
		std::vector<Component> m_Components;
	};

}