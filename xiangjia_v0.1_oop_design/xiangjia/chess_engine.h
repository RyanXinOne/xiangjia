
//棋子颜色和种类
enum class colors { none, red, black };
enum class types { none, che_, ma_, pao_, bing_, xiang_, shi_, jiang_ };

//坐标，右下角为(0,0)
typedef struct position {
    int x = -1;
    int y = -1;
}position;


//棋子父类
class chessman
{
public:
    colors colour = colors::none;
    types species = types::none;
    position pos;  //当前坐标
    int imageNo = -1;
    position next_moverable[20];  //下一步可走位置列表
    int num = 0;  //下一步可走位置数量
    int value = 0;  //子力价值

    void moverable_position(chessman* board[9][10]);

    int move(position target, chessman* operate_board[9][10]);
};

extern chessman reset;
extern chessman* checkerboard[9][10];

//车
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

//马
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

//炮
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

//兵
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

//象
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

//士
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

//将
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
