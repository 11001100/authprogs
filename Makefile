VERSION=0.9.103
TEMP_DIR=/tmp/authprogs-$(VERSION)


all:
	$(MAKE) -C src


distfile:
	mkdir $(TEMP_DIR)
	cp -R * $(TEMP_DIR)
	tar -C /tmp -jcvf $(TEMP_DIR).tar.bz2 authprogs-$(VERSION)
	rm -rf $(TEMP_DIR)


clean:
	$(MAKE) -C src clean
