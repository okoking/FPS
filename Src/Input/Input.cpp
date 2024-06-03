#include "Input.h"

#define KEY_BUF_LEN	(256)

//現在のフレームのキー情報
char currentKeyBuf[KEY_BUF_LEN] = { 0 };

//前のフレームのキー情報
char preKeyBuf[KEY_BUF_LEN] = { 0 };

//入力制御初期化
void Input::InitInput()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}

//入力制御ステップ
//他のStepより早く呼ぶ
void Input::StepInput()
{
	for (int index = 0; index < KEY_BUF_LEN; index++) {
		preKeyBuf[index] = currentKeyBuf[index];
	}

	//現在のキー情報を取得
	GetHitKeyStateAll(currentKeyBuf);
}

//今押された
bool Input::IsKeyPush(int key_code)
{
	//前フレで押されてない かつ 現フレで押されている
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1) {
		return true;
	}

	//押されていないので false
	return false;
}

//押し続けられているか
bool Input::IsKeyKeep(int key_code)
{
	//前フレで押されている かつ 現フレで押されている
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1) {
		return true;
	}

	//押されていないので false
	return false;
}

//たった今離されたか
bool Input::IsKeyRelease(int key_code)
{
	//前フレで押されている かつ 現フレで押されていない
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0) {
		return true;
	}

	//押されていないので false
	return false;
}

//単純に押されているか
bool Input::IsKeyDown(int key_code)
{
	//現フレで押されている（前フレの状態は関係なし）
	if (currentKeyBuf[key_code] == 1) {
		return true;
	}

	return false;
}