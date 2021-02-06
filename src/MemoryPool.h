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

				if (!alocatedData) {
					throw std::exception("Unable to allocate memory for Chunk block");
				}

				m_chunks = reinterpret_cast<Chunk*>(alocatedData);
				m_data = alocatedData + CHUNK_STRUCT_SIZE * CHUNKS_PER_BLOCK;
	

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
				if (m_chunks) {
					free(m_chunks);
					m_chunks = nullptr;
					m_data = nullptr;
				}
			}

			Data AllocateChunk() {
				Byte* freeChunkData = m_nextFreeChunk->Data;
				m_nextFreeChunk = m_nextFreeChunk->Next;
				m_freeChunks--;

				return freeChunkData;
			}

			void Deallocate(Data data) {
				Size chunkIdx = ((static_cast<Byte*>(data) - m_data) / chunkSize);
				Chunk* chunks = m_chunks + chunkIdx;

				chunks->Data = reinterpret_cast<Byte*>( data );
				chunks->Next = m_nextFreeChunk;
				m_nextFreeChunk = chunks;

				m_freeChunks++;
			}

			bool IsFreeChunk() const {
				return m_nextFreeChunk;
			}

			bool IsFreeChunkBlock() const {
				return m_freeChunks == CHUNKS_PER_BLOCK;
			}

			bool IsBlockOccupyData(Data data) {
				CByte* dataStart = m_data;
				CByte* dataEnd = dataStart + (CHUNKS_PER_BLOCK * chunkSize);

				return data >= dataStart && data < dataEnd;
			}


			UI16 m_freeChunks = CHUNKS_PER_BLOCK;
			Byte * m_data = nullptr;
			Chunk * m_chunks = nullptr;
			Chunk * m_nextFreeChunk = nullptr;
		};

	public:
		MemoryPool() {
			ChunkBlock chunkBlock;
			m_blocks.push_back(std::move(chunkBlock));
		}

		~MemoryPool() {
			for (auto& block : m_blocks) {
				block.Release();
			}
		}

		Data Allocate() {
			for (auto block = m_blocks.rbegin(); block != m_blocks.rend(); block++) {
				if (block->IsFreeChunk()) {
					return block->AllocateChunk();
				}
			}

			ChunkBlock newChunk;
			m_blocks.push_back(newChunk);
			return newChunk.AllocateChunk();
		}

		void Dellocate(Data data) {
			for (auto block = m_blocks.begin(); block != m_blocks.end(); block++) {
				if (block->IsBlockOccupyData(data)) {
					block->Deallocate(data);

					if (block->IsFreeChunkBlock()) {
						block->Release();
						m_blocks.erase(block);
						return;
					}
				}
			}
		}
	private:
		
		std::list<ChunkBlock> m_blocks;
	};
}