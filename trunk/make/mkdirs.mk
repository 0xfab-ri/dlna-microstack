################################################################################
## @file:	mkdirs.mk
## @author	����ï <gcm.ustc.edu>
## @brief	�������Ŀ¼�Ĺ���
## @version	1.0
###############################################################################
.PHONY: mkdirs
mkdirs: $(MAKE_DIRECTORYS)

$(MAKE_DIRECTORYS):
	$(MKDIR) $@