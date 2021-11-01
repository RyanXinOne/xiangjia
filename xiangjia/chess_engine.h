
//������ɫ������
enum class colors { none, red, black };
enum class types { none, che_, ma_, pao_, bing_, xiang_, shi_, jiang_ };

//���꣬���½�Ϊ(0,0)
typedef struct position {
    int x = -1;
    int y = -1;
}position;


//���Ӹ���
class chessman
{
public:
    colors colour = colors::none;
    types species = types::none;
    position pos;  //��ǰ����
    int imageNo = -1;
    position next_moverable[20];  //��һ������λ���б�
    int num = 0;  //��һ������λ������
    int value = 0;  //������ֵ

    void moverable_position(chessman* board[9][10]);

    int move(position target, chessman* operate_board[9][10]);
};

extern chessman reset;
extern chessman* checkerboard[9][10];

//��
class che :virtual public chessman
{
public:
    che(colors c)
    {
        species = types::che_;
        colour = c;
        if (colour == colors::black)
        {
            imageNo = 1;
        }
        else
        {
            imageNo = 8;
        }
        value = 8;
    }
};

//��
class ma :virtual public chessman
{
public:
    ma(colors c)
    {
        species = types::ma_;
        colour = c;
        if (colour == colors::black)
        {
            imageNo = 2;
        }
        else
        {
            imageNo = 9;
        }
        value = 4;
    }
};

//��
class pao :virtual public chessman
{
public:
    pao(colors c)
    {
        species = types::pao_;
        colour = c;
        if (colour == colors::black)
        {
            imageNo = 3;
        }
        else
        {
            imageNo = 10;
        }
        value = 4;
    }
};

//��
class bing :virtual public chessman
{
public:
    bing(colors c)
    {
        species = types::bing_;
        colour = c;
        if (colour == colors::black)
        {
            imageNo = 6;
        }
        else
        {
            imageNo = 13;
        }
        value = 1;
    }
};

//��
class xiang :virtual public chessman
{
public:
    xiang(colors c)
    {
        species = types::xiang_;
        colour = c;
        if (colour == colors::black)
        {
            imageNo = 5;
        }
        else
        {
            imageNo = 12;
        }
        value = 2;
    }
};

//ʿ
class shi :virtual public chessman
{
public:
    shi(colors c)
    {
        species = types::shi_;
        colour = c;
        if (colour == colors::black)
        {
            imageNo = 4;
        }
        else
        {
            imageNo = 11;
        }
        value = 2;
    }
};

//��
class jiang :virtual public chessman
{
public:
    jiang(colors c)
    {
        species = types::jiang_;
        colour = c;
        if (colour == colors::black)
        {
            imageNo = 0;
        }
        else
        {
            imageNo = 7;
        }
        value = 1000;
    }
};

void initialize();

colors isGameOver(chessman* board[9][10]);
