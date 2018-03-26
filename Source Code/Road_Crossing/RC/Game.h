#ifndef _GAME_H
#define _GAME_H

#include "MyLib.h"

#include "People.h"

#include "Animal.h"
#include "Bird.h"
#include "Dinosaur.h"

#include "Vehicle.h"
#include "Truck.h"
#include "Car.h"

#include "Traffic.h"

#include <Windows.h>
#include <time.h>
#include <iostream>

using namespace std;

class CGame
{
private:
	CPeople m_person;
	CPeople *m_peoArr;//win peoples array
	CTruck *m_truckArr;
	CBird  *m_birdArr;
	CCar   *m_carArr;
	CDinosaur *m_dinoArr;
	CTraffic m_trafic;
	int m_level;
	bool m_Paused;
	int m_speed;
	bool m_Sound_On;
	int m_Mode; // easy = 1, nor = 2, hard = 3;
public:
	CGame(); //Chuẩn bị dữ liệu cho tất cả đôi tượng
	~CGame(); // Hủy tài nguyên đã cấp phát
	int	 getSpeed();
	void setSpeed(int x);
	int	 getSoundMode();
	void setSoundMode(bool mode);
	int	 getMode();
	void setMode(int mode);
	int getCounter();
	void increaseSpeed();
	void drawGame(); //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
	void drawBoard();
	void drawAllEnemy(bool show);
	void levelUp();
	int getLevel();
	void Pause(bool p);
	void Resume();
	bool isPaused();
	CPeople& getPeople();//Lấy thông tin người
	CTraffic& getTraffic(){ return m_trafic; }
	CVehicle** getVehicle();//Lấy danh sách các xe
	CAnimal** getAnimal(); //Lấy danh sách các thú

	void createData();
	void releaseData();

	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu 
	void exitGame(HANDLE); // Thực hiện thoát Thread 
	void startGame(); // Thực hiện bắt đầu vào trò chơi
	void settingGame(); // Thực hiện bắt đầu vào trò chơi

	bool loadGame(const string fileName); // Thực hiện tải lại trò chơi đã lưu
	void LoadFunction();
	bool saveGame(const string fileName); // Thực hiện lưu lại dữ liệu trò chơi
	void pauseGame(HANDLE); // Tạm dừng Thread
	void resumeGame(HANDLE); //Quay lai Thread
	void updatePosPeople(int); //Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosVehicle(); //Thực hiện cho CTRUCK & CCAR di chuyển
	void updatePosAnimal();

	CPeople*& getPeopleArray(){ return m_peoArr; }
	bool addToWinArray();//Đưa m_person vao m_peoArr trả về true nếu được false nếu sai
};

#endif