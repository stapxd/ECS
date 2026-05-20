#pragma once

#include "ComponentPool.h"

#include <tuple>
#include <limits>

namespace ecs {

	template<typename... Components>
	class multi_view {
	public:
		using pool_tuple_type = std::tuple<component_pool<Components>*...>;

		multi_view(pool_tuple_type pools)
			: m_Pools(pools)
		{
			m_SmallestPool = FindSmallestPool();
		}

		struct iterator {
			const std::tuple<component_pool<Components>*...>& pools;
			const std::vector<entity>& entities;
			size_t index;

			iterator(const pool_tuple_type& p, const std::vector<entity>& ents, size_t idx)
				: pools(p), entities(ents), index(idx)
			{
				SkipInvalid();
			}

			iterator& operator++() {
				index++;
				SkipInvalid();
				return *this;
			}

			bool operator!=(const iterator& other) const {
				return index != other.index;
			}

			auto operator*() {
				entity e = entities[index];

				return std::tuple_cat(
					std::make_tuple(e),
					std::forward_as_tuple(*(std::get<component_pool<Components>*>(pools)->Get(e))...)
				);
			}

		private:
			bool ValidAll(entity e) const {
				return (std::get<component_pool<Components>*>(pools)->has(e) && ...);
			}

			void SkipInvalid() {
				while (index < entities.size() && !ValidAll(entities[index])) {
					index++;
				}
			}
		};

		iterator begin() const {
			if (!m_SmallestPool) return end();
			return iterator(m_Pools, *m_SmallestPool, 0);
		}

		iterator end() const {
			if (!m_SmallestPool) return iterator(m_Pools, m_EmptyFallback, 0);
			return iterator(m_Pools, *m_SmallestPool, m_SmallestPool->size());
		}

	private:
		std::vector<entity>* FindSmallestPool() {
			std::vector<entity>* smallest = nullptr;
			size_t minSize = std::numeric_limits<size_t>::max();

			auto checkSize = [&](auto* pool) {
				if (pool && pool->Size() < minSize) {
					smallest = const_cast<std::vector<entity>*>(&pool->GetEntities());
					minSize = pool->Size();
				}
			};

			std::apply([&](auto*... poolPtr) { (checkSize(poolPtr), ...); }, m_Pools);

			return smallest;
		}

	private:
		pool_tuple_type m_Pools;
		const std::vector<entity>* m_SmallestPool = nullptr;
		inline static std::vector<entity> m_EmptyFallback{};
	};

}