COMP=iverilog

TARGETS=fadd_test negafadd_test qimagfadd_test

$(TARGETS):
	$(COMP) -o $@.out $@.v
	./$@.out
	
