#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective,
	Orthographic
};

class Camera : public Component
{
	using Super = Component;
public:
	Camera();
	virtual ~Camera();
//member
private:
	ProjectionType _type = ProjectionType::Orthographic;
public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;
//function
public:
	void SetProjectionType(ProjectionType type) { _type = type; }
public:
	ProjectionType GetProjectionType() const { return _type; }
public:
	void UpdateMatrix();
public:
	virtual void Update() override;
};

