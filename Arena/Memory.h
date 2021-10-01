
#ifndef MEMORY_ARENA_
#define MEMORY_ARENA_

#include <cstddef>
using std::byte;
using uint = unsigned int;

class Arena
{
private:
	const uint headerSize = sizeof(byte*);
	uint   blockCount;
	uint   blockSize;
	byte * memory;
	byte * head;

public:
	Arena(uint dataCount, uint dataSize);
	~Arena();

	void * New();
	void   Delete(void * mem);
};

#endif
