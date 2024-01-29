#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"

class Service;

/*--------------
	Session
---------------*/

class Session : public IocpObject
{
	/*GameServer���� ��Ʈ��ũ�� ���õ�
	�Լ����� private���ִ°� �����ϱ�
	�� �ʿ��� �ֵ鸸 �����Ҽ� �ֵ��� friendŬ���� ���ش�.*/
	friend class Listener;
	friend class IocpCore;
	friend class Service;

	enum
	{
		BUFFER_SIZE = 0x10000, // 64KB
	};

public:
	Session();
	virtual ~Session();

public:
	/* �ܺο��� ��� */
	void Send(SendBufferRef sendBuffer);
	bool Connect();

	/*Disconnect: ���� ������ ���� ���ڷ� ����*/
	void				Disconnect(const WCHAR* cause);

	shared_ptr<Service>	GetService() { return _service.lock(); }
	void				SetService(shared_ptr<Service> service) { _service = service; }

public:
						/* ���� ���� */
	void				SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress			GetAddress() { return _netAddress; }
	SOCKET				GetSocket() { return _socket; }
	//IsConnected:������ִ��� Ȯ���ؼ� ��Ŷ�� ��� Recv���ٰ����� ���θ� ��ȯ
	bool				IsConnected() { return _connected; }
	//GetSessionRef: SessionRef�� ��ȯ�ϱ� ���� ĳ������ ����
	SessionRef			GetSessionRef() { return static_pointer_cast<Session>(shared_from_this()); }

private:
						/* �������̽� ���� */
	virtual HANDLE		GetHandle() override;
	virtual void		Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
						/* ���� ���� */
	/*Register�� �Ϸ�Ǹ� Process���� �˷���*/
	bool				RegisterConnect();
	bool				RegisterDisconnect();
	void				RegisterRecv();
	void				RegisterSend();

	void				ProcessConnect();
	void				ProcessDisconnect();
	void				ProcessRecv(int32 numOfBytes);
	void				ProcessSend(int32 numOfBytes);
	/*Error�ڵ带 ó���ϴ� �Լ�*/
	void				HandleError(int32 errorCode);

protected:
						/* ������ �ڵ忡�� ������ */
	virtual void		OnConnected() { }
	virtual int32		OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void		OnSend(int32 len) { }
	virtual void		OnDisconnected() { }

private:
	/*���������ε� ������ ��Ȳ�� �˱����� service �����ͷ� ����ֱ�*/
	weak_ptr<Service>	_service;
	SOCKET				_socket = INVALID_SOCKET;
	NetAddress			_netAddress = {};
	Atomic<bool>		_connected = false;

private:
	USE_LOCK;

	/* ���� ���� */
	RecvBuffer _recvBuffer;

	/* �۽� ���� */
	Queue<SendBufferRef> _sendQueue;
	Atomic<bool> _sendRegistered = false;

private:
	/*IocpEvent ������ �ϱ� ���� ��� */
	ConnectEvent		_connectEvent;
	DisconnectEvent		_disconnectEvent;
	RecvEvent			_recvEvent;
	SendEvent			_sendEvent;
};

/* PacketSession */

struct PacketHeader
{
	uint16 size;
	uint16 id; // ��������ID ( ex 1=�α���, 2=�̵���û)
	bool other; // �ٸ� ��Ŷ�̸� �� �ƴϸ� ����
};

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

	PacketSessionRef  GetPacketSessionRef() { return static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	// sealed�� �ٿ��ָ� OnRecv�� ��� �� �� ����.
	virtual int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) abstract;

private:
};