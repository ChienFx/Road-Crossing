#include "Game.h"

//Chuẩn bị dữ liệu cho tất cả đối tượng
CGame::CGame()
{
	m_level = 0;
	m_Sound_On = true;
	setMode(E_EASY); //easy
	m_Paused = false;
	m_birdArr = NULL;
	m_carArr = NULL;
	m_dinoArr = NULL;
	m_truckArr = NULL;
	m_peoArr = NULL;
}

int	CGame::getSpeed(){ return m_speed; }
void CGame::setSpeed(int x){ m_speed = x; }
int	 CGame::getSoundMode(){ return m_Sound_On; }
void CGame::setSoundMode(bool mode){ m_Sound_On = mode; }
int	 CGame::getMode(){ return m_Mode; }
void CGame::setMode(int mode){
	m_Mode = mode;
	switch (m_Mode)
	{
	case E_EASY:
		setSpeed(SPEED_EASY);
		break;
	case E_NORMAL:
		setSpeed(SPEED_NORMAL);
		break;
	case E_HARD:
		setSpeed(SPEED_HARD);
		break;
	}
}
int CGame::getCounter(){
	switch (m_Mode)
	{
		case E_EASY: return COUNTER_EASY;
		case E_NORMAL:return COUNTER_NORMAL;
		case E_HARD: return COUNTER_HARD;
	}
	return 0;
}
void CGame::releaseData()
{
	if (m_birdArr != NULL)
	{
		delete[]m_birdArr;
		m_birdArr = NULL;
	}
	if (m_carArr != NULL)
	{
		delete[]m_carArr; m_carArr = NULL;
	}
	if (m_truckArr != NULL)
	{
		delete[]m_truckArr; m_truckArr = NULL;
	}
	if (m_dinoArr != NULL)
	{
		delete[]m_dinoArr; m_dinoArr = NULL;
	}
	if (m_peoArr != NULL)
	{
		delete[]m_peoArr;
		m_peoArr = NULL;
	}
}

CGame::~CGame()
{
	this->releaseData();
}

void CGame::resetGame()
{
	this->createData();
}

void CGame::createData()
{
	this->releaseData();
	loadGame("default.txt");
}

void CGame::increaseSpeed(){
	m_speed -= 10; 
	if (m_speed < 0)
		m_speed = 0;
}

void CGame::drawGame()
{
	drawBoard();

	//Draw win people
	int n = CPeople::getAmount() - 1;//không tính m_person
	for (int i = 0; i < n; i++)
	{	
		m_peoArr[i].Draw();
	}
	//draw Person
	TextColor(CO_PEOPLE);
	m_person.Draw();
}

void CGame::drawBoard()
{
	//Draw traffic
	int pos_x, pos_y;

	TextColor(CO_TEXTSCAN);
	GotoXY(0, NUM_ROWS + 1);
	//std::cout << "   Hotkey:  MOVE: WSAD   P: Pause  L: Save   ESC: Exit";
	std::cout << "Hotkey:  MOVE: WSAD  P: Pause  L: Save  T: Load   ESC: Exit";
	TextColor(7);
	//-----------
	pos_x = COMMUNICATE_X;
	pos_y = 0;
	
	GotoXY(pos_x + 0, pos_y + 0);
	TextColor(CO_TITLE);
	std::cout << "    ROAD CROSSING     ";
	
	TextColor(CO_DEFAULT);
	
	GotoXY(pos_x + 0, pos_y + 2);
	cout << "- LEVEL  :  ";
	switch (this->getMode())
	{
	case E_EASY: cout << "EASY   "; break;
	case E_NORMAL: cout << "NORMAL "; break;
	case E_HARD: cout << "HARD   "; break;
	}
	GotoXY(pos_x + 0, pos_y + 3);
	cout << "- Counter:  " << CPeople::getAmount() - 1 << "/" << getCounter();
	
	pos_y += 4;
	
	GotoXY(pos_x + 0, pos_y + 1);
	TextColor(CO_TITLE);
	std::cout << "     TRAFFIC LIGHT    ";
	
	TextColor(14);
	GotoXY(pos_x + 0, pos_y + 2);
	
	if (m_trafic.isLightOn())
	{
		GotoXY(pos_x + 2, pos_y + 3);
		TextColor(202);//red full
		std::cout << " ";
		TextColor(12);
		std::cout << " " << setw(2) << m_trafic.getTimeOn() - m_trafic.getCount();

		GotoXY(pos_x + 2, pos_y + 4);
		TextColor(34);//green off
		std::cout << " ";
		TextColor(2); std::cout << "  0";
		TextColor(7);
	}
	else
	{
		GotoXY(pos_x + 2, pos_y + 3);
		TextColor(68);//red off
		std::cout << " ";
		TextColor(4); std::cout << "  0";

		GotoXY(pos_x + 2, pos_y + 4);
		TextColor(170);//green full
		std::cout << " ";
		TextColor(10);
		std::cout << " " << setw(2) << m_trafic.getTimeOff() - m_trafic.getCount();
		TextColor(7);
	}
	//Draw Introduction
	pos_y = COMMUNICATE_Y-2;

	GotoXY(pos_x + 0, pos_y + 1);
	TextColor(CO_TITLE);
	std::cout << "      COMMUNICATE     ";
	TextColor(14);
	GotoXY(pos_x + 0, pos_y + 2);

	TextColor(CO_DEFAULT);
	if (!this->isPaused())//paused
	{
		GotoXY(pos_x + 0, pos_y + 2);
		std::cout << "- Running   ";
		GotoXY(pos_x + 0, pos_y + 3);
		std::cout << "                     ";
	}
		
}

