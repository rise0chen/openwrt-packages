include $(TOPDIR)/rules.mk

PKG_NAME:=webConfig
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_INSTALL_DIR:=$(PKG_BUILD_DIR)/ipkg-install

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=mytool
	CATEGORY:=My
	TITLE:=config by web
	DEPENDS :=+luci
endef

define Package/$(PKG_NAME)/description
	This package provides  UCI for wifi Configuration.
endef

define Build/Prepare
	echo
endef

define Build/Compile
	echo
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/www/
	$(CP) ./files/www/* $(1)/www/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

