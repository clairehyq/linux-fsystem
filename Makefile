all: 
	mkdir -p targets
	+$(MAKE) -C lab5
	+$(MAKE) -C lab5-tests
	+$(MAKE) -C Studio16
	+$(MAKE) -C Studio17
	+$(MAKE) -C Studio18
	+$(MAKE) -C Studio19
	+$(MAKE) -C Studio20
	+$(MAKE) -C Studio21

clean:
	+$(MAKE) -C lab5 clean
	+$(MAKE) -C lab5-tests clean
	+$(MAKE) -C Studio16 clean
	+$(MAKE) -C Studio17 clean
	+$(MAKE) -C Studio18 clean
	+$(MAKE) -C Studio19 clean
	+$(MAKE) -C Studio20 clean
	+$(MAKE) -C Studio21 clean
