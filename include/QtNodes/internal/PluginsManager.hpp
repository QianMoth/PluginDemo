#pragma once

#include "Export.hpp"
#include "PluginInterface.hpp"

#include <QObject>
#include <QPluginLoader>
#include <vector>
#include <unordered_map>

namespace QtNodes 
{

class NodeDelegateModelRegistry;

class NODE_EDITOR_PUBLIC PluginsManager
{
  PluginsManager();

  ~PluginsManager();

public:

  static
  PluginsManager*
  instance();

  std::shared_ptr<NodeDelegateModelRegistry>
  registry();

  void
  loadPlugins(const QString &folderPath = "./plugins");

  void
  unloadPlugins();

  /**
   * @brief Load the plug-in from the full file path
   * 
   * @param filePath "C:/plugin_text.dll"
   * @return PluginInterface* 
   */
  PluginInterface*
  loadPluginFromPath(const QString &filePath);

  /**
   * @brief Unload the plugin from the full file path
   * 
   * @param filePath "C:/plugin_text.dll"
   * @return int 
   */
  int
  unloadPluginFromPath(const QString &filePath);

  /**
   * @brief Uninstall a plugin by its name, not its file name
   * 
   * @param pluginName "pluginText"
   * @return int 
   */
  int
  unloadPluginFromName(const QString &pluginName);

  inline
  std::unordered_map<QString, PluginInterface*>
  plugins()
  { return _plugins; };

private:
  static PluginsManager* _instance;

  std::unordered_map<QString, PluginInterface*> _plugins;
  std::unordered_map<QString, QPluginLoader*> _loaders; ///< plugin path

  std::shared_ptr<NodeDelegateModelRegistry> _register;
};

} // namespace QtNodes