
#include "Memory.h"

Arena::Arena(uint dataCount, uint dataSize) : 
	blockCount(dataCount),							// quantidade de blocos 
	blockSize(headerSize + dataSize),				// tamanho do bloco = cabeçalho + dado
	memory (new byte[blockCount * blockSize]),		// memória para armazenar dados
	head (memory)									// local da próxima alocação
{
	// liga ponteiros dos cabeçalhos
	byte ** pointer;
	byte * pCurr = head;	
	for (uint i = 0; i < blockCount-1; ++i)
	{
		// calcula a posição do próximo bloco
		byte * pNext = pCurr + blockSize;

		// pointer permite alterar 4 bytes da memória a partir da posição pCurr
		pointer = reinterpret_cast<byte**>(pCurr);
		*pointer = pNext;
		
		// avança para próximo bloco
		pCurr = pNext;
	}
	
	// último cabeçalho aponta para nulo
	pointer = reinterpret_cast<byte**>(pCurr);
	*pointer = nullptr;
}

Arena::~Arena()
{
	delete[] memory;
}

void * Arena::New()
{
	// se não existe memória disponível retorne nulo
	if (!head)
		return nullptr;

	// pegue endereço do bloco de dados
	byte * dataPtr = head + headerSize;

	// cabeça da lista passa para próximo bloco disponível
	byte ** pointer = reinterpret_cast<byte**>(head);
	head = *pointer;

	// retorna endereço de um bloco de dados
	return dataPtr;
}

void Arena::Delete(void * mem)
{
	// se endereço é nulo
	if (!mem)
		return;
	
	// retorna para o endereço do bloco inteiro (incluindo cabeçalho)
	byte * block = static_cast<byte*>(mem) - headerSize;

	// muda ponteiro do cabeçalho para apontar para cabeça da lista
	byte ** pointer = reinterpret_cast<byte**>(block);
	*pointer = head;

	// nova cabeça da lista
	head = block;
}
