#include <UnitCategory.h>

#include <util/ErrorHandling.h>

UnitCategory::UnitCategory(int categoryId) : categoryId(categoryId), test(0) {
	//logMessage("CATEGORY ID PARAM:");
	//logMessage(categoryId);
	//logMessage("CATEGORY ID IN OBJ:");
	//logMessage(this->categoryId);
}

UnitCategory::~UnitCategory() {
	//logMessage("DECONSTRUCTION UnitCategory");
}

bool UnitCategory::isValid() const {
	return categoryId >= 0 && test != 0;
}