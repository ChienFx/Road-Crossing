#include "Game.h"
#include "MyLib.h"
#include <thread>
//#include <pthread.h>
using  namespace std;

void UpdateThread();
void CommunicateThread();

bool IS_RUNNING;
bool IS_END_SUB;
int MOVING;
int temp;
CGame cg;
unsigned long count_moving;
bool draw_done;

CVehicle **vehicle_ptr = NULL;
CAnimal  **animal_ptr = NULL;

int main()
{
	draw_done = false;
	int i,j;
	int choice;
	string StrName;
	Common_Init();
	IS_RUNNING = true;
	count_moving = 0;
	cg.startGame();
	
	vehicle_ptr = cg.getVehicle();
	animal_ptr = cg.getAnimal();
	thread t1 (UpdateThread);
	IS_END_SUB = false;
	while (1)
	{
		temp = getch();
		if (temp == 0 || temp == 224)
			temp = 256 + getch(); // Handle multi-char keys
		temp = toupper(temp);
		
		if (!cg.getPeople().isDead() && cg.getLevel() < cg.getCounter())
		{
			if (temp == 27) {
					cg.exitGame(t1.native_handle());
					return 0;
			}
			else if (temp == 'L') {//save game
				while (!draw_done){}
				
				cg.pauseGame(t1.native_handle());

				i = COMMUNICATE_X;
				j = COMMUNICATE_Y;

				TextColor(CO_DEFAULT);
				GotoXY(i, j);
				std::cout << "- File Name:";
				GotoXY(i+1, j + 1);
				ShowCursor(true);
				getline(cin, StrName);
				ShowCursor(false);
				GotoXY(i, j+2);
				if (cg.saveGame(StrName))
					std::cout << "- Saved Done";
				else
					std::cout << "- Saved Fail";
				GotoXY(i, j+3);
				std::cout << "- Any key to continue";
				
				if (getch())
				{
					CleanCommunicateArea();
					cg.resumeGame((HANDLE)t1.native_handle());
				}
			}
			else if (temp == 'T') {//LOAD game
			
				IS_RUNNING = false;
				
				if (t1.joinable())
					t1.join();

				cg.LoadFunction();

				vehicle_ptr = cg.getVehicle();
				animal_ptr = cg.getAnimal();
				
				IS_RUNNING = true;
				/*if (t1.joinable())
					t1.join();*/
				temp = ' ';
				MOVING = temp;
				t1 = thread(UpdateThread);
			}
			else if (temp == 'P' && !cg.isPaused()) {
				
				while (!draw_done){}
				cg.Pause(true);
				cg.pauseGame(t1.native_handle());

				i = COMMUNICATE_X;
				j = COMMUNICATE_Y;
				TextColor(CO_DEFAULT);
				GotoXY(i, j);
				std::cout << "- Paused ";
				GotoXY(i, j+1);
				std::cout << "- Any key to continue";
			}
			else
			{
				//CleanCommunicateArea();
				if (cg.isPaused())
				{
					cg.resumeGame((HANDLE)t1.native_handle());
					cg.Pause(false);
					MOVING = ' ';
				}
				else
					MOVING = temp; //Cập nhật bước di chuyển
			}
		}
		else//dead
		{
			IS_RUNNING = false;
			if (vehicle_ptr)
				delete[] vehicle_ptr;
			if (animal_ptr)
				delete[] animal_ptr;

		Label_Dead_Processing:

			if (cg.getPeople().isDead())
			{
				MyPlaySound(cg.getSoundMode(), PTH_SOUND_GAMEOVER, E_SOUND_LOOP);
				choice = MenuGameOut(false, cg.getSoundMode());
			}
			else
			{
				MyPlaySound(cg.getSoundMode(), PTH_SOUND_WIN, E_SOUND_LOOP);
				choice = MenuGameOut(true, cg.getSoundMode());
			}

			i = NUM_COLS / 4;
			j = NUM_ROWS / 2;

			switch (choice)
			{
			case 0://replay
				cg.resetGame();
				vehicle_ptr = cg.getVehicle();
				animal_ptr = cg.getAnimal();
				break;
			case 1://loadgame

				cg.LoadFunction();

				vehicle_ptr = cg.getVehicle();
				animal_ptr = cg.getAnimal();
							
				break;
			case 2://setting
				cg.settingGame();
				goto Label_Dead_Processing;
				break;

			case 3:
				cg.exitGame(t1.native_handle());
				break;
			}
			
			IS_RUNNING = true;
			if (t1.joinable())
				t1.join();
			temp = ' ';
			MOVING = temp;
			t1 = thread(UpdateThread);
		}
	}
	return 0;
}

void UpdateThread()
{
	int i = COMMUNICATE_X;
	int j = COMMUNICATE_Y;

	while (IS_RUNNING)
	{
		draw_done = false;

		cg.getTraffic().increaseCount();
	
		if (!cg.getPeople().isDead()) //Nếu người vẫn còn sống
			cg.updatePosPeople(MOVING);//Cập nhật vị trí người theo thông tin từ main

		MOVING = ' ';// Tạm khóa không cho di chuyển, chờ nhận phím từ hàm main
			
		if (cg.getTraffic().isLightOff())
			cg.updatePosVehicle();//Cập nhật vị trí xe

		cg.updatePosAnimal(); //Cập nhật vị trí thú
			
		cg.drawGame();//Ve map

		draw_done = true;
			
		animal_ptr = cg.getAnimal();
		vehicle_ptr = cg.getVehicle();

		if ((cg.getPeople().isImpact(vehicle_ptr)) || (cg.getPeople().isImpact(animal_ptr)))
		{
			// Xử lý khi đụng xe hay thú
			IS_RUNNING = false;
			TextColor(CO_PEOPLE_DEAD);
			cg.getPeople().Draw();

			TextColor(CO_DEFAULT);
			GotoXY(i, j);
			std::cout << "- CRASH !  ";
			GotoXY(i, j + 1);
			std::cout << "- Any key to continue";
			//std::cout << "                     ";
			cg.getPeople().Die();
			cg.getPeople().Tell(cg.getSoundMode());
			
		}

		if (cg.getPeople().isFinish())
		{
			//kiem tra de cho vao mang
			if (cg.addToWinArray())//finish
			{
				cg.getPeople() = CPeople(rand() % (NUM_COLS - 1) + 1, NUM_ROWS - 1);
				cg.levelUp();

				TextColor(CO_DEFAULT);
				GotoXY(i, j);
				std::cout << "- Level up!   ";
				GotoXY(i, j + 1);
				std::cout << "                      ";

				if (cg.getLevel() == cg.getCounter())
				{
					IS_RUNNING = false;
					GotoXY(i, j);
					std::cout << "- VICTORY   ";
					GotoXY(i, j + 1);
					std::cout << "- Any key to continue";
				}

				if (vehicle_ptr)
					delete[] vehicle_ptr;
				if (animal_ptr)
					delete[] animal_ptr;

				vehicle_ptr = cg.getVehicle();
				animal_ptr = cg.getAnimal();
			}
			else//dead
			{
				IS_RUNNING = false;
				
				TextColor(7);
				GotoXY(i, j);
				std::cout << "- CRASH !  ";
				GotoXY(i, j + 1);
				std::cout << "                  ";
				cg.getPeople().Tell(cg.getSoundMode());
				cg.getPeople().Die();

			}
		}
		Sleep(cg.getSpeed());//150 -> 10
	}
	IS_END_SUB = true;
}