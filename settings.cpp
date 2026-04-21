#include "settings.h"
#include "debug_str.h"

#define CS_PIN 5

short Settings::initSDCard(void)
{
  if(!SD.begin(CS_PIN))
  {
    debug_str("Card Mount Failed");
    return -1;
  }
  uint8_t cardType = SD.cardType();
 
  if(cardType == CARD_NONE)
  {
    debug_str("No SD card attached");
    return -2;
  }
 
  debug_str("SD Card Type: ");
  switch(cardType)
  {
    case CARD_MMC: 
      debug_str("MMC");
      break;
    case CARD_SD: 
      debug_str("SDSC");
      break;
    case CARD_SDHC: 
      debug_str("SDHC");
      break;
    default:
      debug_str("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  return 0;
}

void Settings::printErrorMessage(uint8_t e, bool eol = true)
{
  switch (e) {
  case IniFile::errorNoError:
    debug_str("no error");
    break;
  case IniFile::errorFileNotFound:
    debug_str("file not found");
    break;
  case IniFile::errorFileNotOpen:
    debug_str("file not open");
    break;
  case IniFile::errorBufferTooSmall:
    debug_str("buffer too small");
    break;
  case IniFile::errorSeekError:
    debug_str("seek error");
    break;
  case IniFile::errorSectionNotFound:
    debug_str("section not found");
    break;
  case IniFile::errorKeyNotFound:
    debug_str("key not found");
    break;
  case IniFile::errorEndOfFile:
    debug_str("end of file");
    break;
  case IniFile::errorUnknownError:
    debug_str("unknown error");
    break;
  default:
    debug_str("unknown error value");
    break;
  }
  if (eol)
    Serial.println();
}

char* Settings::NewValue(int i, const char* v)
{
  FreeValue(i);
  listsetting[i].str = (char*) malloc(strlen(v) + 1);
  strcpy(listsetting[i].str, v);
  return listsetting[i].str;
}

void Settings::FreeValue(int i)
{
  if(listsetting[i].str)
  {
    Serial.printf("delete\n");
    free(listsetting[i].str);
    listsetting[i].str = nullptr;
  }
}

short Settings::ReadSettings(const char* ns)
{
  IniFile ini(FileName);
  if (!ini.open()) 
  {
    debug_str("Ini file does not exist", FileName);
    return -1;
  }
  const size_t bufferLen = 100;
  char buffer[bufferLen];
    // Check the file is valid. This can be used to warn if any lines
  // are longer than the buffer.
  if (!ini.validate(buffer, bufferLen)) 
  {
    debug_str("ini file", ini.getFilename());
    debug_str("not valid", ini.getError());
    return -2;
  }
  debug_str("Ini file opened successfully. Reading settings:");
  
  for( int i = 0; i < count_settings; i++)
  {
    if(!ini.getValue(ns, listsetting[i].name, buffer, bufferLen))
    {
      printErrorMessage(ini.getError());
      return -2 - i;
    }
    NewValue(i, buffer);
    debug_str(listsetting[i].name, listsetting[i].str);
  }
  
  ini.close();
  return 0;
}
