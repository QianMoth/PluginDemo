#include "PluginDefinition.h"

#include "models/TextModel.hpp"

#include <QDebug>
#include <iostream>
#include <string>

// Plugin *Plugin::_this_plugin = NULL;

Plugin::Plugin() {} //_this_plugin = this; }

Plugin::~Plugin()
{
    // TODO: Unregister all models here
}

void Plugin::registerDataModels(std::shared_ptr<QtNodes::NodeDelegateModelRegistry> &reg)
{
    assert(reg);

    reg->registerModel<TextModel>("text");
}
