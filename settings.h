#include <string.h>
#include "SD.h"
#include "SPI.h"
#include <IniFile.h>


// list setting
struct NameSetting
{
  unsigned int index;
  String name;
  String value;
};

const int count_settings = 11;

class Settings
{
  char* FileName;
  char* NameSection;

  NameSetting listsetting[count_settings] = {
    {1, "tz_zone_info", ""},
    {2, "ssid", ""},
    {3, "password", ""},
    {4, "server", ""},
    {5, "name_sensor", ""},
    {6, "ntp_server", ""},
    {7, "recipient", ""},
    {8, "passxmpp", ""},
    {9, "port", ""},
    {10, "sleep", ""},
    {11, "resource", ""}
  };

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
  String operator[](int index)
  {
    if(index < 0 || index > count_settings)
      return "";
    return listsetting[index].value;
  }
};
