include $(TOPDIR)/rules.mk

PKG_NAME:=supervisor
PKG_VERSION:=1.0
PKG_RELEASE:=1
PKG_MAINTAINER:=rise0chen

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=mytool
	CATEGORY:=My
	TITLE:=SuperVisor
endef

define Package/$(PKG_NAME)/description
	This is supervisor.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
