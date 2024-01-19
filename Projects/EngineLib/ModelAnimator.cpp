#include "pch.h"
#include "ModelAnimator.h"

ModelAnimator::ModelAnimator() : Super(ComponentType::ModelAnimator)
{
}

ModelAnimator::ModelAnimator(shared_ptr<Shader> shader) : Super(ComponentType::ModelAnimator), _shader(shader)
{
}

ModelAnimator::~ModelAnimator()
{
}

void ModelAnimator::CreateTexture()
{
	if (_model->GetAnimationCount() == 0)
		return;

	_animTransforms.resize(_model->GetAnimationCount());
	for (uint32 i = 0; i < _model->GetAnimationCount(); i++)
		CreateAnimationTransform(i);

	// Creature Texture
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = MAX_MODEL_TRANSFORMS * 4;
		desc.Height = MAX_MODEL_KEYFRAMES;
		desc.ArraySize = _model->GetAnimationCount();
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // 16바이트
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;

		const uint32 dataSize = MAX_MODEL_TRANSFORMS * sizeof(Matrix);
		const uint32 pageSize = dataSize * MAX_MODEL_KEYFRAMES;
		void* mallocPtr = ::malloc(pageSize * _model->GetAnimationCount());

		// 파편화된 데이터를 조립한다.
		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			uint32 startOffset = c * pageSize;

			BYTE* pageStartPtr = reinterpret_cast<BYTE*>(mallocPtr) + startOffset;

			for (uint32 f = 0; f < MAX_MODEL_KEYFRAMES; f++)
			{
				void* ptr = pageStartPtr + dataSize * f;
				::memcpy(ptr, _animTransforms[c].transforms[f].data(), dataSize);
			}
		}

		// 리소스 만들기
		vector<D3D11_SUBRESOURCE_DATA> subResources(_model->GetAnimationCount());

		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			void* ptr = (BYTE*)mallocPtr + c * pageSize;
			subResources[c].pSysMem = ptr;
			subResources[c].SysMemPitch = dataSize;
			subResources[c].SysMemSlicePitch = pageSize;
		}

		HRESULT hr = DEVICE()->CreateTexture2D(&desc, subResources.data(), _texture.GetAddressOf());
		CHECK(hr);

		::free(mallocPtr);
	}

	// Create SRV
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipLevels = 1;
		desc.Texture2DArray.ArraySize = _model->GetAnimationCount();

		HRESULT hr = DEVICE()->CreateShaderResourceView(_texture.Get(), &desc, _srv.GetAddressOf());
		CHECK(hr);
	}
}

void ModelAnimator::CreateAnimationTransform(uint32 index)
{
	vector<Matrix> tempAnimBoneTransforms(MAX_MODEL_TRANSFORMS, Matrix::Identity);

	shared_ptr<ModelAnimation> animation = _model->GetAnimationByIndex(index);

	for (uint32 f = 0; f < animation->frameCount; f++)
	{
		for (uint32 b = 0; b < _model->GetBoneCount(); b++)
		{
			shared_ptr<ModelBone> bone = _model->GetBoneByIndex(b);

			Matrix matAnimation;

			shared_ptr<ModelKeyframe> frame = animation->GetKeyframe(bone->name);

			if (frame != nullptr)
			{
				ModelKeyframeData& data = frame->transforms[f];

				Matrix S, R, T;
				S = Matrix::CreateScale(data.scale.x, data.scale.y, data.scale.z);
				R = Matrix::CreateFromQuaternion(data.rotation);
				T = Matrix::CreateTranslation(data.translation.x, data.translation.y, data.translation.z);
				matAnimation = S * R * T;
			}
			else
			{
				matAnimation = Matrix::Identity;
			}

			Matrix toRootMatrix = bone->transform;
			Matrix invGlobal = toRootMatrix.Invert();
			int32 parentIndex = bone->parentIndex;

			Matrix matParent = Matrix::Identity;
			if (parentIndex >= 0)
				matParent = tempAnimBoneTransforms[parentIndex];

			tempAnimBoneTransforms[b] = matAnimation * matParent;

			// 결론
			_animTransforms[index].transforms[f][b] = invGlobal * tempAnimBoneTransforms[b];
		}
	}
}

