#include <Helltooth.hpp>
using namespace ht;
using namespace core;
using namespace graphics;

class Player : public EventListener {
public:
	Player() : EventListener("Player") {}

	bool OnMove(float x, float y) override { return false; }
	bool OnPress(float x, float y) override {
		HT_WARN("Mouse pressed at %.2f , %.2f", x, y);
		return true;
	}
	bool OnRelease(float x, float y) override { return false; }

	bool OnScroll(float xOffset) override { return false; }

	bool OnKeyPress(int key, unsigned short modifier) override { return false; }
	bool OnKeyRepeat(int key, unsigned short modifier) override { return false; }
	bool OnKeyRelease(int key) override { return false; }
};