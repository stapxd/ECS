#pragma once

#include <stdint.h>

namespace ecs {

	class entity {
	public:
		static uint32_t invalid_entity;

	public:
		entity(uint32_t id)
			: m_ID(id)
		{}

		uint32_t GetID() const { return m_ID; }

		bool IsValid() {
			return m_ID != invalid_entity;
		}

	private:
		uint32_t m_ID = invalid_entity;
	};

}