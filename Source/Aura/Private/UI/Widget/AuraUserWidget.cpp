// Copyright CyberFrog


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetControllet(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
