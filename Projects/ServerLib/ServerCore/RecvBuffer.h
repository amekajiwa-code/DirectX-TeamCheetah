#pragma once

/* ���ۿ��� readPos�� ù��°ĭ�� �ְ�
writePos�� 4��° ĭ�� �ִٸ�
�׻��̰� �о�ü� �ִ� �����Ͱ� �ȴ�.*/

/*w �ں��� ��� �����͸� ����.  ��ȯ���۸� ����Ѵ�. */

/* r�� w�� ��ġ�� �����͸� ���� �о��ٰ� �Ǵ��Ͽ� rw�� �ѹ��� 0����ġ�� �ű��. */

/* ��ȯ�����̱� ������ w�� ������ �Դٸ� r�� 0���迭�� �ű�� w�� ���� ������ ��ŭ���� �ű��.*/

// [r][][][w][][][][]

/* RecvBuffer */

class RecvBuffer
{
	enum { BUFFER_COUNT = 10 };
public:
	RecvBuffer(int32 bufferSize);
	~RecvBuffer();

	void Clean();
	/*�����͸� ���������� Read�ϰų�
	Write �ϸ� Ŀ���� ������ ����*/
	bool OnRead(int32 numOfBytes);
	bool OnWrite(int32 numOfBytes);

	BYTE* ReadPos() { return &_buffer[_readPos]; }
	BYTE* WrtiePos() { return &_buffer[_writePos]; }
	int32 DataSize() { return _writePos - _readPos; } // ������ ũ��
	int32 FreeSize() { return _capacity - _writePos; } // ��� ������ ũ��

private:
	int _capacity = 0;
	int32 _bufferSize = 0;
	int32 _readPos = 0;
	int32 _writePos = 0;
	Vector<BYTE> _buffer; // unsigned char = BYTE
};

