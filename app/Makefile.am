bin_SCRIPTS = seaf-cli

EXTRA_DIST = seaf-cli

# 定义 thrift 文件和输出目录
THRIFT_FILE = ../idl/seafile.thrift
GENPY_OUTDIR = genpy

# 指定生成规则为不需要输出文件名
.PHONY: generate_py

# 声明 all target，表示 make 默认执行的目标
all: generate_py

# 定义 generate_py 目标，用于生成 Python 代码
generate_py:
	@echo "Generating Python code from Thrift..."
	mkdir -p $(GENPY_OUTDIR)
	thrift --gen py -out $(GENPY_OUTDIR) $(THRIFT_FILE)

# 清理目标，删除生成的 Python 代码
clean:
	rm -rf $(GENPY_OUTDIR)
