#pragma once
class MonsterData {
public:
	static MonsterData* Create(string name = "MonsterData");

	class Monster* Mon;
	class UI_Monster* UI;
	// 추가 데이터 필드들

	MonsterData();
	~MonsterData();

	void Update();
	void Render(shared_ptr<Shader> pShader = nullptr);
	void Hierarchy();
};
