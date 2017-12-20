#include <Helltooth.hpp>
using namespace ht;
using namespace core;
using namespace graphics;

class Player : public EventListener {
public:
	Player() : EventListener("Player") {}

	bool OnMove(f32 x, f32 y) override { return false; }
	bool OnPress(f32 x, f32 y) override {
		HT_WARN("Mouse pressed at %.2f , %.2f", x, y);
		return true;
	}
	bool OnRelease(f32 x, f32 y) override { return false; }

	bool OnScroll(f32 xOffset) override { return false; }

	bool OnKeyPress(u16 key, u16 modifier) override { return false; }
	bool OnKeyRepeat(u16 key, u16 modifier) override { return false; }
	bool OnKeyRelease(u16 key) override { return false; }
};