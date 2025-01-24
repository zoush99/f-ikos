# Makefile for Fortran project using Flang

# FC = flang
CFLAGS = -I./include

# 源文件列表
SRC = main.f90 math_operations.f90
OBJ = $(SRC:.f90=.o)
EXEC = my_program

# 确保先编译 math_operation.f90
$(EXEC): $(OBJ)
	$(FC) $(OBJ) -o $(EXEC)

# 编译 .f90 文件为 .o 文件
%.o: %.f90
	$(FC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJ) $(EXEC) ./include/*.mod

