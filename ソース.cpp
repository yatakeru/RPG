//[1]�w�b�_�[���C���N���[�h����ꏊ

#include <stdio.h>	//[1-1]�W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> //[1-2]�W���֐����C�u�w�b�_�[���C���N���[�h����
#include <string.h>	//[1-3]�����񑀍�w�b�_�[���C���N���[�h����
#include <time.h>	//[1-4]���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>	//[1-5]�R���\�[�����o�̓w�b�_�[���C���N���[�h����



//[2]�萔���`����ꏊ

#define SPELL_COST		(3)		//[2-1]�����̏���MP���`����
#define MAP_WIDTH		(16)	//[2-2]�}�b�v�̕����`����
#define	MAP_HEIGHT		(16)	//[2-3]�}�b�v�̍������`����
#define	SCREEN_WIDTH	(16)	//[2-4]�X�N���[����ʂ̕����`����
#define	SCREEN_HEIGHT	(12)	//[2-5]�X�N���[����ʂ̍������`����



//[3]�񋓒萔���`����ꏊ

//[3-1]�����X�^�[�̎�ނ��`����
enum {
	MONSTER_PLAYER,				//[3-1-1]�v���C���[
	MONSTER_SLIME,				//[3-1-2]�X���C��
	MONSTER_BOSS,				//[3-1-3]����
	MONSTER_MAX					//[3-1-4]�����X�^�[�̎�ނ̐�
};

//[3-2]�L�����N�^�[�̎�ނ��`����
enum {
	CHARACTER_PLAYER,			//[3-2-1]�v���C���[
	CHARACTER_MONSTER,			//[3-2-2]�����X�^�[
	CHARACTER_MAX				//[3-2-3]�L�����N�^�[�̎�ނ̐�
};

//[3-3]�R�}���h�̎�ނ��`����
enum {
	COMMAND_FIGHT,				//[3-3-1]�키
	COMMAND_SPELL,				//[3-3-2]����
	COMMAND_RUN,				//[3-3-3]������
	COMMAND_MAX					//[3-3-4]�R�}���h�̎�ނ̐�
};

//[3-4]�}�b�v�̎�ނ��`����
enum
{
	MAP_FIELD,			//[3-4-1]�t�B�[���h
	MAP_KING_CASTLE,	//[3-4-2]���l�̏�
	MAP_BOSS_CASTLE,	//[3-4-3]�����̏�	
	MAP_MAX				//[3-4-4]�}�b�v�̎��
};


//[4]�\���̂�錾����ꏊ

//[4-1]�L�����N�^�[�̍\���̂�錾����
typedef struct {
	int hp;						//[4-1-1]HP
	int maxHp;					//[4-1-2]�ő�HP
	int mp;						//[4-1-3]MP
	int maxMp;					//[4-1-4]�ő�MP
	int attack;					//[4-2-5]�U����
	char name[4 * 2 + 1];		//[4-1-6]���O
	char aa[256];				//[4-1-7]�A�X�L�[�A�[�g
	int command;				//[4-1-8]�R�}���h
	int target;					//[4-1-9�U���Ώ�]
}CHARACTER;



//[5]�ϐ���錾����ꏊ

//[5-1]�����X�^�[�̃X�e�[�^�X�̔z���錾����
CHARACTER monsters[MONSTER_MAX] = {
	//[5-1-1]MONSTER_PLAYER		�v���C���[
	{
		100,					//[5-1-2]int hp						HP
		100,					//[5-1-3]int maxHp					�ő�HP
		15,						//[5-1-4]int mp						MP
		15,						//[5-1-5]int maxMp					�ő�MP
		30,						//[5-1-6]int attack					�U����
		"�䂤����",				//[5-1-7]char name[4 * 2 + 1]		���O
	},
	//[5-1-8]MONSTER_SLIME		�X���C��
	{
		3,						//[5-1-9]int hp						HP
		3,						//[5-1-10]int maxHp					�ő�HP
		0,						//[5-1-11]int mp					MP
		0,						//[5-1-12]int maxMp					�ő�MP
		2,						//[5-1-13]int attack				�U����
		"�X���C��",				//[5-1-14]char name[4 * 2 + 1]		���O

		//[5-1-15]char aa[256] �A�X�L�[�A�[�g
		"�^�E�D�E�_\n"
		"�`�`�`�`�`",
	},
	//[5-1-16]MONSTER_BOSS ����
	{
		255,
		255,
		0,
		0,
		50,
		"�܂���",

		//[5-1-23]char aa[256]�@�A�X�L�[�A�[�g
		"�@�@�`���`\n"
		"�Ձi���M���j��"
	}
};

