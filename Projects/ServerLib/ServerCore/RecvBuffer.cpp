#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int32 bufferSize) : _bufferSize(bufferSize)
{
	//���� ���� ���ۺ��� ���� ���� ũ�⸦ ũ�� ��Ƽ� rw�� ��ĥȮ���� �ø�
	_capacity = bufferSize * BUFFER_COUNT;
	_buffer.resize(_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	int dataSize = DataSize();
	if (dataSize == 0)
	{
		// r�� w�� ������ ��ġ��� ��ġ ó������ ����
		_readPos = _writePos = 0;
	}
	else
	{
		// ���� ������ ���� ���� 1�� ũ�� �̸��̸�, �����͸� ������ �����.
		if (FreeSize() < _bufferSize)
		{
			//���� ��ȿ�� �����͸� ������ �����.
			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}

		
	}
}

bool RecvBuffer::OnRead(int32 numOfBytes)
{
	//read�� �����Ͱ� ������ ������� ������ false
	if (numOfBytes > DataSize()) return false;
	//�ƴ϶�� _readPos �׸�ŭ �̵�
	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(int32 numOfBytes)
{
	//write�� ���� ������ ������� ������ false
	if (numOfBytes > FreeSize()) return false;
	//�ƴ϶�� _writePos �׸�ŭ �̵�
	_writePos += numOfBytes;
	return true;
}
