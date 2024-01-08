USER = antonstrand
KEYBOARDS = bm40hsrgb crkbd
ACTION = build

# keyboard name
NAME_crkbd = crkbd
NAME_bm40hsrgb = kprepublic/bm40hsrgb/rev1

all: $(KEYBOARDS)

.PHONY: $(KEYBOARDS)
$(KEYBOARDS):
	# init submodule
	git submodule update --init --recursive
	git submodule update --remote

	# cleanup old symlinks
	rm -rf qmk_firmware/keyboards/$(NAME_$@)/keymaps/$(USER)
	rm -rf qmk_firmware/users/$(USER)

	# add new symlinks
	mkdir -p qmk_firmware/keyboards/$(NAME_$@)/keymaps/$(USER)
	ln -s $(shell pwd)/$@/* qmk_firmware/keyboards/$(NAME_$@)/keymaps/$(USER)
	mkdir -p qmk_firmware/users/$(USER)
	ln -s $(shell pwd)/user/* qmk_firmware/users/$(USER) 

ifeq ($(ACTION), flash)
	@echo "Flash $@"
	cd qmk_firmware; qmk flash -km $(USER) -kb $(NAME_$@)
endif

ifeq ($(ACTION), build)
	@echo "Build $@"
	make BUILD_DIR=$(shell pwd)/build -j1 -C qmk_firmware $(NAME_$@):$(USER)
endif

ifeq ($(ACTION), lint)
	@echo "Lint $@"
	cd qmk_firmware; qmk lint -km $(USER) -kb $(NAME_$@)
endif

	# cleanup symlinks
	rm -rf qmk_firmware/keyboards/$(NAME_$@)/keymaps/$(USER)
	rm -rf qmk_firmware/users/$(USER)

.PHONY: flash
flash-%: 
	make ACTION=flash $*

.PHONY: lint
lint-%: 
	make ACTION=lint $*

.PHONY: clean
clean:
	rm -rf ./build/
	rm -rf ./qmk_firmware/

.PHONY: new
new:
	# https://docs.qmk.fm/#/newbs_building_firmware?id=create-a-new-keymap
	# init submodule
	git submodule update --init --recursive
	git submodule update --remote
	
	cd qmk_firmware; qmk new-keyboard