//[5-2]�L�����N�^�[�̔z���錾����
CHARACTER characters[CHARACTER_MAX];

//[5-3]�R�}���h�̖��O��錾����
char commandNames[COMMAND_MAX][4 * 2 + 1] = {
	"��������",		//[5-3-1]COMMAND_FIGHT�@�키
	"�������",		//[5-3-2]COMMAND_SPELL	����
	"�ɂ���"		//[5-3-3]COMMAND_RUN	������
};

//[5-4]�}�b�v�̒n�`�f�[�^��錾����
char map[MAP_MAX][MAP_HEIGHT][MAP_WIDTH + 1] =
{
	//[5-4-1]MAP_FIELD �t�B�[���h
	{
		"~~~~~~~~~~~~~~~~",
		"~~MMMMM~~MMMM.~~",
		"~M...M.##..M...~",
		"~M.M.M.~~M.M.M.~",
		"~M.M...~~M...M.~",
		"~M.MMMM~~MMMM..~",
		"~M..MM.~~~~~~#~~",
		"~~M.M.~~~~~~~#~~",
		"~~M.MM~~~~BMM..~",
		"~~...MM~~M.MMM.~",
		"~...~~M~~M...M.~",
		"~..~~~K~~MMM.M.~",
		"~..~~~.~~M...M.~",
		"~......~~M.MM..~",
		"~~....~~~~....~~",
		"~~~~~~~~~~~~~~~~"
	},

	//[5-4-2]MAP_KING_CASTLE	���l�̏�
	{
		"HHH.......HHH",
		"H.H.......H.H",
		"HHHHHHHHHHHHH",
		".H.........H.",
		".H.HHH.HHH.H.",
		".H.H0H.H1H.H.",
		".H.........H.",
		".HW.......WH.",
		".HY.......YH.",
		"HHHHHH.HHHHHH",
		"H.H~~~#~~~H.H",
		"HHH~~~#~~~HHH",
		"............."
	},

	//[5-4-3]MAP_BOSS_CASTLE	�����̏�
	{
		"HHH.......HHH",
		"H.H.......H.H",
		"HHHHHHHHHHHHH",
		".H....H....H.",
		".H..WHHHW..H.",
		".H..YH2HY..H.",
		".H.........H.",
		".H..W...W..H.",
		".H..Y...Y..H.",
		".H.........H.",
		"HHHHHH.HHHHHH",
		"H.H~~~#~~~H.H",
		"HHH~~~#~~~HHH",
		"~~~~~~#~~~~~~",
		"~~~~~~#~~~~~~",
		"............."
}
};

int currentMap;		//[5-5]���݂̃}�b�v��錾����

int playerX = 6;	//[5-6]�v���C���[�̂w���W

int playerY = 12;	//[5-7]�v���C���[�̂x���W



//[6]�֐���錾����ꏊ

//[6-1]�Q�[��������������֐���錾����
void Init() {

	//[6-1-1]�v���C���[�̃X�e�[�^�X������������
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];

	//[6-1-2]���݂̃}�b�v������������
	currentMap = MAP_KING_CASTLE;

	playerX = 4;	//[6-1-3]�v���C���[�̂w���W������������
	playerY = 6;	//[6-1-4]�v���C���[�̂x���W������������
}

