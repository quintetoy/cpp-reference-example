src=$(wildcard *.cpp )
dir=$(notdir $(src))
obj=$(patsubst %.cpp,%.o,$(dir)) 
MAINS=test.so

all:$(obj)
	@echo ${src}  
	@echo $(dir)  
	@echo $(obj) 
	@ g++ -fPIC -shared $(obj) -o $(MAINS)
	@echo "end"

.PHONY:clean

clean:
	rm -rf ./*.o



	








