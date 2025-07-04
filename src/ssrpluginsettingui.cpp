#include "ssrpluginsettingui.h"
#include "ui_ssrpluginsettingui.h"

SSRPluginSettingUI::SSRPluginSettingUI(QWidget *parent) : QDialog(parent), ui(new Ui::SSRPluginSettingUI)
{
        ui->setupUi(this);
}

SSRPluginSettingUI::~SSRPluginSettingUI()
{
        delete ui;
}
