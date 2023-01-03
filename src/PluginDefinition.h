/**
 * @file PluginDefinition.h
 * @author moth (QianMoth@qq.com)
 * @brief 插件接口定义，基于qt插件
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "config.h"

#include <QObject>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtNodes/PluginInterface>

// This needs to be the same as the name of your project file ${PROJECT_NAME}
#ifdef pluginbase_EXPORTS
#define DLL_EXPORT Q_DECL_EXPORT
#else
#define DLL_EXPORT Q_DECL_IMPORT
#endif

#define PLUGIN_NAME PROJECT_NAME

class DLL_EXPORT Plugin
    : public QObject
    , public QtNodes::PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(QtNodes::PluginInterface)
    Q_PLUGIN_METADATA(IID PLUGIN_NAME)

  public:
    Plugin();
    ~Plugin();

    QString name() const override { return PLUGIN_NAME; };

    void registerDataModels(std::shared_ptr<QtNodes::NodeDelegateModelRegistry> &reg) override;

  private:
    // static Plugin *_this_plugin;
};
