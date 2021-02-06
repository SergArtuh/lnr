#include "Vector.h"

#include "MemoryPool.h"

#include <ctime>
#include <iostream>


//#define MEMPOOL

void main() {


	const clock_t begin_time = clock();

	{
		lnr::MemoryPool<sizeof(float) * 4> memPool;

		std::vector<float*> datas(500000);

		int counter = 0;


		for (int i = 0; i < 200000; ++i, counter++) {
#ifdef  MEMPOOL
			float* data = reinterpret_cast<float*>(memPool.Allocate());
#else
			float* data = (float*)malloc(sizeof(float) * 4);
#endif //  MEMPOOL

			data[0] = counter + 0;
			data[1] = counter + 1;
			data[2] = counter + 2;
			data[3] = counter + 3;
			datas.push_back(data);
		}

		Size freeCount = 100000;
		for (int i = 0; i < freeCount; ++i) {
#ifdef  MEMPOOL
			memPool.Dellocate(datas[i]);
#else
			free(datas[i]);
#endif //  MEMPOOL
			//
			
		}
		datas.erase(datas.begin(), datas.begin() + freeCount);

		for (int i = 0; i < 200000; ++i) {
#ifdef  MEMPOOL
			float* data = reinterpret_cast<float*>(memPool.Allocate());
#else
			float* data = (float*)malloc(sizeof(float) * 4);
#endif //  MEMPOOL
			data[0] = i + 0;
			data[1] = i + 1;
			data[2] = i + 2;
			data[3] = i + 3;
			datas.push_back(data);
		}

		for (auto data : datas) {
#ifdef  MEMPOOL
			memPool.Dellocate(data);
#else
			free(data);
#endif //  MEMPOOL			
		}

	}
	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC;
	_sleep(2000);

	EXIT_SUCCESS;
}