void CGame::drawAllEnemy(bool show)
{
	//Draw vehicle
	int n;
	//n = CTruck::getAmount();
	n = m_level;
	TextColor(CO_PEOPLE);
	for (int i = 0; i < n; i++)
	{
		if (show)
			m_peoArr[i].Draw();
		else
			m_peoArr[i].Erase();
	}
	//Draw vehicle
	n = CTruck::getAmount();
	TextColor(CO_TRUCK);
	for (int i = 0; i < n; i++)
	{	
		if (show)
			m_truckArr[i].Draw();
		else
			m_truckArr[i].Erase();
	}
	
	n = CCar::getAmount();
	TextColor(CO_CAR);
	for (int i = 0; i < n; i++)
	{	
		if (show)
			m_carArr[i].Draw();
		else
			m_carArr[i].Erase();
	}
	//Draw animal
	n = CBird::getAmount();
	TextColor(CO_BIRD);
	for (int i = 0; i < n; i++)
	{
		if (show)
			m_birdArr[i].Draw();
		else
			m_birdArr[i].Erase();
	}
	n = CDinosaur::getAmount();
	TextColor(CO_DINO);
	for (int i = 0; i < n; i++)
	{
		if (show)
			m_dinoArr[i].Draw();
		else
			m_dinoArr[i].Erase();
	}
	TextColor(CO_DEFAULT);
}

CPeople& CGame::getPeople()
{
	return m_person;
}

CVehicle** CGame::getVehicle()//Lấy danh sách các xe
{
	int n = CTruck::getAmount() + CCar::getAmount();
	//CVehicle**list = (CVehicle**)malloc(n*sizeof(CVehicle*));
	CVehicle** list = new CVehicle*[n];
	int i = 0,j = 0;
	for (j = 0; j < CTruck::getAmount(); j++,i++)
	{
		list[i] = &m_truckArr[j];
	}

	for (j = 0; j < CCar::getAmount(); j++,i++)
	{
		list[i] = &m_carArr[j];
	}

	return list;
}

CAnimal** CGame::getAnimal()//Lấy danh sách các xe
{
	int n = CBird::getAmount() + CDinosaur::getAmount();

	CAnimal** list = new CAnimal*[n];
	int i = 0, j = 0;
	for (j = 0; j < CBird::getAmount(); j++, i++)
	{
		list[i] = &m_birdArr[j];
	}

	for (j = 0; j < CDinosaur::getAmount(); j++, i++)
	{
		list[i] = &m_dinoArr[j];
	}

	return list;
}

