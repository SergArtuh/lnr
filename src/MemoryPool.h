#pragma once
#include "types.h"

#include <vector>
#include <list>

namespace lnr {

	template<Size chunkSize>
	class MemoryPool final {

		struct Chunk {
			Byte* Data;
			Chunk* Next;
		};


		class ChunkBlock {

			static const Size PAGE_SIZE = 0x1000;
			static const Size CHUNK_STRUCT_SIZE = sizeof(Chunk);
			constexpr static const Size CHUNKS_PER_BLOCK = (PAGE_SIZE) / (chunkSize + CHUNK_STRUCT_SIZE);

		public:
			ChunkBlock() {
				Byte * alocatedData = reinterpret_cast<Byte*>(malloc(PAGE_SIZE));

				if (alocatedData) {
					std::exception("Unable to allocate memory for Chunk block");
				}

				m_chunks = reinterpret_cast<Chunk*>(alocatedData);
				m_data = alocatedData + CHUNK_SIZE * CHUNKS_PER_BLOCK;
	

				m_chunks[0].Data = m_data;
				m_chunks[CHUNKS_PER_BLOCK - 1].Next = nullptr;

				m_nextFreeChunk = &m_chunks[0];

				Byte* currentData = m_data + chunkSize;
				Chunk* currentChunk = &m_chunks[1];

				for (int i = 1; i < CHUNKS_PER_BLOCK; ++i) {
					m_chunks[i - 1].Next = m_chunks + i;
					m_chunks[i].Data = currentData;
					currentData += chunkSize;
				}
			}

			void Release() {
				if (m_data) {
					free(m_data);
				}
			}

			Data AlocateChunk() {
				Byte* freeChunkData = m_nextFreeChunk->Data;
				m_nextFreeChunk = m_nextFreeChunk->Next;

				return freeChunkData;
			}

			bool IsFreeChunk() const {
				return m_nextFreeChunk;
			}

			Byte * m_data = nullptr;
			Chunk * m_chunks = nullptr;
			Chunk * m_nextFreeChunk = nullptr;
		};

	public:
		MemoryPool() {
			ChunkBlock chunkBlock;
			m_blocks.push_back(std::move(chunkBlock));
		}

		MemoryPool() {
			for (auto& block : m_blocks) {
				block.Release();
			}
		}

		Data Alocate() {
			for (auto block = m_blocks.rbegin(); block != m_blocks.rend(); block++) {
				if (block->IsFreeChunk()) {
					return block->AlocateChunk();
				}
			}

			ChunkBlock newChunk;
			m_blocks.push_back(newChunk);
			return newChunk.AlocateChunk();
		}
	private:
		
		std::list<ChunkBlock> m_blocks;
	};
}