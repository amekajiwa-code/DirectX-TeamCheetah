#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#pragma comment(lib, "../../../Libraries/lib/server/ServerCore.lib")

#include "CorePch.h"
#include "../..//Engine/SimpleMath.h"

using Vec2 = DirectX::SimpleMath::Vector2;
using Vec3 = DirectX::SimpleMath::Vector3;