void ModelAnimator::Start()
{
	_model = GetGameObject()->GetModelRenderer()->GetModel();
	assert(_model != nullptr);

	if (_model)
	{
		if (_anims.size() > 0)
		{
			_anims.clear();
		}

		uint32 count = _model->GetAnimationCount();
		if (count > 0)
		{
			for (uint32 i = 0; i < count; i++)
			{
				_anims.push_back(_model->GetAnimationByIndex(i));
			}
		}
	}

	_shader = GetGameObject()->GetModelRenderer()->GetShader();
	assert(_shader != nullptr);
}

//트윈 이전
//void ModelAnimator::Update()
//{
//	if (_isPlay)
//	{
//		if (_model == nullptr || _shader == nullptr)
//			return;
//
//		if (_texture == nullptr)
//			CreateTexture();
//
//		if (_isLoop)
//		{
//			
//			_keyFrameDesc.sumTime += MANAGER_TIME()->GetDeltaTime();
//			if (_currentAnim)
//			{
//				_timePerFrame = 1 / (_currentAnim->frameRate * _keyFrameDesc.speed);
//
//				if (_keyFrameDesc.sumTime >= _timePerFrame)
//				{
//					_keyFrameDesc.currentFrame = (_keyFrameDesc.currentFrame + 1) % _currentAnim->frameCount;
//					_keyFrameDesc.nextFrame = (_keyFrameDesc.currentFrame + 1) % _currentAnim->frameCount;
//					_keyFrameDesc.sumTime = 0.f;
//				}
//
//				_keyFrameDesc.ratio = (_keyFrameDesc.sumTime / _timePerFrame);
//			}
//			// 애니메이션 현재 프레임 정보
//			MANAGER_RENDERER()->PushKeyframeData(_keyFrameDesc);
//
//			// SRV를 통해 정보 전달
//			_shader->GetSRV("TransformMap")->SetResource(_srv.Get());
//		}
//	}
//}

void ModelAnimator::Update()
{
	if (_isPlay)
	{
		if (_model == nullptr || _shader == nullptr)
			return;

		if (_texture == nullptr)
			CreateTexture();

		//루프 애니메이션
		if (_isLoop)
		{
			//현재 애니메이션
			if (_tweenDesc.current.animIndex >= 0)
			{
				if (_currentAnim)
				{
					_tweenDesc.current.sumTime += MANAGER_TIME()->GetDeltaTime();
					_timePerFrame = 1 / (_currentAnim->frameRate * _tweenDesc.current.speed);

					if (_tweenDesc.current.sumTime >= _timePerFrame)
					{
						_tweenDesc.current.sumTime = 0;
						_tweenDesc.current.currentFrame = (_tweenDesc.current.currentFrame + 1) % _currentAnim->frameCount;
						_tweenDesc.current.nextFrame = (_tweenDesc.current.currentFrame + 1) % _currentAnim->frameCount;

					}

					_tweenDesc.current.ratio = (_tweenDesc.current.sumTime / _timePerFrame);
				}
			}
			//다음 애니메이션 예약 시
			if (_tweenDesc.next.animIndex >= 0)
			{
				_tweenDesc.tweenSumTime += MANAGER_TIME()->GetDeltaTime();
				_tweenDesc.tweenRatio = _tweenDesc.tweenSumTime / _tweenDesc.tweenDuration;

				if (_tweenDesc.tweenRatio >= 1.f)
				{
					_tweenDesc.current = _tweenDesc.next;
					_tweenDesc.ClearNextAnim();
				}
				else
				{
					if (_nextAnim)
					{
						_tweenDesc.next.sumTime += MANAGER_TIME()->GetDeltaTime();

						float timeperFrame = 1.f / (_nextAnim->frameRate * _tweenDesc.next.speed);

						if (_tweenDesc.next.ratio >= 1.f)
						{
							_tweenDesc.next.sumTime = 0;
							_tweenDesc.next.currentFrame = (_tweenDesc.next.currentFrame + 1) % _nextAnim->frameCount;
							_tweenDesc.next.nextFrame = (_tweenDesc.next.currentFrame + 1) % _nextAnim->frameCount;
						}
						_tweenDesc.next.ratio = _tweenDesc.next.sumTime / timeperFrame;
					}
				}
			}
		}
		//논 루프 애니메이션
		else
		{

		}

		// 애니메이션 현재 프레임 정보
		MANAGER_RENDERER()->PushTweenData(_tweenDesc);

		// SRV를 통해 정보 전달
		_shader->GetSRV("TransformMap")->SetResource(_srv.Get());
	}
}