#include"net/net.hpp"

#include"model/main/mainwindow.hpp"
#include"model/login/loginwindow.hpp"

#include<mutex>

#include<QtWidgets/QApplication>

//Shared variables
net::Client* clientNet;
std::mutex netMutexLock;


static inline void checkLocalConfig();
static inline int setupNet();
static inline void startProgram();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    startProgram();

    return a.exec();
}

static inline void checkLocalConfig()
{
    //Left for check Local config.
}

static inline int setupNet()
{
    int netSetUpErrNum;

    net::serverInfo* serverInfo = new net::serverInfo;
    net::getConfig(serverInfo);
    netSetUpErrNum = net::setUp();

    if (netSetUpErrNum != 0)
    {
        //Remains for exception handler.
    }

    clientNet = new net::Client(serverInfo);
    clientNet->connectToServer();
    if (clientNet->fail())
    {
        TipWindow* tipwindow = new TipWindow;
        
        tipwindow->inform(U"网络错误\n服务器连接");
        return -1;
    }
    return 0;
}

static inline void startProgram()
{
    LoginWindow* loginWindow = new LoginWindow;
    MainWindow* mainWindow = new MainWindow;
    
    checkLocalConfig();
    
    if(0==setupNet())
    {
        loginWindow->show();

        QObject::connect(loginWindow, SIGNAL(properLogin()), mainWindow, SLOT(init()));
        QObject::connect(loginWindow, SIGNAL(properLogin()), loginWindow, SLOT(close()));
    }
}
