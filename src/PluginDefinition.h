/**
 * @file PluginDefinition.h
 * @author moth (QianMoth@qq.com)
 * @brief 插件接口定义，基于qt插件
 * @version 0.0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <nodes2/PluginInterface>

#include <QObject>

#if defined(plugindemo_EXPORTS) // 这里需要和您的工程文件名一致${PROJECT_NAME}
#define DLL_EXPORT Q_DECL_EXPORT
#else
#define DLL_EXPORT Q_DECL_IMPORT
#endif

/* 在此定义您的插件名称，一个插件可以存在多个节点 */
#define PLUGIN_NAME "PluginDemo"

class DLL_EXPORT Plugin : public QObject, public PluginInterface
{

    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID PLUGIN_NAME)

public:
    explicit Plugin();

    /**
     * @~English
     * @brief Plugin Name
     * @return
     *
     * @~Chinese
     * @brief 插件名称
     * @return
     */
    QString name() const override { return PLUGIN_NAME; };

    /**
     * @brief setInfo
     */
    void setInfo() override;

    // virtual std::list<FuncItem> getFuncsArray(){return _funcList;};

    /**
     * @~Chinese
     * @brief node的注册函数
     *
     * @param reg
     */
    void registerDataModels(std::shared_ptr<QtNodes::DataModelRegistry> &reg) override;

public:
    virtual void recvMessage(PluginMessageData) override;

signals:
    void sendMessage(PluginMessageData) override;

private:
    static Plugin *_this_plugin;

private:
    /**
     * @brief 创建本插件的命令菜单栏
     */
    void commandMenuInit();
    /**
     * @brief 创建本插件的销毁菜单栏
     */
    void commandMenuCleanUp();
    int setCommand(std::string cmdName, PFUNC pFunc = NULL, const ShortcutKey &sk = ShortcutKey(), bool checkOnInit = false);

    /* 下面实现所有本插件自定义函数 */
    static void hello(bool);
    static void insertCurrentFullPath(bool);
};
