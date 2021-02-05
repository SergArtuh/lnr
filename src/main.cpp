#include "Vector.h"

#include "MemoryPool.h"

void main() {


	lnr::MemoryPool<sizeof(float) * 4> memPool;

	std::vector<float*> datas;

	for (int i = 0; i < 500; ++i) {
		float* data = reinterpret_cast<float*>(memPool.Alocate());
		data[0] = i + 0;
		data[1] = i + 1;
		data[2] = i + 2;
		data[3] = i + 3;
		datas.push_back(data);
	}
	
	EXIT_SUCCESS;
}