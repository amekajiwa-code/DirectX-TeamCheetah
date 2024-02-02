#pragma once

/* 버퍼에서 readPos가 첫번째칸에 있고
writePos가 4번째 칸에 있다면
그사이가 읽어올수 있는 데이터가 된다.*/

/*w 뒤부터 계속 데이터를 쓴다.  순환버퍼를 사용한다. */

/* r와 w가 겹치면 데이터를 전부 읽었다고 판단하여 rw를 한번에 0번위치로 옮긴다. */

/* 순환버퍼이기 때문에 w가 끝까지 왔다면 r을 0번배열로 옮기고 w도 원래 떨어진 만큼으로 옮긴다.*/

// [r][][][w][][][][]

/* RecvBuffer */

class RecvBuffer
{
	enum { BUFFER_COUNT = 10 };
public:
	RecvBuffer(int32 bufferSize);
	~RecvBuffer();

	void Clean();
	/*데이터를 성공적으로 Read하거나
	Write 하면 커서를 앞으로 땡김*/
	bool OnRead(int32 numOfBytes);
	bool OnWrite(int32 numOfBytes);

	BYTE* ReadPos() { return &_buffer[_readPos]; }
	BYTE* WrtiePos() { return &_buffer[_writePos]; }
	int32 DataSize() { return _writePos - _readPos; } // 데이터 크기
	int32 FreeSize() { return _capacity - _writePos; } // 사용 가능한 크기

private:
	int _capacity = 0;
	int32 _bufferSize = 0;
	int32 _readPos = 0;
	int32 _writePos = 0;
	Vector<BYTE> _buffer; // unsigned char = BYTE
};

