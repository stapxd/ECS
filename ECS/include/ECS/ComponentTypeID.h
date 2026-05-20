#pragma once

#include <stdint.h>

namespace ecs {

	class component_type_id {
	public:
		template<typename C>
		static uint32_t Get() {
			static uint32_t id = s_Counter++;
			return id;
		}

	private:
		static uint32_t s_Counter;
	};

}