void CGame::updatePosPeople(int btn) //Thực hiện điều khiển di chuyển của CPEOPLE
{

	//btn = toupper(btn);

	switch (btn)
	{
	case 'W': case KEY_UP:
		m_person.Erase();
		m_person.move_Up(1);
		//m_person.Draw();
		break;
	case 'A': case KEY_LEFT:
		m_person.Erase();
		m_person.move_Left(1);
		//m_person.Draw();
		break;
	case 'S': case KEY_DOWN:
		m_person.Erase();
		m_person.move_Down(1); 
		//m_person.Draw();
		break;
	case 'D':case KEY_RIGHT:
		m_person.Erase();
		m_person.move_Right(1); 
		//m_person.Draw();
		break;
	}
}

void CGame::updatePosVehicle() //Thực hiện cho CTRUCK & CCAR di chuyển
{
	int n = CTruck::getAmount();
	if (n>0)
	{
		////TextColor(CO_DEFAULT);
		//if (m_truckArr[0].getDirect()==E_RIGHT)
		//	m_truckArr[0].Erase();
		//else
		//	m_truckArr[n-1].Erase();
		for (int i = 0; i < n; i++)
		{
			m_truckArr[i].Erase();
			m_truckArr[i].Move();
			
			TextColor(CO_TRUCK);
			m_truckArr[i].Draw();
		}
		//TextColor(CO_TRUCK);
/*
		if (m_truckArr[0].getDirect() == E_RIGHT)
			m_truckArr[n-1].Draw();
		else
			m_truckArr[0].Draw();*/
	}
	
	
	n = CCar::getAmount();
	if (n>0)
	{
		TextColor(CO_DEFAULT);
		/*
		if (m_carArr[0].getDirect() == E_RIGHT)
			m_carArr[0].Erase();
		else
			m_carArr[n - 1].Erase();*/
		for (int i = 0; i < n; i++)
		{
			m_carArr[i].Erase();
			m_carArr[i].Move();
			TextColor(CO_CAR);
			m_carArr[i].Draw();
		}
		//TextColor(CO_CAR);
		/*if (m_carArr[0].getDirect() == E_RIGHT)
			m_carArr[n-1].Draw();
		else
			m_carArr[0].Draw();
			*/
		}
}

void CGame::updatePosAnimal() //Thực hiện cho CBird & CDinosaur di chuyển
{
	int n = CBird::getAmount();
	if (n > 0)
	{
		/*TextColor(CO_DEFAULT);

		if (m_birdArr[0].getDirect() == E_RIGHT)
			m_birdArr[0].Erase();
		else
			m_birdArr[n - 1].Erase();
		*/
		for (int i = 0; i < n; i++)
		{
			m_birdArr[i].Erase();
			m_birdArr[i].Move();
			TextColor(CO_BIRD);
			m_birdArr[i].Draw();
		}
		/*TextColor(CO_BIRD);
		if (m_birdArr[0].getDirect() == E_RIGHT)
			m_birdArr[n-1].Draw();
		else
			m_birdArr[0].Draw();*/
	}
	

	n = CDinosaur::getAmount();
	if (n>0)
	{
		/*TextColor(CO_DEFAULT);
		if (m_dinoArr[0].getDirect() == E_RIGHT)
			m_dinoArr[0].Erase();
		else
			m_dinoArr[n - 1].Erase();
		*/
		for (int i = 0; i < n; i++)
		{
			m_dinoArr[i].Erase();
			m_dinoArr[i].Move();
			TextColor(CO_DINO);
			m_dinoArr[i].Draw();
		}
		/*TextColor(CO_DINO);
		if (m_dinoArr[0].getDirect() == E_RIGHT)
			m_dinoArr[n-1].Draw();
		else
			m_dinoArr[0].Draw();*/
	}
}

bool CGame::addToWinArray()//Đưa m_person vao m_peoArr trả về true nếu được false nếu sai
{
	int n = CPeople::getAmount();
	for (int i = 0; i < n - 1;i++)
	if (m_person == m_peoArr[i])
		return false;

	CPeople *tmp = new CPeople[n-1];
	for (int i = 0; i < n-1; i++)
		tmp[i] = m_peoArr[i];

	delete[]m_peoArr;//xóa để đếm lại m_Amount
	m_peoArr = new CPeople[n];

	for (int i = 0; i < n - 1; i++)
		m_peoArr[i] = tmp[i];
	m_peoArr[n - 1] = m_person;

	delete[]tmp;//Xóa để cập nhật đúng m_Amount
	return true;
}

