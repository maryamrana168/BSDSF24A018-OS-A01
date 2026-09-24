SUBDIR = src

all:
	$(MAKE) -C $(SUBDIR)

run:
	$(MAKE) -C $(SUBDIR) run

clean:
	$(MAKE) -C $(SUBDIR) clean



