#include "mainwindow.h"
#include "ui_mainwindow.h"
QPushButton *startgame;
QPushButton *Help;
QTextEdit *helpwords;
QPushButton *back;
QLabel *label;//标题
poke *pokes[104];
QComboBox *huase;//花色
QComboBox *nandu;//难度
QPushButton *restart;//重新开始
QMovie *movie;//win烟花
QLabel *label1;//
QVector <int> nowpokes;//用来存现在被选中的扑克的编号
poke *lineemptypoke[10];//每一行最上面留一张空白的牌
QPushButton *addpokebutton[5];//用来发牌
poke *zuoxia[8];//用来控制左下角的牌
QMediaPlayer *player;
QMediaPlaylist *playlist;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    setGeometry(0,0,1920,1680);
    startgame = new QPushButton(this);
    Help = new QPushButton(this);
    label1=new QLabel(this);
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    // player->setMedia(QUrl::fromLocalFile("E://qtproject//zhizhu0.65//zhizhu//bgm.mp3"));
    player->setVolume(80);
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("E://qtproject//zhizhu0.65//zhizhu//bgm.mp3"));
    player->setPlaylist(playlist);
    player->setVolume(80);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->play();
    qDebug()<<"play"<<endl;
    for(int i=0;i<8;i++)
    {
        zuoxia[i] = new poke(this);
        zuoxia[i]->setGeometry(100,750,130,180);
        zuoxia[i]->setVisible(false);
    }
    label=new QLabel(this);//开始
    label->setText("选择一副纸牌");
    label->setGeometry(800,300,250,50);
    QFont ft;
    ft.setPointSize(12);
    label->setFont(ft);
    huase=new QComboBox(this);
    nandu=new QComboBox(this);
    huase->addItem("单花色");
    huase->addItem("双花色");
    huase->addItem("四种花色");
    huase->setGeometry(800,350,250,50);
    nandu->addItem("简单");
    nandu->addItem("一般");
    nandu->addItem("困难");
    nandu->setGeometry(800,425,250,50);
    startgame->setStyleSheet("background:rgb(44,128,197);color:white");
    startgame->setGeometry(800,500,250,75);
    startgame->setText("开始游戏");
    startgame->setFont(QFont("STHupo", 14, QFont::Normal));
    QFont sansFont("Helvetica [Cronyx]", 12);
    startgame->setEnabled(true);
    Help->setText("Help");
    Help->setGeometry(800,600,250,40);
    Help->setEnabled(1);
    Help->setStyleSheet("background:rgb(107,155,184)");//结束
    for(int i=0;i<104;i++)
    {
        pokes[i]=new poke(this);
        pokes[i]->setVisible(false);
        pokes[i]->my=i;
    }//在主菜单的时候先将所有扑克设置为不可见
    restart=new QPushButton(this);//
    restart->setVisible(false);//
    restart->setGeometry(850,900,150,50);//
    restart->setText("新游戏");//
    for(int i=0;i<104;i++)
    {
        lineemptypoke[i] = new poke(this);
        lineemptypoke[i]->setVisible(false);
        lineemptypoke[i]->ontable=1;
    }
    helpwords = new QTextEdit(this);
    helpwords->setPlainText("您仅可将牌依序放在其前一张牌上。该顺序是K、Q、J、10、9、8、7、6、5、4、3、2、1。 ");
    helpwords->setGeometry(800,300,300,300);
    helpwords->setVisible(0);
    back = new QPushButton(this);
    back->setGeometry(800,650,300,50);
    back->setVisible(false);
    back->setText("back");
    setAutoFillBackground(true);
    setPalette(QPalette(QColor(51,153,51)));
    connect(startgame,SIGNAL(clicked(bool)),this,SLOT(start()));
    connect(Help,SIGNAL(clicked(bool)),this,SLOT(readhelp()));
    connect(back,SIGNAL(clicked(bool)),this,SLOT(backtomenu()));
    for(int i=0;i<104;i++)
    {
        connect(pokes[i],SIGNAL(clicked(bool)),pokes[i],SLOT(clickpoke()));
    }
    for(int i=0;i<10;i++)
    {
        connect(lineemptypoke[i],SIGNAL(clicked(bool)),lineemptypoke[i],SLOT(clickpoke()));
    }
    for(int i=0;i<5;i++)
    {
        addpokebutton[i] = new QPushButton(this);
        addpokebutton[i]->setVisible(false);
        connect(addpokebutton[i],SIGNAL(clicked(bool)),this,SLOT(addpoke()));
    }//把放在一边的50张牌的顶部五张设置上发牌的槽
    for(int i=0;i<104;i++)
    {
        connect(pokes[i],SIGNAL(clicked(bool)),this,SLOT(check()));
    }
    connect(restart,SIGNAL(clicked(bool)),this,SLOT(backtomenu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::start()
{
    qDebug()<<"1"<<endl;
    startgame->setVisible(false);
    Help->setVisible(false);
    huase->setVisible(false);//不可见
    nandu->setVisible(false);//不可见
    label->setVisible(false);//不可见
    restart->setVisible(true);
    for(int i=0;i<54;i++)
    {
        pokes[i]->setGeometry(16+(i%10+1)*150,16+(i/10+1)*30,130,180);
        pokes[i]->setVisible(true);
        pokes[i]->ontable=1;
    }//设置初始位置
    vector <int> nnnnnnn;
    vector <int> mmmmmmm;
    for(int i=1;i<=13;i++)
    {
        nnnnnnn.push_back(8);
        mmmmmmm.push_back(0);
    }
    for(int i=0;i<104;i++)
    {
        if(nandu->currentText()=="简单")
        {
             pokes[i]->number=i%13+1;
        }
        if(nandu->currentText()=="一般")
        {
            if(i%13==0)
            {
                for(int j=0;j<13;j++)
                {
                    mmmmmmm[j]++;
                }
            }
            int x=rand()%13+1;
            if(mmmmmmm[x-1]>0)
            {
                pokes[i]->number=x;
                mmmmmmm[x-1]--;
                continue;
            }
            if(mmmmmmm[x-1]==0)
            {
                i--;
                continue;
            }
        }
        if(nandu->currentText()=="困难")
        {
            int x=rand()%13+1;
            if(nnnnnnn[x-1]>0)
            {
                pokes[i]->number=x;
                nnnnnnn[x-1]--;
                continue;
            }
            if(nnnnnnn[x-1]==0)
            {
                i--;
                continue;
            }
        }
    }
    if(huase->currentText()=="单花色")
    {
        for(int i=0;i<104;i++)
        {
            pokes[i]->color=4;
        }//单色牌设置初始花色
    }
    if(huase->currentText()=="双花色")
    {
        for(int i=0;i<=103;i++)
        {
            if(nnnnnnn[pokes[i]->number-1]%2==0)
            {
                pokes[i]->color=4;
                nnnnnnn[pokes[i]->number-1]++;
                continue;
            }
            if(nnnnnnn[pokes[i]->number-1]%2==1)
            {
                pokes[i]->color=1;
                nnnnnnn[pokes[i]->number-1]++;
                continue;
            }
        }//2种花色的初始生成颜色
    }
    if(huase->currentText()=="四种花色")
    {
        for(int i=0;i<=103;i++)
        {
            if(nnnnnnn[pokes[i]->number-1]%4==0)
            {
                pokes[i]->color=4;
                nnnnnnn[pokes[i]->number-1]++;
                continue;
            }
            if(nnnnnnn[pokes[i]->number-1]%4==1)
            {
                pokes[i]->color=3;
                nnnnnnn[pokes[i]->number-1]++;
                continue;
            }
            if(nnnnnnn[pokes[i]->number-1]%4==2)
            {
                pokes[i]->color=2;
                nnnnnnn[pokes[i]->number-1]++;
                continue;
            }
            if(nnnnnnn[pokes[i]->number-1]%4==3)
            {
                pokes[i]->color=1;
                nnnnnnn[pokes[i]->number-1]++;
                continue;
            }
        }//4种花色的初始生成颜色
    }
    for(int i=44;i<54;i++)
    {
        pokes[i]->open=1;
        pokes[i]->setEnabled(true);
    }//设置初始是否打开，能不能动
    qDebug()<<"able!"<<endl;
    for(int i=0;i<10;i++)
    {
        lineemptypoke[i]->setEnabled(false);//空牌初始不能被点击
        lineemptypoke[i]->setVisible(true);//空牌初始可见
        lineemptypoke[i]->setFlat(true);//空牌设置为透明的
        lineemptypoke[i]->setGeometry(16+(i%10+1)*150,16,130,180);//空牌的位置放在桌面的最上方
        lineemptypoke[i]->number=-1;//将空牌的点数设置为-1，方便移动判定（任何牌都可移动到这个上面）
    }//每一行留下一个空的牌，用来判断当某一列为空的时候的点击
    for(int i=0;i<54;i++)
    {
        if(i-10>=0)
        {
            pokes[i]->father=pokes[i-10];
        }
        if(i+10<54)
        {
            pokes[i]->child =pokes[i+10];
        }
        if(i-10<0)
        {
            lineemptypoke[i]->child=pokes[i];
            pokes[i]->father=lineemptypoke[i];
        }//将每一行最上面一张牌的father设置为每行留下的空白牌
    }
    for(int i=0;i<104;i++)
    {
        if(i<44||i>=54)
        {
            pokes[i]->setEnabled(false);
        }
        pokes[i]->showpicture();
    }//设置初始图片
    for(int i=0;i<54;i++)
    {
        pokes[i]->raise();
    }
    for(int i=0;i<5;i++)
    {
        addpokebutton[i]->setGeometry(1600+30*i,800,130,180);
        addpokebutton[i]->setStyleSheet("border-image: url(:/back.jpg);");
    }
    for(int i=4;i>=0;i--)
    {
        addpokebutton[i]->setVisible(true);
        addpokebutton[i]->raise();
    }
}//开始游戏
void MainWindow::readhelp()
{
    startgame->setVisible(false);
    Help->setVisible(false);
    helpwords->setVisible(true);
    back->setVisible(true);
}//进入帮助页面
void MainWindow::backtomenu()
{
    startgame->setVisible(true);
    Help->setVisible(true);
    helpwords->setVisible(false);
    back->setVisible(false);
    for(int i=0;i<104;i++)
    {
        pokes[i]->setVisible(false);
    }
    restart->setVisible(false);
    for(int i=0;i<=4;i++)
    {
        addpokebutton[i]->setVisible(false);
    }
    for(int i=0;i<8;i++)
    {
        zuoxia[i]->setVisible(false);
    }
    huase->setVisible(true);
    nandu->setVisible(true);
    for(int i=0;i<10;i++)
    {
        lineemptypoke[i]->setVisible(false);
    }
    label->setVisible(true);
    for(int i=0;i<104;i++)
    {
        pokes[i]->setVisible(false);
        pokes[i]->my=i;
    }
    for(int i=0;i<104;i++)
    {
        if(i>=44&&i<=53)
        {
            pokes[i]->setEnabled(true);
            pokes[i]->open=1;
        }
        else
        {
            pokes[i]->setEnabled(false);
            pokes[i]->open=0;
        }
        pokes[i]->solved=0;
        pokes[i]->ontable=0;
        pokes[i]->father=NULL;
        pokes[i]->child=NULL;
    }
}//回到主菜单
void poke::clickpoke()
{
    //首先，既然能点击，说明这张卡一定是明着放在外面的
    //然后，对于被点击的卡，如果中继区有牌，需要判断这张卡有没有child，如果有则不能移动，如果没有，则判断是否能够全部接上
    //如果中继区没有牌，那么需要判断这张卡有没有child，如果有就全都移动到中继区
    //每次点击过后，需要对部分牌能否被点击进行刷新，方便起见对所有牌都进行刷新
    //每次点击过后，需要对部分牌的父牌/子牌进行刷新，这部分牌是中继区的牌，被点击的牌的父/子，被点击的牌本身
    if(this->ontable==0)
    {
        return;
    }//对于不在桌面上的牌，这个槽无作用
    if(nowpokes.empty()==1)
    {
        if(this->number==-1)
        {
            return;
        }//中继区为空的时候，点击空牌不产生效果
        if(this->child==NULL)
        {
            this->setGeometry(800,600,130,180);
            nowpokes.push_back(this->my);
            this->father->setEnabled(true);
            /*if(this->father!=NULL)
            {
                this->father->open=1;
                this->father->showpicture();
                this->father->setEnabled(true);
                this->father->child=NULL;
                this->father=NULL;
            }*/
            this->setEnabled(false);
        }//以上部分是对于中继区为空的时候，点击某张牌，将其放到中继区的情形
        //判断这张牌是否有后继的牌，如果没有，就单独把它放到中继区
        //然后判断其上一张牌是否未被翻开，如果是，就把它翻开
        //然后把这张牌设置为不可点击
        //后来发现这部分应该放到把牌从中继区挪动到其他地方，不然会出现这样的情况，把牌从某个地方拿起来然后放回原处
        if(this->child!=NULL)
        {
            if(this->child->number==this->number-1&&this->child->color==this->color)
            {
                this->setGeometry(800,600,130,180);
                poke *emptypoke=this;
                while(emptypoke!=NULL)
                {
                    nowpokes.push_back(emptypoke->my);
                    if(emptypoke->child!=NULL)
                    {
                        emptypoke->child->setGeometry(emptypoke->pos().rx()+30,emptypoke->pos().ry(),130,180);
                    }
                emptypoke->setEnabled(false);
                emptypoke=emptypoke->child;
                }
                this->father->setEnabled(true);
            }
            //对这一部分，即将有后继牌的牌移动到中继区，需要首先利用链表把所有的后继牌都一起移动到中继区
            //然后把它们所有都设置为不可点击
            //并且为它们设置一个合适的位置
            /*if(this->father!=NULL)
            {
                this->father->open=1;
                this->father->showpicture();
                this->father->setEnabled(true);
                this->father->child=NULL;
                this->father=NULL;
            }*/
            //这一段是和上面类似的对被点击的牌的father的处理
        }
        return;
    }
    //下面要写中继区有牌时的情况
    //首先，需要判断能否符合移动的条件
    //然后，需要整理father和child的关系
    //再然后，需要一通合适的操作使覆盖的顺序合理
    //不要忘了把覆盖上去的牌变成可以点击的
    //还要清空用来存储中继牌的vector
    if(nowpokes.empty()!=1)
    {
        //中继区不为空的时候，如果点击空牌或者点击了能连接起来的牌，所有牌都移动到这个位置
        if(((this->number==pokes[nowpokes[0]]->number+1)&&(this->open==1))||this->number==-1)
        {
            if(pokes[nowpokes[0]]->father!=NULL)
            {
                pokes[nowpokes[0]]->father->open=1;
                pokes[nowpokes[0]]->father->showpicture();
                pokes[nowpokes[0]]->father->setEnabled(true);
                poke *linshipokex=pokes[nowpokes[0]]->father;
                if(linshipokex->father!=NULL)
                {
                    while(linshipokex->father->open!=0&&((linshipokex->father->number==linshipokex->number+1&&linshipokex->father->color==linshipokex->color)||(linshipokex->father->number==-1)))
                    {
                        linshipokex->father->setEnabled(true);
                        linshipokex=linshipokex->father;
                        if(linshipokex->father==NULL)
                        {
                            break;
                        }
                    }
                }
                pokes[nowpokes[0]]->father->child=NULL;
                pokes[nowpokes[0]]->father=this;
            }
            for(int i=0;i<nowpokes.size();i++)
            {
                pokes[nowpokes[i]]->setGeometry(this->pos().rx(),this->pos().ry()+30*(i+1),130,180);
                pokes[nowpokes[i]]->raise();
                pokes[nowpokes[i]]->setEnabled(true);
            }
            this->child=pokes[nowpokes[0]];
            nowpokes.clear();
            return;
        }
        //下面补充误操作以后回到原来的那张牌上面的操作
        if(this->child==pokes[nowpokes[0]])
        {
            for(int i=0;i<nowpokes.size();i++)
            {
                pokes[nowpokes[i]]->setGeometry(this->pos().rx(),this->pos().ry()+30*(i+1),130,180);
                pokes[nowpokes[i]]->raise();
                pokes[nowpokes[i]]->setEnabled(true);
            }
            nowpokes.clear();
        }
    }
}
//当前版本的移动初现了迷之bug，暂时不明白bug原理，某些时候把牌放回去以后被压住的应该能动的牌不能动了
//已解决，bug原因是有个地方应该用点数判定写成了用编号判定
void poke::showpicture()
{
    if(this->open==0)
    {
        this->setStyleSheet("border-image: url(:/back.jpg);");
    }
    if(this->open==1)
    {
        if(this->color==4)
        {
            if(this->number==1)
            {
                this->setStyleSheet("border-image: url(:/heitao1.jpg);");
            }
            if(this->number==13)
            {
                this->setStyleSheet("border-image: url(:/heitao13.jpg);");
            }
            if(this->number==12)
            {
                this->setStyleSheet("border-image: url(:/heitao12.jpg);");
            }
            if(this->number==11)
            {
               this->setStyleSheet("border-image: url(:/heitao11.jpg);");
            }
            if(this->number==10)
            {
               this->setStyleSheet("border-image: url(:/heitao10.jpg);");
            }
            if(this->number==9)
            {
               this->setStyleSheet("border-image: url(:/heitao9.jpg);");
            }
            if(this->number==8)
            {
               this->setStyleSheet("border-image: url(:/heitao8.jpg);");
            }
            if(this->number==7)
            {
               this->setStyleSheet("border-image: url(:/heitao7.jpg);");
            }
            if(this->number==6)
            {
               this->setStyleSheet("border-image: url(:/heitao6.jpg);");
            }
            if(this->number==5)
            {
               this->setStyleSheet("border-image: url(:/heitao5.jpg);");
            }
            if(this->number==4)
            {
                this->setStyleSheet("border-image: url(:/heitao4.jpg);");
            }
            if(this->number==3)
            {
                this->setStyleSheet("border-image: url(:/heitao3.jpg);");
            }
            if(this->number==2)
            {
                this->setStyleSheet("border-image: url(:/heitao2.jpg);");
            }
        }
        if(this->color==3)
        {
            if(this->number==1)
            {
                this->setStyleSheet("border-image: url(:/meihua1.jpg);");
            }
            if(this->number==13)
            {
                this->setStyleSheet("border-image: url(:/meihua13.jpg);");
            }
            if(this->number==12)
            {
                this->setStyleSheet("border-image: url(:/meihua12.jpg);");
            }
            if(this->number==11)
            {
               this->setStyleSheet("border-image: url(:/meihua11.jpg);");
            }
            if(this->number==10)
            {
               this->setStyleSheet("border-image: url(:/meihua10.jpg);");
            }
            if(this->number==9)
            {
               this->setStyleSheet("border-image: url(:/meihua9.jpg);");
            }
            if(this->number==8)
            {
               this->setStyleSheet("border-image: url(:/meihua8.jpg);");
            }
            if(this->number==7)
            {
               this->setStyleSheet("border-image: url(:/meihua7.jpg);");
            }
            if(this->number==6)
            {
               this->setStyleSheet("border-image: url(:/meihua6.jpg);");
            }
            if(this->number==5)
            {
               this->setStyleSheet("border-image: url(:/meihua5.jpg);");
            }
            if(this->number==4)
            {
                this->setStyleSheet("border-image: url(:/meihua4.jpg);");
            }
            if(this->number==3)
            {
                this->setStyleSheet("border-image: url(:/meihua3.jpg);");
            }
            if(this->number==2)
            {
                this->setStyleSheet("border-image: url(:/meihua2.jpg);");
            }
        }
        if(this->color==2)
        {
            if(this->number==1)
            {
                this->setStyleSheet("border-image: url(:/fangpian1.jpg);");
            }
            if(this->number==13)
            {
                this->setStyleSheet("border-image: url(:/fangpian13.jpg);");
            }
            if(this->number==12)
            {
                this->setStyleSheet("border-image: url(:/fangpian12.jpg);");
            }
            if(this->number==11)
            {
               this->setStyleSheet("border-image: url(:/fangpian11.jpg);");
            }
            if(this->number==10)
            {
               this->setStyleSheet("border-image: url(:/fangpian10.jpg);");
            }
            if(this->number==9)
            {
               this->setStyleSheet("border-image: url(:/fangpian9.jpg);");
            }
            if(this->number==8)
            {
               this->setStyleSheet("border-image: url(:/fangpian8.jpg);");
            }
            if(this->number==7)
            {
               this->setStyleSheet("border-image: url(:/fangpian7.jpg);");
            }
            if(this->number==6)
            {
               this->setStyleSheet("border-image: url(:/fangpian6.jpg);");
            }
            if(this->number==5)
            {
               this->setStyleSheet("border-image: url(:/fangpian5.jpg);");
            }
            if(this->number==4)
            {
                this->setStyleSheet("border-image: url(:/fangpian4.jpg);");
            }
            if(this->number==3)
            {
                this->setStyleSheet("border-image: url(:/fangpian3.jpg);");
            }
            if(this->number==2)
            {
                this->setStyleSheet("border-image: url(:/fangpian2.jpg);");
            }
        }
        if(this->color==1)
        {
            if(this->number==1)
            {
                this->setStyleSheet("border-image: url(:/hongtao1.jpg);");
            }
            if(this->number==13)
            {
                this->setStyleSheet("border-image: url(:/hongtao13.jpg);");
            }
            if(this->number==12)
            {
                this->setStyleSheet("border-image: url(:/hongtao12.jpg);");
            }
            if(this->number==11)
            {
               this->setStyleSheet("border-image: url(:/hongtao11.jpg);");
            }
            if(this->number==10)
            {
               this->setStyleSheet("border-image: url(:/hongtao10.jpg);");
            }
            if(this->number==9)
            {
               this->setStyleSheet("border-image: url(:/hongtao9.jpg);");
            }
            if(this->number==8)
            {
               this->setStyleSheet("border-image: url(:/hongtao8.jpg);");
            }
            if(this->number==7)
            {
               this->setStyleSheet("border-image: url(:/hongtao7.jpg);");
            }
            if(this->number==6)
            {
               this->setStyleSheet("border-image: url(:/hongtao6.jpg);");
            }
            if(this->number==5)
            {
               this->setStyleSheet("border-image: url(:/hongtao5.jpg);");
            }
            if(this->number==4)
            {
                this->setStyleSheet("border-image: url(:/hongtao4.jpg);");
            }
            if(this->number==3)
            {
                this->setStyleSheet("border-image: url(:/hongtao3.jpg);");
            }
            if(this->number==2)
            {
                this->setStyleSheet("border-image: url(:/hongtao2.jpg);");
            }
        }
    }
}
void MainWindow::addpoke()
{
    //只有5张牌被设置了这个槽
    //当点击这5张牌的时候，首先把它们成10张地放到桌面上
    //然后每一张放到一个合适的位置，并且设置合适的father
    //它们的father的child要设置为它们
    //要更改它们father是否可以点击。要把它们默认设置为可以点击。
    //蜘蛛纸牌的特殊规则：当场上有空位的时候，不能发牌
    for(int i=0;i<10;i++)
    {
        if(lineemptypoke[i]->child==NULL)
        {
            return;
        }
    }
    for(int i=54;i<=94;i++)
    {
        if(pokes[i]->ontable==1)
        {
            continue;
        }
        if(pokes[i]->ontable!=1)
        {
            for(int j=i;j<i+10;j++)
            {
                pokes[j]->ontable=1;
                poke *linshipoke;
                linshipoke=lineemptypoke[j-i];
                while(linshipoke->child!=NULL)
                {
                    linshipoke=linshipoke->child;
                }
                linshipoke->child=pokes[j];
                pokes[j]->father=linshipoke;
                pokes[j]->setGeometry(pokes[j]->father->pos().rx(),pokes[j]->father->pos().ry()+30,130,180);
                pokes[j]->setEnabled(true);
                pokes[j]->setVisible(true);
                pokes[j]->open=1;
                pokes[j]->raise();
                pokes[j]->showpicture();
                if(pokes[j]->father->number!=pokes[j]->number+1||pokes[j]->father->color!=pokes[j]->color)
                {
                    poke *linshipoke2;
                    linshipoke2=pokes[j]->father;
                    linshipoke2->setEnabled(false);
                    while(linshipoke2->father->number==linshipoke2->number+1&&linshipoke2->father->color==linshipoke2->color)
                    {
                        linshipoke2->father->setEnabled(false);
                        linshipoke2=linshipoke2->father;
                    }
                }//这一段是把新发的牌上面的牌的可否点击这一属性刷新一遍
            }
            addpokebutton[i/10-5]->setVisible(false);
            break;
        }
    }
//待填，往桌面上发牌
//已经基本填完了//对单色牌而言//多色牌的话需要在其父亲是否可以移动的地方补充判定
}
void MainWindow::check()//用来检查是否有1-13已经完成了//写的很乱//但是不想改了
{
    for(int i=0;i<104;i++)
    {
        if(pokes[i]->open==1&&pokes[i]->number==13&&pokes[i]->solved==0)
        {
            int cando=0;
            poke *linshipoke3=pokes[i];
            if(linshipoke3->child==NULL)
            {
                continue;
            }
            while(linshipoke3!=NULL)
            {
                if(linshipoke3->number==1&&linshipoke3->color==linshipoke3->father->color)
                {
                    cando=1;
                    break;
                }
                if(linshipoke3->child==NULL)
                {
                    cando=0;
                    break;
                }
                if(linshipoke3->child->number!=linshipoke3->number-1||linshipoke3->child->color!=linshipoke3->color)
                {
                    cando=0;
                    break;
                }
                linshipoke3=linshipoke3->child;
            }
            if(cando==0)
            {
                continue;
            }
            if(cando==1)
            {
                for(int x=1;x<=13;x++)
                {
                    linshipoke3->setVisible(false);
                    linshipoke3->solved=1;
                    linshipoke3=linshipoke3->father;
                }
                linshipoke3->setEnabled(true);
                if(linshipoke3->number!=-1)
                {
                    linshipoke3->open=1;
                    linshipoke3->showpicture();
                }
                if(linshipoke3->child!=NULL)
                {
                    linshipoke3->child=NULL;
                }
                if(linshipoke3->father!=NULL)
                {
                    while(linshipoke3->number==linshipoke3->father->number-1&&linshipoke3->color==linshipoke3->father->color)
                    {
                        linshipoke3->father->setEnabled(true);
                        linshipoke3=linshipoke3->father;
                    }
                }
            }
        }
    }
    int okpokenumber=0;
    int colorsoknum[5]={0,0,0,0,0};
    for(int i=0;i<104;i++)
    {
        if(pokes[i]->solved==1)
        {
            okpokenumber+=1;
            colorsoknum[pokes[i]->color]++;
        }
    }
    okpokenumber/=13;
    for(int i=1;i<=4;i++)
    {
        colorsoknum[i]/=13;
    }
    int k=0;
    for(int i=1;i<=4;i++)
    {
        for(int j=0;j<colorsoknum[i];j++)
        {
            zuoxia[k]->setVisible(true);
            zuoxia[k]->setGeometry(100+30*k,750,130,180);
            if(i==4)
            {
                zuoxia[k]->setStyleSheet("border-image: url(:/heitao13.jpg);");
            }
            if(i==3)
            {
                zuoxia[k]->setStyleSheet("border-image: url(:/meihua13.jpg);");
            }
            if(i==2)
            {
                zuoxia[k]->setStyleSheet("border-image: url(:/fangpian13.jpg);");
            }
            if(i==1)
            {
                zuoxia[k]->setStyleSheet("border-image: url(:/hongtao13.jpg);");
            }
            k++;
        }
    }
    if(okpokenumber==8)
    {
        movie = new QMovie(":/fire1.gif");//
        label1->setMovie(movie);
        label1->setGeometry(850,300,400,400);
        label1->setScaledContents(true);
        label1->setVisible(true);
        label1->setStyleSheet("background:rgb(51,153,51);color:white");
        movie->start();//
    }
}