void CGame::levelUp()
{
	m_level++;
	increaseSpeed();
	drawAllEnemy(false);
	int n, d;
	//Truck level up
	n = CTruck::getAmount();
	d = m_truckArr[0].getDirect();
	if (d == E_LEFT || n % 2==0)
	{
		for (int i = 0; i < n; i++)
			m_truckArr[i].switchDirect();
	}
	else
	{
		CTruck *tr_ptr = new CTruck[n + 1];
		for (int i = 0; i < n; i++)
			tr_ptr[i] = m_truckArr[i];
		tr_ptr[n] = m_truckArr[n - 1];
		tr_ptr[n].Move(d, MOVE_DISTANCE);
		if (m_truckArr)
			delete[]m_truckArr;
		m_truckArr = tr_ptr;
	}
	//Car level up
	n = CCar::getAmount();
	d = m_carArr[0].getDirect();
	if (d == E_LEFT||n % 2 == 0)
	{
		for (int i = 0; i < n; i++)
			m_carArr[i].switchDirect();
	}
	else
	{
		CCar *car_ptr = new CCar[n + 1];
		for (int i = 0; i < n; i++)
			car_ptr[i] = m_carArr[i];
		car_ptr[n] = m_carArr[n - 1];

		car_ptr[n].Move(d, MOVE_DISTANCE);
		if (m_carArr)
			delete[]m_carArr;
		m_carArr = car_ptr;

	}
	//Bird level up
	n = CBird::getAmount();
	d = m_birdArr[0].getDirect();
	if (d == E_LEFT || n % 2 == 0)
	{
		for (int i = 0; i < n; i++)
			m_birdArr[i].switchDirect();
	}
	else
	{
		CBird *bi_ptr = new CBird[n + 1];
		for (int i = 0; i < n; i++)
			bi_ptr[i] = m_birdArr[i];
		bi_ptr[n] = m_birdArr[n - 1];
		bi_ptr[n].Move(d, MOVE_DISTANCE);
		if (m_birdArr)
			delete[]m_birdArr;
		m_birdArr = bi_ptr;
	}

	//Dinosaur levup
	n = CDinosaur::getAmount();
	d = m_dinoArr[0].getDirect();
	if (d == E_LEFT || n % 2 == 0)
	{
		for (int i = 0; i < n; i++)
			m_dinoArr[i].switchDirect();
	}
	else
	{
		CDinosaur *di_ptr = new CDinosaur[n + 1];
		for (int i = 0; i < n; i++)
			di_ptr[i] = m_dinoArr[i];
		di_ptr[n] = m_dinoArr[n - 1];
		di_ptr[n].Move(d, MOVE_DISTANCE);
		if (m_dinoArr)
			delete[]m_dinoArr;
		m_dinoArr = di_ptr;
	}
	drawAllEnemy(true);
}

int CGame::getLevel()
{ 
	return m_level; 
}

void CGame::Pause(bool p)
{ 
	m_Paused = p; 
}

void CGame::Resume()
{ 
	m_Paused = false; 
}

bool CGame::isPaused()
{ 
	return m_Paused == true; 
}

void CGame::pauseGame(HANDLE t_handle)
{
	SuspendThread((_In_ HANDLE)t_handle);
}

void CGame::resumeGame(HANDLE t_handle)
{
	ResumeThread((_In_ HANDLE)t_handle);
}

void CGame::exitGame(HANDLE t_handle)
{
	releaseData();
	SetFontSize(FONT_SIZE_NORMAL);
	exit(0);
}

void CGame::startGame()
{
	drawBoard();
	int choice = MenuStart(getSoundMode());// -1: newgame, 0 load game, 1: setting
	string fileName;
	CleanScreen();
	DrawWall();
	drawBoard();
	int i = NUM_COLS / 4;
	int j = NUM_ROWS / 2;

	switch (choice)
	{
	case 0://new game
		this->createData();
		break;
	case 1://load game
		LoadFunction();
		break;
	case 2:
		settingGame();
		startGame();
		break;
	case 3://exit
		exit(0);
		break;
	default:
		cout << "No Func - NewGame!";
		getch();
		break;
	}
}

