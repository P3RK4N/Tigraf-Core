#include "Layers/AppLayer.h"

#include <Tigraf.h>

#include <vector>

using namespace std;
using namespace Tigraf;

//Add layers to Application
void STARTUP(std::vector<Layer*>& layers)
{
	layers.push_back(new AppLayer());
}