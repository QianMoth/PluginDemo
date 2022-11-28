#include "PluginDefinition.h"

#include <string>
#include <iostream>

#include <QDebug>

#include "Node.hpp" // node头文件

Plugin *Plugin::_this_plugin = NULL;

Plugin::Plugin()
{
    _this_plugin = this;
    setInfo();
}

void Plugin::setInfo()
{
    qDebug();

    commandMenuInit();
}

void Plugin::registerDataModels(std::shared_ptr<QtNodes::DataModelRegistry> &reg)
{
    if (reg == NULL)
        reg = std::make_shared<QtNodes::DataModelRegistry>();

    reg->registerModel<QtNodes::TestNode>("source");
}

void Plugin::commandMenuInit()
{
    qDebug();

    setCommand("Hello Plugin", hello, ShortcutKey(), true);
    setCommand(""); // add a separator
    setCommand("Current Full Path", insertCurrentFullPath, ShortcutKey(ShortcutKey::ALT | ShortcutKey::CTRL, 0x46 /* F */));
}

int Plugin::setCommand(std::string cmdName, PFUNC pFunc, const ShortcutKey &sk, bool checkOnInit)
{
    if (!cmdName.empty() && !pFunc)
        return -1;

    FuncItem item;
    cmdName.copy(item._itemName, 64, 0);
    item._pFunc = pFunc;
    item._pShKey = sk;
    item._checkOnInit = checkOnInit;

    _funcList.push_back(item);

    return 0;
}

void Plugin::recvMessage(PluginMessageData)
{
}

/**
 * @brief Plugin::Hello
 * 创建一个新编辑器
 * 设置新建的编辑器为选中
 * 填入文本内容“Hello Notepad”
 */
void Plugin::hello(bool checked = false)
{
    qDebug();

    PluginMessageData m;
    m.dest = "Plugin02";
    m.from = "Plugin01";
    m.msg = "插件1给插件2发的消息";

    emit _this_plugin->sendMessage(m);

    if (checked)
        std::cout << "Hello checked" << std::endl;
    else
        std::cout << "Hello !checked" << std::endl;
}

void Plugin::insertCurrentFullPath(bool /* checked */)
{
    qDebug();

    std::cout << "insertCurrentFullPath" << std::endl;
}
