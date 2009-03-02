INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/CopyIfDifferent.cmake )
SET(BUTTON_BMPS
	icon_button_friends.bmp
	icon_button_friends_mousedown.bmp
	icon_button_friends_mouseover.bmp
	icon_button_news.bmp
	icon_button_news_mousedown.bmp
	icon_button_news_mouseover.bmp
	icon_button_settings.bmp
	icon_button_settings_mousedown.bmp
	icon_button_settings_mouseover.bmp
	icon_button_support.bmp
	icon_button_support_mousedown.bmp
	icon_button_support_mouseover.bmp
)
COPY_IF_DIFFERENT(
	${CMAKE_SOURCE_DIR}/images/
	${CMAKE_BUILD_DIR}/${CMAKE_BUILD_TYPE}/images/
	${BUTTON_BMPS} ButtonBmpCopy "ButtonBmps")
#ADD_TARGET(CopyButtonBmp ALL DEPENDS ${ButtonBmpCopy})
