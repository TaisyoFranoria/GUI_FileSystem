#include"DxLib.h"
#include<vector>
#include<string>

class DropFile {
	char filepath[30 + 1][256];
public :
	int count;

	DropFile() {
		count = 0;
		filepath[0][0] = 0;
	}

	DropFile(bool init) {
		if (init) {
			DragFileInfoClear();
			SetAlwaysRunFlag(true);
			SetDragFileValidFlag(true);
		}
		count = 0;
		filepath[0][0] = 0;
	}

	~DropFile() {

	}

	const char* operator[](const int i)const {return filepath[i];}

	void check() {
		int num = GetDragFileNum();
		if (num == 0)return;
		for (int i = 0; GetDragFilePath(filepath[i]) == 0; i++);
		filepath[num][0] = 0;
		count = num;
		DragFileInfoClear();
		return;
	}


};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowText("ファイルサーバーワープ！！");
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	DropFile dr(true);

	std::vector<std::string> path;
	

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		dr.check();
		for (int i = 0; i < dr.count; i++) {
			path.push_back(dr[i]);
			DrawString(0, i*16, path[i].c_str(), 0xFFFFFF);
		}

		

		if (CheckHitKey(KEY_INPUT_ESCAPE))break;
	}
	DxLib_End();
	return  0;
}