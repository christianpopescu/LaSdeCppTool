#pragma once
ref class ConfigManager
{
protected:
	ConfigManager();
	static ConfigManager _configManager;
public:
	static property ConfigManager^ Instance { ConfigManager^ get() { return % _configManager; }}

protected:
	ConfigManager(ConfigManager^ const) ;
	

};

