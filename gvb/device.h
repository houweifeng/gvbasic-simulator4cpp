#ifndef GVBASIC_DEVICE_H
#define GVBASIC_DEVICE_H

#include <string>
#include <cstdint>
#include <mutex>
#include <unordered_map>
#include "fake6502_wrap.h"

namespace gvbsim {

class IGui;

using std::uint8_t;
using std::uint16_t;


class Device : public fake6502::Fake6502Wrapper {
public:
   enum class ScreenMode {
      TEXT, GRAPH
   };

   enum DrawMode {
      CLEAR, PAINT, XOR, NONE = 3, DRAW_MASK = 3
   };

   enum class PaintMode { // for PAINT statement only
      COPY, OR, NOT, AND, XOR, DUMMY
   };

   enum class CursorPosInfo {
      ASCII, GB1st, GB2nd
   };

private:
   IGui *m_gui;
   std::unordered_map<int, int> m_keyMap;
   uint8_t m_x, m_y;
   ScreenMode m_scrMode;
   uint8_t m_mem[UINT16_MAX];
   std::mutex m_mutGraph;
   uint8_t *m_memGraph;
   uint8_t *m_memText;
   std::mutex m_mutKey; // for memKey
   uint8_t *m_memKey;
   uint8_t *m_memKeyMap;
   bool m_enableCursor;
   char m_tmpchar;

public:
   Device();

public:
   void setGui(IGui *);

   void init();

   void setKeyMap(const std::unordered_map<int, int> &m) {
      m_keyMap = m;
   }

   // called from gui thread
   void onKeyDown(int key, char c); // wqx key code
   void onKeyUp(int key);
   // for painting screen
   std::mutex &getGraphMutex() {
      return m_mutGraph;
   }

   void appendText(const std::string &s) {
      appendText(s.data(), static_cast<int>(s.size()));
   }
   void appendText(const char *, int size);
   void nextRow(); //如果滚屏则屏幕上滚一行
   void updateLCD();
   void locate(uint8_t row, uint8_t col);
   uint8_t getX();
   uint8_t getY();
   void setMode(ScreenMode mode);
   void cls();
   std::string input();
   uint8_t getKey();
   bool checkKey(uint8_t);
   bool getPoint(int x, int y);
   void point(uint8_t x, uint8_t y, DrawMode);
   void rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill, DrawMode);
   void line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, DrawMode);
   void ellipse(uint8_t x, uint8_t y, uint8_t rx, uint8_t ry, bool fill, DrawMode);

   uint8_t peek(uint16_t);
   void poke(uint16_t, uint8_t value); // 可能抛出Quit
   void call(uint16_t);

   void sleep(int ticks);
   void paint(const uint8_t *, int x, int y, uint8_t w, uint8_t h, PaintMode);
   void paint(uint16_t addr, int x, int y, uint8_t w, uint8_t h, PaintMode mode) {
      paint(m_mem + addr, x, y, w, h, mode);
   }

   void setTextAddr(uint16_t);
   void setGraphAddr(uint16_t);
   void setKeyAddr(uint16_t);
   void setKeyMapAddr(uint16_t);

   uint8_t *getGraphBuffer() { return m_memGraph; }
   ScreenMode getMode() const { return m_scrMode; }
   CursorPosInfo getPosInfo() const;
   bool cursorEnabled() const {
      return ScreenMode::TEXT == m_scrMode && m_enableCursor;
   }

   static void loadData();
   static void loadFile(const char *, uint8_t *, size_t n);

protected:
   uint8_t read6502(uint16_t) override;
   void write6502(uint16_t, uint8_t) override;
   void interrupt(uint16_t) override;
   void stepHook() override;

private:
   void moveRow();
   void setPoint(uint8_t, uint8_t, DrawMode);
   void hLine(uint8_t, uint8_t, uint8_t, DrawMode);
   void ovalPoint(uint8_t, uint8_t, uint8_t, uint8_t, DrawMode);

   void tinyTextOut(const uint8_t *, int size, int x, int y);
   void drawChar12(const uint8_t *, int x, int y);

   static void rollData(void *, int, int);
   static void py2GB(uint8_t *, int size, const uint8_t *&list, int &len);

private:
   static uint8_t s_dataImage[];
   static uint8_t s_dataAscii16[];
   static uint8_t s_dataGB16[];
   static uint8_t s_dataAscii12[];
   static uint8_t s_dataGB12[];
   static uint8_t s_dataAscii8[];
   static uint8_t s_dataGBChar[];
   static uint8_t s_dataPY[];

   static const uint8_t s_bitmask[];
   static const uint8_t s_maskl[], s_maskr[];
};

}

#endif //GVBASIC_DEVICE_H
