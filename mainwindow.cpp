#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ipapirequest.h"
#include "inimanager.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_api =new IpApiRequest();
    this->setWindowTitle("Ip-Tools");

    connect(m_api,&IpApiRequest::ipInfoReceived,this,&MainWindow::slotIpInfoReceived);
    connect(m_api,&IpApiRequest::errorOccurred,this,&MainWindow::slotErrorOccurred);

    int langtype = IniManager::instance()->value("system/lang").toInt();
    if( langtype < ui->com_lang->count() )
    {
        ui->com_lang->setCurrentIndex(langtype);
    }

    ui->label_git->setText("<a href=\"https://github.com/dependon/IpTools\">Click here to visit github code</a>");
    ui->label_git->setTextFormat(Qt::RichText);
    ui->label_git->setOpenExternalLinks(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_serach_clicked()
{
    QString strIp = ui->edit_ip->text();
    QString strLang = ui->com_lang->currentText();
    QString strCode;
    if(strLang == u8"English")
    {
        strCode = "en";
    }
    else if (strLang == u8"Deutsch")
    {
        strCode = "de";
    }
    else if (strLang == u8"Español")
    {
        strCode = "es";
    }
    else if (strLang == u8"Português-Brasil")
    {
        strCode = "pt-BR";
    }
    else if (strLang == u8"Français")
    {
        strCode = "fr";
    }
    else if (strLang == u8"日本語")
    {
        strCode = "ja";
    }
    else if (strLang == u8"中文")
    {
        strCode = "zh-CN";
    }
    else if (strLang == u8"Русский")
    {
        strCode = "ru";
    }
    m_api->queryIpInfo(strIp,strCode);
}

void MainWindow::slotIpInfoReceived(const QString &country, const QString &regionName, const QString &city, const QString &isp, const QString &query)
{
    ui->country->setText(country);
    ui->regionName->setText(regionName);
    ui->city->setText(city);
    ui->isp->setText(isp);
    ui->ip->setText(query);
}

void MainWindow::slotErrorOccurred(const QString &errorMessage)
{
    ui->country->setText(errorMessage);
    ui->regionName->setText("");
    ui->city->setText("");
    ui->isp->setText("");
}

void MainWindow::on_com_lang_currentIndexChanged(const QString &arg1)
{
    IniManager::instance()->setValue("system/lang",ui->com_lang->currentIndex());

    QString strLang = arg1;
    if(strLang == u8"English")
    {
        ui->label_Country->setText(u8"Country");
        ui->label_RegionName->setText(u8"Region Name");
        ui->label_City->setText(u8"City");
        ui->label_Isp->setText(u8"Internet Service Provider");
        ui->label_Ip->setText(u8"Ip");
        ui->btn_serach->setText(u8"Search");
        ui->label_tip->setText(u8"A small tool made using the API provided by ip-api.com that needs to be connected to the internet. Please enter the IP address you want to query and click search. Wait for the API to return the IP information");
    }
    else if (strLang == u8"Deutsch")
    {
        ui->label_Country->setText(u8"Land");
        ui->label_RegionName->setText(u8"Region Name");
        ui->label_City->setText(u8"Stadt");
        ui->label_Isp->setText(u8"Internet Service Provider");
        ui->label_Ip->setText(u8"Ip");
        ui->btn_serach->setText(u8"Suche");
        ui->label_tip->setText(u8"Ein kleines Tool mit der API von ip-api.com, das mit dem Internet verbunden sein muss. Bitte geben Sie die IP-Adresse ein, die Sie abfragen möchten und klicken Sie auf Suchen. Warten Sie, bis die API die IP-Informationen zurückgegeben hat.");
    }
    else if (strLang == u8"Español")
    {
        ui->label_Country->setText(u8"País");
        ui->label_RegionName->setText(u8"Nombre de la región");
        ui->label_City->setText(u8"Ciudad");
        ui->label_Isp->setText(u8"Proveedores de servicios de Internet");
        ui->label_Ip->setText(u8"Ip");
        ui->btn_serach->setText(u8"Buscar");
        ui->label_tip->setText(u8"Utilice el gadget hecho de la API proporcionada por ip-api.com, que necesita estar conectado a internet, introduzca la IP que necesita ser consultada y haga clic en buscar, a la espera de que la API devuelva la información para obtener la Ip.");
    }
    else if (strLang == u8"Português-Brasil")
    {
        ui->label_Country->setText(u8"Country");
        ui->label_RegionName->setText(u8"Nome da região");
        ui->label_City->setText(u8"Cidade");
        ui->label_Isp->setText(u8"Fornecedor de Serviços de Internet");
        ui->label_Ip->setText(u8"Ip");
        ui->btn_serach->setText(u8"Procurar");
        ui->label_tip->setText(u8"Uma pequena ferramenta feita usando a API fornecida por ip-api.com que precisa ser conectada à internet. Por favor, introduza o endereço IP que você quer consultar e clice na procura. Espere que a API devolva a informação IP");
    }
    else if (strLang == u8"Français")
    {
        ui->label_Country->setText(u8"Pays");
        ui->label_RegionName->setText(u8"Nom de la région");
        ui->label_City->setText(u8"La ville");
        ui->label_Isp->setText(u8"Fournisseurs de services Internet");
        ui->label_Ip->setText(u8"Ip");
        ui->btn_serach->setText(u8"Rechercher");
        ui->label_tip->setText(u8"Gadget fait avec l'API fournie par ip-api.com, besoin de mise en réseau, s'il vous plaît entrer l'IP qui doit être interrogé et appuyez sur rechercher, attendez que l'API retourne les informations pour obtenir l'IP");
    }
    else if (strLang == u8"日本語")
    {
        ui->label_Country->setText(u8"国");
        ui->label_RegionName->setText(u8"地域名");
        ui->label_City->setText(u8"とし");
        ui->label_Isp->setText(u8"インターネットサービスプロバイダ");
        ui->label_Ip->setText(u8"Ip");
        ui->btn_serach->setText(u8"検索けんさく");
        ui->label_tip->setText(u8"ip-api.comで提供されているapiを使用したガジェットは、ネットワークに接続する必要があります。検索するipを入力して検索をクリックし、ipの情報が戻ってくるのを待ってください");
    }
    else if (strLang == u8"中文")
    {
        ui->label_Country->setText(u8"国家");
        ui->label_RegionName->setText(u8"地区名称");
        ui->label_City->setText(u8"城市");
        ui->label_Isp->setText(u8"互联网服务提供商");
        ui->label_Ip->setText(u8"Ip");
        ui->btn_serach->setText(u8"搜索");
        ui->label_tip->setText(u8"使用ip-api.com提供的api做成的小工具，需要联网，请输入需要查询的ip并点击搜索，等待api返回得到ip的信息");
    }
    else if (strLang == u8"Русский")
    {
        ui->label_Country->setText(u8"Страна");
        ui->label_RegionName->setText(u8"Название района");
        ui->label_City->setText(u8"Города");
        ui->label_Isp->setText(u8"Интернет - провайдеры");
        ui->label_Ip->setText(u8"ИП");
        ui->btn_serach->setText(u8"Поиск");
        ui->label_tip->setText(u8"С помощью гаджета, сделанного из API, предоставленного ip - api.com, необходимо подключиться к сети, введите IP, который нужно запросить, и нажмите на поиск, ожидая, когда API вернется, чтобы получить информацию об IP");
    }
}
