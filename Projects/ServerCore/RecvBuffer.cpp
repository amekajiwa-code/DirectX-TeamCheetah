#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int32 bufferSize) : _bufferSize(bufferSize)
{
	//원래 쓰는 버퍼보다 실제 버퍼 크기를 크게 잡아서 rw가 겹칠확률을 늘림
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
		// r과 w가 동일한 위치라면 위치 처음으로 리셋
		_readPos = _writePos = 0;
	}
	else
	{
		// 여유 공간이 원래 버퍼 1개 크기 미만이면, 데이터를 앞으로 땡긴다.
		if (FreeSize() < _bufferSize)
		{
			//먼저 유효한 데이터를 앞으로 땡긴다.
			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}

		
	}
}

bool RecvBuffer::OnRead(int32 numOfBytes)
{
	//read할 데이터가 공간이 충분하지 않으면 false
	if (numOfBytes > DataSize()) return false;
	//아니라면 _readPos 그만큼 이동
	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(int32 numOfBytes)
{
	//write할 여유 공간이 충분하지 않으면 false
	if (numOfBytes > FreeSize()) return false;
	//아니라면 _writePos 그만큼 이동
	_writePos += numOfBytes;
	return true;
}
