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
	/*GameServer에서 네트워크와 관련된
	함수들은 private해주는게 좋으니까
	꼭 필요한 애들만 접근할수 있도록 friend클래스 해준다.*/
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
	/* 외부에서 사용 */
	void Send(SendBufferRef sendBuffer);
	bool Connect();

	/*Disconnect: 연결 해제된 사유 인자로 받음*/
	void				Disconnect(const WCHAR* cause);

	shared_ptr<Service>	GetService() { return _service.lock(); }
	void				SetService(shared_ptr<Service> service) { _service = service; }

public:
						/* 정보 관련 */
	void				SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress			GetAddress() { return _netAddress; }
	SOCKET				GetSocket() { return _socket; }
	//IsConnected:연결되있는지 확인해서 패킷을 계속 Recv해줄것인지 여부를 반환
	bool				IsConnected() { return _connected; }
	//GetSessionRef: SessionRef를 반환하기 위해 캐스팅을 해줌
	SessionRef			GetSessionRef() { return static_pointer_cast<Session>(shared_from_this()); }

private:
						/* 인터페이스 구현 */
	virtual HANDLE		GetHandle() override;
	virtual void		Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
						/* 전송 관련 */
	/*Register가 완료되면 Process에게 알려줌*/
	bool				RegisterConnect();
	bool				RegisterDisconnect();
	void				RegisterRecv();
	void				RegisterSend();

	void				ProcessConnect();
	void				ProcessDisconnect();
	void				ProcessRecv(int32 numOfBytes);
	void				ProcessSend(int32 numOfBytes);
	/*Error코드를 처리하는 함수*/
	void				HandleError(int32 errorCode);

protected:
						/* 컨텐츠 코드에서 재정의 */
	virtual void		OnConnected() { }
	virtual int32		OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void		OnSend(int32 len) { }
	virtual void		OnDisconnected() { }

private:
	/*내부적으로도 서비스의 상황을 알기위해 service 포인터로 들고있기*/
	weak_ptr<Service>	_service;
	SOCKET				_socket = INVALID_SOCKET;
	NetAddress			_netAddress = {};
	Atomic<bool>		_connected = false;

private:
	USE_LOCK;

	/* 수신 관련 */
	RecvBuffer _recvBuffer;

	/* 송신 관련 */
	Queue<SendBufferRef> _sendQueue;
	Atomic<bool> _sendRegistered = false;

private:
	/*IocpEvent 재사용을 하기 위한 멤버 */
	ConnectEvent		_connectEvent;
	DisconnectEvent		_disconnectEvent;
	RecvEvent			_recvEvent;
	SendEvent			_sendEvent;
};

/* PacketSession */

struct PacketHeader
{
	uint16 size;
	uint16 id; // 프로토콜ID ( ex 1=로그인, 2=이동요청)
	bool other; // 다른 패킷이면 참 아니면 거짓
};

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

	PacketSessionRef  GetPacketSessionRef() { return static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	// sealed를 붙여주면 OnRecv를 사용 할 수 없다.
	virtual int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) abstract;

private:
};