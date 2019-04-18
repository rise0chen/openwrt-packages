include $(TOPDIR)/rules.mk

PKG_NAME:=smartNet
PKG_VERSION:=1.0.0
PKG_RELEASE:=1
PKG_MAINTAINER:=rise0chen

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://gitee.com/cnCrise/fiip-example-linux.git
PKG_SOURCE_VERSION:=origin/master
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=mytool
	CATEGORY:=My
	TITLE:=SmartNet
	DEPENDS:=+libpthread
endef

define Package/$(PKG_NAME)/description
	This is SmartNet.
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fiip.ini $(1)/etc
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
