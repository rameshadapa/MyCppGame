APP_STL := gnustl_static

LIBCXX_USE_GABIXX:=true

APP_CPPFLAGS := -frtti -DCC_ENABLE_BOX2D_INTEGRATION=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic


ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif
