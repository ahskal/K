#pragma once

class Scene4 : public Scene
{
private:

	Deferred* deferred;   //4���� ����Ÿ��  
	thread* Thread;
	Camera* cam;
	UI* BG;


public:
	Scene4();
	~Scene4();

	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

