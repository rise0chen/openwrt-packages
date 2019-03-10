include $(TOPDIR)/rules.mk

PKG_NAME:=smartNet
PKG_VERSION:=2.1
PKG_RELEASE:=2
PKG_MAINTAINER:=rise0chen

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://gitee.com/cnCrise/fiip-example.git
PKG_SOURCE_VERSION:=d81fc1ab78adb28eee26a3598eb8a78287b2c7d3
PKG_MIRROR_HASH:=7b3e9bd9a2b5d9cb70564f4d505feafa9e3ab3af881c66b52d768ae15b143b35
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=mytool
	CATEGORY:=My
	TITLE:=FengdiSmartNet
	DEPENDS:=+libpthread
endef

define Package/$(PKG_NAME)/description
	This is Fengdi SmartNet.
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
