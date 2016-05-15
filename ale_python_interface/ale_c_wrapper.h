#ifndef __ALE_C_WRAPPER_H__
#define __ALE_C_WRAPPER_H__

#include <ale_interface.hpp>
#ifdef _EXPORTING
#define CLASS_DECLSPEC    extern "C" __declspec(dllimport)
#else
#define CLASS_DECLSPEC    extern "C" __declspec(dllexport)
#endif
//extern "C" {
  // Declares int rgb_palette[256]
CLASS_DECLSPEC  ALEInterface *ALE_new() { return new ALEInterface(); }
CLASS_DECLSPEC  void ALE_del(ALEInterface *ale){ delete ale; }
CLASS_DECLSPEC  const char *getString(ALEInterface *ale, const char *key){ return ale->getString(key).c_str(); }
CLASS_DECLSPEC  int getInt(ALEInterface *ale, const char *key) { return ale->getInt(key); }
CLASS_DECLSPEC  bool getBool(ALEInterface *ale, const char *key){ return ale->getBool(key); }
CLASS_DECLSPEC  float getFloat(ALEInterface *ale, const char *key){ return ale->getFloat(key); }
CLASS_DECLSPEC  void setString(ALEInterface *ale, const char *key, const char *value){ ale->setString(key, value); }
CLASS_DECLSPEC  void setInt(ALEInterface *ale, const char *key, int value){ ale->setInt(key, value); }
CLASS_DECLSPEC  void setBool(ALEInterface *ale, const char *key, bool value){ ale->setBool(key, value); }
CLASS_DECLSPEC  void setFloat(ALEInterface *ale, const char *key, float value){ ale->setFloat(key, value); }
CLASS_DECLSPEC  void loadROM(ALEInterface *ale, const char *rom_file){ ale->loadROM(rom_file); }
CLASS_DECLSPEC  int act(ALEInterface *ale, int action){ return ale->act((Action)action); }
CLASS_DECLSPEC  bool game_over(ALEInterface *ale){ return ale->game_over(); }
CLASS_DECLSPEC  void reset_game(ALEInterface *ale){ ale->reset_game(); }
CLASS_DECLSPEC  void getLegalActionSet(ALEInterface *ale, int *actions){
    ActionVect action_vect = ale->getLegalActionSet();
    for(unsigned int i = 0;i < ale->getLegalActionSet().size();i++){
      actions[i] = action_vect[i];
    }
  }
CLASS_DECLSPEC  int getLegalActionSize(ALEInterface *ale){ return ale->getLegalActionSet().size(); }
CLASS_DECLSPEC  void getMinimalActionSet(ALEInterface *ale, int *actions){
    ActionVect action_vect = ale->getMinimalActionSet();
    for(unsigned int i = 0;i < ale->getMinimalActionSet().size();i++){
      actions[i] = action_vect[i];
    }
  }
CLASS_DECLSPEC  int getMinimalActionSize(ALEInterface *ale){ return ale->getMinimalActionSet().size(); }
CLASS_DECLSPEC  int getFrameNumber(ALEInterface *ale){ return ale->getFrameNumber(); }
CLASS_DECLSPEC  int lives(ALEInterface *ale){ return ale->lives(); }
CLASS_DECLSPEC  int getEpisodeFrameNumber(ALEInterface *ale){ return ale->getEpisodeFrameNumber(); }
CLASS_DECLSPEC  void getScreen(ALEInterface *ale, unsigned char *screen_data){
    int w = ale->getScreen().width();
    int h = ale->getScreen().height();
    pixel_t *ale_screen_data = (pixel_t *)ale->getScreen().getArray();
    memcpy(screen_data,ale_screen_data,w*h*sizeof(pixel_t));
  }
CLASS_DECLSPEC  void getRAM(ALEInterface *ale, unsigned char *ram){
    unsigned char *ale_ram = ale->getRAM().array();
    int size = ale->getRAM().size();
    memcpy(ram,ale_ram,size*sizeof(unsigned char));
  }
CLASS_DECLSPEC  int getRAMSize(ALEInterface *ale){ return ale->getRAM().size(); }
CLASS_DECLSPEC  int getScreenWidth(ALEInterface *ale){ return ale->getScreen().width(); }
CLASS_DECLSPEC  int getScreenHeight(ALEInterface *ale){ return ale->getScreen().height(); }

CLASS_DECLSPEC  void getScreenRGB(ALEInterface *ale, unsigned char *output_buffer){
    size_t w = ale->getScreen().width();
    size_t h = ale->getScreen().height();
    size_t screen_size = w*h;
    pixel_t *ale_screen_data = ale->getScreen().getArray();

    ale->theOSystem->colourPalette().applyPaletteRGB(output_buffer, ale_screen_data, screen_size );
  }

CLASS_DECLSPEC  void getScreenGrayscale(ALEInterface *ale, unsigned char *output_buffer){
    size_t w = ale->getScreen().width();
    size_t h = ale->getScreen().height();
    size_t screen_size = w*h;
    pixel_t *ale_screen_data = ale->getScreen().getArray();

    ale->theOSystem->colourPalette().applyPaletteGrayscale(output_buffer, ale_screen_data, screen_size);
  }

CLASS_DECLSPEC  void saveState(ALEInterface *ale){ ale->saveState(); }
CLASS_DECLSPEC  void loadState(ALEInterface *ale){ ale->loadState(); }
CLASS_DECLSPEC  ALEState* cloneState(ALEInterface *ale){ return new ALEState(ale->cloneState()); }
CLASS_DECLSPEC  void restoreState(ALEInterface *ale, ALEState* state){ ale->restoreState(*state); }
CLASS_DECLSPEC  ALEState* cloneSystemState(ALEInterface *ale){ return new ALEState(ale->cloneSystemState()); }
CLASS_DECLSPEC  void restoreSystemState(ALEInterface *ale, ALEState* state){ ale->restoreSystemState(*state); }
CLASS_DECLSPEC  void deleteState(ALEState* state){ delete state; }
CLASS_DECLSPEC  void saveScreenPNG(ALEInterface *ale, const char *filename){ ale->saveScreenPNG(filename); }

  // Encodes the state as a raw bytestream. This may have multiple '\0' characters
  // and thus should not be treated as a C string. Use encodeStateLen to find the length
  // of the buffer to pass in, or it will be overrun as this simply memcpys bytes into the buffer.
CLASS_DECLSPEC  void encodeState(ALEState *state, char *buf, int buf_len);
CLASS_DECLSPEC  int encodeStateLen(ALEState *state);
CLASS_DECLSPEC  ALEState *decodeState(const char *serialized, int len);
//}

#endif
