#ifndef BLUESJACKRABBIT_EDITOR_MAP_H
#define BLUESJACKRABBIT_EDITOR_MAP_H
#include <vector>
#include "Level.h"

class Map {
public:
	void add_level(Level* level);
	const std::vector<Level*>& levels() const;

private:
	std::vector<Level*> levels_;
};

#endif // BLUESJACKRABBIT_EDITOR_MAP_H