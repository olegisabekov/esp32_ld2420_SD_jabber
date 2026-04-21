#include <string.h>
#include "SD.h"
#include "SPI.h"
#include <IniFile.h>


// list setting
struct NameSetting
{
  unsigned int index;
  const char* name;
  char* str;
  int val;
};

const int count_settings = 11;

class Settings
{
private:
  char* FileName;
  char* NameSection;

  NameSetting listsetting[count_settings] = {
    {1, "tz_zone_info", nullptr, 0},
    {2, "ssid", nullptr, 0},
    {3, "password", nullptr, 0},
    {4, "server", nullptr, 0},
    {5, "name_sensor", nullptr, 0},
    {6, "ntp_server", nullptr, 0},
    {7, "recipient", nullptr, 0},
    {8, "passxmpp", nullptr, 0},
    {9, "port", nullptr, 0},
    {10, "sleep", nullptr, 0},
    {11, "resource", nullptr, 0}
  };
  char* NewValue(int, const char*);
  void FreeValue(int i);
  void printErrorMessage(uint8_t , bool );
public:
  Settings() {;};
  Settings(char* fn) { FileName = fn; };
  void SetFileName(char* fn)
  {
    FileName = fn;
  }
  const char* GetFileName(void)
  {
    return FileName;
  }
  short initSDCard(void);
  short ReadSettings(const char * );
  const char* ToChar(size_t index)
  {
    if(index > count_settings)
      return "";
    return listsetting[index - 1].str;
  }
  const int& ToInt(size_t index)
  {
    int i = index - 1;
    if(index > count_settings)
      return (listsetting[i].val = 0);
    listsetting[i].val = atoi(listsetting[i].str);
    return listsetting[i].val;
  }
};
