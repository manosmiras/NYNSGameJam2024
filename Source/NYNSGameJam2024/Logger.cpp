#include "Logger.h"

DEFINE_LOG_CATEGORY(LoggerCategory);

void Logger::Log(FString Text)
{
	UE_LOG(LoggerCategory, Display, TEXT("%s"), *Text);
}
