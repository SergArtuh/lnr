#include "MemoryPool.h"

#include <memory>

namespace lnr {
	Data MemoryPool::Alocate(Size size) {
		return reinterpret_cast<Data>(malloc(size));
	}
}