bool CGame::saveGame(const string filename) // Thực hiện lưu lại dữ liệu trò chơi
{
	bool flag = true;
	string _path = PTH_SAVE + filename;
	fstream f;
	f.open(_path, ios::out);
	if (f.is_open())
	{
		f << CONFIRM_CODE << endl;
		f << m_Mode << endl;
		f << m_speed << endl;
		//Write m_person
		this->m_person.writeData(f);
		//Draw win people
		int n = CPeople::getAmount() - 1;//không tính m_person
		f << n << endl;
		for (int i = 0; i < n; i++)
		{
			m_peoArr[i].writeData(f);
		}
		//Draw truck
		n = CTruck::getAmount();
		f << n << endl;
		for (int i = 0; i < n; i++)
		{
			m_truckArr[i].writeData(f);
		}
		n = CCar::getAmount();
		f << n << endl;
		for (int i = 0; i < n; i++)
		{
			m_carArr[i].writeData(f);
		}
		//Draw animal
		n = CBird::getAmount();
		f << n << endl;
		for (int i = 0; i < n; i++)
		{
			m_birdArr[i].writeData(f);
		}
		n = CDinosaur::getAmount();
		f << n << endl;
		for (int i = 0; i < n; i++)
		{
			m_dinoArr[i].writeData(f);
		}
	}
	else
		flag = false;
	f.close();
	return flag;
}

bool CGame::loadGame(const string fileName) // Thực hiện tải lại dữ liệu trò chơi
{
	bool flag = true;
	string _path = PTH_SAVE + fileName;
	string _confirm_code;
	fstream f;
	f.open(_path, ios::in);
	int x, y,dir,n;
	char tmp;
	if (f.is_open())
	{
		this->releaseData();
		getline(f, _confirm_code);
		if (_confirm_code.compare(CONFIRM_CODE) != 0)
			return false;
		f >> x;//mode
		f >> y;//speed
		
		////Trường hợp là file của he thong:
		//if ((x == E_EASY && y == SPEED_EASY) || (x == E_NORMAL&&y == SPEED_NORMAL) || (x == E_HARD&&y == SPEED_HARD))
		//{
		//	setMode(x);
		//}
		//
		////Trường hợp là file của người dùng: 
		//else 

		if ((x == E_EASY && y != SPEED_EASY) || (x == E_NORMAL&&y != SPEED_NORMAL) || (x == E_HARD&&y != SPEED_HARD))
		{
			setMode(x);
			//m_Mode = x;
			//m_speed = y;
		}

		//Read m_person
		f >> x;
		f >> tmp;
		f >> y;
		m_person = CPeople(x, y);
		//Read people win array
		f >> n;
		m_level = n;
		if (n > 0)
		{
			m_peoArr = new CPeople[n];
			for (int i = 0; i < n; i++)
			{
				f >> x;
				f >> tmp;
				f >> y;
				m_peoArr[i] = CPeople(x, y);
			}
		}
		
		//Read truck
		f >> n;
		if (n > 0)
		{
			m_truckArr = new CTruck[n];
			for (int i = 0; i < n; i++)
			{
				f >> x;
				f >> tmp;
				f >> y;
				f >> tmp;
				f >> dir;
				m_truckArr[i] = CTruck(x, y,dir);
			}
		}
		
		//Read car
		f >> n;
		if (n > 0)
		{
			m_carArr = new CCar[n];
			for (int i = 0; i < n; i++)
			{
				f >> x;
				f >> tmp;
				f >> y;
				f >> tmp;
				f >> dir;
				m_carArr[i] = CCar(x, y,dir);
			}
		}
		
		//Read Bird
		f >> n;
		if (n > 0)
		{
			m_birdArr = new CBird[n];
			for (int i = 0; i < n; i++)
			{
				f >> x;
				f >> tmp;
				f >> y;
				f >> tmp;
				f >> dir;
				m_birdArr[i] = CBird(x, y,dir);
			}
		}
		
		//Read Dinosaur
		f >> n;
		if (n > 0)
		{
			m_dinoArr = new CDinosaur[n];
			for (int i = 0; i < n; i++)
			{
				f >> x;
				f >> tmp;
				f >> y;
				f >> tmp;
				f >> dir;
				m_dinoArr[i] = CDinosaur(x, y,dir);
			}
		}
		CleanScreen();
		drawAllEnemy(true);
		drawBoard();
		TextColor(CO_PEOPLE);
		m_person.Draw();
		m_trafic = CTraffic();
		MyPlaySound(this->getSoundMode(),PTH_SOUND_BACKGROUND, E_SOUND_LOOP);
	}
	else
		flag = false;
	f.close();
	return flag;
}

