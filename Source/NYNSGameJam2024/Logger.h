#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LoggerCategory, Log, All);

class Logger
{
public:
	static void Log(FString Text);
};
