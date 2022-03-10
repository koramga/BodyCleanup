//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Frameworks/MarkerGenerator/MarkerGenLayer.h"

#include "Frameworks/MarkerGenerator/MarkerGenPattern.h"

void UMarkerGenLayer::Compile() {
	if (Pattern) {
		Pattern->Compile();
	}
}