//[6-2]�퓬�V�[���̉�ʂ�`�悷��֐���錾����
void DrawBattleScreen() {

	//[6-2-1]��ʂ��N���A�ɂ���
	system("cls");

	//[6-2-2]�v���C���[�̖��O��\������
	printf("%s\n", characters[CHARACTER_PLAYER].name);

	//[6-2-3]�v���C���[�̃X�e�[�^�X��\������
	printf("�g�o �F %d�^%d�@�l�o �F %d�^%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp);

	//[6-2-4]��s�󂯂�
	printf("\n");

	//[6-2-5]�����X�^�[�̃A�X�L�[�A�[�g��`�悷��
	printf("%s", characters[CHARACTER_MONSTER].aa);

	//[6-2-6]�����X�^�[�̂g�o��\������
	printf("�i�g�o �F %d�^%d�j\n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp);

	//[6-2-7]��s�󂯂�
	printf("\n");
}

//[6-3]�R�}���h��I������֐���錾����
void SelectCommand() {

	//[6-3-1]�v���C���[�̃R�}���h������������
	characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

	//[6-3-2]�R�}���h�����肳���܂Ń��[�v����
	while (1) {
		//[6-3-3]�퓬��ʂ�`�悷��֐����Ăяo��
		DrawBattleScreen();

		//[6-3-4]�R�}���h�̈ꗗ��\������
		for (int i = 0; i < COMMAND_MAX; i++) {

			//[6-3-5]�I�𒆂̃R�}���h�̂Ȃ�
			if (i == characters[CHARACTER_PLAYER].command) {

				//[6-3-6]�J�[�\����`�悷��
				printf("��");
			}
			//[6-3-7]�I�𒆂̃R�}���h�łȂ����
			else {

				//[6-3-8]�S�p�X�y�[�X��`�悷��
				printf("�@");
			}

			//[6-3-9]�R�}���h�̖��O��\������
			printf("%s\n", commandNames[i]);

		}

		//[6-3-10]���͂��ꂽ�L�[�ɂ���ĕ��򂷂�
		switch (_getch()) {
		case 'w': //[6-3-11]w�L�[������������

			//[6-3-12]��̃R�}���h�ɐ؂�ւ���
			characters[CHARACTER_PLAYER].command--;

			break;

		case 's': //[6-3-13]s�L�[�������ꂽ��

			//[6-3-14]���̃R�}���h�ɐ؂�ւ���
			characters[CHARACTER_PLAYER].command++;

			break;

		default:			//[6-3-15]��L�ȊO�̃L�[�������ꂽ��
			return;			//[6-3-16]�֐��𔲂���
		}

		//[6-3-17]�J�[�\�����㉺�Ƀ��[�v������
		characters[CHARACTER_PLAYER].command = (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;

	}
}

//[6-4]�퓬�V�[���̊֐���錾����
void Battle(int _monster) {

	//[6-4-1]�����X�^�[�̃X�e�[�^�X������������
	characters[CHARACTER_MONSTER] = monsters[_monster];

	//[6-4-2]�v���C���[�̍U���Ώۂ������X�^�[�ɐݒ肷��
	characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

	//[6-4-3]�����X�^�[�̍U���Ώۂ��v���C���[�ɐݒ肷��
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	//[6-4-4]�퓬�V�[���̉�ʂ�`�悷��֐����Ăяo��
	DrawBattleScreen();

	//[6-4-5]�퓬�V�[���̍ŏ��̃��b�Z�[�W��\������
	printf("%s���@�����ꂽ�I\n", characters[CHARACTER_MONSTER].name);

	//[6-4-6]�L�[�{�[�h���͂�҂�
	_getch();

	//[6-4-7]�퓬���I������܂Ń��[�v����
	while (1) {

		//[6-4-8]�R�}���h��I������֐����Ăяo��
		SelectCommand();

		//[6-4-9]�e�L�����N�^�[�𔽕�����
		for (int i = 0; i < CHARACTER_MAX; i++) {

			//[6-4-10]�퓬�V�[���̉�ʂ�`�悷��֐����Ăяo��
			DrawBattleScreen();

			//[6-4-11]�I�����ꂽ�R�}���h�ŕ��򂷂�
			switch (characters[i].command) {

			case COMMAND_FIGHT:			//[6-4-12]�키z
			{
				//[6-4-13]�U�����郁�b�Z�[�W��\������
				printf("%s�́@���������I\n", characters[i].name);

				//[6-4-14]�L�[�{�[�h���͂�҂�
				_getch();

				int damege = 0;

				//[6-4-15]�G�ɗ^����_���[�W���L�����N�^�[���ɕ��򂵂Čv�Z����
				if (strcmp(characters[i].name, "�䂤����") == 0) {

					//[6-4-15-1]�����v���C���[�Ȃ�
					damege += (characters[i].attack / 3) + (rand() % (1 + (characters[i].attack) - (characters[i].attack / 3)));
				}
				else {

					//[6-4-15-2]���������X�^�[�Ȃ�
					damege += 1 + (rand() % characters[i].attack);
				}

				//[6-4-16]�G�Ƀ_���[�W��^����
				characters[characters[i].target].hp -= damege;

				//[6-4-17]�G�̂g�o�����̒l�ɂȂ������ǂ����𔻒肷��
				if (characters[characters[i].target].hp < 0) {

					//[6-4-18]�G�g�o���O�ɂ���
					characters[characters[i].target].hp = 0;
				}

				//[6-4-19]�퓬�V�[���̉�ʂ��ĕ`�悷��֐����Ăяo��
				DrawBattleScreen();

				//[6-4-20]�G�Ƀ_���[�W��^�������b�Z�[�W��\������
				printf("%s�Ɂ@%d�́@�_���[�W�I\n",
					characters[characters[i].target].name,
					damege);

				//[6-4-21]�L�[�{�[�h���͂�҂�
				_getch();

				break;
			}

			case COMMAND_SPELL:			//[6-4-22]����

				//[6-4-23]MP������邩�ǂ����𔻒肷��
				if (characters[i].mp < SPELL_COST) {

					//[6-4-24]MP������Ȃ����b�Z�[�W��\������
					printf("�l�o���@����Ȃ��I\n");

					//[6-4-25]�L�[�{�[�h���͂�҂�
					_getch();

					//[6-4-26]�����������鏈���𔲂���
					break;

				}

				//[6-4-27]MP���������
				characters[i].mp -= SPELL_COST;

				//[6-4-28]��ʂ��ĕ`�悷��
				DrawBattleScreen();

				//[6-4-29]���������������b�Z�[�W��\������
				printf("%s�́@�q�[�����ƂȂ����I\n", characters[i].name);

				//[6-4-30]�L�[�{�[�h���͂�҂�
				_getch();

				//[6-4-31]�g�o���񕜂�����
				characters[i].hp = characters[i].maxHp;

				//[6-4-32]�퓬�V�[���̍ĕ`�悷��
				DrawBattleScreen();

				//[6-4-33]�g�o���񕜂������b�Z�[�W��\������
				printf("%s�̂������@�����ӂ������I\n", characters[i].name);

				//[6-4-34]�L�[�{�[�h���͂�҂�
				_getch();

				break;

			case COMMAND_RUN:			//[6-4-35]������

				//[6-4-36]�������������b�Z�[�W��\������
				printf("%s�́@�ɂ��������I\n", characters[i].name);

				//[6-4-37]�L�[�{�[�h���͂�҂�
				_getch();

				//[6-4-38]�퓬�����𔲂���
				return;

				break;
			}

			//[6-4-39]�U���Ώۂ�|�������ǂ����𔻒肷��
			if (characters[characters[i].target].hp <= 0) {

				//[6-4-40]�U���Ώۂɂ���ď����𕪊򂷂�
				switch (characters[i].target) {

					//[6-4-41]�v���C���[�Ȃ�
				case CHARACTER_PLAYER:

					//[6-4-42]�v���C���[�����񂾃��b�Z�[�W��\������
					printf("���Ȃ��́@���ɂ܂���");

					break;

					//[6-4-43]�����X�^�[�Ȃ�
				case CHARACTER_MONSTER:

					//[6-4-44]�����X�^�[�̃A�X�L�[�A�[�g�������\�����Ȃ��悤�ɏ���������
					strcpy_s(characters[characters[i].target].aa, "\n");

					//[6-4-45]�퓬�V�[���̉�ʂ��ĕ`�悷��֐����Ăяo��
					DrawBattleScreen();

					//[6-4-46]�����X�^�[��|�������b�Z�[�W��\������
					printf("%s���@���������I\n", characters[characters[i].target].name);

					break;
				}

				//[6-4-47]�L�[�{�[�h���͂�҂�
				_getch();

				//[6-4-48]�퓬�V�[���̊֐��𔲂���
				return;

			}

		}
	}
}

//[6-5]�}�b�v��`�悷�鏈�����L�q����֐���錾����
void DrawMap()
{
	system("cls");	//[6-5-1]��ʂ��N���A�ɂ���

	//[6-5-2]�`�悷�邷�ׂĂ̍s�𔽕�����
	for (int y = playerY - SCREEN_HEIGHT / 2; y < playerY + SCREEN_HEIGHT / 2; y++)
	{
		//[6-5-3]�`�悷�邷�ׂĂ̗�𔽕�����
		for (int x =  playerX - SCREEN_WIDTH / 2; x < playerX + SCREEN_WIDTH; x++)
		{

			//[6-5-4]�Ώۂ̍��W���v���C���[�Ɠ��������ǂ����𔻒肷��
			if ((x == playerX) && (y == playerY))
			{
				//[6-5-5]�v���C���[�̃A�X�L�[�A�[�g��`�悷��
				printf("�E");
			}

			//[6-5-6]�Ώۂ̍��W���}�b�v�f�[�^�͈͓̔����ǂ����𔻒肷��
			else if ((x < 0) || (x >= MAP_WIDTH)
				|| (y < 0) || (y >= MAP_HEIGHT)
				|| (map[currentMap][y][x] == '\0'))
			{
				//[6-5-7]�}�b�v�̎�ނɂ���ĕ��򂷂�
				switch (currentMap)
				{
				case MAP_FIELD:			printf("�`");	break;	//[6-5-8]�t�B�[���h�̊O�͊C
				case MAP_KING_CASTLE:	printf("�D");	break;	//[6-5-9]���l�̏�̊O�͕��n
				case MAP_BOSS_CASTLE:	printf("�D");	break;	//[6-5-10]�����̏�̊O�͕��n
				}
			}

			//[6-5-11]��L�ȊO�ł����
			else
			{

				//[6-5-12]�}�X�̎�ނɂ���ĕ��򂷂�
				switch (map[currentMap][y][x])
				{
				case '~':	printf("�`");	break;	//[6-5-13]�C
				case '.':	printf("�D");	break;	//[6-5-14]���n
				case 'M':	printf("�l");	break;	//[6-5-15]�R
				case '#':	printf("��");	break;	//[6-5-16]��
				case 'K':	printf("��");	break;	//[6-5-17]���l�̏�
				case 'B':	printf("��");	break;	//[6-5-18]�����̏�
				case 'H':	printf("��");	break;	//[6-5-19]��
				case 'W':	printf("��");	break;	//[6-5-20]��
				case 'Y':	printf("�x");	break;	//[6-5-21]�C��
				case '0':	printf("��");	break;	//[6-5-22]��
				case '1':	printf("�P");	break;	//[6-5-23]�P
				case '2':	printf("��");	break;	//[6-5-24]����

				}
			}
		}

		//[6-5-25]��s�`�悷�閈�ɉ��s����
		printf("\n");
	}

	//[6-5-26]�P�s�󂯂�
	printf("\n");

	//[6-5-27]�v���C���[�̖��O��\������
	printf("%s\n", characters[CHARACTER_PLAYER].name);

	//[6-5-28]�v���C���[�̃X�e�[�^�X��\������
	printf("�g�o�F%d�^%d�@�l�o�F%d�^%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp);

	//[6-5-29]�P�s�󂯂�
	printf("\n");	
}

//[6-6]�v���O�����̎��s�J�n�_��錾����
int main() {

	//[6-6-1]�������V���b�t������
	srand((unsigned int)time(NULL));

	//[6-6-2]�Q�[��������������֐����Ăяo��
	Init();

	//[6-6-3]���C�����[�v
	while (1)
	{
		//[6-6-4]�}�b�v��`�悷��֐����Ăяo��
		DrawMap();

		int lastPlayerX = playerX;	//[6-6-5]�v���C���[�̈ړ��O�̂w���W��錾����
		int lastPlayerY = playerY;	//[6-6-6]�v���C���[�̈ړ��O�̂x���W��錾����

		//[6-6-7]���͂��ꂽ�L�[�ŕ��򂷂�
		switch (_getch())
		{
		case 'w':	playerY--;	break;	//[6-6-8]���L�[�ŏ�ړ�
		case 's':	playerY++;	break;	//[6-6-9]���L�[�ŉ��ړ�
		case 'a':	playerX--;	break;	//[6-6-10]���L�[�ō��ړ�
		case 'd':	playerX++;	break;	//[6-6-11]���L�[�ŉE�ړ�
		}

		//[6-6-12]�}�b�v�̊O�ɏo�����ǂ����𔻒肷��
		if ((playerX < 0) || (playerX >= MAP_WIDTH)
			|| (playerY < 0) || (playerY >= MAP_HEIGHT)
			|| (map[currentMap][playerY][playerX] == '\0'))
		{
			//[6-6-13]���݂̃}�b�v�ɂ���ĕ��򂷂�
			switch (currentMap)
			{
			case MAP_KING_CASTLE:	//[6-6-14]���l�̏�

				//[6-6-15]�t�B�[���h�}�b�v�ɐ؂�ւ���
				currentMap = MAP_FIELD;

				playerX = 6;	//[6-6-16]�v���C���[�̂w���W��ݒ肷��
				playerY = 12;	//[6-6-17]�v���C���[�̂x���W��ݒ肷��

				break;

			case MAP_BOSS_CASTLE:	//[6-6-18]�����̏�

				//[6-6-19]�t�B�[���h�}�b�v�ɐ؂�ւ���
				currentMap = MAP_FIELD;

				playerX = 10;	//[6-6-20]�v���C���[�̂w���W��ݒ肷��
				playerY = 9;	//[6-6-21]�v���C���[�̂x���W��ݒ肷��

				break;
			}
		}

		//[6-6-22]�ړ���̃}�X�ɂ���ĕ��򂳂���
		switch (map[currentMap][playerY][playerX])
		{

		case 'K':	//[6-6-23]���l�̏�

			//[6-6-24]���l�̏�Ƀ}�b�v��؂�ւ���
			currentMap = MAP_KING_CASTLE;

			playerX = 6;	//[6-6-25]�v���C���[�̂w���W��ݒ肷��
			playerY = 12;	//[6-6-26]�v���C���[�̂x���W��ݒ肷��

			break;

		case 'B':	//[6-6-27]�����̏�

			//[6-6-28]�����̏�Ƀ}�b�v��؂�ւ���
			currentMap = MAP_BOSS_CASTLE;

			playerX = 6;	//[6-6-29]�v���C���[�̂w���W��ݒ肷��
			playerY = 15;	//[6-6-30]�v���C���[�̂x���W��ݒ肷��

			break;


		case '0':	//[6-6-31]���l

			//[6-6-32]���l�̉�b���b�Z�[�W��\������
			printf("���u�����@�E�҂�I\n"
				"���́@����́@������\n"
				"�|���@���E���@�~���Ă���I�v\n");

			_getch();	//[6-6-33]�L�[�{�[�h���͑҂���Ԃɂ���

			break;

		case '1':	//[6-6-34]�P

			//[6-6-35]�P�̉�b���b�Z�[�W��\������
			printf("���u�_�Ɂ@�F����@�����܂��B\n"
				"�����@�_��I\n"
				"�E�җl�ɏj�����I�v\n");

			//[6-6-36]�L�[�{�[�h���͑҂���Ԃɂ���
			_getch();

			//[6-6-37]�v���C���[�̂g�o���񕜂�����
			characters[CHARACTER_PLAYER].hp = characters[CHARACTER_PLAYER].maxHp;

			//[6-6-38]�v���C���[�̂l�o���񕜂�����
			characters[CHARACTER_PLAYER].mp = characters[CHARACTER_PLAYER].maxMp;
			
			break;

		case '2':	//[6-6-39]����

			//[6-6-40]�����̉�b���b�Z�[�W��\������
			printf("���u�����ȁ@�l�Ԃ�I\n"
				"�䂪�@��]���@�j�ގ҂�\n"
				"���̐�����@���������Ă����I�v\n");

			//[6-6-41]�L�[�{�[�h���͑҂���Ԃɂ���
			_getch();

			//[6-6-42]�����Ƃ̐퓬�𔭐�������
			Battle(MONSTER_BOSS);

			//[6-6-43]���������񂾂��ǂ����𔻒肷��
			if (characters[CHARACTER_MONSTER].hp <= 0)
			{
				//[6-6-44]��ʂ��N���A�ɂ���
				system("cls");

				//[6-6-45]�G���f�B���O�̃��b�Z�[�W��\������
				printf("�@�����́@�łс@���E��\n"
					"�ŖS�Ɋ�@����@�~��ꂽ�I\n"
					"\n"
					"�@���́@���G����o���@�E�҂�\n"
					"�T�����߂����A�N��\n"
					"�����҂́@���Ȃ������Ƃ����c\n"
					"\n"
					"\n"
					"�@�@�@�s�g�d�@�d�m�c");

				//[6-6-46]�L�[�{�[�h���͑҂���Ԃɂ���
				_getch();

				//[6-6-47]�Q�[�����I��������
				return 0;
			}

			break;
		}

		//[6-6-48]�ړ���̃}�X�̎�ނɂ���ĕ��򂳂���
		switch (map[currentMap][playerY][playerX])
		{
		case '.':	//[6-6-49]���n
		case '#':	//[6-6-50]��

			//[6-6-51]�G�Ƒ����������ǂ����𔻒肷��
			if ((currentMap == MAP_FIELD) && (rand() % 16 == 0))
			{
				//[6-6-52]�G�������X�^�[�Ƃ̐퓬�𔭐�������
				Battle(MONSTER_SLIME);
			}

			break;

		default:	//[6-6-53]��L�ȊO�̃}�X
			playerX = lastPlayerX;	//[6-6-54]�v���C���[�̂w���W���ړ��O�ɖ߂�
			playerY = lastPlayerY;	//[6-6-55]�v���C���[�̂x���W���ړ��O�ɖ߂�
			break;
		}

		//[6-6-56]�v���C���[�����񂾂��ǂ����𔻒肷��
		if (characters[CHARACTER_PLAYER].hp <= 0)
		{
			//[6-6-57]�Q�[��������������֐����Ăяo��
			Init();

			//[6-6-58]��ʂ��ĕ`�悷��
			DrawMap();

			//[6-6-59]���l�̃��b�Z�[�W��\������
			printf("���u�����@�E�҂�I\n"
				"�_���@���Ȃ����@�~��ꂽ�I\n"
				"�E�҂Ɂ@�h������I\n");

			//[6-6-60]�L�[�{�[�h�̓��͑҂���Ԃɂ���
			_getch();
		}
	}
/*���X�������R�[�h

	//[6-6-3]�퓬�V�[���̊֐����Ăяo��
	Battle(MONSTER_SLIME);

	//[6-6-4]�Q�[��������������֐����Ăяo��
	Init();

	//[6-6-5]�퓬�V�[���̊֐����Ăяo��
	Battle(MONSTER_BOSS);
*/
}

