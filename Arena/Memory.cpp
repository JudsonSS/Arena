
#include "Memory.h"

Arena::Arena(uint dataCount, uint dataSize) : 
	blockCount(dataCount),							// quantidade de blocos 
	blockSize(headerSize + dataSize),				// tamanho do bloco = cabe�alho + dado
	memory (new byte[blockCount * blockSize]),		// mem�ria para armazenar dados
	head (memory)									// local da pr�xima aloca��o
{
	// liga ponteiros dos cabe�alhos
	byte ** pointer;
	byte * pCurr = head;	
	for (uint i = 0; i < blockCount-1; ++i)
	{
		// calcula a posi��o do pr�ximo bloco
		byte * pNext = pCurr + blockSize;

		// pointer permite alterar 4 bytes da mem�ria a partir da posi��o pCurr
		pointer = reinterpret_cast<byte**>(pCurr);
		*pointer = pNext;
		
		// avan�a para pr�ximo bloco
		pCurr = pNext;
	}
	
	// �ltimo cabe�alho aponta para nulo
	pointer = reinterpret_cast<byte**>(pCurr);
	*pointer = nullptr;
}

Arena::~Arena()
{
	delete[] memory;
}

void * Arena::New()
{
	// se n�o existe mem�ria dispon�vel retorne nulo
	if (!head)
		return nullptr;

	// pegue endere�o do bloco de dados
	byte * dataPtr = head + headerSize;

	// cabe�a da lista passa para pr�ximo bloco dispon�vel
	byte ** pointer = reinterpret_cast<byte**>(head);
	head = *pointer;

	// retorna endere�o de um bloco de dados
	return dataPtr;
}

void Arena::Delete(void * mem)
{
	// se endere�o � nulo
	if (!mem)
		return;
	
	// retorna para o endere�o do bloco inteiro (incluindo cabe�alho)
	byte * block = static_cast<byte*>(mem) - headerSize;

	// muda ponteiro do cabe�alho para apontar para cabe�a da lista
	byte ** pointer = reinterpret_cast<byte**>(block);
	*pointer = head;

	// nova cabe�a da lista
	head = block;
}