void CGame::settingGame()
{
	int i, j;
	CleanScreen();
	DrawWall();

	i = NUM_COLS / 2 - 5;
	j = NUM_ROWS / 2 + 1;

	int j2 = j + 10;
	TextColor(12);

	GotoXY(i - 1, j - 4);
	cout << "   SETTING";
	GotoXY(i - 1, j - 3);
	cout << "     +-+      ";

	TextColor(CO_DEFAULT);

	int c = 0, c2 = 0;
	int k = -1;
	int k2 = -1;
	do
	{
		if (c == 'W' || c == KEY_UP)//up
		{
			k--;
		}
		else if (c == 'S' || c == KEY_DOWN)//down
		{
			k++;
		}

		if (k == -2) k = 2;
		else if (k == 3) k = -1;

	Label_ReWrite:
		(k == -1) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j - 1);
		cout << "   Resume              ";	// k == -1

		(k == 0) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j);
		cout << "   Sound               "; // k == -2 (on - off)

		(k == 1) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j + 1);
		cout << "   Level               ";	// k == -3  (easy - normal - hard)

		(k == 2) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j + 2);
		cout << "   Screen              "; // k == -4 (small - normal - large)

		TextColor(CO_DEFAULT);
		GotoXY(i, j + 3);
		cout << "                            "; // k == -4 (small - normal - large)
		GotoXY(i, j + 4);
		cout << "                            ";

		TextColor(CO_HIGHLIGHT);
		GotoXY(i, j + k);
		cout << "-> ";

		if (c == 13 || c == 'D' || c== KEY_RIGHT)
		{
			k2 = 0; c2 = 0;
			switch (k)
			{
			case 0:
				do
				{
					c2 = toupper(c2);
					if (c2 == 'W' || c2 == KEY_UP)//up
					{
						k2--;
					}
					else if (c2 == 'S' || c2 == KEY_DOWN)//down
					{
						k2++;
					}

					if (k2 == -1) k2 = 1;
					else if (k2 == 2) k2 = 0;

					(k2 == 0) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
					GotoXY(i + 10, j);
					cout << "|   On  ";	// k == -3  (easy - normal - hard)

					(k2 == 1) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
					GotoXY(i + 10, j + 1);
					cout << "|   Off ";	// k == -3  (easy - normal - hard)

					GotoXY(i + 11, j + k2);
					TextColor(CO_HIGHLIGHT);
					cout << " * ";	// k == -3  (easy - normal - hard)
					
					c2 = getch();
					if (c2 == 0 || c2 == 224)
						c2 = 256 + getch();
					c2 = toupper(c2);

					if (c2 == 'W' || c2 == 'S' || c2 == KEY_UP || c2 == KEY_DOWN || c2 == 13)
						MyPlaySound(getSoundMode(), PTH_SOUND_BEEP, E_SOUND_SINGLE);

				} while (c2 != 13 && c2 != 'A' && c2 != KEY_LEFT);

				if (c2 == 13)
				if (k2 == 0)
				{
					setSoundMode(true);
					MyPlaySound(true, PTH_SOUND_BACKGROUND, E_SOUND_LOOP);
				}
				else
				{
					setSoundMode(false);
					MyPlaySound(false, "", E_SOUND_NULL);
				}
				break;

			case 1://Game mode
				do
				{
					c2 = toupper(c2);
					if (c2 == 'W'||c2 == KEY_UP)//up
					{
						k2--;
					}
					else if (c2 == 'S' || c2==KEY_DOWN)//down
					{
						k2++;
					}

					if (k2 == -1) k2 = 2;
					else if (k2 == 3) k2 = 0;

					(k2 == 0) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
					GotoXY(i + 10, j);
					cout << "|   Easy  ";	// k == -3  (easy - normal - hard)

					(k2 == 1) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
					GotoXY(i + 10, j + 1);
					cout << "|   Normal";	// k == -3  (easy - normal - hard)

					(k2 == 2) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
					GotoXY(i + 10, j + 2);
					cout << "|   Hard  ";	// k == -3  (easy - normal - hard)


					GotoXY(i + 11, j + k2);
					TextColor(CO_HIGHLIGHT);
					cout << " * ";	// k == -3  (easy - normal - hard)
				
					c2 = getch();
					if (c2 == 0 || c2 == 224)
						c2 = 256 + getch();
					c2 = toupper(c2);

					if (c2 == 'W' || c2 == 'S' || c2 == KEY_UP || c2 == KEY_DOWN || c2 == 13)
						MyPlaySound(getSoundMode(), PTH_SOUND_BEEP, E_SOUND_SINGLE);

				} while (c2 != 13 && c2 != 'A' && c2 != KEY_LEFT);
				if (c2 == 13)
				if (k2 == 0)
					setMode(E_EASY);
				else if (k2 == 1)
					setMode(E_NORMAL);
				else
					setMode(E_HARD);
				break;

			case 2://Screen
				do
				{
					if (c2 == 'W' || c2 == KEY_UP)//up
					{
						k2--;
					}
					else if (c2 == 'S' || c2 == KEY_DOWN)//down
					{
						k2++;
					}

					if (k2 == -1) k2 = 2;
					else if (k2 == 3) k2 = 0;

					(k2 == 0) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
					GotoXY(i + 10, j);
					cout << "|   Small  ";	// k == -3  (easy - normal - hard)

					(k2 == 1) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
					GotoXY(i + 10, j + 1);
					cout << "|   Normal ";	// k == -3  (easy - normal - hard)

					(k2 == 2) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
					GotoXY(i + 10, j + 2);
					cout << "|   Large  ";	// k == -3  (easy - normal - hard)


					GotoXY(i + 11, j + k2);
					TextColor(CO_HIGHLIGHT);
					cout << " * ";	// k == -3  (easy - normal - hard)
					
					c2 = getch();
					if (c2 == 0 || c2 == 224)
						c2 = 256 + getch();
					c2 = toupper(c2);
					if (c2 == 'W' || c2 == 'S' || c2 == KEY_UP || c2 == KEY_DOWN || c2 == 13)
						MyPlaySound(getSoundMode(), PTH_SOUND_BEEP, E_SOUND_SINGLE);

				} while (c2 != 13 && c2 != 'A' && c2 != KEY_LEFT);
				if (c2 == 13)
				if (k2 == 0)
					SetFontSize(FONT_SIZE_SMALL);
				else if (k2 == 1)
					SetFontSize(FONT_SIZE_NORMAL);
				else
					SetFontSize(FONT_SIZE_LARGE);
				break;
			}
			c = 0;
			drawBoard();
			goto Label_ReWrite;
		}
		if (c == 'W' || c=='S' || c == KEY_UP || c==KEY_DOWN || c == 13)
			MyPlaySound(getSoundMode(), PTH_SOUND_BEEP, E_SOUND_SINGLE);

		c = getch();
		if (c == 0 || c == 224)
			c = 256 + getch(); // Handle multi-char keys
		c = toupper(c);

	} while (c != 13 || k != -1);//ENTER

	CleanScreen();
	DrawWall();
}

void CGame::LoadFunction()
{
	string StrName;
	int i = NUM_COLS / 4;
	int j = NUM_ROWS / 2;

	CleanScreen();
	TextColor(CO_TEXTSCAN);
	GotoXY(i, j - 2);
	std::cout << "- Path file:";
	ShowCursor(true);
	getline(cin, StrName);
	ShowCursor(false);
	GotoXY(i, j);
	if (!loadGame(StrName))
	{
		std::cout << "->Loaded Fail. Load default game.";
		GotoXY(i, j + 1);
		std::cout << "->Press any key to continue";
		getch();
		resetGame();
	}
	else
	{
		j = COMMUNICATE_Y - 2;
		i = COMMUNICATE_X;
		TextColor(14);
		GotoXY(i + 0, j + 2);
		TextColor(CO_DEFAULT);

		GotoXY(i + 0, j + 2);
		std::cout << "- Load Done!         ";
		GotoXY(i + 0, j + 3);
		std::cout << "- Any key to continue";
				
		getch();
	}
}