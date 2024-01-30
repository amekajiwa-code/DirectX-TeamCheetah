#pragma once
class Light : public MonoBehaviour
{
public:
	Light(){}
	virtual ~Light(){}
private:
	shared_ptr<Shader> _shader;
public:
	void SetShader(const shared_ptr<Shader> shader) { _shader = shader; }
public:
	virtual void Start() override;
	virtual void Update() override;
};

